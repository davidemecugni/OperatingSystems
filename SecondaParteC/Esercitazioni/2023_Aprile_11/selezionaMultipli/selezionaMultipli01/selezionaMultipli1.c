//Using C11
//Davide Mecugni
//File selezionaMultipli.c
#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG



//Stampa l'n-esimo carattere nel file fornito
void stampaNEsimoCarattereInFileConRead(const char *F, int n){
    //Apertura file
    int fd, num;
    if((fd = open(F, O_RDONLY)) < 0){
        printf("Errore: impossibile aprire il file %s\n", F);
        exit(4);
    }
    char *buffer = malloc(sizeof(char) * n);
    if(buffer == NULL){
        printf("Impossibile allocare dinamicamente la memoria\n");
        exit(5);
    }
    //Lettura file carattere per carattere
    while((num = read(fd, buffer, n)) > 0){
        printf("Il carattere multiplo %d-esimo all'interno del file %s e' %c\n", n,F,buffer[num-1]);
    }
    close(fd);
    free(buffer);
}

int main(int argc, char const *argv[])
{
    //Controllo esatto parametri
    if(argc != 3){
        printf("Errore: inserire esattamente  2 parametri\n");
        return 1;
    }
    const char* F = argv[1];
    //Controllo se e' un file
    if( open(F, O_RDONLY) < 0){
        printf("Errore: il parametro %s non e' un file\n", F);
        return 2;
    }
    int n;
    //Controllo se e' un numero
    n = atoi(argv[2]);
    if(n <= 0){
        printf("Errore: il parametro %s non e' un numero\n", argv[2]);
        return 3;
    }
    printf("Stampo i caratteri:\n");
    stampaNEsimoCarattereInFileConRead(F,n);

      
    return 0;
}
