//Using C11
//Davide Mecugni
//File mycat1.c
#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG

//Se file non esiste, usa lo standard input
void myCat(const char* file)
{       
    int nread;                      // valore ritorno read 
    char buffer[BUFSIZ];            // usato per i caratteri 
    int fd = 0;                     // usato per la open; N.B. se non viene passato alcun parametro allora rimarra' uguale a 0, quindi identifichera' lo STANDARD INPUT 

    if ((fd = open(file, O_RDONLY)) < 0)// ERRORE se non si riesce ad aprire in LETTURA il file 
    {       printf("Errore in apertura file %s dato che fd = %d\n", file, fd);
            exit(1); 
    }

    while ((nread = read(fd, buffer, BUFSIZ)) > 0 ){
        // scrittura sullo standard output dei caratteri letti 
        write(1, buffer, nread);
    }
    if(fd != 0){
        close(fd);
    }
}




int main(int argc, char const *argv[])
{
    if(argc == 1){
        myCat(NULL);
    }
    for(int i= 1; i < argc; i++){
        myCat(argv[i]);
    }
    return 0;
}