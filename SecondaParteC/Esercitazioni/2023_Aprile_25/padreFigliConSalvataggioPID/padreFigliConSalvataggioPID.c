//Using C11
//Davide Mecugni
//File padreFigliConSalvataggioPID.c

#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG
#include <sys/wait.h> //SYStem WAIT: wait

#include <time.h> // Per generare il seed di random

int generatoreRandom(int n){
    return rand() % n;
}

int main(int argc, char const *argv[])
{
    
    int pid;
    int pidPadre = getpid();
    //Controllo esatto parametri
    if(argc != 2){
        printf("Errore: inserire esattamente 1 parametri\n");
        exit(1);
    }
    //Controllo se e' un numero
    int N = atoi(argv[1]);
    if(N <= 0 || N >= 255){
        printf("Errore: il parametro %s non e' un numero compreso tra 1 e 254\n",argv[1]);
        exit(2);
    }
    //Seed random
    srand(time(NULL));

    printf("La pid del padre e' :%d\n", pidPadre);
    printf("Il padre deve generare %d figli\n", N);
    
    pid_t *pidDeiFigli = malloc(N*sizeof(pid_t));
    
    if(pidDeiFigli == NULL){
        printf("Errore nell'allocazione della memoria\n");
        exit(3);
    }
    
    // Per la creazione di N figli
    for(int i=0; i < N; i++){
        if ((pid = fork()) < 0)
        {
            //Fork fallita
            printf("Errore in fork\n");
            free(pidDeiFigli);
            exit(4);
        }
        
        if (pid == 0)
        { 
            /* CODICE DEL FIGLIO*/
    
            printf("Figlio, pid: %d, indice %d\n", getpid(), i);
            exit(generatoreRandom(100+i));
    
            /*FINE CODICE DEL FIGLIO*/
        }
        printf("Generato figlio con PID = %d\n", pid);
        pidDeiFigli[i] = pid;
    }
    
    /* padre */
    pid_t pidFiglio;
    int status, ritorno;
    // Il padre aspetta i figli salvando lo status
    for(int i=0; i<N;i++){
        if ((pidFiglio=wait(&status)) < 0)
        {
            //La wait non ha avuto successo
            printf("Errore in wait\n");
            free(pidDeiFigli);
            exit(5);
        }
    
        int posizione = 0;
        for(int j=0; j<N; j++){
            if(pidDeiFigli[j] == pidFiglio){
                posizione = j;
                break;
            }
        }
        printf("Terminato figlio con PID = %d, creato per %d-esimo\n", pidFiglio, posizione);
        if (WIFEXITED(status)) {
            //Ricavo l'exitcode del figlio con la funzione WEXITSTATUS
            ritorno = WEXITSTATUS(status);
            printf("Il figlio di pid = %d (di indice %d) e' ritornato con codice: %d\n", pidDeiFigli[posizione], posizione, ritorno);
        } else {
            //Lo status riporta una terminazione anomala
            printf("Il figlio di pid = %d (di indice %d) e' terminato in modo anomalo\n", pidDeiFigli[posizione], posizione);
        }
    }
    //Libero la memoria dove ho salvato i PID dei figli
    free(pidDeiFigli);
    return 0;
}
