#include "fiche.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int Consultation(char *NomFichier) {
    int file = open(NomFichier, O_RDONLY);
    if(file==-1) {
        fprintf(stderr, "\nERROR : Le fichier n'a pas pu être ouvert\n");
        return(ERROPEN);
    }

    Infos f;
    int nbFiches = 0;
    while(read(file, &f, sizeof(Infos))) {
        nbFiches++;
    }
    if(nbFiches == 0) {printf("\nERROR : Il n'existe pas encore de fiche !\n"); return(ERRNOFI);}
    printf("\nIl existe %d fiches", nbFiches);

    int iFiche = -1;
    while(iFiche != 0) {
        printf("\nQuelle fiche souhaitez vous consulter ? (0 pour quitter)");
        scanf(" %d", &iFiche);
        if (iFiche > nbFiches || iFiche < 0) { printf("\nCette fiche n'existe pas !\n\n"); }
        else if (iFiche != 0){
            lseek(file, sizeof(Infos) * (iFiche -1), SEEK_SET);
            read(file, &f, sizeof(Infos));

            printf("\nLecture de la fiche...");
            printf("\nNom : %s, Age : %d, Nb Enfant : %d\n\n", f.Nom, f.Age, f.NbEnfants);
        }
    }

    close(file);

    return 0;
}


int Creation(char *NomFichier) {
    Infos f;
    char tempChar;
    int tempInt;
    int file = creat(NomFichier, S_IRWXU | S_IRWXO | S_IRWXG);
    if(file==-1) {
        fprintf(stderr, "\nERROR : Le fichier n'a pas pu être créé\n");
        return(ERRCREA);
    }

    int nbFich;
    printf("\nCombien de fiches voulez vous créer ?");
    scanf(" %d", &nbFich);

    for(int i = 0; i < nbFich; i++) {
        printf("\n\nCréation de la fiche %d :", i+1);

        printf("\nChoisissez un nom :");
        scanf(" %s", f.Nom);

        printf("\nChoisissez un âge :");
        scanf(" %s", &tempChar);
        tempInt = atoi(&tempChar);
        if(tempInt == 0) {
            fprintf(stderr, "\nERREUR : âge rentré incorrect\n");
            return(ERRXAGE);
        } else {
            f.Age = tempInt;
        }

        printf("\nChoisissez un nombre d'enfants :");
        scanf(" %s", &tempChar);
        tempInt = atoi(&tempChar);
        if(tempInt == 0) {
            fprintf(stderr, "\nERREUR : Nombre d'enfant rentré incorrect\n");
            return(ERRCHIL);
        } else {
            f.NbEnfants = tempInt;
        }

        write(file, &f, sizeof(Infos));
    }

    close(file);

    return 0;
}


int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "ERROR : %s doit être appelé avec un paramètre\n", argv[0]);
    }
    clear_terminal();
    int errCode;
    char tempChoiceCh;
    int tempChoiceInt;
    int choice;

    while(1) {
        printf("\n* ========================== *\n        *** MENU ***\n\n\n* Choisissez une option *\n1 - Creation de fiches\n2 - Consultation de fiches\n3 - Exit\n\n\n* ========================== *");

        hide_cursor();
        scanf("%s", &tempChoiceCh);
        show_cursor();
        tempChoiceInt = atoi(&tempChoiceCh);
        if(tempChoiceInt != 0) {
            choice = tempChoiceInt;
        }

        clear_terminal();

        switch (choice) {
            case 1:
                if ((errCode = Creation(argv[1])) != 0) {
                    exit(errCode);
                }
                break;
            case 2:
                if ((errCode = Consultation(argv[1])) != 0) {
                    printf("\n%d\n", errCode);
                    exit(errCode);
                }
                break;
            case 3:
                exit(0);
            default:
                clear_terminal();
        }
    }
}