//
// Created by Valentin
//

/*************************************************************
* proto_tdd_v1 -  récepteur                                  *
* TRANSFERT DE DONNEES  v01                                  *
*                                                            *
* Transfert de donnees avec detection d’erreurs et controle  *
* de flux "Stop-and-Wait"                                    *
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

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
    while ( !fin ) {
        //printf("[TRP] En attente d'émission du paquet.\n");
        de_reseau(&paquet);
        //printf("[TRP] Paquet reçu.\n");

        sum = 0;
        sum = sum^paquet.type^paquet.num_seq^paquet.lg_info;

        /* extraction des donnees du paquet recu */
        for (int i=0; i<paquet.lg_info; i++) {
            message[i] = paquet.info[i];
            sum = sum^message[i];
        }

        // Envoie un accusé de réception du paquet
        paquet_t controle;
        //printf("Controle = %d ||| Sum = %d\n", paquet.somme_ctrl, sum);
        if(paquet.somme_ctrl == sum) {
            controle.type = ACK;
        }
        else {
            controle.type = NACK;
        }
        //printf("[TRP] Envoi d'un accusé de reception.\n");
        vers_reseau(&controle);

        /* remise des données à la couche application */
        fin = vers_application(message, paquet.lg_info);
    }

    printf("[TRP] Fin execution protocole transport.\n");
    return 0;
}
