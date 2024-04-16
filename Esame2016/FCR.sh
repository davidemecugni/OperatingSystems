#!/bin/bash

cartella=$1
numero=$2
file=$3

cd $cartella
echo Sono nella cartella: `pwd`

validi=true
for i in *
do
    if test -f $i -a -r $i
    then
        lunghezza=`wc -l < $i`
        echo "File $i lungo $lunghezza"
        if test $lunghezza -le $numero 
        then
            echo Trovato file troppo corto
            validi=false
        fi
    else
        validi=false
    fi
done

if $validi
then
    pwd >> $3
fi

for i in *
do
    if test -d $i -a -x $i
    then
        $0 $cartella $numero $file
    fi
done