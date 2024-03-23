/*************************************************************
* proto_tdd_v3 -  émetteur                                   *
* TRANSFERT DE DONNEES  v03                                  *
*                                                            *
* Transfert de donnees avec fenetre d’anticipation et        *
* reprise sur erreurs "Go-Back-N"                            *
**************************************************************/

#include <stdio.h>
#include <unistd.h>
#include "application.h"
#include "couche_transport.h"
#include "services_reseau.h"

/* =============================== */
/* Programme principal - émetteur  */
/* =============================== */
int main(int argc, char* argv[])
{
    unsigned char message[MAX_INFO]; /* message de l'application */
    int taille_msg = 1; /* taille du message */
    uint8_t sum; /* verification xor */
    unsigned int curseur = 0;
    unsigned int borne_inf = 0;
    unsigned int taille_fenetre = 4;
    paquet_t lPaquet[8];
    int lg_recepteur = -1;

    init_reseau(EMISSION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");


    /* tant que l'émetteur a des données à envoyer */
    while ( taille_msg != 0 || !lg_recepteur ) {
        printf("\n\n\n\n");
        if (dans_fenetre(borne_inf, curseur, taille_fenetre)) {
            de_application(message, &taille_msg);
            sum = 0;

            /* construction paquet */
            for (int i = 0; i < taille_msg; i++) {
                lPaquet[curseur].info[i] = message[i];
                sum = sum ^ lPaquet[curseur].info[i];
            }
            lPaquet[curseur].lg_info = taille_msg;
            lPaquet[curseur].type = DATA;
            lPaquet[curseur].num_seq = curseur;

            /* Verifications */
            sum = sum ^ lPaquet[curseur].type ^ curseur ^ lPaquet[curseur].lg_info;
            lPaquet[curseur].somme_ctrl = sum;

            printf("[EN] Envoi du paquet numero %d\n\n", curseur);
            vers_reseau(&lPaquet[curseur]);
            if (curseur == borne_inf) {
                depart_temporisateur(0, 50);
            }
            curseur = (curseur + 1) % 8;
        } else {
            /* Tant qu'on ne reçoit pas l'acquittement */
            int evt = attendre();
            if(evt == -1) {
                printf("[RE] Reception d'un paquet !\n\n");
                paquet_t ack;
                de_reseau(&ack);
                uint8_t ctrl = ack.num_seq ^ ack.type ^ ack.lg_info;
                lg_recepteur = ack.lg_info;
                if(dans_fenetre(borne_inf, ack.num_seq, taille_fenetre) && ack.somme_ctrl == ctrl) {
                    printf("[RE] Reception du paquet numero %d !\n\n", ack.num_seq);
                    borne_inf = (ack.num_seq+1)%8;
                    if(curseur == borne_inf) {
                        arreter_temporisateur(0);
                    }
                }
            } else {
                printf("[TO] Timeout !\n\n");
                int i = borne_inf;
                depart_temporisateur(0, 50);
                while(i != curseur) {
                    printf("[TO] Envoi du paquet numero %d\n\n", i);
                    vers_reseau(&lPaquet[i]);
                    i = (i + 1) % 8;
                }
            }
        }
        //printf("\n\n[INFO] TAILLE MSG : %d", taille_msg);
    }

    printf("\n\n[TRP] Fin execution protocole transfert de donnees (TDD).\n");
    return 0;
}
