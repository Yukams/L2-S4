/*************************************************************
* proto_tdd_v2 -  émetteur                                   *
* TRANSFERT DE DONNEES  v02                                  *
*                                                            *
* Transfert de donnees avec controle de flux et reprise sur  *
* erreur "Stop-and-Wait"                                     *
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
    int taille_msg; /* taille du message */
    paquet_t paquet; /* paquet utilisé par le protocole */
    uint8_t sum; /* verification xor */
    uint8_t num_seq = 0;

    init_reseau(EMISSION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* lecture de donnees provenant de la couche application */
    de_application(message, &taille_msg);

    /* tant que l'émetteur a des données à envoyer */
    while ( taille_msg != 0 ) {
        sum = 0;

        /* construction paquet */
        for (int i=0; i<taille_msg; i++) {
            paquet.info[i] = message[i];
            sum = sum^paquet.info[i];
        }
        paquet.lg_info = taille_msg;
        paquet.type = DATA;
        paquet.num_seq = num_seq;

        /* Verifications */
        sum = sum^paquet.type^num_seq^paquet.lg_info;
        paquet.somme_ctrl = sum;

        int reponse = -2;
        /* Tant qu'on ne reçoit pas l'acquittement */
        while(reponse != -1) {
            /* remise à la couche reseau */
            printf("\nEnvoi du paquet numero %d\n", num_seq);
            vers_reseau(&paquet);
            depart_temporisateur(0, 150);

            /* Attente du paquet de reception */
            reponse = attendre();

            if(reponse != 0) {
                arreter_temporisateur(0);
                paquet_t ack;
                de_reseau(&ack);

                uint8_t ctrl = num_seq ^ ack.type ^ ack.lg_info;
                if(ack.somme_ctrl == ctrl) {
                    /* lecture des donnees suivantes de la couche application */
                    de_application(message, &taille_msg);
                    num_seq++;
                }
            }

        }







    }

    printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
    return 0;
}
