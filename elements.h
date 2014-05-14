
#ifndef _ELEMENTS_H
#define _ELEMENTS_H
#define TIGRE 1
#define CHEVRE 0
typedef struct Element_D * Element ;

//----------------------------------------------------------------- CREATION 

Element creerTigre(int posX, int posY) ;
Element creerChevre(int posX, int posY) ;

//----------------------------------------------------------------- GETTEUR

int   estChevre(Element e) ;
int   getPosX(Element e) ;
int   getPosY(Element e) ;
      
//----------------------------------------------------------------- AFFICHAGE 

void  afficherElementTest(Element e) ;
      
#endif
 