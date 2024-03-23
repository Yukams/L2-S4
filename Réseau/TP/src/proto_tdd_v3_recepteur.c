/*************************************************************
* proto_tdd_v3 -  récepteur                                  *
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
/* Programme principal - récepteur */
/* =============================== */
int main(int argc, char* argv[])
{
    unsigned char message[MAX_INFO]; /* message pour l'application */
    paquet_t paquet; /* paquet utilisé par le protocole */
    int fin = 0; /* condition d'arrêt */
    uint8_t sum; /* verification xor */
    uint8_t num_seq = 0;
    paquet_t controle;
    controle.type = ACK;

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
    while ( !fin ) {
        printf("\n\n\n\n");
        de_reseau(&paquet);
        printf("[RE] Reception du paquet numero %d\n\n", paquet.num_seq);
        if(paquet.num_seq == num_seq) {
            sum = 0;

            /* extraction des donnees du paquet recu */
            for (int i = 0; i < paquet.lg_info; i++) {
                message[i] = paquet.info[i];
                sum = sum ^ message[i];
            }

            sum = sum ^ paquet.type ^ paquet.num_seq ^ paquet.lg_info;

            // Envoie un accusé de réception du paquet
            if (paquet.somme_ctrl == sum) {
                paquet_t controle;
                controle.type = ACK;
                controle.num_seq = num_seq;

                /* remise des données à la couche application */
                fin = vers_application(message, paquet.lg_info);
                controle.lg_info = fin;

                controle.somme_ctrl = controle.num_seq ^ controle.type ^ controle.lg_info;
                printf("[SE] Envoi de l'ACK numéro %d\n\n", num_seq);
                vers_reseau(&controle);

                num_seq = (num_seq+1)%8;
            }
        } else {
            printf("\x1B[31mERREUR PAQUET\x1B[37m\n\n");
            printf("[SE] Envoi de l'ACK numéro %d\n\n", (num_seq+7)%8);
            paquet_t controle;
            controle.type = ACK;
            controle.num_seq = (num_seq+7)%8;

            /* remise des données à la couche application */
            controle.lg_info = fin;

            controle.somme_ctrl = controle.num_seq ^ controle.type ^ controle.lg_info;
            vers_reseau(&controle);
        }
    }

    printf("\n[TRP] Fin execution protocole transport.\n\n");
    return 0;
}
