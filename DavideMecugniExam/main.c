//Using C11
//Davide Mecugni
//File main.c

#include <stdio.h> //Standard I/O: printf, BUFSIZ
#include <fcntl.h> //File CoNTrol: open, O_RDONLY, O_WRONLY, O_RDWR, O_CREAT(crea se non esiste), O_APPEND(solo R o RW)
//O_TRUNC(distrugge contenuto se esiste, O_EXCL(fallisce se il file esiste gia'), O_NDELAY (non bloccante per FIFO e pipe in W)
#include <stdlib.h> //STanDard LIBrary: exit, malloc, calloc, atoi
#include <unistd.h> //UNIx Standard: read, write, close, SEEK_SET, SEEK_CUR, SEEK_END
#include <sys/wait.h> //SYStem WAIT: wait
#include <string.h> //STRING: strlen, strcpy, strcat

#define PERMESSI 0644

typedef int pipe_t[2]; /* definizione del TIPO pipe_t come array di 2 interi */

int main(int argc, char* argv[]) {

    /* -------- Variabili locali ---------- */
    int status;            /* variabile di stato per la wait */
    pipe_t *piped;         /* array dinamico di pipe descriptors per comunicazioni tra coppie */
    int j;                 /* indice per i cicli */
    int ritorno;           /* variabile che viene ritornata da ogni figlio al padre e che contiene il ritorno del nipote */
    int pidFiglio;         /* pid figlio per wait */
    char* nomeFile;        /*Nome del file .max su cui scrive il secondo della coppia*/
    int fd;                /*FD del file aperto in lettura*/
    int dimRigaDisp;       /*Usato dal secondo figlio */
    long unsigned dim;     /* Usato per verificare la lungh delle read/write*/
    int nrLinea;           /*Usato per determinare la riga corrente*/
    char* nomeMax;         /*Puntatore al nuovo nome del file*/
    char lineaPrima[250];  /*Contiene la linea ricevuta dal primo figlio*/
    /*Dal testo*/
    int N;                 /*Per il numero dei file*/
    int n;                 /*Contiene l'indice dei processi figli*/
    char linea[250];       /*Contiene la linea letta corrente, 250 in linea con il testo*/
    int nro;               /*Per il valore massimo della lunghezza delle linee p/d dei file*/
    int fcreato;           /*FD del file creato*/

    /* ------------------------------------ */
    /*Print di debug*/
    printf("\n----  PARTE C ----\n");

    /* controllo numero parametri */
    if (argc < 2) {
        printf("Errore: numero parametri '%d' errato\n", argc - 1);
        exit(1);
    }
    /* Numero di file*/
    N = argc - 1;

    /* Si hanno bisogno di sole N pipe perche' dispari comunica a pari*/
    piped = malloc(sizeof(pipe_t) * N);
    if(piped == NULL){
        printf("Errore nella malloc\n");
        exit(2);
    }
    
    /* Creazione delle N pipe figlio-dispari -> figlio-pari */
    for (j=0; j < N; j++)
    { 
        if(pipe(piped[j]) < 0)
        {  
            printf("Errore nella creazione della pipe\n");
            exit(3);     
        }
    }
    
    // Per la creazione di N*2 figli
    for(n=0; n < N*2; n++){
        if ((pidFiglio = fork()) < 0)
        {
            //Fork fallita
            printf("Errore in fork\n");
            exit(4);
        }
        
        if (pidFiglio == 0)
        {     
            /* Chiusura delle pipe non usate nella comunicazione tra figlio primo e secondo della coppia */
            for (j=0; j < N; j++)
            { 
                if (n<N){
                    /*Il primo chiude tutto il lettura e tiene aperto in scrittura verso la coppia*/
                    close(piped[j][0]);
                    if(j != n){
                        close(piped[j][1]);
                    }
                }else{
                    /*Il secondo chiude tutto in scrittura e tiene aperto in lettura dalla coppia*/
                    close(piped[j][1]);
                    if(j != n-N){
                        close(piped[j][0]);
                    }
                }
            }
    
    
            /*Se siamo il secondo figlio creo il file*/
            if(n >= N){
                /*Creo spazio per ospitare nome del file + .max */
                nomeMax = malloc(strlen(argv[n-N+1]) + 4 + 1);
                if(nomeMax == NULL){
                    printf("Errore nella allocazione della memoria per il nome .max del figlio %d\n", n);
                    exit(-1);
                }
                strcat(nomeMax, argv[n-N+1]);
                strcat(nomeMax, ".max");
                /* Salvo il nome del file da leggere*/
                nomeFile = argv[n-N+1];
                /* Si poteva svolgere anche con creat*/
                if ( (fcreato = open (nomeMax, O_CREAT | O_WRONLY, PERMESSI)) < 0 )
                { 
                    printf("Errore in creazione file %s dal figlio %d\n", nomeMax, n);
                    exit(-1);
                }
            }else{
                /* Salvo il nome del file da leggere*/
                nomeFile = argv[n+1];
            }

            /* Apro il file assegnato alla coppia in lettura */
            if((fd = open(nomeFile, O_RDONLY)) < 0){
                printf("Errore: impossibile aprire il file %s\n", nomeFile);
                exit(-1);
            }

            j=0;
            nrLinea=1; /* Come da testo parte da 1*/
            nro = -1;   /* Inizializzata a negativo per salvare sempre la prima come max temporaneo*/

            /* Leggo il file char per char*/
            while((n = read(fd, &(linea[j]), 1)) > 0){
                /* Se la riga e' terminata*/
                if(linea[j] == '\n'){
                    /* Se la linea corrente e' dispari e il figlio e' il primo della coppia*/
                    if((nrLinea % 2 == 1) && (n<N)){
                        printf("DEBUG: %d linea, n %d e sono primo\n", nrLinea, n);
                        /* Essendo all'indice dell''\n' bisogna aggiungere 1 per la lunghezza*/
                        j = j + 1;
                        /*Essendo di competenza controllo se la lun corrente e' max rispetto alle prec*/
                        if(j > nro){
                            nro = j;
                        }
                        dim = write(piped[n][1], &j, sizeof(j));
                        if(dim != sizeof(j)){
                            printf("Errore nella write da figlio %d verso %d della lunghezza\n", n, n+N);
                            exit(-1);
                        }
                        /* Eseguo write di dimensione minima necessaria*/
                        dim = write(piped[n][1], &linea, j * sizeof(char));
                        if(dim != (j * sizeof(char))){
                            printf("Errore nella write da figlio %d verso %d della linea\n", n, n+N);
                            exit(-1);
                        }
                    }
                    /* Se la linea corrente e' pari e il figlio e' il secondo della coppia*/
                    if((nrLinea % 2 == 0) && (n >= N)){
                        printf("DEBUG: %d linea, n %d e sono secondo\n", nrLinea, n);

                        /* Leggo dal primo figlio*/
                        dim = read(piped[n-N][0], &dimRigaDisp, sizeof(dimRigaDisp));
                        if(dim != sizeof(dimRigaDisp)){
                            printf("Errore nella read da figlio %d verso %d della lunghezza della riga %d\n", n-N, n, nrLinea);
                            exit(-1);
                        }
                        dim = read(piped[n-N][0], &lineaPrima, dimRigaDisp * sizeof(char));
                        if(dim != dimRigaDisp * sizeof(char)){
                            printf("Errore nella read da figlio %d verso %d della linea %d\n", n-N, n, nrLinea);
                            exit(-1);
                        }
                        
                        j = j + 1; /* Includo terminatore nel calcolo lunghezza*/

                        /*Essendo di competenza controllo se la lun corrente e' max rispetto alle prec*/
                        if(j > nro){
                            nro = j;
                        }
                        /* Se la propria riga pari ha dim maggiore della dispari*/
                        if(j > dimRigaDisp){
                            dim = write(fcreato, &linea, j * sizeof(char));
                            if(dim != j * sizeof(char)){
                                printf("Errore di scrittura da parte del figlio %d sul file %s\n", n, nomeFile);
                                exit(-1);
                            }
                        }else{
                            dim = write(fcreato, &lineaPrima, dimRigaDisp * sizeof(char));
                            if(dim != dimRigaDisp * sizeof(char)){
                                printf("Errore di scrittura da parte del figlio %d sul file %s\n", n, nomeFile);
                                exit(-1);
                            }
                        }
                    }

                    /* Incremento la linea letta*/
                    nrLinea++;
                    /* Resetto il counter all'inizio della riga*/
                    j=0;
                }else{
                    j++;
                }
            }
            /*Ritorno con la lunghezza massima trovata fra le proprie righe*/
            exit(nro);
    
            /*FINE CODICE DEL FIGLIO*/
        }
    }
    
    
    /*Padre chiude tutte le pipe che non usa ossia tutte visto che la comunicazione e' sono a coppie*/
    for (j=0; j < N; j++)
    {
        close(piped[j][0]);
        close(piped[j][1]);
    }
    
    
    // Il padre aspetta i figli salvando lo status
    for(n=0; n< N * 2; n++){
        if ((pidFiglio=wait(&status)) < 0)
        {
            //La wait non ha avuto successo
            printf("Errore in wait\n");
            exit(5);
        }
        
        if (WIFEXITED(status)) {
            //Ricavo l'exitcode del figlio con la funzione WEXITSTATUS
            ritorno = WEXITSTATUS(status);
            printf("Il figlio di pid %d e' ritornato con %d lunghezza max trovata, se 255 problemi!\n", pidFiglio, ritorno);
        } else {
            //Lo status riporta una terminazione anomala
            printf("DEBUG: Il figlio e' terminato in modo anomalo\n");
        }
    }

    exit(0);
}
