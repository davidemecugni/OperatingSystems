//Using C11
//Davide Mecugni
//File parametri1.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if(argc < 2){
        printf("Errore: inserire almeno un parametro\n");
        exit(1);
    }
    printf("Nome del eseuguibile: %s\n", argv[0]);
    for(int i = 0; i < argc-1; i++){
        printf("Parametro %d: %s\n", i + 1, argv[i+1]);
    }
    return 0;
}
