#ifndef UNTITLED_MENU_H
#define UNTITLED_MENU_H

#include "adatstruktura.h"

//Bekert szam ellenorzese
int szam_ellenorzes(int min, int max);

//Főmenü megjelenítése a konzolon
int fomenuBetolt();

//Új bejegyzés létrehozása
Bejegyzes *ujBejegyzes(Bejegyzes *lista);

//Bejegyzések kilistázása
Bejegyzes *kilistaz(Bejegyzes *lista);

//Keresés a bejegyzése között
Bejegyzes *keres(Bejegyzes *lista);

//Kilépés a programból
void kilep(Bejegyzes *lista);
#endif //UNTITLED_MENU_H
