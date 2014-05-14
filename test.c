
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  

#include "partie.h" 
#include "plateau.h" 

int main(void) {
  Plateau p = creerPLateau() ;
  Partie jeu = creerPartie();
  plateauDepard(p);
  placerChevre(p,0,0);
  placerChevre(p,0,1) ;
  placerChevre(p, 4,4) ;
  deplacementChevre(p, 0,2,0,1) ; 
  deplacementTigre(p,0,0,4,4) ;
  
  suppression(p,4,4);

  /* deplacementChevreTest(p, 0,3,0,2) ;
  deplacementChevreTest(p, 0,3,0,2) ;
  deplacementChevreTest(p, 0,2,0,1) ; 
  afficherPlateau_test(p);
  
  printf("\n");
  deplacementTigreTest(p, 0,0,0,1) ; 
  deplacementTigreTest(p, 0,0,0,2) ;
  afficherPlateau_test(p);
  


  deplacementPossibleTous(p); 
  printf("%d ", abs(-10));
  printf("%d",deplacementPossible_1(p,0,0,1,1));
  printf("%d",deplacementPossible_1(p,2,2,3,3));*/
  
  // printf("-%d-",deplacementChevre(p, 2, 2, 2, 1)) ;
  // printf("-%d-",deplacementTigre(p, 0, 0, 0, 1)) ;
  setPlateau(jeu, p);
  affPTEST (getPlateau(jeu)) ;
  printf("-%d-", gagnant( p) );

  

  return (0);
}