//Using C11
//Davide Mecugni
//File provaValoriWait.c

#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, free, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <string.h> //STRING: strlen, strcpy, strcat
#include <sys/stat.h> //SYStem STATus: stat, fstat, S_IFMT, S_IFDIR, S_IFREG
#include <sys/wait.h> //SYStem WAIT: wait

int main(int argc, char const *argv[])
{
    int pid, pidFiglio; /* pid per fork e pidFiglio per wait */
    int pidPadre = getpid();
    printf("La pid del padre e' :%d\n", pidPadre);
    if ((pid = fork()) < 0)
    { 	
        //Fork fallita
        printf("Errore in fork\n");
        exit(1);
    }
    
    if (pid == 0)
    { 	
        /* CODICE DEL FIGLIO*/
        
        int numero_letto;
        printf("Inserire numero\n");
        if( scanf("%d",&numero_letto) != 1){
            printf("Numero non letto correttamente!\n");
        }
        if(numero_letto < 0 || numero_letto > 255){
            printf("Il numero verra' troncato\n");
        }
        else{
            printf("Il numero non verra' troncato\n");
        }
        exit(numero_letto);
    
        /*FINE CODICE DEL FIGLIO*/
    }
    
    /* padre */
    printf("Generato figlio con PID = %d\n", pid);
    // Il padre aspetta il figlio salvando lo status
    int status;
    if ((pidFiglio=wait(&status)) < 0)
    {
        //La wait non ha avuto successo
        printf("Errore in wait\n");
        exit(2);
    }
    //Se il pid ritornato dalla wait e' corretto
    if (pid == pidFiglio){
        printf("Terminato figlio con PID = %d\n", pidFiglio);
        if (WIFEXITED(status)) {
            //Ricavo l'exitcode del figlio con la funzione WEXITSTATUS
            printf("Il figlio e' ritornato con codice: %d\n", WEXITSTATUS(status));
        } else {
            //Lo status riporta una terminazione anomala
            printf("Il figlio e' terminato in modo anomalo\n");
        }
    }
    else 
    {       
        //Il pid non corrisponde con il figlio aspettato
        printf("Il pid della wait non corrisponde al pid della fork!\n");
        exit(3);
    }
    return 0;
}
