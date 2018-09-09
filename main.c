#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>

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



    int lastX;
    int lastY;

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

    int numBoards;
    int A;
    int B;
    int C;
    int D;
    
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





    // FIN SIMULACIÓN


    printBoard(&mainGame.boards[0],D);

    freeAllMemory(&mainGame, D, numBoards);

    fclose(pInput);
    fclose(pOutput);
    return 0;
}