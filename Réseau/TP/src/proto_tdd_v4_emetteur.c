/*************************************************************
* proto_tdd_v4 -  émetteur                                   *
* TRANSFERT DE DONNEES  v04                                  *
*                                                            *
* Transfert de données avec fenêtre d’anticipation et        *
* reprise sur erreurs "Selective Repeat"                     *
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
    while ( taille_msg != 0 && lg_recepteur != 0 ) {
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

            // Envoi du paquet
            printf("[EN] Envoi du paquet numero %d\n\n", curseur);
            vers_reseau(&lPaquet[curseur]);
            depart_temporisateur(curseur, 50);
            curseur = (curseur + 1) % 8;
        } else {
            /* Tant qu'on ne reçoit pas l'acquittement */
            int evt = attendre();
            if(evt == -1) {
                // Reception paquet
                printf("[RE] Reception d'un paquet !\n\n");
                paquet_t ack;
                de_reseau(&ack);
                uint8_t ctrl = ack.num_seq ^ ack.type ^ ack.lg_info;

                // Le recepteur envoie ce type de paquet avant de se terminer
                // Permet donc d'arrêter l'emetteur
                if(ack.type == OTHER) {
                    lg_recepteur = 0;
                }

                // Si paquet sans erreur
                if(dans_fenetre(borne_inf, ack.num_seq, taille_fenetre) && ack.somme_ctrl == ctrl) {
                    printf("[RE] Reception du paquet numero %d !\n\n", ack.num_seq);
                    arreter_temporisateur(ack.num_seq);
                    // Remplacer le paquet par le paquet reçu
                    lPaquet[ack.num_seq] = ack;
                    // incrémente borne_inf
                    while(lPaquet[borne_inf].type == ACK) {
                        lPaquet[borne_inf].type = NACK;
                        borne_inf = (borne_inf + 1) % 8;
                    }
                }
            } else {
                // renvoi si timeout
                printf("[TO] Timeout du temporisateur numero %d !\n\n", evt);
                printf("\n\n[INFO] TAILLE MSG : %d", lPaquet[evt].lg_info);
                vers_reseau(&lPaquet[evt]);
                depart_temporisateur(evt, 50);
            }
        }

    }

    printf("\n\n[TRP] Fin execution protocole transfert de donnees (TDD).\n");
    return 0;
}
