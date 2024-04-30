//Using C11
//Davide Mecugni
//File myhead1.c

#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG


// f char per char finche' non si trovano n /n
void myhead(const char* f, int num){
    char buffer;
    int contaACapo = 0, n, fd;
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
    //Leggo e mi fermo quando gli a capo sono == num
    while(((n = read(fd, &buffer, 1)) > 0) && contaACapo < num){
        if(buffer == '\n'){
            contaACapo++;
        }
        write(STDOUT_FILENO, &buffer, 1);
    }
}

int main(int argc, char const *argv[])
{
    int n = 10;
    const char *f = NULL;
    if(argc != 1 && argc != 2 && argc != 3){
        printf("Numero di parametri non corretto, me ne aspetto 0 o 1 o 2\n");
        exit(1);
    }
    if(argc == 2 || argc == 3){
        n = atoi(&(argv[1][1]));
        printf("Numero: %d\n\n", n);
        if(argv[1][0] != '-' ){
            printf("Errore: paramentro non corretto\n");
            exit(2);
        }
        if(n <= 0){
            printf("Errore: mi aspetto un numero positivo intero\n");
            exit(3);
        }
        if(argc == 3){
            f = argv[2];
            //Controllo se e' un file
            if( open(f, O_RDONLY) < 0){
                printf("Errore: il parametro %s non e' un file\n", f);
                exit(4);
            }
        }
    }

    myhead(f,n);
    
    return 0;
}
