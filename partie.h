#ifndef _PARTIE_H_
#define _PARTIE_H_

#include "plateau.h" 

typedef struct Partie_D * Partie ;

//----------------------------------------------------------------- CREATION

Partie creerPartie() ;

//----------------------------------------------------------------- GETEURS SETEURS

void setPlateau(Partie p, Plateau pl) ;
Plateau getPlateau(Partie p) ;

//----------------------------------------------------------------- FONCTIONS MENU

void sauvegarder (Partie jeu, char * nomFichier) ;
Partie charger(char * nomFichier) ;

//----------------------------------------------------------------- NOUVEAU COUP

int nouveauCoup(Partie jeu) ;

#endif
 