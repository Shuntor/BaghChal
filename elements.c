#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  
#include <string.h>  

#include "elements.h" 

struct Element_D {
  char type ;
  int posX ;
  int posY ;
} ;

Element creerTigre(int posX, int posY) {
  Element e = (Element) malloc (sizeof(struct Element_D));
  e->type = 't';
  e->posX = posX ;
  e->posY = posY ;
  return e;
}


Element creerChevre(int posX, int posY) {
  Element e = (Element) malloc (sizeof(struct Element_D));
  e->type = 'c' ;
  e->posX = posX ;
  e->posY = posY ;
  return e;
}

int plusGrand_E(Element e1, Element e2) {
  if (e1->posX > e2->posX) {
    return 1 ;
  } else {
    if (e1->posX < e2->posX) {
      return 0 ;
    } else {
      return (e1->posY > e2->posY) ;
    }
  }
}

int estChevre(Element e) {
  return (e->type == 'c' );
}
      
int plusGrand_P(Element e1, int posX, int posY) {
  if (e1->posX > posX) {
    return 1 ;
  } else {
    if (e1->posX < posX) {
      return 0 ;
    } else {
      return (e1->posY > posY) ;
    }
  }
}
      
int positionEgale(Element e, int posX, int posY) {
  return (e->posX == posX && e->posY == posY) ;
}
      
void afficherElementTest(Element e) {
  printf("%c (%d,%d) \n", e->type, e->posX, e->posY);
}