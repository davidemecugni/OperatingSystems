# Script di creazione gerarchia

Lo script `create.sh` è uno script di shell che crea una gerarchia di directory e file.

## Utilizzo

Per utilizzare lo script, eseguire il comando seguente nel terminale:

Se non avete zsh
```shell
    sudo apt install zsh
```

```shell
    chmod u+x create.sh
````
```shell
    ./create.sh <nome_gerarchia> <num_livelli>
````
## Note
La gerarchia viene creata nella directory corrente, per ciascun livello sarà richiesto il numero di directory e file, con la possibilità di personalizzare il contenuto e il numero di linee. Altrimenti di default i file consistono in '5' linee di `Abc123`.

**ATTENZIONE!!**
Se il nome passato come primo parametro corrisponde ad una directory esistente, essa verrà eliminata e riscritta con la gerarchia creata. 
