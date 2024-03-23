/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Mathias Paulin (Mathias.Paulin@irit.fr)
 
 Implantation du TAD List vu en cours.
 */
/*-----------------------------------------------------------------*/
#include <stdio.h>
#
#include <stdlib.h>
#include <assert.h>

#include "list.h"

typedef struct s_LinkedElement {
	int value;
	struct s_LinkedElement *previous;
	struct s_LinkedElement *next;
} LinkedElement;

/* Use of a sentinel for implementing the list :
 The sentinel is a LinkedElement * whose next pointer refer always to the head of the list and previous pointer to the tail of the list
 */
struct s_List {
	LinkedElement *sentinel;
	int size;
};

typedef struct s_subList {
    LinkedElement *tete;
    LinkedElement *queue;
    int size;
} SubList;


/*-----------------------------------------------------------------*/

List *list_create() {
    List *l = malloc(sizeof(struct s_List));
    if(l == NULL) {
        printf("ERREUR : Allocation mémoire échouée\n");
    }
    LinkedElement *s = malloc(sizeof(struct s_LinkedElement));
    s->previous = s->next = s;
    l->sentinel = s;
    l->size = 0;
	return l;
}

/*-----------------------------------------------------------------*/

List *list_push_back(List *l, int v) {
    LinkedElement *e = malloc(sizeof(struct s_LinkedElement));
    e->value = v;
    e->previous = l->sentinel->previous;
    e->next = l->sentinel;
    e->previous->next = e;
    l->sentinel->previous = e;

	l->size += 1;
	return l;
}

/*-----------------------------------------------------------------*/

void list_delete(ptrList *l) {
    free(*l);
    *l = NULL;
}

/*-----------------------------------------------------------------*/

List *list_push_front(List *l, int v) {
    LinkedElement *e = malloc(sizeof(struct s_LinkedElement));
    e->value = v;
    e->next = l->sentinel->next;
    e->previous = l->sentinel;
    e->next->previous = e;
    l->sentinel->next = e;

    l->size += 1;
    return l;
}

/*-----------------------------------------------------------------*/

int list_front(List *l) {
    assert(list_is_empty(l));
	return l->sentinel->next->value;
}

/*-----------------------------------------------------------------*/

int list_back(List *l) {
    assert(list_is_empty(l));
	return l->sentinel->previous->value;
}

/*-----------------------------------------------------------------*/

List *list_pop_front(List *l) {
    assert(list_is_empty(l));
    l->sentinel->next = l->sentinel->next->next;
    l->size--;
	return l;
}

/*-----------------------------------------------------------------*/

List *list_pop_back(List *l){
    assert(list_is_empty(l));
    l->sentinel->previous = l->sentinel->previous->previous;
    l->size--;
	return l;
}

/*-----------------------------------------------------------------*/

List *list_insert_at(List *l, int p, int v) {
    LinkedElement *ptr = l->sentinel->next;
    for(int i = 0; i < p-1; i++) {
        ptr = ptr->next;
    }

    LinkedElement *e = malloc(sizeof(struct s_LinkedElement));
    e->value = v;
    e->next = ptr->next;
    e->previous = ptr;
    ptr->next = e;
    e->next->previous = e;

    l->size += 1;
    return l;
}

/*-----------------------------------------------------------------*/

List *list_remove_at(List *l, int p) {
    LinkedElement *ptr = l->sentinel->next;
    for(int i = 0; i < p; i++) {
        ptr = ptr->next;
    }
    ptr->next->previous = ptr->previous;
    ptr->previous->next = ptr->next;
    l->size--;
    return l;
}

/*-----------------------------------------------------------------*/

int list_at(List *l, int p) {
    LinkedElement *ptr = l->sentinel->next;
    for(int i = 0; i < p; i++) {
        ptr = ptr->next;
    }
    return ptr->value;
}

/*-----------------------------------------------------------------*/

bool list_is_empty(List *l) {
	if(l->size == 0) {return 0;}
	return 1;
}

/*-----------------------------------------------------------------*/

int list_size(List *l) {
	return l->size;
}

/*-----------------------------------------------------------------*/

List * list_map(List *l, SimpleFunctor f) {
    LinkedElement *ptr = l->sentinel->next;
	for(int i = 0; i < l->size; i++) {
        ptr->value = f(ptr->value);
        ptr = ptr->next;
	}
	return l;
}


List *list_reduce(List *l, ReduceFunctor f, void *userData) {
    LinkedElement *ptr = l->sentinel->next;
    for(int i = 0; i < l->size; i++) {
        ptr->value = f(ptr->value, userData);
        ptr = ptr->next;
    }
    return l;
}

/*-----------------------------------------------------------------*/
SubList subList_create() {
    SubList *l = malloc(sizeof(struct s_subList));
    if(l == NULL) {
        printf("ERREUR : Allocation mémoire échouée\n");
    }
    l->tete = l->queue = NULL;
    l->size = 0;
    return l;
}

SubList subList_push(SubList *l, int v) {
    LinkedElement *e = malloc(sizeof(struct s_LinkedElement));
    e->value = v;
    if(!list_is_empty(l)) {
        e->previous = l->queue;
        l->queue->next = e;
        l->queue = e;
    } else {
        l->queue = l->tete = e;
    }

    l->size++;
    return l;
}


SubList list_split(SubList *l) {
    int i = 0;
    SubList *result = subList_create();
    SubList *subLeft = subList_create();
    SubList *subRight = subList_create();
    LinkedElement *ptr = l->tete;
    while (i < l->size/2) {
        subList_push(subLeft, ptr->value);
        ptr = ptr->next;
        i++;
    }
    result->tete = subLeft->queue;

    ptr = ptr->next;
    subList_push(subRight, ptr->value);
    result->queue = subRight->tete;
    i++;

    while (i < l->size) {
        subList_push(subRight, ptr->value);
        ptr = ptr->next;
        i++;
    }

    result->size = l->size/2;
    return result;
}


SubList list_merge(SubList leftlist, SubList rightlist, OrderFunctor f) {
    SubList *result = subList_create();
    if(f(leftlist, rightlist)) {

    }
}


SubList list_mergesort(SubList l, OrderFunctor f) {
    SubList *split = list_split(l);
    if(split->size != 1) {
        list_mergesort(l)
    } else {
        return list_merge(l->queue, l->tete);
    }
}


List *list_sort(List *l, OrderFunctor f) {
    SubList *sub = malloc(sizeof(struct s_subList));
    sub->size = l->size;
    sub->queue = l->sentinel->previous;
    sub->tete = l->sentinel->next;
    list_split(sub);
	return l;
}


