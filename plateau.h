
#ifndef _PLATEAU_H_
#define _PLATEAU_H_


#include "elements.h" 

typedef struct Case_D * Case ;
typedef struct Plateau_D * Plateau ;

Plateau creerPLateau();
void afficherTableau();
void placerTigres(Plateau p) ;
void placerChevre(Plateau p, int posX, int posY);
void ajouter(Plateau p, Element e) ;

#endif
 