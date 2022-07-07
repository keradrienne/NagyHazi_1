#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "menu.h"
#include "fajlkezeles.h"
#include "debugmalloc.h"

//Választásokhoz beírt szám helyességének ellenőrzése
int szam_ellenorzes(int min, int max) {
    while (true) {
        int olvasott;
        int sikerult = scanf("%d", &olvasott);
        if (sikerult != 1) {
            printf("\nNem megfelelo bemenet!\n\n>");
            scanf("%*[^\n]");
            getchar();
        } else if (olvasott > max || olvasott < min) {
            printf("\nNem megfelelo ertek!\n\n>");
            scanf("%*[^\n]");
            getchar();
        } else {
            scanf("%*[^\n]");
            return olvasott;
        }
    }
}

//Főmenü megjelenítése
int fomenuBetolt() {
    printf("\t\t\t\tNaplo\n\n"
           "Irja be a hasznalni kivant funkcio sorszamat es nyomjon egy entert!\n\n"
           "[1] Uj bejegyzes\n"
           "[2] Kereses datum alapjan\n"
           "[3] Kereses nev alapjan\n"
           "[4] Kilepes\n\n"
           ">");
    return szam_ellenorzes(1, 4);
}

//Új bejegyzés rögzítése
Bejegyzes *ujBejegyzes(Bejegyzes *lista){
    //dátum eltárolása
    getchar();
    printf("\t\t\t\tUj bejegyzes\n\n"
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
            printf("\nNem megfelelo ertek!\n\n>");
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
            printf("\nNem megfelelo ertek!\n\n>");
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
    printf("Biztos, hogy akarja menteni a kovetkezo bejegyzest?\n"
           "\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\n"
           "(Megerosites: 1\t Elvetes: 0)\n>", datum, idopont, helyszin, elnevezes, megjegyzes);
    int megerosites = szam_ellenorzes(0, 1);
    if(megerosites == 1){
        printf("\nSikeres rogzites!\n\n");
        return beszur(lista, 1, datum, idopont, helyszin, elnevezes, megjegyzes);
    }
    else{
        printf("\nA bejegyzes nem kerult rogzitesre!\n\n");
        return lista;
    }
}

//Keresés a bejegyzések között dátum alapján
Bejegyzes *kilistaz(Bejegyzes *lista){
    bool kesz = false;
    while (!kesz){
        printf("\t\t\t\tBejegyzesek\n\n"
               "Milyen szempont alapjan tortenjen a megjelenites? ([0] Vissza a fomenube   [1] Nap   [2] Honap)\n>");
        int valasztas = szam_ellenorzes(0, 2);
        if(valasztas == 0) return lista;
        else if (valasztas == 1){
            printf("\nIrja be a pontos datumot EV.HONAP.NAP. fomatumban\n>");
            getchar();
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
            Bejegyzes *i;
            bool talalat = false;
            for (i = lista; i != NULL; i = i->kov) {
                if (strncmp(datum, i->datum, 101) == 0) {
                    printf("[%d]\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n",
                           i->sorszam, i->datum, i->idopont, i->helyszin, i->elnevezes, i->megjegyzes);
                    talalat = true;
                }
            }
            if (!talalat){
                printf("Nincs talalat!\n\n");
                printf("\n\n[0] Vissza a fomenube   [1] Uj kereses\n>");
                int valasztas = szam_ellenorzes(0, 1);
                if(valasztas == 1) {
                    kesz = false;
                    continue;
                }
                else return lista;
            } else{
                printf("\n\n[0] Vissza a fomenube   [1] Uj kereses   [2] Torles   [3]Modositas\n>");
                int valasztas = szam_ellenorzes(0, 3);
                if(valasztas == 0) return lista;
                else if(valasztas == 1) {
                    kesz = false;
                    continue;
                }
                else if(valasztas == 2){
                    lista = torol(lista);
                    kiir(lista);
                    return lista;
                    break;
                }
                else if(valasztas == 3){
                    lista = modosit(lista);
                    kiir(lista);
                    return lista;
                    break;
                }
            }
        }else if(valasztas == 2){
            printf("Irja be datumot EV.HONAP. fomatumban\n>");
            getchar();
            char datum[9];
            while (true) {
                char datumbe[9];
                int ev, honap;
                scanf("%[^\n]", datumbe);
                int sikerult = sscanf(datumbe, "%d.%d.", &ev, &honap);
                int hossz = (int)strlen(datumbe);
                if (sikerult != 2  || datumbe[strlen(datumbe) - 1] != '.' || hossz != 8) {
                    printf("\nNem megfelelo bemenet!\n\n>");
                    scanf("%*[^\n]");
                    getchar();
                } else if (ev < 0 || ev > 10000 || honap < 1 || honap > 13) {
                    printf("\nNem megfelelo bemenet!\n\n>");
                    getchar();
                } else {
                    strcpy(datum, datumbe);
                    break;
                }
            }
            getchar();
            Bejegyzes *i;
            bool talalat = false;
            for (i = lista; i != NULL; i = i->kov) {
                if (strstr(i->datum, datum) != NULL) {
                    printf("[%d]\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n",
                           i->sorszam, i->datum, i->idopont, i->helyszin, i->elnevezes, i->megjegyzes);
                    talalat = true;
                }
            }
            if (!talalat){
                printf("Nincs talalat!\n\n");
                printf("\n\n[0] Vissza a fomenube   [1] Uj kereses\n>");
                int valasztas = szam_ellenorzes(0, 1);
                if(valasztas == 1) {
                    kesz = false;
                    continue;
                }
                else return lista;
            }else{
                printf("\n\n[0] Vissza a fomenube   [1] Uj kereses   [2] Torles   [3]Modositas\n>");
                int valasztas = szam_ellenorzes(0, 3);
                if(valasztas == 0) return lista;
                else if(valasztas == 1){
                    kesz = false;
                    continue;
                }
                else if(valasztas == 2){
                    lista = torol(lista);
                    kiir(lista);
                    return lista;
                    break;
                }
                else if(valasztas == 3){
                    lista = modosit(lista);
                    kiir(lista);
                    return lista;
                    break;
                }
            }
        }
    }
}

//Keresés a bejegyzések között név alapján
Bejegyzes *keres(Bejegyzes *lista){
    bool kesz = false;
    while (!kesz){
        printf("\t\t\t\tKereses\n\n");
        printf("Irja be a keresendo Bejegyzes nevet!\n>");
        getchar();
        char keresett[101];
        scanf("%100[^\n]", keresett);
        Bejegyzes *i;
        bool talalat = false;
        for (i = lista; i!=NULL ; i = i->kov) {
            if(strncmp(keresett, i->elnevezes, 101) == 0) {
                printf("[%d]\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n",
                       i->sorszam, i->datum, i->idopont, i->helyszin, i->elnevezes, i->megjegyzes);
                talalat = true;
            }
        }
        if (!talalat){
            printf("Nincs talalat!\n\n");
            printf("\n\n[0] Vissza a fomenube   [1] Uj kereses\n>");
            int valasztas = szam_ellenorzes(0, 1);
            if(valasztas == 1) {
                kesz = false;
                continue;
            }
            else return lista;
        }else{
            printf("\n\n[0] Vissza a fomenube   [1] Uj kereses   [2] Torles   [3]Modositas\n>");
            int valasztas = szam_ellenorzes(0, 3);
            if(valasztas == 0) return lista;
            else if(valasztas == 1){
                kesz = false;
                continue;
            }
            else if(valasztas == 2){
                lista = torol(lista);
                kiir(lista);
                return lista;
                break;
            }
            else if(valasztas == 3){
                lista = modosit(lista);
                kiir(lista);
                return lista;
                break;
            }
        }
    }



}

//Kilépés a programból
void kilep(Bejegyzes *lista){
    printf("Biztos, hogy ki akar lepni a programbol? ([0] Nem    [1] Igen)\n>");
    int valasz = szam_ellenorzes(0, 1);
    if(valasz == 0) return;
    else{
        felszabadit(lista);
        exit(0);
    }
}