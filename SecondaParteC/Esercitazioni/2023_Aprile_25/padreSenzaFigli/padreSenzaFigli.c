//Using C11
//Davide Mecugni
//File padreSenzaFigli.c

#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG
#include <sys/wait.h> //SYStem WAIT: wait

int main(int argc, char const *argv[])
{
    int pidFiglio; /* pid per fork e pidFiglio per wait */
    int pidPadre = getpid();
    printf("La pid del padre e' :%d\n", pidPadre);
    
    
    /* padre */
    // Il padre aspetta il figlio salvando lo status
    int status;
    if ((pidFiglio=wait(&status)) < 0)
    {
        //La wait non ha avuto successo
        printf("Errore in wait\n");
        exit(1);
    }
    return 0;
}
