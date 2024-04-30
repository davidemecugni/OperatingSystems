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
    //Controllo esatto parametri
    if(argc != 2){
        printf("Errore: inserire esattamente 1 parametro\n");
        return 1;
    }

    const char * argomento = argv[1];

    if(argomento[0] != '-'){
        printf("Errore: paramentro non corretto");
        exit(2);
    }

    int n = atoi(&(argomento[1]));
    printf("Numero: %d\n\n", n);
    if(n <= 0){
        printf("Errore: mi aspetto un numero positivo intero");
        exit(3);
    }
    myhead(n);
    return 0;
}
