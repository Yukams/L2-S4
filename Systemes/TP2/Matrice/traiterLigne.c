
#include "matrice.h"
#include "traiterLigne.h"

/* retourne 0: aucun trouve, 1: V1 trouve, 2: v2 trouve et 3: v1 et v2 trouve */
unsigned traiterLigne(int uneLigne[NB_COLONNES_MAX], unsigned nbC,
			unsigned v1, unsigned v2)
{
    int find_v1 = 0;
    int find_v2 = 0;
    for(int i=0; i < nbC; i++) {
        if(uneLigne[i] == v1) {
            find_v1 = 1;
        } else if(uneLigne[i] == v2) {
            find_v2 = 1;
        }
    }

    if(find_v1 == 1 && find_v2 == 1) {
        return 3;
    } else if (find_v1 == 1) {
        return 2;
    }  else if (find_v2 == 1) {
        return 1;
    }
    return 0;
}
