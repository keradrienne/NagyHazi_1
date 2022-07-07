#include <stdio.h>
#include "menu.h"
#include "fajlkezeles.h"
#include "debugmalloc.h"

int main() {
    bool kesz = false;
    while (!kesz) {
        Bejegyzes *lista = beolvas();

        switch (fomenuBetolt()) {
            case 1:
                lista = ujBejegyzes(lista);
                kiir(lista);
                felszabadit(lista);
                for (int i = 0; i < 100; ++i) printf("-");
                printf("\n\n");
                kesz = false;
                break;
            case 2:
                if (lista == NULL) {
                    printf("Nincs megjelenitheto bejegyzes!\n");
                    kesz = false;
                    continue;
                } else {
                    lista = kilistaz(lista);
                    felszabadit(lista);
                    for (int i = 0; i < 100; ++i) printf("-");
                    printf("\n\n");
                    kesz = false;
                    break;
                    case 3:
                        if (lista == NULL) {
                            printf("Nincs megjelenitheto bejegyzes!\n");
                            kesz = false;
                            continue;
                        } else {
                            lista = keres(lista);
                            felszabadit(lista);
                            for (int i = 0; i < 100; ++i) printf("-");
                            printf("\n\n");
                            kesz = false;
                        }
                    break;
                    case 4:
                        kilep(lista);
                    felszabadit(lista);
                    for (int i = 0; i < 100; ++i) printf("-");
                    printf("\n\n");
                    kesz = false;
                    break;
                }
        }
    }

    return 0;
}
