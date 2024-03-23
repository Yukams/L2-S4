#include <stdlib.h>
#include <stdio.h>
#include "erreur.h"

void erreur(const char *message, int valExit) {
    perror(message);
    exit(valExit);
}
