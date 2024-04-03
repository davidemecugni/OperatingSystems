# PrimaProvaOS

Aggiungere prove passate(preferibilmente **parziali** e non totali) con la seguente struttura:

+ Data gg/mm/yyyy
+ Descrizione completa con note ed eventuali evidenziazioni del testo
+ FCP.sh in blocco di testo bash
+ FCR.sh in blocco di testo bash
+ Tag ossia parole chiave che possono tornare utili per trovare
quella prova usando CTRL-F durante l'esame(es. for, controllo file vuoto, controllo stretto 2 parametri)

L'importante è tenere il markdown aggiornato, si può sempre convertire il .md in PDF con il comando sotto da Linux:

```console
sudo apt install npm
sudo npm install -g pretty-markdown-pdf
pretty-md-pdf -i FILE.md
```
