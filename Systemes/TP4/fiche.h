#ifndef TP4_FICHE_H
#define TP4_FICHE_H

#define LONG_MAX_NOM 20
#define ERRCREA 1
#define ERROPEN 2
#define ERRXAGE 3
#define ERRCHIL 4
#define ERRNOFI 0 // Not really an error

typedef struct {
    char Nom[LONG_MAX_NOM+1];
    int Age;
    int NbEnfants;
} Infos;


void clear_terminal() {
    printf("\033[H\033[J");
    fflush(stdout);
}

void hide_cursor() {
    printf("\033[?25l");
    fflush(stdout);
}

void show_cursor() {
    printf("\033[?25h");
    fflush(stdout);
}

#endif //TP4_FICHE_H
