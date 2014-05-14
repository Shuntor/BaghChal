#ifndef _PLATEAU_H_
#define _PLATEAU_H_

#include "elements.h" 

typedef struct Case_D * Case ;
typedef struct Coup_D * Coup ;
typedef struct Plateau_D * Plateau ;

//----------------------------------------------------------------- CREATION  

Plateau creerPLateau() ;

//----------------------------------------------------------------- GETEURS SETEURS

void setCaptured (Plateau p, int captured) ;
int getPlaced (Plateau p) ;
int getCaptured (Plateau p) ;
int getPhase (Plateau p) ;
Element getElement (Plateau p, int posX, int posY) ;
int getCoup (Plateau p) ;
void setCoup (Plateau p, int val) ;
void setDernierCoup(Plateau p, int type, int x1, int y1, int x2, int y2) ;

//----------------------------------------------------------------- LISTE  

void afficherPlateau_test (Plateau p) ;
void ajouter (Plateau p, Element el) ;
void suppression (Plateau p, int posX, int posY) ;

//----------------------------------------------------------------- POSITION 

bool estPaire (int posX, int posY) ;
bool positionExiste (int posX, int posY) ;
int positionDejaPrise (Plateau p, int posX, int posY) ;
bool positionEgale (int posX1, int posY1, int posX2, int posY2) ;
bool plusGrand (int posX1, int posY1, int posX2, int posY2) ;

//----------------------------------------------------------------- PLACEMENT 

void plateauDepard (Plateau p) ;  
void placerTigre (Plateau p, int posX, int posY) ;
bool placerChevre (Plateau p, int posX, int posY) ;

//----------------------------------------------------------------- DEPLACEMENT 

int deplacementPossible_1 (Plateau p, int posX, int posY, int newX, int newY) ;
int deplacementPossible_2 (Plateau p, int posX, int posY, int newX, int newY) ;
bool deplacementChevre (Plateau p,int posX, int posY, int newX, int newY) ;
bool deplacementTigre (Plateau p,int posX, int posY, int newX, int newY) ;

//----------------------------------------------------------------- ANNULATION

int annulationCoup(Plateau p) ;
void annulationCoup_deplacementTigre(Plateau p,int posX, int posY, int newX, int newY) ;

//----------------------------------------------------------------- PARTIE GAGNEE ? 

bool encercle (Plateau p, Element e) ;
int gagnant (Plateau p) ;

//----------------------------------------------------------------- FONCTIONS MENU

void ecrirePlateau (Plateau p, FILE * fichier) ;
void lirePlateau (FILE * fichier, Plateau p) ;

//----------------------------------------------------------------- TESTS

void affPTEST (Plateau p) ;


int placerChevreIA(Plateau p) ;


int deplacerTigreIA (Plateau p) ;

#endif
 