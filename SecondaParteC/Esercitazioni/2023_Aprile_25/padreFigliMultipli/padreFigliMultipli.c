//Using C11
//Davide Mecugni
//File padreFigliMultipli.c

#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG
#include <sys/wait.h> //SYStem WAIT: wait


int main(int argc, char const *argv[])
{
    //Controllo esatto parametri
    if(argc != 2){
        printf("Errore: inserire esattamente 1 parametri\n");
        exit(1);
    }   

    //Controllo se e' un numero
    int N = atoi(argv[1]);
    if(N <= 0 || N >= 255){
        printf("Errore: il parametro %s non e' un numero positivo strettamente minore di 255\n", argv[1]);
        exit(2);
    }
    
    int pid;
    int pidPadre = getpid();
    printf("La pid del padre e' :%d\n", pidPadre);
    printf("Il padre deve generare %d figli\n", N);
    
    // Per la creazione di N figli
    for(int i=0; i < N; i++){
        if ((pid = fork()) < 0)
        {
            //Fork fallita
            printf("Errore in fork\n");
            exit(3);
        }
        
        if (pid == 0)
        { 
            /* CODICE DEL FIGLIO*/
    
            printf("Figlio, pid: %d, indice %d\n", getpid(), i);
            exit(i);
    
            /*FINE CODICE DEL FIGLIO*/
        }
        printf("Generato figlio con PID = %d\n", pid);
    }
    
    /* padre */
    int pidFiglio, status, ritorno;
    // Il padre aspetta i figli salvando lo status
    for(int i=0; i<N;i++){
        if ((pidFiglio=wait(&status)) < 0)
        {
            //La wait non ha avuto successo
            printf("Errore in wait\n");
            exit(4);
        }
    
        printf("Terminato figlio con PID = %d\n", pidFiglio);
        if (WIFEXITED(status)) {
            //Ricavo l'exitcode del figlio con la funzione WEXITSTATUS
            ritorno = WEXITSTATUS(status);
            printf("Il figlio e' ritornato con codice: %d\n", ritorno);
        } else {
            //Lo status riporta una terminazione anomala
            printf("Il figlio e' terminato in modo anomalo\n");
        }
    }
    return 0;
}
