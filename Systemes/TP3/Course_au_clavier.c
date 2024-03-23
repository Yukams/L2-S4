#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "term_canon.h"

/*
void touche() {
    pid_t pid_s = getpid();
    char ch[1];
    while((read(0, &ch, sizeof(char)) && ch[0] != 'f'))
    {
        printf("%d %c\n", pid_s, ch[0]);
    }
}
*/

void clear_terminal() {
    printf("\033[H\033[J");
    fflush (stdout);
}

void hide_cursor() {
    printf("\033[?25l");
    fflush (stdout);
}

void show_cursor() {
    printf("\033[?25h");
    fflush (stdout);
}

/*
void joueur(char my_char, int ligne, int distance) {
    char ch[1];
    int position = 0;
    struct timespec micro_pause;
    micro_pause.tv_sec = 0;
    micro_pause.tv_nsec = 1000;

    // Affiche l'arrivée
    printf ("\033[%d;%dH%c", ligne+1, distance+1, '|');
    printf ("\033[%d;%dH%c", ligne+1, position+1, my_char);
    fflush (stdout);

    //
    while(distance > position) {

        // Lis le caractère
        read(0, &ch, sizeof(char));
        nanosleep(&micro_pause, NULL);

        // Fais déplacer le joueur si il tape sa lettre
        if(ch[0] == my_char ) {
            position+=1;
            printf ("\033[%d;%dH%c", ligne+1, position, ' ');
            printf ("\033[%d;%dH%c", ligne+1, position+1, my_char);
            fflush (stdout);
        }
    }
}
*/

void joueur(char my_char, int ligne, int distance, int fd) {
    char ch[1];
    char buffer[1] = {49};
    struct timespec micro_pause;
    micro_pause.tv_sec = 0;
    micro_pause.tv_nsec = 1000;
    pwrite(fd, buffer, sizeof(char), ligne);

    while(distance > buffer[0] - 49) {
        // Lis le caractère
        read(0, &ch, sizeof(char));
        nanosleep(&micro_pause, NULL);

        // Fais déplacer le joueur si il tape sa lettre
        if(ch[0] == my_char) {
            buffer[0] += 1;
            pwrite(fd, buffer, sizeof(char), ligne);
        }
    }
}


int hasAllArrived(int* state, int players, int distance) {
    int sum = 0;
    for(int i = 0; i < players; i++) {
        sum += state[i];
    }
    return sum < distance * players;
}


void moniteur(int fd, int players, int distance, char* chars) {
    char buffer[1] = {49};
    int state[players];
    // Affiche la ligne d'arrivée et le premier char
    for(int i = 0; i < players; i++) {
        state[i] = 0;
        printf("\033[%d;%dH%c", i + 1, distance + 1, '|');
        printf("\033[%d;%dH%c", i + 1, buffer[0] - 49 + 1, chars[i]);
        fflush(stdout);
    }

    while(hasAllArrived(state, players, distance)) {
        for (int i = 0; i < players; i++) {
            pread(fd, &buffer, sizeof(char), i + 1);
            state[i] = buffer[0] - 49;
            printf("\033[%d;%dH%c", i + 1, state[i], ' ');
            printf("\033[%d;%dH%c", i + 1, state[i] + 1, chars[i]);
            fflush(stdout);
        }
    }
}

int main(int argc, char* argv[]) {
    if(argc != 3) {
        fprintf(stderr, "%s needs two arguments\n", argv[0]);
        exit(255);
    }

    int nb_players = atoi(argv[1]);
    int distance = atoi(argv[2]);

    if (nb_players > 4 || nb_players < 2) {
        fprintf(stderr, "%s first argument must be between 2 and 4 players\n", argv[0]);
        exit(255);
    }
    if (distance > 50 || distance < 2) {
        fprintf(stderr, "%s second argument must be between 2 and 50 distance\n", argv[0]);
        exit(255);
    }

    int file = creat("temp.txt", S_IRWXU|S_IRWXG|S_IRWXO);
    close(file);
    file = open("temp.txt", O_RDWR);

    clear_terminal();
    hide_cursor();
    Term_non_canonique();

    pid_t pid;

    char chars[4] = "abcd";
    int place = 1;

    // Création des fils
    for(int i = 0; i<nb_players; i++) {
        switch(pid = fork()) {
            case -1:
                clear_terminal();
                show_cursor();

                perror("ERREUR lors de la création du fils\n");
                close(file);
                exit(255);
            case 0:
                //touche()
                joueur(chars[i], i+1, distance, file);
                exit(i);
            default:
                break;
        }
    }

    // Création du moniteur
    switch(pid = fork()) {
        case -1:
            clear_terminal();
            show_cursor();

            perror("ERREUR lors de la création du moniteur\n");
            close(file);
            exit(255);
        case 0:
            moniteur(file, nb_players, distance, chars);
            sleep(1);
            exit(4);
        default:
            break;
    }

    int status;
    while((wait(&status)) != -1) {
        int nb_stat = WEXITSTATUS(status);
        if(nb_stat < 4) {printf("\033[%d;%dH Arrivé en numéro %d !", nb_stat + 1, distance + 4, place++);}
        fflush(stdout);
    }

    Term_canonique();
    clear_terminal();
    show_cursor();

    close(file);

    return 0;
}