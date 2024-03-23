#include <stdio.h>
#include <stdlib.h>
#include "traiterLigne.h"
#include "matrice.h"

int main(int argc, char **argv) {
    if(argc != 5) {
        perror("ERROR : needs 4 arguments");
        exit(1);
    }

    unsigned nbLignes = atoi(argv[1]);
    unsigned nbColonnes = atoi(argv[2]);
    unsigned v1 = atoi(argv[3]);
    unsigned v2 = atoi(argv[4]);

    int matrice[NB_LIGNES_MAX][NB_COLONNES_MAX];
    initialiserMatrice(matrice, nbLignes, nbColonnes);
    afficherMatrice(matrice, nbLignes, nbColonnes);

    int nbl_aucun_trouve = 0;
    int nbl_V1_trouve = 0;
    int nbl_V2_trouve = 0;
    int nbl_V1_V2_trouve = 0;
    for(int i=0; i < nbLignes; i++) {
        unsigned int codeRetour = traiterLigne(matrice[i], nbColonnes, v1, v2);
        printf("\nLigne %d : %d", i, codeRetour);

        if (codeRetour == 0) {
            nbl_aucun_trouve += 1;
        } else if (codeRetour == 1) {
            nbl_V1_trouve += 1;
        } else if (codeRetour == 2) {
            nbl_V2_trouve += 1;
        } else {
            nbl_V1_V2_trouve += 1;
        }
    }

    printf("\n\nTOTAL\n=========\nAucun : %d\nV1 seulement : %d\nV2 seulement : %d\nV1 et V2 : %d", nbl_aucun_trouve, nbl_V1_trouve, nbl_V2_trouve, nbl_V1_V2_trouve);

    return 0;
}