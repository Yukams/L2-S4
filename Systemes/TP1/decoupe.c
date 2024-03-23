#include "decoupe.h"
#define NBMOTSMAX 20
/* Construction d'un tableau de pointeurs vers le d�but des mots d'une chaine
 * de caract�res en vue de l'utilisation de la fonction execvp.
 * Retourne le nombre de mots trouves.
 */
int Decoupe(char Chaine[], char *pMots[])
{
  char *p;
  int NbMots=0;

  p=Chaine; /* On commence par le d�but */
  /* Tant que la fin de la cha�ne n'est pas atteinte et qu'on ne d�borde pas */
  while ((*p)!='\0' && NbMots<NBMOTSMAX)
  {
    while ((*p)==' ' && (*p)!='\0') p++; /* Recherche du d�but du mot */
    if ((*p)=='\0') break; /* Fin de cha�ne atteinte */
    pMots[NbMots++]=p; /* Rangement de l'adresse du 1er caract�re du mot */
    while ((*p)!=' ' && (*p)!='\0') p++; /* Recherche de la fin du mot */
    if ((*p)=='\0') break; /* Fin de cha�ne atteinte */
    *p='\0'; /* Marquage de la fin du mot */
    p++; /* Passage au caract�re suivant */
  }
  pMots[NbMots]=0; /* Derni�re adresse */
  return NbMots;
}

