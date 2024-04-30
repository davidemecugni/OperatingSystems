//Using C11
//Davide Mecugni
//File parametri2.c

#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG



int main(int argc, char const *argv[])
{
    if(argc != 4){
        printf("Errore: inserire esattamente 3 parametri\n");
        return 1;
    }
    //Controllo primo parametro se e' un file
    if( open(argv[1], O_RDONLY) < 0){
        printf("Errore: il primo parametro non e' un file\n");
        return 2;
    }
    //Controllo secondo parametro se e' un numero
    int n = atoi(argv[2]);
    if(n<=0){
        printf("Errore: il secondo parametro non e' un numero\n");
        return 3;
    }
    //Controllo terzo parametro se e' un carattere
    if(argv[3][1] != '\0'){
        printf("Errore: il terzo parametro non e' un carattere\n");
        return 4;
    }
    printf("Nome del eseuguibile: %s\n", argv[0]);
    printf("Numero di parametri: %d\n", argc-1);
    printf("Nome del file: %s\n", argv[1]);
    printf("Numero: %d\n", n);
    printf("Carattere: %c\n", argv[3][0]);

    
    return 0;
}



