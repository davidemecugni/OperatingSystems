//Using C11
//Davide Mecugni
//File contaOccorrenze.c
#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG


//Ritorna il numero di occorrenze del carattere Cx nel file F
long int contaOccorrenzeCarattere(const char *F, char Cx){
    //Apertura file
    int fd, n;
    if((fd = open(F, O_RDONLY)) < 0){
        printf("Errore: impossibile aprire il file %s\n", F);
        exit(2);
    }
    char buffer;
    long int occorrenze = 0;
    //Lettura file carattere per carattere
    while((n = read(fd, &buffer, 1)) > 0){
        if(buffer == Cx){
            occorrenze++;
        }
    }
    printf("Il carattere %c compare %ld volte nel file %s\n", Cx, occorrenze, F);
    close(fd);
    return occorrenze;
}

int main(int argc, char const *argv[])
{
    //Controllo esatto parametri
    if(argc != 3){
        printf("Errore: inserire esattamente 2 parametri\n");
        return 1;
    }
    const char *F = argv[1];
    //Controllo se e' un file
    if( open(F, O_RDONLY) < 0){
        printf("Errore: il parametro %s non e' un file\n", F);
        return 2;
    }
    const char *Cx = argv[2];
    //Controllo se e' un carattere
    if(Cx[1] != '\0'){
        printf("Errore: il parametro %s non e' un carattere\n", Cx);
        return 3;
    }
    printf("Nome del eseguibile: %s\n", argv[0]);
    printf("File: %s\n", F);
    printf("Carattere: %s\n", Cx);
    contaOccorrenzeCarattere(F, Cx[0]);
    return 0;
}


