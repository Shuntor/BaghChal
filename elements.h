
#ifndef _ELEMENTS_H
#define _ELEMENTS_H



typedef struct Element_D * Element ;


Element creerTigre(int posX, int posY) ;
Element creerChevre(int posX, int posY) ;
int estChevre(Element e) ;
int plusGrand_E(Element e1, Element e2) ;
int plusGrand_P(Element e1, int posX, int posY) ;
void afficherElementTest(Element e);
int positionEgale(Element e, int posX, int posY) ;
      
#endif
 