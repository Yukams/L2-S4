#ifndef __COUCHE_TRANSPORT_H__
#define __COUCHE_TRANSPORT_H__

#include <stdint.h> /* uint8_t */
#define MAX_INFO 96

/*************************
 * Structure d'un paquet *
 *************************/

typedef struct paquet_s {
    uint8_t type;         /* type de paquet, cf. ci-dessous */
    uint8_t num_seq;      /* numéro de séquence */
    uint8_t lg_info;      /* longueur du champ info */
    uint8_t somme_ctrl;   /* somme de contrôle */
    unsigned char info[MAX_INFO];  /* données utiles du paquet */
} paquet_t;

/******************
 * Types de paquet *
 ******************/
#define DATA          1  /* données de l'application */
#define ACK           2  /* accusé de réception des données */
#define NACK          3  /* accusé de réception négatif */
#define OTHER         4  /* extensions */

/* Capacite de numerotation */
#define SEQ_NUM_SIZE 8

/* ************************************** */
/* Fonctions utilitaires couche transport */
/* ************************************** */

// TODO...

/*--------------------------------------*
 * Fonction d'inclusion dans la fenetre *
 *--------------------------------------*/
int dans_fenetre(unsigned int inf, unsigned int pointeur, int taille);

#endif
