//Using C11
//Davide Mecugni
//File padreFigliConConteggiOccorrenze.c

#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG
#include <sys/wait.h> //SYStem WAIT: wait

//Ritorna il numero di occorrenze del carattere Cx nel file F
long int contaOccorrenzeCarattere(const char *F, char Cx){
    //Apertura file
    int fd, n;
    if((fd = open(F, O_RDONLY)) < 0){
        printf("Errore: impossibile aprire il file %s\n", F);
        exit(-1);
    }
    char buffer;
    long int occorrenze = 0;
    //Lettura file carattere per carattere
    while((n = read(fd, &buffer, 1)) > 0){
        if(buffer == Cx){
            occorrenze++;
        }
    }
    close(fd);
    return occorrenze;
}

int main(int argc, char const *argv[])
{
    //Controllo parametri
    if(argc < 4){
        printf("Errore: inserire N+1 parametri, con N>=2\n");
        exit(1);
    }
    char Cx = argv[argc-1][0];
    //Controllo se e' un carattere
    if(argv[argc-1][1] != '\0'){
        printf("Errore: il parametro %s non e' un carattere\n", argv[argc-1]);
        exit(2);
    }
    
    pid_t pidPadre = getpid(), pid;
    int N = argc-2;

    printf("La pid del padre e' :%d\n", pidPadre);
    printf("Il padre deve generare %d figli\n", N);
    
    pid_t *pidDeiFigli = malloc(N*sizeof(pid_t));
    
    if(pidDeiFigli == NULL){
        printf("Errore nell'allocazione della memoria\n");
        exit(3);
    }
    
    // Per la creazione di N figli
    for(int Pi=0; Pi < N; Pi++){
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
    
            printf("Figlio, pid: %d, indice %d\n", getpid(), Pi);
            exit(contaOccorrenzeCarattere(argv[Pi+1], Cx));
    
            /*FINE CODICE DEL FIGLIO*/
        }
        printf("Generato figlio con PID = %d\n", pid);
        pidDeiFigli[Pi] = pid;
    }
    
    /* padre */
    pid_t pidFiglio;
    int status, ritorno;
    // Il padre aspetta i figli salvando lo status
    for(int Pi=0; Pi<N;Pi++){
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
            if(ritorno == 255){
                printf("Errore: impossibile aprire il file %s\n", argv[Pi]);
                continue;
            }
            printf("Il file %s contiene %d caratteri %c\n", argv[Pi], ritorno, Cx);
        } else {
            //Lo status riporta una terminazione anomala
            printf("Il figlio e' terminato in modo anomalo\n");
        }
    }
    //Libero la memoria dove ho salvato i PID dei figli
    free(pidDeiFigli);
    return 0;
}
