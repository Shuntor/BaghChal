#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  
#include <string.h>  

#include "plateau.h" 

struct Case_D {
  Element e ;
  struct Case_D * suivant ;
} ;


struct Plateau_D {
    Case debut;
} ;

Plateau creerPLateau() {
  Plateau p = (Plateau) malloc (sizeof(struct Plateau_D));
  placerTigres(p);
  return p;  
}

void afficher_plateau_test(Plateau p) {
  if( p->debut != NULL ) {
    Case tmp = p->debut ;
    do {
      afficherElementTest(tmp->e) ;
      tmp = tmp->suivant ;
    } while ( tmp != NULL ) ;
  } else {
    printf("Liste vide \n") ;
  }
}

void placerTigres(Plateau p) {
  Element e = creerTigre(0,0);
  ajouter(p, e);
  e = creerTigre(0,4);
  ajouter(p, e);
  e = creerTigre(4,0);
  ajouter(p, e);
  e = creerTigre(4,4);
  ajouter(p, e);
} 

void placerChevre(Plateau p, int posX, int posY) {
  Element e = creerChevre(posX,posY);
  ajouter(p,e);
}

void ajouter(Plateau p, Element el) {
  Case add = (Case) malloc(sizeof(struct Case_D));
  add->e = el ;
  if( p->debut != NULL ) {
    Case tmp = p->debut ;
    if (plusGrand_E(tmp->e,el)) {
      add->suivant = tmp ;
      p->debut = add ;
    } else {
      while ( tmp->suivant != NULL && !(plusGrand_E(tmp->suivant->e,el))) {
        tmp = tmp->suivant ;
      }
      add->suivant = tmp->suivant ;
      tmp->suivant = add ;
    }
  } else {
    add->suivant = NULL ;
    p->debut = add;
  }
}

int positionDejaPrise (Plateau p, int posX, int posY) {
  Case tmp = p->debut ;
    if (plusGrand_P(tmp->e, posX, posY)) {
      return 0;
    } else {
      while ( tmp->suivant != NULL && !(plusGrand_P(tmp->suivant->e,posX,posY))) {
        tmp = tmp->suivant ;
      }
      if (positionEgale(tmp->e, posX, posY)) {
	if (estChevre(tmp->e)) {
	  return 1 ;
	} else {
	  return 2 ;
	}
      } 
      return 0 ;
    }
}
int main() {
  Plateau p = creerPLateau() ;
  afficher_plateau_test(p);
  return (0);
}
/*
void deplacementTigre(Element e, int newX, */