#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  
#include <string.h>  

#include "elements.h" 


struct Element_D {
  int type ;
  int posX ;
  int posY ;
} ;

//----------------------------------------------------------------- CREATION 

Element creerTigre(int posX, int posY) {
  Element e = (Element) malloc (sizeof(struct Element_D));
  e->type = TIGRE;
  e->posX = posX ;
  e->posY = posY ;
  return e;
}

Element creerChevre(int posX, int posY) {
  Element e = (Element) malloc (sizeof(struct Element_D));
  e->type = CHEVRE ;
  e->posX = posX ;
  e->posY = posY ;
  return e;
}

//----------------------------------------------------------------- GETTEUR

int estChevre(Element e) {
  return (e->type == CHEVRE);
}

int getPosX(Element e) {
  return e->posX;
}

int getPosY(Element e) {
  return e->posY;
}
           
//----------------------------------------------------------------- AFFICHAGE 

void afficherElementTest(Element e) {
  printf("%d (%d,%d) \n", e->type, e->posX, e->posY);
}