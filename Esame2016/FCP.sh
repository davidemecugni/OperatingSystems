#!/bin/bash

# controllo il numero dei parametri
case $# in
0|1|2) echo ERROR: numero di paramtri non accettabile
     exit 3;;
*)echo DEBUG-OK: numero di parametri corretto;;
esac

cartelle=""
conta=1
numero=
for i in $*
do
    if test $conta -lt $#
    then
        if test -d $i -a -x $i
        then
            case $i in
            /*) echo "$i cartella OK"; conta=`expr $conta + 1`; cartella="$cartella $i";;
            *)  echo "Cartella $i non in forma assoluta";exit 2;;
            esac
        fi
    else
        case $i in
        *[^0-9]*)   echo "$i non numerico"; exit 3;;
        *)          echo "Parametro $i numerico"; 
                    numero=$i;;
        esac
    fi
done

# aggiugo la directory corrente al path e la esporto
PATH=`pwd`:$PATH
export PATH

salvati="/tmp/esame2016-$$"
> $salvati

for i in $cartella
do
    ./FCR.sh "$i" "$numero" "$salvati"
done


numero_trovati=`wc -l < $salvati`

echo "Numero di file trovati: $numero_trovati"

for d in `cat $salvati`
do
    echo "Cartella: $d"
    cd $d
    for f in *
    do
        echo "Nel file $f"
        echo "La $numero riga e': "
        echo `head -n $numero $f | tail -n 1`
    done

done
rm /tmp/esame2016-$$



