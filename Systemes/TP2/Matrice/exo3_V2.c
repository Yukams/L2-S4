#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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

    pid_t fils = 0;
    int* cir;
    unsigned int codeRetour;
    int code;

    for(int i=0; i < nbLignes; i++) {
        pid_t pid;
        switch(pid=fork()) {
            case -1:
                perror("ERROR : Le fils n'a pas pu être créé");
                exit(255);
            case 0:
                codeRetour = traiterLigne(matrice[i], nbColonnes, v1, v2);
                printf("\nLigne %d : %d", i, codeRetour);
                exit(codeRetour);
            default:
                while((fils = wait(&cir)) != -1) {
                    code = WEXITSTATUS(cir);

                    if (code == 0) {
                        nbl_aucun_trouve += 1;
                    } else if (code == 1) {
                        nbl_V1_trouve += 1;
                    } else if (code == 2) {
                        nbl_V2_trouve += 1;
                    } else {
                        nbl_V1_V2_trouve += 1;
                    }
                }
        }
    }

    printf("\n\nTOTAL\n=========\nAucun : %d\nV1 seulement : %d\nV2 seulement : %d\nV1 et V2 : %d", nbl_aucun_trouve, nbl_V1_trouve, nbl_V2_trouve, nbl_V1_V2_trouve);

    return 0;
}