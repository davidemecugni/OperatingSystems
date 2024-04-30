//Using C11
//Davide Mecugni
//File pappagallo.c
#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close
#include <string.h> //STRING: strlen, strcpy, strcat

int main(int argc, char const *argv[])
{
    char buffer [BUFSIZ];
    int nread;
    while ( (nread = read (0, buffer, BUFSIZ)) > 0 ) {
        /* lettura dallo standard input fino a che ci sono caratteri */
        write (1 , buffer, nread);
        /* scrittura sullo standard output dei caratteri letti */
    }
    return 0;
}
