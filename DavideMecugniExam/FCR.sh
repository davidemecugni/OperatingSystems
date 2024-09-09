#!/bin/sh
#File FCR.sh

G=$1
C=$2

#Entro nella gerarchia fornita
cd $G

#Inizializzo il contatore di file validi come da specifica
cont=0
fileValidi=

#Variabili booleane per contenere se i requisiti sono stati soddisfatti
nomeOK=false
case $G in
    ?$C?$C) nomeOK=true;;
    *);;
esac


# Ciclo sui file della cartella
for F in *
do 
    # Controllo se e' un file e se e leggibile
    if test -f $F -a -r $F
    then
        if test `wc -c < $F` -ne 0 #Se il numero di caratteri del file non e' 0, ossia se non e' vuoto
        then 
            #Contiene le linee del file
            L=`wc -l < $F`
            #Contiene linee modulo 2
            resto=`expr $L % 2`
            #Ossia se e' pari
            if test $resto -eq 0
            then
                #Aggiungo 1 al contatore dei file validi
                cont=`expr $cont + 1`
                #Aggiungo il nome alla lista dei file validi
                fileValidi="$fileValidi $F"
            fi
        fi
    fi
done

#Se la cartella soddisfa A e B ma non C
if test $nomeOK="true" -a $cont -eq 0
then
    echo Trovata cartella `pwd` con nome valido, ma NON contiene file validi!
fi
#Se la cartella soddisfa A B C
if test $nomeOK="true" -a $cont -gt 0
then
    echo Trovata cartella `pwd` con nome valido e CONTIENE file validi!
    echo DEBUG-OK: Chiamo C con $fileValidi
    main $fileValidi
fi

#Ricorsione sulle cartelle presenti nella cartella corrente
#Per ogni file nella cartella presente
for F in *
do
#Se il file e' una cartella ed e' attraversabile
    if test -d $F -a -x $F
    then 
        FCR.sh `pwd`/$F $C #Chiamo il ricorsivo sulla cartella trovata
    fi
done
