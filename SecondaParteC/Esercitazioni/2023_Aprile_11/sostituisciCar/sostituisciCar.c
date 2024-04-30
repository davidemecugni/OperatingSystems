//Using C11
//Davide Mecugni
//File sostituisciCar.c

#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG

// Apertura file RW e sostituzione del carattere Cx con lo spazio
void fileSostituisciCarattere(const char *F, char Cx){
    //Apertura file
    int fd, n;
    if((fd = open(F, O_RDWR)) < 0){
        printf("Errore: impossibile aprire il file %s\n", F);
        exit(4);
    }
    char buffer;
    const char spazio = ' ';
    //Lettura file carattere per carattere
    while((n = read(fd, &buffer, 1)) > 0){
        if(buffer == Cx){
            lseek(fd, -1, SEEK_CUR);
            write(fd, &spazio, 1);
        }
    }
    close(fd);
}


int main(int argc, char const *argv[])
{
    //Controllo esatto parametri
    if(argc != 3){
        printf("Errore: inserire esattamente 2 parametri\n");
        return 1;
    }

    const char* F = argv[1];
    //Controllo se e' un file
    if( open(F, O_RDONLY) < 0){
        printf("Errore: il parametro %s non e' un file\n", argv[1]);
        return 2;
    }
    
    char Cx = argv[2][0];
    //Controllo se e' un carattere
    //ARRAY DI CARATTERI
    if(argv[2][1] != '\0'){
        printf("Errore: il parametro %s non e' un carattere\n", argv[2]);
        return 3;
    }
    fileCharPerChar(F, Cx);

    return 0;
}