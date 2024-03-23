#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#define BUFFSIZE 100


void calculateSize(const char *pathDir, long long int* total) {
    DIR *dirCourant;

    if((dirCourant=opendir(pathDir)) == NULL)
    {
        perror("ERROR : Cannot open directory\n");
        exit(2);
    }

    struct dirent *entreeCourante;
    struct stat pInfos;
    long int sum = 0;

    char pathBase[BUFFSIZE];
    const char *nomCourant;
    char pathCourant[BUFFSIZE];

    strcpy(pathBase,pathDir);
    strcat(pathBase,"/");

    while((entreeCourante=readdir(dirCourant)) != NULL) {
        nomCourant = entreeCourante->d_name;

        if(strcmp(nomCourant, ".") != 0 && strcmp(nomCourant, "..") != 0) {
            strcpy(pathCourant, pathBase);
            strcat(pathCourant, nomCourant);

            if(stat(pathCourant, &pInfos) == -1) {
                printf("ERROR : Cannot retrieve stats from file");
            } else {
                if(S_ISDIR(pInfos.st_mode)) {
                    calculateSize(pathCourant, total);
                } else {
                    sum += pInfos.st_size;
                    printf("%-35s : %8lld octets\n", pathCourant, pInfos.st_size);
                }
            }
        }
    }

    printf("\n-----------------------------------------------------------------------\n");
    printf("\nTOTAL DIRECTORY %-19s : %8ld octets\n", pathDir, sum);
    printf("\n=======================================================================\n");
    *total += sum;

    closedir(dirCourant);
}

int main(int argc, char* argv[]){
    long long int total;

    if(argc!=2)
    {
        fprintf(stderr,"Usage : %s [Répertoire]", argv[0]);
        exit(1);
    }

    calculateSize(argv[1], &total);
    printf("\n\n*** *=* END OF CALCUL *=* ***\n");
    printf("\nTOTAL DIRECTORY \"%s\" : %lld\n\n", argv[0], total);

    return 0;
}
