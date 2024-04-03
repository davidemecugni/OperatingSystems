# PrimaProvaOS

Aggiungere prove passate(preferibilmente parziali e non totali) con la seguente struttura:

+ Data gg/mm/yyyy
+ Descrizione completa con note ed eventuali evidenziazioni del test
+ FCP.sh in blocco di testo bash
+ FCR.sh in blocco di testo bash
+ Tag ossia parole chiave che possono tornare utili per trovare
quella prova usando CTRL-F durante l'esame

Convertire i file markdown con:

```console
npm install -g pretty-markdown-pdf
pretty-md-pdf -i FILE.md
```
