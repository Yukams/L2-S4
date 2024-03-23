/*************************************************************
* proto_tdd_v2 -  récepteur                                  *
* TRANSFERT DE DONNEES  v02                                  *
*                                                            *
* Transfert de donnees avec controle de flux et reprise sur  *
* erreur "Stop-and-Wait"                                     *
**************************************************************/

#include <stdio.h>
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

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
    while ( !fin ) {
        de_reseau(&paquet);
        printf("Reception du paquet numero %d\n", paquet.num_seq);
        if(paquet.num_seq == num_seq-1) {
            paquet_t controle;
            controle.type = ACK;
            controle.lg_info = 0;
            controle.somme_ctrl = num_seq-1 ^ controle.type ^ controle.lg_info;
            vers_reseau(&controle);
        } else if(paquet.num_seq == num_seq) {
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
                controle.lg_info = 0;
                controle.somme_ctrl = num_seq ^ controle.type ^ controle.lg_info;
                vers_reseau(&controle);

                /* remise des données à la couche application */
                fin = vers_application(message, paquet.lg_info);
                num_seq++;
            }
        } else {
            printf("\x1B[31mERREUR PAQUET\n\n\x1B[37m");
        }
    }

    printf("[TRP] Fin execution protocole transport.\n");
    return 0;
}
