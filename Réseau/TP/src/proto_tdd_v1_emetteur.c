//
// Created by Valentin
//

/*************************************************************
* proto_tdd_v1 -  émetteur                                   *
* TRANSFERT DE DONNEES  v01                                  *
*                                                            *
* Transfert de donnees avec detection d’erreurs et controle  *
* de flux "Stop-and-Wait"                                    *
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
        num_seq++;

        /* remise à la couche reseau */
        vers_reseau(&paquet);

        /* Attente du paquet de reception */
        paquet_t ack;
        //printf("[TRP] En attente de l'accusé de réception du paquet.\n");
        de_reseau(&ack);
        //printf("[TRP] Accusé de réception reçu.\n");
        printf("Type de reception : %d\n", ack.type);

        /* lecture des donnees suivantes de la couche application */
        de_application(message, &taille_msg);
    }

    printf("[TRP] Fin execution protocole transfert de donnees (TDD).\n");
    return 0;
}
