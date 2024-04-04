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
La gerarchia viene creata nella directory corrente, per ciascun livello sarà richiesto il numero di directory e file. Di default i file consistono in '5' linee di `Abc123`, cioè caratteri maiuscoli, minuscoli e numeri.
