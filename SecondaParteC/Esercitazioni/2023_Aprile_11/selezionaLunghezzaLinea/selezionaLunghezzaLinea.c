//Using C11
//Davide Mecugni
//File selezionaLunghezzaLinea.c

#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG


// f char per char finche' non si trova l'n-esima riga
//ATTENZIONE: il buffer deve essere abbastanza grosso
void righeLungheN(const char* f, int num){
    char buffer[256];
    int fd;
    if((fd = open(f, O_RDONLY)) < 0){
        printf("Errore: impossibile aprire il file %s\n", f);
        exit(4);
    }

    int j=0;
    int righeTrovate = 1;
    while ((read(fd, &(buffer[j]), 1) != 0) && j<255){
        if(buffer[j] == '\n'){
            buffer[j] = '\n';
            buffer[j+1] = '\0';
            if(j + 1 == num){
                printf("Trovata %d-esima riga: %s", righeTrovate, buffer);
                righeTrovate++;
            }
            j = 0;
            continue;
        }
        ++j;
    }
}

int main(int argc, char const *argv[])
{
    //Controllo esatto parametri
    if(argc != 3){
        printf("Errore: inserire esattamente 2 parametri\n");
        exit(1);
    }

    const char *F = argv[1];

    //Controllo se e' un file
    if( open(F, O_RDONLY) < 0){
        printf("Errore: il parametro %s non e' un file\n", F);
        exit(2);
    }

    //Controllo se e' un numero
    int n = atoi(argv[2]);
    if(n <= 0){
        printf("Errore: il parametro %s non e' un numero\n", argv[2]);
        exit(3);
    }

    righeLungheN(F, n);

    return 0;
}
