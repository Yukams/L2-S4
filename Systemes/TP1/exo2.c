#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define NB_MOTS_MAX 20

/* FONCTION DECOUPE */
int Decoupe(char chaine[], char *pMots[])
{
    char *p;
    int nbMots = 0;

    p = chaine;

    while ((*p) != '\0' && nbMots < NB_MOTS_MAX)
    {
        while ((*p) == ' ' && (*p) != '\0')
            p++;

        if ((*p) == '\0')
            break;

        pMots[nbMots++] = p;

        while ((*p) != ' ' && (*p) != '\0')
            p++;

        if ((*p) == '\0')
            break;
        *p = '\0';
        p++;
    }
    pMots[nbMots] = NULL;

    return nbMots;
}


int main(int argc, char *argv[]) {
    int i = 1;
    while (i<argc) {
        pid_t pid;
        //int cir;
        //pid_t pidFils;
        switch(pid=fork()) {
            case -1:
                printf("\n\n*** ERREUR : La création du fils a échoué ***\n\n");
                break;
            case 0:
                printf("\n[%d] J'ai délégué %s à %d. J'attends sa fin...\n", getppid(), argv[i], getpid());
                printf("[%d] Je lance %s :\n", getpid(), argv[i]);
                char *chaine[NB_MOTS_MAX+1];
                Decoupe(argv[i], chaine);
                execvp(chaine[0], chaine);
            default:
                /*pidFils = wait(&cir);
                int exit_code = WEXITSTATUS(cir);
                if (exit_code != 0) {printf("ERREUR : Le fils ne s'est pas correctement terminé (exit code : %d)\n\n", exit_code);}
                if (exit_code == -1) {break;}
                printf("[%d] %d terminé.\n\n", getpid(), pidFils);*/
                i++;
        }
    }
    while(wait(NULL)!=-1){};
    printf("\n[%d] J'ai fini, tous les processus fils sont morts\n\n", getpid());
    return 97;
}
