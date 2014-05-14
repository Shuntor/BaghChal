#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  
#include <string.h>  




#define C_PLACEMENT     0
#define C_DEPLACEMENT   1
#define T_DEPLACEMENT   2


#include "plateau.h" 


struct Case_D {
  Element e ;
  struct Case_D * suivant ;
} ;

struct Coup_D {
  int type ;			
  int posX1 ;
  int posX2 ;
  int posY1 ;
  int posY2 ;
} ;

struct Plateau_D {
    Case debut;
    int captured ;
    int placed ;
    int coup ;
    struct Coup_D * precedent ;
} ;

//----------------------------------------------------------------- CREATION  

Plateau creerPLateau() {
  Plateau p = (Plateau) malloc (sizeof(struct Plateau_D));
  p->debut = NULL ;
  p->captured = 0;
  p->placed = 0;
  p->coup=0;
  p->precedent = (Coup) malloc (sizeof(struct Coup_D)) ;
  setDernierCoup(p,-1,0,0,0,0);
  return p;  
}

//----------------------------------------------------------------- GETEURS SETEURS

void setCaptured (Plateau p, int captured) {
  p->captured = captured ;
}

int getPlaced (Plateau p) {
  return p->placed ;
}

int getCaptured (Plateau p) {
  return p->captured ;
}

int getCoup (Plateau p) {
  return p->coup ;
}

void setDernierCoup(Plateau p, int type, int x1, int y1, int x2, int y2) {
  p->precedent->type = type ;
  p->precedent->posX1 = x1 ;
  p->precedent->posY1 = y1 ;
  p->precedent->posX2 = x2 ;
  p->precedent->posY2 = y2 ;
}

void setCoup (Plateau p, int val) {
  p->coup = val ;
}

int getPhase(Plateau p) {
  return (((p->captured + p->placed) == 20) +1 );
}

Element getElement (Plateau p, int posX, int posY) {
  if(positionExiste(posX, posY) && positionDejaPrise(p, posX, posY)) {
    Case tmp = p->debut ;
    while (!positionEgale(getPosX(tmp->e), getPosY(tmp->e), posX, posY)) {
      tmp = tmp->suivant ;
    }
    return tmp->e ;
  } else { 
    return NULL ; 
  }
}

//----------------------------------------------------------------- LISTE  

void afficherPlateau_test(Plateau p) {
  if( p->debut != NULL ) {
    Case tmp = p->debut ;
    do {
      afficherElementTest(tmp->e);
      tmp = tmp->suivant ;
    } while ( tmp != NULL ) ;
  } 
}

void ajouter(Plateau p, Element el) {
  Case add = (Case) malloc(sizeof(struct Case_D));
  add->e = el ;
  if(p->debut != NULL) {
    Case tmp = p->debut ;
    
    // Recherche du bon endroit où le placer l'élément dans la liste (ordre poition croissant)
    if (plusGrand(getPosX(tmp->e),getPosY(tmp->e),getPosX(el), getPosY(el))) {
      add->suivant = tmp ;
      p->debut = add ;
    } else {
      while (tmp->suivant != NULL && !plusGrand(getPosX(tmp->suivant->e), getPosY(tmp->suivant->e),getPosX(el), getPosY(el))) {
	tmp = tmp->suivant ;
      }
      add->suivant = tmp->suivant ;
      tmp->suivant = add ;
    }
  } else {
    add->suivant = NULL ;
    p->debut = add;
  }
  
  if(estChevre(el)) {
    p->placed ++ ;
  } 
}

void suppression(Plateau p, int posX, int posY) {
  Case tmp = p->debut ;
  Case prec = NULL ;
  
  // Recherche de l'élément correspondant à la position
  while (!positionEgale(getPosX(tmp->e),getPosY(tmp->e),posX,posY)) {
      prec = tmp ;
      tmp = tmp->suivant ;
  }
  
  if(prec==NULL) {
    p->debut = tmp->suivant ;
  } else {
    prec->suivant = tmp->suivant ;
  }
  if(estChevre(tmp->e)) {
    p->placed -- ;
  } 

  free(tmp);
  
}

//----------------------------------------------------------------- POSITION 

bool estPaire(int posX, int posY) {
  return ((posX + posY) %2 ==0);
}

bool positionExiste(int posX, int posY) {
  return (posX >= 0 && posX <= 4 && posY >=0 && posY <= 4);
}

int positionDejaPrise (Plateau p, int posX, int posY) {
  if(positionExiste(posX,posY)) {
    Case tmp = p->debut ;
    while (tmp != NULL && !positionEgale(getPosX(tmp->e), getPosY(tmp->e), posX, posY)) {
      tmp = tmp->suivant ;
    }
  
    if(tmp==NULL) {
      return (-1) ;
    } else { 
      if(estChevre(tmp->e)) {
        return CHEVRE ;
      } else { 
        return TIGRE ; 
      }
    }
  } else {
    return (-2);
  }
}

bool positionEgale(int posX1, int posY1, int posX2, int posY2) {
  return ((posX1 == posX2) && (posY1 == posY2));
}

bool plusGrand(int posX1, int posY1, int posX2, int posY2) {
  if (posX1 > posX2) {
    return true ;
  } else {
    if (posX1 < posX2) {
      return false ;
    } else {
      return (posY1 >= posY2) ;
    }
  }
}

//----------------------------------------------------------------- PLACEMENT 

void plateauDepard(Plateau p) {
  placerTigre(p,0,0);
  placerTigre(p,0,4);
  placerTigre(p,4,0);
  placerTigre(p,4,4);
}
  
void placerTigre(Plateau p, int posX, int posY) {
  Element e = creerTigre(posX,posY);
  ajouter(p,e);
}

bool placerChevre(Plateau p, int posX, int posY) {
  if(positionExiste(posX,posY) && positionDejaPrise(p, posX, posY) == -1 && getPhase(p) == 1) {
    Element e = creerChevre(posX,posY);
    ajouter(p,e);
    p->coup++;
    setDernierCoup(p, C_PLACEMENT, posX, posY, 0, 0) ;
    return true;
  } else {
    return false ;
  }
}

//----------------------------------------------------------------- DEPLACEMENT 


int deplacementPossible_1(Plateau p, int posX, int posY, int newX, int newY)  {
  // si la position n'existe pas ou ne se trouve pas a la bonne distance
  if (!positionExiste(newX, newY) || !(abs(posX-newX)<2 && abs(posY-newY)<2) || (!estPaire(posX, posY) &&  !(posX==newX || posY==newY))) {
    return (-1) ;
  } else {
    if (positionDejaPrise(p,newX, newY)==-1) {
      return (1) ; // vide
    } else { 
      return (0) ; // deja prise
    }
  }
}

	  /************* A AMELIORER !!! **********/
int deplacementPossible_2(Plateau p, int posX, int posY, int newX, int newY)  {
  if (positionDejaPrise(p,newX, newY) == -1 && (abs(posX-newX)<3 || abs(posY-newY)<3) && (abs(posX-newX)==2 || abs(posY-newY)==2) && positionDejaPrise(p,(posX + newX) / 2,(posY + newY)/2) == CHEVRE) {
    if (estPaire(posX, posY)) {
       return (1);
    } else {
       if (!estPaire(posX, posY) &&  (posX==newX || posY==newY)) {
	  return (1);
       }
    }	
  } 
  return (0);
}

bool deplacementChevre(Plateau p,int posX, int posY, int newX, int newY) {
  // si on deplace bien une chevre et si le deplacement et possible à un de distance
   if(positionDejaPrise(p, posX, posY) == CHEVRE && deplacementPossible_1(p, posX, posY, newX, newY) == 1) {
      // deplacement
      suppression(p, posX, posY);
      placerChevre(p, newX, newY);  
      setDernierCoup(p, C_DEPLACEMENT, posX, posY, newX, newY) ;
      return true;
   }
   return false;
}
															  /* */
bool deplacementTigre(Plateau p,int posX, int posY, int newX, int newY) {
  // si on deplace bien un tigre
  if(positionDejaPrise(p,posX, posY) == TIGRE  ) {
    // si on veut et peut de placer à un de distance
    if(deplacementPossible_1(p, posX, posY, newX, newY) == 1) {
    } else {
    // si on veut et peut de placer à deux de distance avec une chevre au milieux
      if(deplacementPossible_2(p, posX, posY, newX, newY) && positionDejaPrise(p, (posX+newX)/2, (posY+newY)/2) == CHEVRE) {
        // suppression de la chevre 
	suppression(p, (posX+newX)/2, (posY+newY)/2);
      	p->captured ++ ;
      } else { 
	return 0 ;
      }
    }
    suppression(p, posX, posY);
    placerTigre(p, newX, newY);  
    p->coup++;   
    setDernierCoup(p, T_DEPLACEMENT, posX, posY, newX, newY) ;
    return true;
  }
  return false;
}


//----------------------------------------------------------------- ANNULATION

int annulationCoup(Plateau p) {
  if (p->precedent->type != -1) {
    int tmp = p->coup ;
    if (p->precedent->type == C_PLACEMENT) {
      suppression(p, p->precedent->posX1, p->precedent->posY1);
      p->precedent->type = -1 ;
    } else {
      if (p->precedent->type == C_DEPLACEMENT) {
        deplacementChevre(p, p->precedent->posX2, p->precedent->posY2, p->precedent->posX1, p->precedent->posY1);
      p->precedent->type = -1 ;
      } else {
        if (p->precedent->type == T_DEPLACEMENT) {
	  annulationCoup_deplacementTigre(p, p->precedent->posX2, p->precedent->posY2, p->precedent->posX1, p->precedent->posY1) ;
          p->precedent->type = -1 ;
        } 
      }
    }
    p->coup = tmp -1  ;
    return (1);
  }
  return (0);
}

void annulationCoup_deplacementTigre(Plateau p,int posX, int posY, int newX, int newY) {
  if(deplacementPossible_1(p, posX, posY, newX, newY) == -1) {
    placerChevre(p, (posX+newX)/2, (posY+newY)/2);
    p->captured -- ;
  }
  suppression(p, posX, posY);
  placerTigre(p, newX, newY); 
}  


//----------------------------------------------------------------- PARTIE GAGNEE ? 

bool encercle(Plateau p, Element e) {
  bool ok = true ; // e encercle
  int i = -1 ;
  int j = -1 ;
  
  // pour chaque direction
  while (ok && i<2) {
     while (ok && j<2) {
       // si on peut ce deplacer de un et si, en tant que tigre ont peut en plus sauter une chevre
       if(deplacementPossible_1(p, getPosX(e), getPosY(e), getPosX(e)+i, getPosY(e)+j)==1 || (!estChevre(e) &&  deplacementPossible_2(p, getPosX(e), getPosY(e), getPosX(e)+i, getPosY(e)+j)) ) {
         ok=false; // e a une possibilite de se deplacer
       }
       j ++ ;
     }
     j=-1;
     i++ ;
  }
  return ok ;
}
  
int gagnant(Plateau p) {
  if (p->captured == 7) {
    return TIGRE ;
  } else {
    if(getPhase(p) == 2 ) {
      int c = 1 ; // chevres encerclees
      int t = 1 ; // tigres encercles
  
      if( p->debut != NULL ) {
        Case tmp = p->debut ;
        do {
          // si l'element n'est pas encercle
          if (estChevre(tmp->e) && !encercle(p, tmp->e)) {
            c = 0;
          } else {
	    if (!estChevre(tmp->e) && !encercle(p, tmp->e)) {
	      t = 0;
	    }     
          }	
          tmp = tmp->suivant;
        } while ( tmp != NULL && t == 1 && c == 1 ) ;
      }
  
      if (c==1) { 
        // les chevres sont encerclees : tigres vainqueurs
        return (TIGRE) ;
      } else {
        if (t==1) { 
          // les tigres sont encerclees : chevres vainqueurs
          return (CHEVRE) ; 
        }
      }
    }
  }
  return (-1);
} 

//----------------------------------------------------------------- FONCTIONS MENU

void ecrirePlateau(Plateau p, FILE * fichier) {
  Case tmp = p->debut ;
  int i=0, j=0 ;
  do {
    do {
      if (tmp != NULL && getPosX(tmp->e)==i && getPosY(tmp->e) == j) {
        if(estChevre(tmp->e)) {
          fputc('c', fichier); 
	} else {
	  fputc('t', fichier); 
	}
	tmp = tmp->suivant ;
      } else {
        fputc('.', fichier); 
      }
      j++;
    } while (j<5);
    fputc('\n', fichier); 
    i++;
    j=0;
  } while (i<5);
}

void lirePlateau (FILE * fichier, Plateau p) {
  if (fichier != NULL) {
    char c;
    int i = 0, j ;
     do {
       c=fgetc(fichier); 
       j=0;
       do {
         c = fgetc(fichier); 
	 if(c=='c') {
	   Element e = creerChevre(i,j) ;
	   ajouter(p, e);
	 } else {
	   if(c=='t'){
	     Element e = creerTigre(i,j) ;
	     ajouter(p, e);
	   }
	}
        j++;
      } while (j<5) ;
      i++;      
    } while (i<5) ; 
    fclose(fichier);
  }
}

//----------------------------------------------------------------- TESTS

void affPTEST (Plateau p) {
  Case tmp = p->debut ;
  int i=0, j=0 ;
  do {
    do {
      if (tmp != NULL && getPosX(tmp->e)==i && getPosY(tmp->e) == j) {
        if(estChevre(tmp->e)) {
	  printf("c "); 
	} else {
	  printf("t "); 
	}
	tmp = tmp->suivant ;
      } else {
	printf(". ");
      }
      j++;
    } while (j<5);
    printf("\n"); 
    i++;
    j=0;
  } while (i<5);
}

//----------------------------------------------------------------- IA

//-------- CHEVRE
  
/*
PLACEMENT : ne pas ce placer à coter d'un tigre avec un vide de lautre coter

*/

int placerChevreIA(Plateau p) {
  int x = 0, y, placed =0 ;
  
  // placer coin 
  while (!placed && x<5) {
    y=0;
    while (!placed && y<5) {
      if (positionDejaPrise(p, x, y) == -1) {
        placerChevre(p, x, y) ;
	placed=1 ;
      }
      y = y + 4 ;
    }
    x = x + 4 ;
  }

 

  if (!placed && getPlaced(p) > 0) {
    printf("lalal\n");
    Element tab[getPlaced(p)];
    int i = 0 ;
    Case tmp = p->debut ;
    do {
      if(estChevre(tmp->e)) {
        tab[i] = tmp->e;
        i++;
      }
      tmp = tmp->suivant;
    } while (i<getPlaced(p)) ;

    
    int x1, y1, mangeable =1;
    int enCours = rand()%(getPlaced(p));
    printf("encours = %d:%d \n", getPosX(tab[0]), getPosY(tab[0]));

    i = 0;
    while (!placed && i<getPlaced(p)) {
      // possibilite de ce placer ?
      if(!encercle(p, tab[enCours])) {
	x=-1;
	while (!placed && x<2) {
	  y=-1;
	  while (!placed && y<2) {
	    printf("test : %d %d \n", getPosX(tab[enCours]) + x, getPosY(tab[enCours])+ y);
	    int a;
	    scanf("%d", &a);
	    if(positionDejaPrise(p, getPosX(tab[enCours]) + x, getPosY(tab[enCours])+ y) == -1) {
	      
	      // et si ce n'est pas dangereux		    
	      x1 = -1;
	      while (!mangeable && x1<2) {
	        y1=-1;
	        while (!mangeable && y1<2) {
		  printf("pour m : %d %d \n", getPosX(tab[enCours]) + x +x1, getPosY(tab[enCours])+ y+y1);
		  printf("pour c : %d %d \n", getPosX(tab[enCours]) + x -2*x1, getPosY(tab[enCours])+ y-2*y1);
	          if(positionDejaPrise(p, getPosX(tab[enCours]) + x + x1, getPosY(tab[enCours]) + y + y1) == TIGRE && positionDejaPrise(p, getPosX(tab[enCours]) + x - 2*x1, getPosY(tab[enCours]) + y - 2*y1) == -1) {
		    mangeable =1;
		    printf("m\n");
		  }
		  y1++;
	        }
	        x1++;
	      }
	      if(!mangeable) {
		placerChevre(p, getPosX(tab[enCours]) + x, getPosY(tab[enCours]) + y);
		placed = 1;
	      }
	    }
	    y++;
	  }
	  x++;
	}
      }
    }
    enCours = (enCours + 1)%getPlaced(p);
    i++;

  }
  
  
  if(!placed) { 
    placerChevre(p, 2, 2);
  }
  return (0);
}
    
  
/*s
DEPLACEMENT : meme chose et/ou se placer à cote d'une autre chevre (autant à l'interieur que sur les bords)
*/
//-------- TIGRE


int deplacerTigreIA (Plateau p) {
  Element tab[4] ;
  int i = 0 ;
  
  /*                 random  *************************/
  Case tmp = p->debut ;
  do {
    if(!estChevre(tmp->e)) {
      tab[i] = tmp->e ;
      i++;
    }
    tmp = tmp->suivant;
  } while (i<4) ;
  
  int maxX ;
  int maxY ;
  int x ;
  int y ;
  bool trouve = false ;
  
  // si une chevre peut etre manger
  while(i<3 && !trouve){
    x = -1 ;
    y = -1 ;
    while(x<2 && !trouve) {
      while(y<2 && !trouve) {
	// si ya bien une chevre à cote
        if(positionExiste(getPosX(tab[i])+x, getPosY(tab[i])+y) && positionDejaPrise(p,getPosX(tab[i])+x, getPosY(tab[i])+y) == CHEVRE) {
	  // si la position dapres est vide
          if(positionExiste(getPosX(tab[i])+x*2, getPosY(tab[i])) && positionDejaPrise(p,getPosX(tab[i])+x*2, getPosY(tab[i])+y*2) == -1) {
            trouve = true ;
            maxX = x ;
            maxY = y ; 
          } 
        } 
      }
    }
    i++;
  }

  // on cherche celle qui est la plus proche pour sen apporcher
  x = -1 ;
  y = -1 ;
  int min = 2 ;
  while (!trouve) {
    while(i<3 && !trouve) {
      x = -1 ;
      y = -1 ;
      while(x<2 && !trouve) {
        while(y<2 && !trouve) {
	  // si la position d'apres est vide
	  if(positionExiste(getPosX(tab[i])+x, getPosY(tab[i])+y) && positionDejaPrise(p,getPosX(tab[i])+x, getPosY(tab[i])+y) == -1) {
	    // si ya une chevre a la distance min en cours
	    if(positionExiste(getPosX(tab[i])+x*min, getPosY(tab[i])+y*min) && positionDejaPrise(p,getPosX(tab[i])+x*min, getPosY(tab[i])+y*min) == CHEVRE ) {
              trouve = true ;
              maxX = min*x ;
              maxY = min*y ; 
	    }
          }  
        }
      }
      i++;
    } min ++ ;
  }
  
  if (trouve) {
    return deplacementTigre(p, getPosX(tab[i]), getPosY(tab[i]), getPosX(tab[i])+maxX, getPosY(tab[i])+maxY) ;
  } else {
    return (-1) ;
  }
}	   
    
     

// DEPLACEMENT : s'approcher d'une chevre ou en manger une

//----------------------------------------------------------------- THEARD

