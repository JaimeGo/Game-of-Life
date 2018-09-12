#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>


struct Board{
    int ** cells;
    char * name;
    int aliveCells;
};


struct Game{
    struct Board * boards;
};


void printBoard(struct Board * board, int D){
    wchar_t white=0x25A0;
    wchar_t black=0x25A1;
    char * locale=setlocale(LC_CTYPE,"UTF-8");
    printf("The current locale is %s\n",locale);


    for (int i=0;i<D;i++){
        for (int j=0;j<D;j++){
            if (board->cells[i][j]==0)
            {
                putwchar(white);
            }
            else {
                putwchar(black);
            }
        }
        putchar('\n');
    }
}

void freeAllMemory(struct Game * game, int D, int numBoards){


    for (int i=0; i<numBoards;i++){


        for (int k=0;k<D;k++){
            free(game->boards[i].cells[k]);

        }

        free(game->boards[i].cells);
        free(game->boards[i].name);
    }

    free(game->boards);



}

void readFirstLine(char * lineStart, int * numBoards, int * A, int* B, int* C, int* D){

    int i=0;

    const char s[2] = " ";
    char *token;

    /* get the first token */
    token = strtok(lineStart, s);

    /* walk through other tokens */
    while( token != NULL ) {
        printf( "FIRST LINE: %s\n", token );



        switch (i){
            case 0:
                *numBoards=atoi(token);
                break;
            case 1:
                *A=atoi(token);
                break;
            case 2:
                *B=atoi(token);
                break;
            case 3:
                *C=atoi(token);
                break;
            case 4:
                *D=atoi(token);
                break;
            default:
                printf("Wrong format for input file");

        }

        token = strtok(NULL, s);

        i++;
    }









}

void readLine(char * lineStart, int i, struct Game * game){



    int lastX=0;
    int lastY=0;

    int j=0;

    const char s[2] = " ";
    char *token;

    /* get the first token */
    token = strtok(lineStart, s);



    /* walk through other tokens */
    while( token != NULL ) {

        printf( "TOKEN j=%d FROM LINE NUMBER %d: %s\n",j,i+1, token );





        if (j==0){
            game->boards[i].name=(char*)malloc(sizeof(token));
            strcpy(game->boards[i].name,token);
            printf("NAME: %s\n",game->boards[i].name);
        }

        else if (j==1){

            game->boards[i].aliveCells=atoi(token);
        }

        else {




            if (j%2==0) {
                lastX=atoi(token);
            }

            else {
                lastY=atoi(token);
                printf("Lastx, lasty: %d,%d\n", lastX,lastY);
                game->boards[i].cells[lastX][lastY] = 1;
            }



        }
        token = strtok(NULL, s);

        j++;
    }



}

void runBoard(struct Board* oldBoard, int D, int A, int B, int C){
    struct Board newBoard;

    newBoard.name=(char*)malloc(sizeof(oldBoard->name));
    strcpy(newBoard.name,oldBoard->name);

    newBoard.aliveCells=oldBoard->aliveCells;


    newBoard.cells=(int**)calloc((size_t)D, sizeof(int*));

    for (int k=0;k<D;k++){
        newBoard.cells[k]=(int*)calloc((size_t)D, sizeof(int));
    }


    for (int i=0;i<D;i++){

        for (int j=0;j<D;j++){
            int left=i-1;
            int right=i+1;
            int up=j-1;
            int down=j+1;

            int aliveNear=0;

            if (left>=0 && left<=D){
                aliveNear+=oldBoard->cells[left][j];

                if (up>=0 && up<=D){
                    aliveNear+=oldBoard->cells[left][up];
                }

                if (down>=0 && down<=D){
                    aliveNear+=oldBoard->cells[left][down];
                }
            }

            if (right>=0 && right<=D){
                aliveNear+=oldBoard->cells[right][j];

                if (up>=0 && up<=D){
                    aliveNear+=oldBoard->cells[right][up];
                }

                if (down>=0 && down<=D){
                    aliveNear+=oldBoard->cells[right][down];
                }
            }

            if (up>=0 && up<=D){
                aliveNear+=oldBoard->cells[i][up];
            }

            if (down>=0 && down<=D){
                aliveNear+=oldBoard->cells[i][down];
            }



            if (oldBoard->cells[i][j]){
                if (aliveNear>=B && aliveNear<= C){
                    newBoard.cells[i][j]=1;
                }
            }

            else {
                if (aliveNear==A){
                    newBoard.cells[i][j]=1;
                }
            }



        }
    }



}


int main(int argc, char * argv[]) {
    printf("Hello, World! %s, %s\n", argv[1], argv[2]);

    struct Game mainGame;


    FILE * pInput = fopen(argv[1],"r");
    FILE * pOutput = fopen("output.txt","r");

    if(pInput == NULL) {
        perror("Error opening file");
        return(-1);
    }

    char line[1024];

    int isFirst=1;

    int numBoards=0;
    int A=0;
    int B=0;
    int C=0;
    int D=0;
    
    int lineNumber=0;

    while(!feof(pInput)){
        if (NULL==fgets(line, sizeof(line)/ sizeof(line[0]), pInput)){
            break;
        }

        printf("LINE: %s\n", line);

        if (isFirst==1){
            readFirstLine(line,&numBoards,&A,&B,&C,&D);
            printf("FIRST LINE IS OK, NUMBOARD IS %d\n", numBoards);
            isFirst=0;



            mainGame.boards=malloc(numBoards*sizeof(struct Board));

        }

        else {
            int boardNumber=lineNumber-1;
            
            mainGame.boards[boardNumber].cells=(int**)calloc((size_t)D, sizeof(int*));

            for (int k=0;k<D;k++){
                mainGame.boards[boardNumber].cells[k]=(int*)calloc((size_t)D, sizeof(int));
            }

            printf("\n\nSTARTING LINE READ FOR LINE %d\n\n", lineNumber);
            readLine(line, boardNumber, &mainGame);
            
        }
        
        lineNumber++;

    }

    printf("FIRST LINE IS: %d, %d, %d, %d, %d\n", numBoards, A, B, C, D);
    printf("ON BOARD 0, POS (3,5) is %d\n", mainGame.boards[0].cells[3][5]);


    // INICIO SIMULACIÓN
    int processesFinished=0;

    for (int q=0; q<numBoards;q++){

        pid_t pid;
        if ((pid = fork()) == 0){
            runBoard(&mainGame.boards[q], D, A, B, C)
        }
        else do {
                if ((pid = waitpid(pid, &status, 1)) == 0) {

                    printf("Still running!\n");

                    //must check if NOTIME

                    sleep(1);
                } else {
                    printf("EXIT!\n");
                    processesFinished++;
                    if (processesFinished==numBoards){


                        //all done by cells -> END


                    }
                }
            } while (pid == 0);



    }



    // FIN SIMULACIÓN


    printBoard(&mainGame.boards[0],D);

    freeAllMemory(&mainGame, D, numBoards);

    fclose(pInput);
    fclose(pOutput);
    return 0;
}