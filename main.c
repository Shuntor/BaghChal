
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  

#include "partie.h" 
#include "plateau.h" 


int test_placement_deplacement () {
  Plateau p = creerPLateau() ;
  plateauDepard(p);
  int ok = 0;
  
  printf("\n----- PLACEMENTS CHEVRES ---- \n") ;
  
  printf("Placements hors champs : ");
  if( !placerChevre(p, -1, 4) && !placerChevre(p, 2, 40)) { 
    ok++;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }    

  printf("Placements déjà pris : ");
  if( !placerChevre(p, 0, 0) && !placerChevre(p, 4, 0)) { 
    ok++;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }
  
  printf("Placements corrects : ") ;
  if( placerChevre(p, 4, 1) && estChevre(getElement(p, 4, 1)) && placerChevre(p, 2, 2) && estChevre(getElement(p, 2, 2))) { 
    ok++;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }
  
  printf("\n----- DEPLACEMENTS CHEVRES ---- \n") ;
      
  printf("Position initiale inexistante : ") ;
  if( !deplacementChevre(p, -1, 4, 2, 1) && !deplacementChevre(p, 2, 40, 2, 1)) { 
    ok++;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }
  
  printf("Position initiale vide ou occuppé par un tigre : ") ;
  if( !deplacementChevre(p, 0, 0, 2,1) && !deplacementChevre(p, 1, 1, 2, 1)) { 
    ok++;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }
  
  printf("Position finale inexistante : ") ;
  if( !deplacementChevre(p, 4, 1, -1,1) && !deplacementChevre(p, 2, 2, 0, 40)) { 
    ok++;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }
  
  printf("Position finale impossible d'accee direct : ") ;
  if( !deplacementChevre(p, 4, 1, 3, 0) && !deplacementChevre(p, 4, 1, 4, 3)  && !deplacementChevre(p, 2, 2, 0, 2)) { 
    ok++;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }
 
  printf("Position finale deja prise : ") ;
  if( !deplacementChevre(p, 4, 1, 4, 0)) { 
    ok++;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }
  
  printf("Deplacements corrects : ") ;
  if( deplacementChevre(p, 4, 1, 4, 2) && estChevre(getElement(p, 4, 2)) && positionDejaPrise(p, 4, 1) == -1 && deplacementChevre(p, 2, 2, 3, 3) && estChevre(getElement(p, 3, 3)) && positionDejaPrise(p, 2, 2) == -1) { 
    ok++;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  } 
  
  printf("\n----- DEPLACEMENTS TIGRES ---- \n") ;
  
  printf("Position initiale inexistante : ") ;
  if( !deplacementTigre(p, -1, 4, 2, 1) && !deplacementTigre(p, 2, 40, 2, 1)) { 
    ok++ ;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }
  
  printf("Position initiale vide ou occuppé par une chevre : ") ;
  if( !deplacementTigre(p, 3, 3, 2,1) && !deplacementTigre(p, 1, 1, 2, 1)) { 
    ok++ ;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }
  
  printf("Position finale inexistante : ") ;
  if( !deplacementTigre(p, 4, 0, -1, 1) && !deplacementTigre(p, 0, 0, 0, 40)) { 
    ok++ ;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }
  
  printf("Position finale impossible d'accee direct : ") ;
  if( !deplacementTigre(p, 4, 0, 3, 2)) { 
    ok++ ;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }
  
  printf("    1) Simples ---- \n") ;
  placerChevre(p, 3, 1);
  printf("Position finale deja prise : ") ;
  if( !deplacementTigre(p, 4, 0, 3, 1)) { 
    ok++ ;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }
  
  printf("Deplacements corrects : ") ;
  if( deplacementTigre(p, 4, 0, 4, 1) && !estChevre(getElement(p, 4, 1)) && positionDejaPrise(p, 4, 0) == -1 && deplacementTigre(p, 0, 0, 0, 1) && !estChevre(getElement(p, 0, 1)) && positionDejaPrise(p, 0, 0) == -1) { 
    ok++ ;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }   

  printf("    2) En mangeant une chevre ---- \n") ;

  placerChevre(p, 0, 2);
  placerChevre(p, 0, 3);
  placerChevre(p, 1, 1);
  placerChevre(p, 1, 3);
  printf("Position finale deja prise : ") ;
  if( !deplacementTigre(p, 0, 1, 0, 3))  { 
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }
 
  printf("Pas de chevres entre : ") ;
  if( !deplacementTigre(p, 0, 4, 2, 4))  { 
    ok++ ;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }
  
  printf("Deplacements corrects : ") ;
  if(deplacementTigre(p, 0, 4, 2, 2) && !estChevre(getElement(p, 2, 2)) && positionDejaPrise(p, 0, 4) == -1  && positionDejaPrise(p, 1, 3) == -1 && deplacementTigre(p, 4, 1, 4, 3) && !estChevre(getElement(p, 4, 3)) && positionDejaPrise(p, 4, 1) == -1  && positionDejaPrise(p, 4, 2)) { 
    ok++ ;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n") ;
  }   
  
  return ok ;
}

int testPhase() {
  printf("\n----- PHASES  ---- \n") ;

  Plateau p = creerPLateau() ;
  plateauDepard(p);
  int ok = 0 ;
  
  // placement de toutes les chevres
  placerChevre(p, 0, 1);		// +1 placed
  placerChevre(p, 0, 2);		// +2 placed
  placerChevre(p, 0, 3);		// +3 placed
  placerChevre(p, 1, 0);		// +4 placed
  placerChevre(p, 1, 1);		// +5 placed
  placerChevre(p, 1, 2);		// +6 placed
  placerChevre(p, 1, 3);		// +7 placed
  placerChevre(p, 1, 4);		// +8 placed	
  deplacementTigre(p,0,4,2,4);		// +7 placed	+1 captured
  placerChevre(p, 0, 4);		// +8 placed	+1 captured	
  placerChevre(p, 1, 4);		// +9 placed	+1 captured	
  placerChevre(p, 2, 0);		// +10 placed	+1 captured
  placerChevre(p, 2, 1);		// +11 placed	+1 captured
  placerChevre(p, 2, 3);		// +12 placed	+1 captured
  deplacementTigre(p,2, 4, 2,2);	// +11 placed	+2 captured
  placerChevre(p, 2, 3);		// +12 placed	+2 captured
  placerChevre(p, 2, 4);		// +13 placed	+2 captured
  placerChevre(p, 3, 0);		// +14 placed	+2 captured
  placerChevre(p, 3, 1);		// +15 placed	+2 captured
  placerChevre(p, 3, 2);		// +16 placed	+2 captured
  placerChevre(p, 3, 3);		// +17 placed	+2 captured
  
  printf("19 - Nombre de chèvres placées : %d -> phase %d\n", getPlaced(p) + getCaptured (p), getPhase(p));
  placerChevre(p, 3, 4);		// +18 placed	+2 captured
  printf("20 - Nombre de chèvres placées : %d -> phase %d\n", getPlaced(p) + getCaptured (p), getPhase(p));
  
  // test de fin des placements
  printf("Arret des placements des chèvres : ") ;
  if(!placerChevre(p, 4, 3)) { 
    ok ++;
    printf("[OK] \n");
  } else {
    printf("[NOK] \n");
  }
   return ok ;
}
  
int finDePartie_tigres() { 
  printf("TIGRES GAGNANTS : 7 chèvres mangées : ");
  
  Plateau p = creerPLateau() ;
  plateauDepard(p);
  
  // on fait manger 7 chevres
  placerChevre(p, 1, 0);
  deplacementTigre(p, 0, 0, 2, 0);	    	// 1 captured
  
  placerChevre(p, 2, 1);
  deplacementTigre(p, 2, 0, 2, 2);		// 2 captured

  placerChevre(p, 1, 2);
  deplacementTigre(p, 2, 2, 0, 2);		// 3 captured
    
  placerChevre(p, 0, 1);
  deplacementTigre(p, 0, 2, 0, 0);		// 4 captured
 
  placerChevre(p, 1, 0);
  deplacementTigre(p, 0, 0, 2, 0);	    	// 5 captured
  
  placerChevre(p, 2, 1);
  deplacementTigre(p, 2, 0, 2, 2);		// 6 captured

  placerChevre(p, 1, 2);
  deplacementTigre(p, 2, 2, 0, 2);		// 7 captured
    
  if(gagnant(p) == TIGRE) {
    printf("[OK] \n") ;
    return (1) ;
  } else {
    printf("[KO] \n");
    return (0);
  }
}

int finDePartie_chevres() { 
  printf("CHEVRES GAGNANTES : encerclements de tigres : ");

  Plateau p = creerPLateau() ;
  plateauDepard(p);
  
  // on encercle les tigres  
  placerChevre(p, 1, 0);
  placerChevre(p, 1, 1);
  placerChevre(p, 0, 1);
  
  placerChevre(p, 3, 0);
  placerChevre(p, 3, 1);
  placerChevre(p, 4, 1);
  
  placerChevre(p, 0, 3);
  placerChevre(p, 1, 3);
  placerChevre(p, 1, 4);
  
  placerChevre(p, 3, 4);
  placerChevre(p, 3, 3);
  placerChevre(p, 4, 3);
    
  // on fait passer le plateau dans la phase deux
  setCaptured(p, 8);
 
  if(gagnant(p) == CHEVRE) {
    printf("[OK] \n") ;
    return (1) ;
  } else {
    printf("[KO] \n");
    return (0);
  }
}

int finDePartie() {
  printf("\n----- FIN DE PARTIE  ---- \n") ;
  
  // pas de gagnant
  Plateau p = creerPLateau() ;
  plateauDepard(p);
  int ok = 0;
  printf("Pas de gagnant : ");
  if(gagnant(p) == -1) {
    ok++;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n");
  }
  
  // gagnant
  ok = ok + finDePartie_chevres() ;
  ok = ok + finDePartie_tigres() ;
  return ok ;
}
 
int testSauvegardeChargement() {
  Plateau p = creerPLateau() ;
  Partie jeu = creerPartie() ;
  int ok = 1;
  
  // creation de plateau
  plateauDepard(p);
  placerChevre(p,1,1);
  placerChevre(p,2,2);
  placerChevre(p,3,3);
  deplacementTigre(p, 4, 0, 3, 1);
  deplacementTigre(p, 3, 1, 1, 3);
  
  // creation de la partie pour la sauvegarde 
  setPlateau(jeu, p);
  sauvegarder(jeu, "test.txt") ;
  
  // creation de la partie copie
  Partie copieJeu = charger("test.txt") ;
  Plateau copieP = getPlateau(copieJeu);
  
  // test de copie
  int i = 0, j;
  while (ok && i <5) {
    j = 0 ;
    while (ok && j<5) {
      if (positionDejaPrise(p,i,j) != positionDejaPrise(copieP,i,j)) {
	ok = 0;
      }
      j++;
    }
    i++;
  }
  
  if (ok) {
    return (getCaptured(p) == getCaptured(copieP)) ; 
  }
  return (0) ;
}

int testAnnulationCoup() {
  printf("\n----- ANNULATION ---- \n") ;

  int ok = 0;
  Plateau p = creerPLateau() ;
  plateauDepard(p);
  
  placerChevre(p,2,2);
  annulationCoup(p);
  printf("Annulation placement : ");
  if(positionDejaPrise(p,2,2) == -1) {
    ok++;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n");
  }
  
  placerChevre(p, 1, 0);
  deplacementTigre(p, 0, 0, 2, 0);	
  annulationCoup(p);
  printf("Annulation d'un deplacement de tigre avec une chevre mangée : ");
  if(positionDejaPrise(p,2,0) == -1 && positionDejaPrise(p,1,0) == CHEVRE) {
    ok++;
    printf("[OK] \n") ;
  } else {
    printf("[KO] \n");
  }
 
  return ok ;
}
int main(void) {


 printf("%d", testAnnulationCoup());

  //printf(" %d",  rand()%9999);
  //printf("\n\n %d [OK] SUR 22 TESTS\n",ok);
  return (0);
}