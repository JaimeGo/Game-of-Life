#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void readFirstLine(char * lineStart, int * numTableros, int * A, int* B, int* C, int* D){

    int i=0;

    const char s[2] = " ";
    char *token;

    /* get the first token */
    token = strtok(lineStart, s);

    /* walk through other tokens */
    while( token != NULL ) {
        printf( " %s\n", token );



        switch (i){
            case 0:
                *numTableros=atoi(token);
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

int * readLine(int count, char * lineStart){



    return 1;

}




int main(int argc, char * argv[]) {
    printf("Hello, World! %s, %s\n", argv[1], argv[2]);


    FILE * pInput = fopen(argv[1],"r");
    FILE * pOutput = fopen("output.txt","r");

    if(pInput == NULL) {
        perror("Error opening file");
        return(-1);
    }

    char line[1024];

    int isFirst=1;

    int numTableros;
    int A;
    int B;
    int C;
    int D;

    while(!feof(pInput)){
        if (NULL==fgets(line, sizeof(line)/ sizeof(line[0]), pInput)){
            break;
        }

        printf("%s\n", line);

        if (isFirst==1){
            readFirstLine(line,&numTableros,&A,&B,&C,&D);
            isFirst=0;
        }
    }

    printf("FIRST LINE IS: %d, %d, %d, %d, %d", numTableros, A, B, C, D);

    fclose(pInput);
    fclose(pOutput);
    return 0;
}