#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "adatstruktura.h"
#include "debugmalloc.h"
#include "menu.h"

//Lista felszabadítása
void felszabadit(Bejegyzes *lista){
    Bejegyzes *i = lista;
    while(i != NULL) {
        Bejegyzes *kov = i->kov;
        free(i);
        i = kov;
    }
}

//Uj adat beszurasa
Bejegyzes *beszur(Bejegyzes *lista, int sorszam, char datum[12], char ido[6],
                  char helyszin[101], char elnevezes[101], char megjegyzes[501]) {
    Bejegyzes *uj = (Bejegyzes *) malloc(sizeof(Bejegyzes));
    uj->sorszam = sorszam;
    strcpy(uj->datum, datum);
    strcpy(uj->idopont, ido);
    strcpy(uj->helyszin, helyszin);
    strcpy(uj->elnevezes, elnevezes);
    strcpy(uj->megjegyzes, megjegyzes);
    uj->kov = NULL;
    if (lista == NULL) {
        return uj;
    } else {
        Bejegyzes *i = lista;
        while (i->kov != NULL) i = i->kov;
        i->kov = uj;
        return lista;
    }
}

//Egy elem törlése a listából
Bejegyzes *torol(Bejegyzes *lista){
    printf("Melyik sorszamu bejegyzest szeretne torolni?\n>");
    int sorszam = szam_ellenorzes(1, 9999);
    printf("Biztos torolni szeretne a bejegyzest? ([1] Megerosites   [0] Elvetes)\n>");
    int megerosit = szam_ellenorzes(0, 1);
    if (megerosit == 1) {
        Bejegyzes *i = lista;
        Bejegyzes *elozo = NULL;
        while (i != NULL) {
            if (i->sorszam == sorszam) {
                Bejegyzes *kov = i->kov;
                if (elozo != NULL)
                    elozo->kov = kov;
                else
                    lista = kov;

                free(i);
                //i = kov;

                printf("\n\nSikeres torles!\n"
                       "\n[%d] sorszamu bejegyzes torolve!\n\n", sorszam);
                return lista;
            } else {
                elozo = i;
                i = i->kov;
            }
        }
        printf("\n\nSikertelen torles! (Nincs ilyen sorszamu bejegyzes)\n\n");
        return lista;
    } else {
        printf("\nA bejegyzes nem kerult torlesre!\n\n");
        return lista;
    }
}

//Egy elem módosítása
Bejegyzes *modosit(Bejegyzes *lista){
    printf("Melyik sorszamu bejegyzest szeretne modositani?\n>");
    int sorszam = szam_ellenorzes(1, 9999);
    //dátum eltárolása
    getchar();
    printf("\t\t\t\tBejegyzes modositasa\n\n"
           "Irja be az esemeny datumat EV.HONAP.NAP. formatumban!\n>");
    char datum[12];
    while (true) {
        char datumbe[12];
        int ev, honap, nap;
        scanf("%[^\n]", datumbe);
        int sikerult = sscanf(datumbe, "%d.%d.%d.", &ev, &honap, &nap);
        int hossz = (int)strlen(datumbe);
        bool szokoev = ev % 4 == 0 && (ev % 100 != 0 || ev % 400 == 0);
        bool februar = honap == 2 && ((szokoev && nap <30) || (!szokoev && nap < 29));
        bool hhonap = ((honap == 1 || honap == 3 || honap == 5 || honap == 7|| honap == 8|| honap == 10|| honap == 12) && (nap < 32 && nap > 0));
        bool rhonap = ((honap == 4 || honap == 6 || honap == 9 || honap == 11) && (nap < 31 && nap > 0));
        bool valid = februar || hhonap || rhonap;
        if (sikerult != 3  || datumbe[strlen(datumbe) - 1] != '.' || hossz != 11) {
            printf("\nNem megfelelo bemenet!\n\n>");
            scanf("%*[^\n]");
            getchar();
        } else if (ev < 0 || ev > 10000 || !valid) {
            printf("\nNem megfelelo bemenet!\n\n>");
            getchar();
        } else {
            strcpy(datum, datumbe);
            break;
        }
    }
    getchar();

    //időpont eltárolása
    printf("\nIrja be az esemeny idopontjat ORA:PERC formatumban!\n>");
    char idopont[6];
    while (true) {
        char idopontbe[6];
        int ora, perc;
        scanf("%[^\n]", idopontbe);
        int sikerult = sscanf(idopontbe, "%d:%d", &ora, &perc);
        int hossz = (int)strlen(idopontbe);
        if (sikerult != 2  || idopontbe[strlen(idopontbe) - 3] != ':' || hossz != 5) {
            printf("\nNem megfelelo bemenet!\n\n>");
            scanf("%*[^\n]");
            getchar();
        } else if (ora > 23 || ora < 0 || perc > 59 || perc < 0) {
            printf("\nNem megfelelo bemenet!\n\n>");
            getchar();
        } else {
            strcpy(idopont, idopontbe);
            break;
        }
    }
    getchar();

    //helyszín eltárolása
    printf("\nIrja be az esemeny helyszinet! (maximum 100 karakter!)\n>");
    char helyszin[101];
    scanf("%100[^\n]", helyszin);
    scanf("%*[^\n]");
    getchar();

    //név eltárolása
    printf("\nIrja be az esemeny nevet! (maximum 100 karakter!)\n>");
    char elnevezes[101];
    scanf("%100[^\n]", elnevezes);
    scanf("%*[^\n]");
    getchar();

    //megjegyzés eltárolása
    printf("\nIrja be az esemenyhez tartozo megjegyzeseit! (maximum 500 karakter!)\n>");
    char megjegyzes[501];
    scanf("%500[^\n]", megjegyzes);
    scanf("%*[^\n]");
    getchar();

    //megerősítés
    printf("Biztos, hogy menteni akarja a valtoztatasokat?\n"
           "\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\n"
           "([1] Megerosites   [0] Elvetes)\n>", datum, idopont, helyszin, elnevezes, megjegyzes);
    int megerosites = szam_ellenorzes(0, 1);
    if(megerosites == 1) {
        Bejegyzes *i = lista;
        while (i->kov != NULL) {
            if (i->sorszam == sorszam) {
                strcpy(i->datum, datum);
                strcpy(i->idopont, idopont);
                strcpy(i->helyszin, helyszin);
                strcpy(i->elnevezes, elnevezes);
                strcpy(i->megjegyzes, megjegyzes);
                printf("\n\nSikeres modositas!\n"
                       "[%d] sorszamu bejegyzes modositva!\n\n", sorszam);
                return lista;
            } else
                i = i->kov;
        }
        printf("\n\nSikertelen modositas! (Nincs ilyen sorszamu bejegyzes)\n\n");
        return lista;
    }
    else {
        printf("\nA bejegyzes nem kerult modositasra!\n\n");
        return lista;
    }
}