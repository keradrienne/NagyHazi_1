#ifndef UNTITLED_ADATSTRUKTURA_H
#define UNTITLED_ADATSTRUKTURA_H

typedef struct Bejegyzes{
    int sorszam;
    char datum[12], idopont[6], helyszin[101], elnevezes[101], megjegyzes[501];
    struct Bejegyzes *kov;
} Bejegyzes;

//Memoria felszabaditasa
void felszabadit(Bejegyzes *lista);

//Uj adat beszurasa
Bejegyzes *beszur(Bejegyzes *lista, int sorszam, char datum[12], char ido[6],
                  char helyszin[101], char elnevezes[101], char megjegyzes[501]);

//Töröl egy elemet
Bejegyzes *torol(Bejegyzes *lista);

//Módosít egy elemet
Bejegyzes *modosit(Bejegyzes *lista);

#endif //UNTITLED_ADATSTRUKTURA_H
