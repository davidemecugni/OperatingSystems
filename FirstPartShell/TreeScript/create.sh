#!/bin/zsh
#FILE create.sh

# Verifica che il numero di argomenti sia corretto
if test $# -ne 2
then
    echo "Usage: $0 <nome_gerarchia> <num_livelli>"
    exit 1
fi

# Verifica che il primo argomento sia una stringa
if ! [[ $1 =~ ^[a-zA-Z]+$ ]]
then
    echo "Errore: Il primo parametro deve essere una stringa."
    exit 2
fi

# Verifica che il secondo argomento sia un numero
if ! [[ $2 =~ ^[0-9]+$ ]]
then
    echo "Errore: Il secondo parametro deve essere un numero."
    exit 2
fi

# Funzione per creare la gerarchia principale
function create_G() {
    # Verifica che il numero di argomenti sia corretto
    if test $# -ne 1
    then
        echo "Usage: $0 <nome_gerarchia>"
        exit 1
    fi

    local G=$1
    
    # Se la directory esiste già, la rimuovi
    if test -d $G
    then
        rm -rP $G
    fi
    # Crea la directory principale
    mkdir $G
}

function getFileContent() {
    echo "Vuoi personalizzare il contenuto del file [Si/No]?" 1>&2
    read risposta < /dev/tty

    case $risposta in
    s*|S*|y*|Y*)  
                    echo "Inserisci il contenuto del file:" 1>&2
                    read content < /dev/tty
                    echo "Inserisci il numero di linee del file:" 1>&2
                    read numLinee < /dev/tty;;
    
    *)              echo "Di default vengono inserite 5 linee con "Abc123"." 1>&2
                    content="Abc123"
                    numLinee=5;;
    esac
    contentResult=$content
    numLineeResult=$numLinee
}

# Funzione per creare le directory e i file
function create_directories() {
    local directory=$1
    local num_dirs=$2
    local num_files=$3
    local lvl=$4

    cd $directory

    # Crea le directory
    if test $num_dirs -gt 0
    then
        for j in $(seq 1 $num_dirs)
        do
            mkdir D.$lvl.$j
        done
    fi

    # Crea i file
    if test $num_files -gt 0
    then
        getFileContent
        for k in $(seq 1 $num_files)
        do
            for l in $(seq 1 $numLineeResult)
            do
                echo $contentResult >> F.$lvl.$k
            done
        done
    fi
}

# Funzione per ottenere il numero di directory da creare
function getNumDir() {
    echo "Quante directory vuoi per questo livello ? or -1 to exit." 1>&2
    read numDir

    if test $numDir -eq -1
    then
        exit 3
    elif ! [[ $numDir =~ ^[0-9]+$ ]]
    then
        echo "Errore: Inserisci un numero." 1>&2
        exit 4
    fi
    numDirResult=$numDir
}

# Funzione per ottenere il numero di file da creare
function getNumFile() {
    echo "Quanti file vuoi per questo livello ? or -1 to exit." 1>&2
    read file 
    if test $file -eq -1 
    then
        exit 3
    elif ! [[ $file =~ ^[0-9]+$ ]]
    then
        echo "Errore: Inserisci un numero." 1>&2
        exit 4
    fi
    fileResult=$file
}

# Crea la gerarchia principale
create_G $1

percorso=`pwd`/$1

# Crea le directory e i file per ogni livello
for i in $(seq 0 $(($2-1)))
do
    echo "Livello $i"
    getNumDir
    getNumFile

    find $percorso -mindepth $i -maxdepth $i -type d | while read dir
    do
        echo "Directory: $dir"
        if test -d "$dir"
        then
            create_directories "$dir" $numDirResult $fileResult $i
            echo "Il tuo albero ora è:"
            ls -R $percorso
        fi
    done
done
