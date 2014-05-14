#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  
#include <string.h>  

#include "partie.h" 

struct Partie_D {
  Plateau pl ;
  int player ;
} ;

//----------------------------------------------------------------- CREATION

Partie creerPartie() {
  Partie p = (Partie) malloc (sizeof(struct Partie_D));
  p->player = CHEVRE ;
  p->pl = creerPLateau();
  return p;  
}

//----------------------------------------------------------------- GETEURS SETEURS

void setPlateau(Partie p, Plateau pl) {
  p->pl = pl ;
}

Plateau getPlateau(Partie p) {
  return p->pl ;
}


//----------------------------------------------------------------- FONCTIONS MENU

void sauvegarder (Partie jeu, char * nomFichier) {
  FILE* fichier = fopen(nomFichier, "w");
  if (fichier != NULL) {
    
    fputs("\\board\n", fichier);
    ecrirePlateau(jeu->pl, fichier);
    fputs("\\endboard\n", fichier);
    
    fprintf(fichier, "\\player %d\n",jeu->player);	
    fprintf(fichier, "\\phase %d\n",getPhase(jeu->pl));	
    fprintf(fichier, "\\captured %d\n",getCaptured(jeu->pl));	
  
    fclose(fichier);
  }
}

Partie charger(char * nomFichier) {
  FILE * fichier = fopen(nomFichier, "r+");
  char tmp[20];
  int i = 0, ok = 1;
  Partie jeu ;
  while (ok && fgets(tmp, 20, fichier) != NULL) {
    switch (i) {
      case 0 : 
	ok = !strcmp(tmp, "\\board\n");
	printf("..%d\n", ok);
	jeu =  creerPartie() ;
	lirePlateau(fichier, jeu->pl); 
	affPTEST(jeu->pl);
	break;
      case 1 : 

	break;
      case 2 : 
	printf("%s", tmp);
	break;
      case 3 : 
	printf("%s", tmp);     
	break;
      case 4 : 
	printf("%s", tmp);
	break;
      case 5 : 
	ok = !strcmp(tmp, "\\board\n");
	break;
      case 6 :
	printf("%s", tmp);
	break;
      case 7 : 
	printf("%s", tmp); 
	break;
    }
    i++;
  }

  
  /*
  Partie jeu =  creerPartie() ;
  lirePlateau(fichier, jeu->pl) ;
  affPTEST(jeu->pl);
fgets(tmp, 10, fichier) ; ;
  fgets(tmp, 10, fichier) ; 
  printf("-%s\n",tmp);
  fgets(tmp, 10, fichier) ; 
  printf("*%s\n",tmp);
*/
  /*
  fscanf(tmp, "%d", &jeu->player);
  fgets(tmp, 10, fichier) ; 
  // fscanf(tmp, "%d", &jeu->phase);
  fgets(tmp, 10, fichier) ; 
  int captured ;
  fscanf(tmp, "%d", &captured);
  setCaptured(p, captured);
  
  jeu->coup = (getCaptured(jeu->pl) + getPlaced(jeu->pl)) * 2 + jeu->player ;
  */
  jeu = NULL ;
  return jeu ;
}

//----------------------------------------------------------------- NOUVEAU COUP

/* 1 : placer chevre 
 * 2 : deplacer chevre
 * 3 : deplacer tigre
 */
int nouveauCoup(Partie jeu) {
  int res = 0 ;
    if (getCoup(jeu->pl) %2 == 1) {
      if (getPhase(jeu->pl)==1) {
        return (1) ;
      } else {
        return (2) ;
      }
  } else {
     return (3);    
  }
  
  return res ;
}
      