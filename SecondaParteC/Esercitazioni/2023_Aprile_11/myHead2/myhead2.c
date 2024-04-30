//Using C11
//Davide Mecugni
//File myhead1.c

#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG

// Stdin char per char finche' non si trovano n /n
void myhead(int num){
    char buffer;
    int contaACapo = 0, n;
    //Lettura file carattere per carattere
    while(((n = read(STDIN_FILENO, &buffer, 1)) > 0) && contaACapo < num){
        if(buffer == '\n'){
            contaACapo++;
        }
        write(STDOUT_FILENO, &buffer, 1);
    }
}

int main(int argc, char const *argv[])
{
    int n = 10;
    if(argc != 1 && argc != 2){
        printf("Numero di parametri non corretto, me ne aspetto 0 o 1\n");
        exit(1);
    }
    if(argc == 2 ){
        n = atoi(&(argv[1][1]));
        printf("Numero: %d\n\n", n);
        if(argv[1][0] != '-' ){
            printf("Errore: paramentro non corretto\n");
            exit(2);
        }
        if(n <= 0){
            printf("Errore: mi aspetto un numero positivo intero\n");
            exit(3);
        }
    }

    myhead(n);
    return 0;
}
