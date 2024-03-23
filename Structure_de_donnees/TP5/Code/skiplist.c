#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "skiplist.h"
#include "rng.h"

typedef struct s_Node {
    int value;
    unsigned int level;
    struct s_Node** prev;
    struct s_Node** next;
} * Node;

struct s_SkipList {
    unsigned int size;
    Node sentinel;
    int nbLevels;
    RNG rng;
};


SkipList skiplist_create(int nblevels) {
    SkipList list = malloc(sizeof(struct s_SkipList));
    list->size = 0;
    list->sentinel = malloc(sizeof(Node));
    list->sentinel->prev = malloc(nblevels * sizeof(Node));
    list->sentinel->next = malloc(nblevels * sizeof(Node));
    list->nbLevels = nblevels;
    list->rng = rng_initialize(0);

    for (int level = 0; level < nblevels; level++){
        list->sentinel->prev[level] = list->sentinel;
        list->sentinel->next[level] = list->sentinel;
    }

    return list;
}


void skiplist_delete(SkipList d) {
    Node del = d->sentinel->next[0];

    while(del != d->sentinel){
        Node end = del;

        del = del->next[0];
        free(end->next);
        free(end->prev);
        free(end);
    }
    free(d->sentinel->next);
    free(d->sentinel->prev);
    free(d->sentinel);
    free(d);
}

unsigned int skiplist_size(SkipList d) {
    return d->size;
}

int skiplist_ith(SkipList d, unsigned int i) {
    assert(i < d->size);
    Node elem = d->sentinel;
    while (i != 0){
        elem = elem->next[0];
        i--;
    }
    return elem->value;
}

void skiplist_map(SkipList d, ScanOperator f, void *user_data) {
    for (Node n = d->sentinel->next[0]; n != d->sentinel; n = n->next[0]) {
        f(n->value, user_data);
    }
}

/*
SkipList skiplist_insert(SkipList d, int value) {
    Node *t = malloc(sizeof(Node) * d->nbLevels);

    for (int i = d->nbLevels - 1; i >= 0; i--) {
        while (d->sentinel->next[i]->value < value) {
            d->sentinel = d->sentinel->next[i];
        }
        t[i] = d->sentinel;
    }

    d->sentinel = d->sentinel->next[0];

    // Si la valeur n'existe pas
    if (d->sentinel->value != value){
        Node new = malloc(sizeof(Node));
        new->level = rng_get_value(&d->rng, d->nbLevels - 1) + 1;
        new->next = malloc(sizeof(Node) * new->level);
        new->prev = malloc(sizeof(Node) * new->level);
        new->value = value;
        for (int i = new->level-1; i >= 0; i--) {
            new->prev[i] = t[i];
            new->next[i] = t[i]->next[i];
            new->prev[i]->next[i] = new;
            new->next[i]->prev[i] = new;
        }
        d->size++;
    }

    d->sentinel->value=-1;
    free(t);
    return d;
}
*/

/*
SkipList skiplist_insert(SkipList d, int value) {
    Node *tab = malloc(sizeof(Node)*d->nbLevels);
    d->sentinel->value = value+1;
    Node sentinel = d->sentinel;
    printf("ok0");
    for (int i = d->nbLevels-1; i >= 0; i--) {
        printf("ok1");
        while (sentinel->next[i]->value < value) {
            printf("ok2");
            sentinel = sentinel->next[i];
        }
        tab[i] = sentinel;
    }
    sentinel = sentinel->next[0];
    if (sentinel->value != value) {
        Node new = malloc(sizeof(Node));
        new->level = rng_get_value(&d->rng,d->nbLevels-1)+1;
        new->next = malloc(sizeof(Node)*new->level);
        new->prev = malloc(sizeof(Node)*new->level);
        new->value = value;
        for (int i = new->level-1; i >= 0; i--) {
            new->prev[i] = tab[i];
            new->next[i] = tab[i]->next[i];
            new->prev[i]->next[i] = new;
            new->next[i]->prev[i] = new;
        }
        new->prev[0] = tab[0];
        d->size++;
    }
    d->sentinel->value = -1;
    free(tab);
    return d;
}*/

/*
SkipList skiplist_insert(SkipList d, int value) {
    Node current = d->sentinel;
    Node futurs_voisins[d->nbLevels];

    Node prochain_noeud;

    for (int lvl = d->nbLevels-1; lvl >= 0; lvl--){
        prochain_noeud = current->next[lvl];
        while(prochain_noeud != d->sentinel && prochain_noeud->value < value){
            prochain_noeud = current->next[lvl];
        }
        futurs_voisins[lvl] = prochain_noeud;
    }
    return d;
}
*/

/*
SkipList skiplist_insert(SkipList d, int value) {
    int lvl = rng_get_value(&d->rng, d->nbLevels-1)+1;
    Node *tab = malloc(sizeof(Node) * lvl);
    Node courant = d->sentinel;

    for(int i = 0; i < lvl; i++) {
        courant = courant->next[lvl];

        while(courant->value < value && courant != d->sentinel) {
            courant =
        }
    }

}*/

/*
tu cree le level avec rng là
        tu cree un tab de Node de taille level

for(chaque level)
courant = next[lvl]
while(courant next < value && != sentinel)
courant = next
inserer courant dans tab

si valeur deja dans skiplist
return

sinon
        creer node
for(chaque level)
tu relis avec cque t'as gardé dans le tab

size++*/



SkipList skiplist_insert(SkipList d, int value) {
    Node current = d->sentinel;

    Node futurs_voisins[d->nbLevels];

    Node prochain_noeud;

    for (int lvl = d->nbLevels-1; lvl >= 0; lvl--){
        prochain_noeud = current->next[lvl];

        while(prochain_noeud!=d->sentinel && prochain_noeud->value<value){
            current=prochain_noeud;
            prochain_noeud = current->next[lvl];
        }
        futurs_voisins[lvl] = prochain_noeud;
    }

    if (current->next[0]->value != value){
        int niveau = rng_get_value(&d->rng, d->nbLevels-1)+1;
        Node newNoeud = malloc(sizeof(Node)*niveau);
        newNoeud->value = value;
        newNoeud->level = niveau;
        newNoeud->prev = malloc(niveau * sizeof(struct s_Node));
        newNoeud->next = malloc(niveau * sizeof(struct s_Node));

        for (int i=0;i<niveau;i++){
            newNoeud->prev[i] = futurs_voisins[i]->prev[i];
            newNoeud->prev[i]->next[i] = newNoeud;
            newNoeud->next[i] = futurs_voisins[i];
            newNoeud->next[i]->prev[i] = newNoeud;
        }
        d->size ++;
    }
    return d;
}
