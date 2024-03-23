/*************************************************************
* proto_tdd_v4 -  récepteur                                  *
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
/* Programme principal - récepteur */
/* =============================== */
int main(int argc, char* argv[])
{
    unsigned char message[MAX_INFO]; /* message pour l'application */
    paquet_t paquet; /* paquet utilisé par le protocole */
    int fin = 0; /* condition d'arrêt */
    uint8_t sum; /* verification xor */
    paquet_t controle;
    controle.type = ACK;
    paquet_t lPaquet[8];

    for(int i = 0; i < 8; i++) {
        lPaquet[i].type = NACK;
    }

    paquet_t end;
    end.num_seq = -1;
    end.type = OTHER;
    int num_seq = 0;
    int nb_pac = 0;
    int taille_fenetre = 4;

    init_reseau(RECEPTION);

    printf("[TRP] Initialisation reseau : OK.\n");
    printf("[TRP] Debut execution protocole transport.\n");

    /* tant que le récepteur reçoit des données */
    while ( !fin ) {
        printf("\n\n\n\n");
        de_reseau(&paquet);
        printf("[RE] Reception du paquet numero %d\n\n", paquet.num_seq);
        sum = 0;

        /* extraction des donnees du paquet recu */
        for (int i = 0; i < paquet.lg_info; i++) {
            message[i] = paquet.info[i];
            sum = sum ^ message[i];
        }

        sum = sum ^ paquet.type ^ paquet.num_seq ^ paquet.lg_info;

        // Envoie un accusé de réception du paquet
        if (paquet.somme_ctrl == sum) {
            // Envoi de l'ack de reception du paquet
            paquet_t controle;
            controle.type = ACK;
            controle.num_seq = paquet.num_seq;

            controle.somme_ctrl = controle.num_seq ^ controle.type ^ controle.lg_info;
            printf("[SE] Envoi de l'ACK numéro %d\n\n", paquet.num_seq);
            vers_reseau(&controle);


            if(num_seq == paquet.num_seq) {
                /* remise des données à la couche application */
                fin = vers_application(message, paquet.lg_info);
                controle.lg_info = fin;

                num_seq = (num_seq + 1) % 8;

                int i = 0;

                while (i < nb_pac && lPaquet[(num_seq + i)%8].type == DATA) {
                    paquet_t buffer = lPaquet[(num_seq + i)%8];
                    for (int j = 0; j < buffer.lg_info; j++) {
                        message[j] = buffer.info[j];
                    }
                    printf("[WR] Write packet numero %d\n\n", (num_seq + i)%8);
                    fin = vers_application(message, buffer.lg_info);

                    lPaquet[(num_seq + i)%8].type = NACK;
                    i++;
                }
                nb_pac -= i;
                num_seq = (num_seq + i) % 8;
            } else if (dans_fenetre(num_seq, paquet.num_seq, taille_fenetre)){
                lPaquet[paquet.num_seq] = paquet;
                printf("[KP] Keep packet numero %d\n\n", paquet.num_seq);
                nb_pac += 1;
            }
        } else {
            printf("\x1B[31mERREUR PAQUET\x1B[37m\n\n");
        }
    }

    // Dis à l'emetteur qu'il peut s'arrêter
    for(int i = 0 ; i < 3; i++) {
        vers_reseau(&end);
    }
    printf("\n[TRP] Fin execution protocole transport.\n\n");
    return 0;
}
