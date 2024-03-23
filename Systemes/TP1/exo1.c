#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// L being a reference letter to track what is Pere/Fils process
void printProcessInfo(char* L) {
    printf("(%s1) PID : %d\n", L, getpid());
    printf("(%s2) PPID : %d\n", L,getppid());
    printf("(%s3) PGRP : %d\n", L, getpgrp());
    sleep(1);
    char* log = getlogin();
    log ? printf("(%s4) USER : %s\n", L, log) : printf("USER is null");
    printf("(%s5) UID : %d\n", L, getuid());
    printf("(%s6) GID : %d\n", L, getgid());
}

int main(void) {
    pid_t pid;
    switch (pid = fork()) {
        case -1:
            printf("\nERREUR : La création du fils a échoué\n");
            exit(1);
        case 0:
            printf("\nSUCCES : Le fils %d a été créé, sa référence sera \"F<nombre>\"\n", getpid());
            printProcessInfo("F");
            printf("\nFIN EXECUTION : Fils\n\n");
            exit(99);
        default:
            printf("\nLe père %d s'execute, sa référence sera \"P<nombre>\"\n", getpid());
            printProcessInfo("P");
            printf("\nPère EN ATTENTE DE LA FIN D'EXECUTION DE : Fils\n\n");
            int cir;
            wait(&cir);
            int exit_code = WEXITSTATUS(cir);
            exit_code == 99 ? printf("\nSUCCESS : Le fils s'est correctement terminé (exit code : %d)\n", exit_code) : printf("\nERREUR : Le fils ne s'est pas correctement terminé (exit code : %d)\n", exit_code) ;
            printf("\nFIN EXECUTION : Père\n\n");
    }
    return 97;
}