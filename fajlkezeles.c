#include <stdio.h>
#include "fajlkezeles.h"
#include "debugmalloc.h"

Bejegyzes *beolvas(){
    FILE *file = fopen("bejegyzesek.txt", "r");
    Bejegyzes *lista = NULL;
    int sorszam;
    char datum[12], ido[6], helyszin[101], elnevezes[101], megjegyzes[501];
    if (file != NULL) {
        char sor[731];
        while (fgets(sor, 731, file) != NULL){
            sscanf(sor, "%d%*c%[^;]%*c%[^;]%*c%[^;]%*c%[^;]%*c%[^\n]",
                   &sorszam, datum, ido, helyszin, elnevezes, megjegyzes);

            lista = beszur(lista, sorszam, datum, ido, helyszin, elnevezes, megjegyzes);
        }
        fclose(file);
        return lista;
    }
    else {
        fclose(file);
        return NULL;
    }
}

void kiir(Bejegyzes *lista){
    FILE *file = fopen("bejegyzesek.txt", "w");
    Bejegyzes *i;
    int j = 1;
    for (i = lista; i != NULL; i = i->kov) {
        fprintf(file, "%d;%s;%s;%s;%s;%s\n", j, i->datum, i->idopont, i->helyszin, i->elnevezes, i->megjegyzes);
        j++;
    }
    fclose(file);
}