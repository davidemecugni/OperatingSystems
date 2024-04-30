//Using C11
//Davide Mecugni
//File selezionaLinea.c

#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG


// f char per char finche' non si trova l'n-esima riga
int nEsimaRiga(const char* f, int num, char *buffer){
    int contaACapo = 0, fd;
    //Se il file e' null leggo da STDIN
    if(f == NULL){
        fd = STDIN_FILENO;
    }
    else{
        if((fd = open(f, O_RDONLY)) < 0){
            printf("Errore: impossibile aprire il file %s\n", f);
            exit(5);
        }
    }
    int j=0;

    while ((read(fd, &(buffer[j]), 1) != 0) && contaACapo < num){
        if(buffer[j] == '\n'){
            contaACapo++;
            buffer[j] = '\0';
            j = 0;
            continue;
        }
        ++j;
    }
    
    return contaACapo == num;
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
    char buffer[256];
    int trovata = nEsimaRiga(F,n,buffer);
    if(trovata){
        printf("L'%d-esima stringa e' stata trovata: %s\n", n, buffer);
    }else{
        printf("La stringa non e' stata trovata\n");
    }
    return 0;
}
