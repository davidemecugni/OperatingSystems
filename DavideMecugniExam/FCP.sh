#!/bin/sh
#File FCP.sh


# Controllo il numero dei parametri
case $# in
0|1|2) echo ERRORE: numero di parametri non accettabile: $#
     exit 1;;
*)echo DEBUG-OK: numero di parametri corretto, sono almeno 3;;
esac

# Dati per salvare le gerarchie in una lista e salvare separatamente C
counter=1
gerarchie=

#Ciclo sui parametri
for i
do
    if test $counter -ne $# # serve per non considerare l'ultimo parametro
    then
        #Controllo che le G siano valide
        case $i in
        /*) if test ! -d $i -o ! -x $i
            then
            echo $i non directory o non attraversabile
            exit 2
            fi;;
        *)  echo $i non nome assoluto; exit 3;;
        esac

        gerarchie="$gerarchie $i" # Se prima dell'ultimo salvo il nome della presunta gerarchia in gerarchie
    else

        C=$i # Se counter == $# allora siamo all'ultimo
    fi
    counter=`expr $counter + 1` #incremento il contatore del ciclo sui parametri
done

#Controllo su C
# Controllo che C sia un carattere
case $C in
?)	echo DEBUG-OK: $C e\' un singolo carattere;;
*)	echo $C non singolo carattere; exit 4 ;;
esac

# Aggiugo la directory corrente al path e la esporto, ai fini del funzionamento di FCR.sh
PATH=`pwd`:$PATH
export PATH

for G in $gerarchie
do
    # Eseguo chiamata al file ricorsivo passando la gerarchia da esplorare e il carattere
    FCR.sh $G $C
done


