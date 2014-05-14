#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "affichage.h"
#include "partie.h" 
#include "plateau.h" 
#include "elements.h"

#define nb_lignes 5
#define nb_colonnes 5
#define WIDTH 30
#define HEIGHT 10 
#define DEBFENX (80 - WIDTH) / 2
#define DEBFENY (24 - HEIGHT) / 2
#define XMIN_GRILLE 16
#define XMAX_GRILLE 37
#define YMIN_GRILLE 4
#define YMAX_GRILLE 16

#define PAS_CASE 100
#define SAUVEGARDER 40
#define QUITTER 50
#define CHARGER 60

#define ENTER 10
#define X_CHARGER 50
#define Y_CHARGER 5
#define X_SAUVEGARDER 50
#define Y_SAUVEGARDER 6
#define X_QUITTER 50
#define Y_QUITTER 7


int startx = 0;
int starty = 0;


char *choices[] = { 
			"Creer",
			"Charger",
			"Quitter",
};
char *choix_creer[] = { 
			"Humain vs humain",
			"Humain vs IA",
			"Retour",
};
char *choix_camp[] = {
			"Chèvres",
			"Tigres",
};		  

int scroll_menu(WINDOW *items, char** choix, int nbr_choices);
void print_menu(WINDOW *menu_win, int highlight, char ** choix, int nbr_choices);
// void print_byebye(WINDOW* menu_win);
void afficher_Grille(int phase, int nbchevres_mortes, int tour, Cellule **t2D, Plateau plateau);
void InitTableau(Cellule **t2D);
Cellule **alloc();
void recuperer_mouse( int * x_win, int * y_win);
int verifier_click( Cellule **t2D, int* x, int* y);
int jouer_partie(Cellule** t2D, Partie partie);
void recuperer_positon(int* x, int* y);
void placer_chevre(int x, int y);
void placer_tigre(int x, int y);
Cellule** initialiser_partie();
void new_sauvegarde(Partie partie);
int confirm_quitter();
int jouer_partie_IA_tigre(Cellule** t2D, Partie partie);
Partie charger_partie(void);

int debut()
{	WINDOW *menu_win;
	int highlight = 1;
	int choice = 1;
	int nbr_choices;
	Partie partie = creerPartie();

	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	intrflush(stdscr, FALSE); 
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
		
	menu_win = newwin(HEIGHT, WIDTH, DEBFENY, DEBFENX); //On crée une nouvelle fenêtre pour le menu
	keypad(menu_win, TRUE); // Active les touches f1, f2 etc
	wclear(menu_win); // Nettoie la fenêtre
	int test=1; 

	while(test)
	{
		wclear(menu_win);
		nbr_choices=sizeof(choices) / sizeof(char *);
		print_menu(menu_win, highlight, choices, nbr_choices);
		choice=scroll_menu(menu_win, choices, nbr_choices);
		switch(choice)
		{
			case 1:
				wclear(menu_win);
				nbr_choices=sizeof(choix_creer) / sizeof(char *);
				print_menu(menu_win, highlight, choix_creer, nbr_choices);
				choice=scroll_menu(menu_win, choix_creer, nbr_choices);
				if (choice==1)
				{
					wclear(menu_win);
					clear();
					//Affichage du plateau pour une partie HvH

					plateauDepard(getPlateau(partie));
					if (jouer_partie(initialiser_partie(), partie))
					{
						return 0;
					}	
				}
				if (choice==2)
				{
					wclear(menu_win);
					//Affichage du plateau pour une partie HvIA
					jouer_partie_IA_tigre(initialiser_partie(), creerPartie());
				}
				if (choice==3)
				{
					return 1;
				}
			break;

			case 2:

				if (jouer_partie(initialiser_partie(), charger_partie()))
					return 0;

			break;
			case 3:
				test=0;
			break;
		}
	}
		clrtoeol();
		refresh();
		endwin();
		return 0;
}



void print_menu(WINDOW *menu_win, int highlight, char** choix, int nbr_choices)
{
	int x, y, i;	
	x = 2;
	y = 2;

	box(menu_win, 0, 0);
	for(i = 0; i < nbr_choices; ++i)
	{	
		if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choix[i]);
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choix[i]);
		++y;
	}
	wrefresh(menu_win);
}

int scroll_menu(WINDOW *menu_win, char** choix, int nbr_choices)
{
	int highlight=1, c;
	while(1)
	{	
		c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = nbr_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == nbr_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				return (highlight);
				break;
			default:
				mvprintw(24, 0, "Vous avez appuyé sur la touche '%c'", c);
				refresh();
				break;
		}
		print_menu(menu_win, highlight, choix, nbr_choices);
	}	
}

Cellule** initialiser_partie()
{
	Cellule **t2D;
	t2D=alloc();
    InitTableau(t2D);
    
    //On place tous les tigres
    t2D[0][0].type=1;
    t2D[0][4].type=1;	
    t2D[4][0].type=1;	
    t2D[4][4].type=1;

    return(t2D);	
}

int jouer_partie(Cellule** t2D, Partie partie)
{
	int testclick;	
	// int nbchevres_mortes=0;

	int tour = CHEVRE;
	int x,y;
	int x2, y2;
	int c;


	  // placement de toutes les chevres
  // placerChevre(getPlateau(partie), 0, 1);		// +1 placed
  // placerChevre(getPlateau(partie), 0, 2);		// +2 placed
  // placerChevre(getPlateau(partie), 0, 3);		// +3 placed
  // placerChevre(getPlateau(partie), 1, 0);		// +4 placed
  // placerChevre(getPlateau(partie), 1, 1);		// +5 placed
  // placerChevre(getPlateau(partie), 1, 2);		// +6 placed
  // placerChevre(getPlateau(partie), 1, 3);		// +7 placed
  // placerChevre(getPlateau(partie), 1, 4);		// +8 placed	
  // deplacementTigre(getPlateau(partie),0,4,2,4);		// +7 placed	+1 captured
  // placerChevre(getPlateau(partie), 0, 4);		// +8 placed	+1 captured	
  // placerChevre(getPlateau(partie), 1, 4);		// +9 placed	+1 captured	
  // placerChevre(getPlateau(partie), 2, 0);		// +10 placed	+1 captured
  // placerChevre(getPlateau(partie), 2, 1);		// +11 placed	+1 captured
  // placerChevre(getPlateau(partie), 2, 3);		// +12 placed	+1 captured
  // deplacementTigre(getPlateau(partie),2, 4, 2,2);	// +11 placed	+2 captured
  // placerChevre(getPlateau(partie), 2, 3);		// +12 placed	+2 captured
  // placerChevre(getPlateau(partie), 2, 4);		// +13 placed	+2 captured
  // placerChevre(getPlateau(partie), 3, 0);		// +14 placed	+2 captured
  // placerChevre(getPlateau(partie), 3, 1);		// +15 placed	+2 captured
  // placerChevre(getPlateau(partie), 3, 2);		// +16 placed	+2 captured
  // placerChevre(getPlateau(partie), 3, 3);		// +17 placed	+2 captured

	// on fait manger 7 chevres
  placerChevre(getPlateau(partie), 1, 0);
  deplacementTigre(getPlateau(partie), 0, 0, 2, 0);	    	// 1 captured
  
  placerChevre(getPlateau(partie), 2, 1);
  deplacementTigre(getPlateau(partie), 2, 0, 2, 2);		// 2 captured

  placerChevre(getPlateau(partie), 1, 2);
  deplacementTigre(getPlateau(partie), 2, 2, 0, 2);		// 3 captured
    
  placerChevre(getPlateau(partie), 0, 1);
  deplacementTigre(getPlateau(partie), 0, 2, 0, 0);		// 4 captured
 
  placerChevre(getPlateau(partie), 1, 0);
  deplacementTigre(getPlateau(partie), 0, 0, 2, 0);	    	// 5 captured
  
  placerChevre(getPlateau(partie), 2, 1);
  deplacementTigre(getPlateau(partie), 2, 0, 2, 2);		// 6 captured

	while(1)
	{
		clear();
		tour = getCoup(getPlateau(partie))%2; 
		// afficher_Grille( getPhase(getPlateau(partie)),getCaptured(getPlateau(partie)),tour, t2D, getPlateau(partie));
		// refresh();

		//Si c'est le tour des chevres
		if(tour==CHEVRE)		
		{
			if(getPhase(getPlateau(partie))==1)
			{	
				do{
					afficher_Grille( getPhase(getPlateau(partie)),getCaptured(getPlateau(partie)),tour, t2D, getPlateau(partie));
					refresh();
					testclick=verifier_click(t2D, &x, &y);
					if (testclick==SAUVEGARDER)//Sauvegarde
						new_sauvegarde(partie);
				}while (testclick!=-1 && testclick!=QUITTER);//Tant qu'il ne click pas sur un endroit vide
					if (testclick==QUITTER)
						if(confirm_quitter())return 1;
				// mvprintw(3,1,"testclick : %d", testclick);refresh();c=getch();
				placerChevre(getPlateau(partie), y, x);				
			}else
			{
				do{ //On selectionne une chevre
					afficher_Grille( getPhase(getPlateau(partie)),getCaptured(getPlateau(partie)),tour, t2D, getPlateau(partie));
					mvprintw(18,1,"Veuillez cliquer d'abord sur une chevre             ");
					refresh();
					testclick=verifier_click(t2D, &x, &y);
					if (testclick==SAUVEGARDER)//Sauvegarde
						new_sauvegarde(partie);
				}while(testclick!=0 && testclick !=QUITTER);
					if (testclick==QUITTER)
						if(confirm_quitter())return 1;
				do{ //On selectionne un emplacement vide
					afficher_Grille( getPhase(getPlateau(partie)),getCaptured(getPlateau(partie)),tour, t2D, getPlateau(partie));
					mvprintw(18,1,"Maintenant sur un emplacement vide               ");
					refresh();
					testclick=verifier_click(t2D, &x2, &y2);
					if (testclick==SAUVEGARDER)//Sauvegarde
						new_sauvegarde(partie);
				}while(testclick!=-1 && testclick !=QUITTER);
					if (testclick==QUITTER)
						if(confirm_quitter())return 1;
				deplacementChevre(getPlateau(partie),y,x,y2,x2);
			}
		}else
		{

			do{ //On selectionne un tigre
				afficher_Grille( getPhase(getPlateau(partie)),getCaptured(getPlateau(partie)),tour, t2D, getPlateau(partie));
				mvprintw(18,1,"Veuillez cliquer d'abord sur un tigre           ");
				refresh();
				testclick=verifier_click(t2D, &x, &y);
				if (testclick==SAUVEGARDER)//Sauvegarde
						new_sauvegarde(partie);
			}while(testclick!=1 && testclick !=QUITTER);
				if (testclick==QUITTER)
						if(confirm_quitter())return 1;
			do{ //On selectionne un emplacement vide
				afficher_Grille( getPhase(getPlateau(partie)),getCaptured(getPlateau(partie)),tour, t2D, getPlateau(partie));
				mvprintw(18,1,"Maintenant sur un emplacement vide              ");
				refresh();
				testclick=verifier_click(t2D, &x2, &y2);
				if (testclick==SAUVEGARDER)//Sauvegarde
						new_sauvegarde(partie);
			}while(testclick!=-1 && testclick !=QUITTER);
				if (testclick==QUITTER)
						if(confirm_quitter())return 1;
			deplacementTigre(getPlateau(partie),y,x,y2,x2);
			//Ici on le déplace ou on mange une chevre
		}

		//Fin du tour
		if (gagnant(getPlateau(partie))==CHEVRE)
		{
			clear();
			mvprintw(7,40,"Les chevres ont gagnées ! ");
			mvprintw(8,10,"Appuyez sur q pour quitter ");
			do{
				c = getch();
			}while(c!='q');
			clear();
			return 1;
		}else
		{
			if (gagnant(getPlateau(partie))==TIGRE)
			{
				clear();
				mvprintw(7,40,"Les tigres ont gagnées !");
				mvprintw(8,40,"Appuyez sur q pour quitter ");
				do{
					c = getch();
				}while(c!='q');
				clear();
				return 1;
			}
		}
		// mvprintw(22,1,"Valeure retorunée par le click : %d", testclick);
		refresh();
	}
}


void afficher_Grille(int phase, int nbchevres_mortes, int tour, Cellule **t2D, Plateau plateau)
{
		int x, y;
		int posX, posY;
        attron(A_BOLD);
        mvprintw(1,10,"Bienvenue sur le jeu Bag-Chal");
        attroff(A_BOLD);        
        box(stdscr, 0,0);
        // clear();


        //On recupere toutes les positions de la liste et on les met dans le tableau
        for (posY = 0; posY < nb_lignes; ++posY)
         {
         	for (posX = 0; posX < nb_colonnes; ++posX)
         	{
         		switch(positionDejaPrise(plateau, posX, posY)){
         		case TIGRE :
         			t2D[posY][posX].type=TIGRE;
         			break;
         		case CHEVRE :
         			t2D[posY][posX].type=CHEVRE;
         			break;
         		case -1:
					t2D[posY][posX].type=-1;         			
         			break;
         		}
         	}
         }


        //Menu
        // mvprintw(Y_CHARGER,X_CHARGER,"Charger");
         attron(A_UNDERLINE);
        mvprintw(Y_SAUVEGARDER,X_SAUVEGARDER,"Sauvegarder");
        mvprintw(Y_QUITTER,X_QUITTER,"Quitter");
        attroff(A_UNDERLINE);

        //Tour Phase
        mvprintw(9, 50, "Phase : %d", phase);
        if (tour==CHEVRE)        
        	mvprintw(10, 50, "Tour : Chevres");
        else
        	mvprintw(10, 50, "Tour : Tigres");


        if(phase==1 && tour == CHEVRE)
        	mvprintw(20,10,"Veuillez placer une chèvre");
        else
        {
        	if (phase==2 && tour == CHEVRE)
        		mvprintw(20,10,"Veuillez déplacer une chèvre");
        	else
	        	mvprintw(20,10,"Veuillez déplacer un tigre");
        }

        //Données
        mvprintw(16,50,"NB chevres mortes : %d", nbchevres_mortes);

        //Grille
        mvprintw(4,15,"[ ]--[ ]--[ ]--[ ]--[ ]");
        mvprintw(5,15," | \\  |  / | \\  |  / |");
        mvprintw(6,15," |  \\ | /  |  \\ | /  |"); 
        mvprintw(7,15,"[ ]--[ ]--[ ]--[ ]--[ ]");
        mvprintw(8,15," |  / | \\  |  / | \\  |");
        mvprintw(9,15," | /  |  \\ | /  |  \\ |");
        mvprintw(10,15,"[ ]--[ ]--[ ]--[ ]--[ ]");
        mvprintw(11,15," | \\  |  / | \\  |  / |");
        mvprintw(12,15," |  \\ | /  |  \\ | /  |"); 
        mvprintw(13,15,"[ ]--[ ]--[ ]--[ ]--[ ]");
        mvprintw(14,15," |  / | \\  |  / | \\  |");
        mvprintw(15,15," | /  |  \\ | /  |  \\ |");
        mvprintw(16,15,"[ ]--[ ]--[ ]--[ ]--[ ]");

        //PLacement des tigres
        /*Position possibles :
            4,16 -- 4,21 -- 4,26 -- 4,31 -- 4,36   
            
            7,16 -- 7,21 -- 7,26 -- 7,31 -- 7,36

            10,16 -- 10,21 -- 10,26 -- 10,31 -- 10,36

            13,16 -- 13,21 -- 13,26 -- 13,31 -- 13,36

            16,16 -- 16,21 -- 16,26 -- 16,31 -- 16,36
        */

         for (y = 0; y < nb_lignes; ++y)
         {
         	for (x = 0; x < nb_colonnes; ++x)
         	{
         		switch(t2D[x][y].type){
         		case 1 :
         			placer_tigre(y,x);
         			break;
         		case 0 :
         			placer_chevre(y,x);
         			break;
         		}
         	}
         }


        mvprintw(1,1," ");

        refresh();
}


void recuperer_mouse(int * x_win, int * y_win)
{
	MEVENT event;
	int ch;
	keypad(stdscr, TRUE);
    mousemask(  ALL_MOUSE_EVENTS, NULL);
    while(1)
    {
	    ch = getch();
	    switch(ch) {
			case KEY_MOUSE:
				if (getmouse(&event) == OK) {
					if (event.bstate & BUTTON1_CLICKED) { // si le bouton gauche a été préssé
						*y_win = event.y;
						*x_win = event.x;
						// clrtobot(); mvprintw(23,1, "X : %d   Y : %d", event.x, event.y); refresh();
						return;
					}
				}
				break;

			case 'q':
				endwin();
				exit(0);
				break;

			default:
				mvprintw(24,0, "Ce n'est pas un clic de souris...");
				refresh();
				break;
		}
	}
}

int verifier_click( Cellule **t2D, int* x_win, int* y_win)
{

	recuperer_mouse( x_win, y_win);

	 // mvprintw(2,1,"y_win : %d  x_win : %d", y_win,x_win);
	 
		
	if (*y_win < YMIN_GRILLE || *y_win > (YMAX_GRILLE) || *x_win < XMIN_GRILLE || *x_win > XMAX_GRILLE) { //Hors de la grille
		
		if (*y_win == Y_SAUVEGARDER && *x_win >= X_SAUVEGARDER ) {
			// Si on a appuyé sur sauvegarder
			return(SAUVEGARDER);
		}
		else if (*y_win == Y_CHARGER && *x_win >= X_CHARGER  ){
			// Si on a appuyé sur charger
			return(CHARGER);
		}
		else if (*y_win == Y_QUITTER && *x_win >= X_QUITTER  ){
			// Si on a appuyé sur charger
			return(QUITTER);
		}

		return(PAS_CASE);
	}
	// mvprintw(3,1,"%d - %d  / 3 != 0 || %d - %d  /  5 != 0", *y_win, YMIN_GRILLE, *x_win, XMIN_GRILLE); refresh();

	if ((*y_win-YMIN_GRILLE ) % 3 != 0 || (*x_win-XMIN_GRILLE) % 5 !=0 ){ // si dans la grille mais pas une case
		return(PAS_CASE);
	}

	recuperer_positon(x_win, y_win);
	 // mvprintw(2,1,"x_win : %d y_win : %d tableau : %d", *x_win, *y_win, t2D[*x_win][*y_win].type);

	return(t2D[*x_win][*y_win].type);

	refresh();

}



void placer_chevre(int x, int y)
    {
        attron( A_BOLD);
        mvprintw((x*3)+4, (y*5)+16, "C");
        attroff( A_BOLD);
        refresh();
    }

void placer_tigre(int x, int y)
    {
        attron( A_REVERSE);
        mvprintw((x*3)+4, (y*5)+16, "T");
        attroff( A_REVERSE);
        refresh();
    } 

//Il faut l'appeler comme ça : recuperer_positon(&x, &y)
void recuperer_positon(int* x, int* y)
    {
        *y = (*y-4)/3;
        *x = (*x-16)/5;
    }

 /*Pour les test */

void InitCellule(Cellule *c) {
  c->type=-1;
}


Cellule **alloc() {
	  int i;
	Cellule *t1D, **t2D; 
	  
	  if( (t1D=malloc(nb_lignes*nb_colonnes*sizeof(Cellule))) == NULL ) {
	    printf("erreur allocation memoire");
	    exit(EXIT_FAILURE);
	  }
	  if( (t2D=malloc(nb_lignes*sizeof(Cellule*))) == NULL ) {
	    printf("erreur allocation memoire");
	    exit(EXIT_FAILURE);
	  }
	  
    for (i=0;i<nb_lignes;i++) t2D[i] = &t1D[i*nb_colonnes];
  
  return t2D;
}


//initialisation de toutes les cellules du Bagchal

void InitTableau(Cellule **t2D) {
  int i,j; 
 for(i=0;i<nb_lignes;i++)
    for (j=0;j<nb_colonnes;j++)
      InitCellule(&(t2D[i][j]));
} 

// void print_byebye(WINDOW* menu_win)
// {   
//         int x, y;	
// 		x = 2;
// 		y = 2;
// 		box(menu_win, 0, 0);
// 		mvwprintw(menu_win, y, x, "Merci d'avoir joué à BagChal !\n");
// 		++y;
// 		mvwprintw(menu_win, y, x, "Bye Bye ! ! !\n");
// 		wrefresh(menu_win);
// }


void new_sauvegarde(Partie partie)
{
	clear();
	char mesg[]="Veuillez entrer le nom du fichier : ";
	char str[80];
	 int row,col;				
	 getmaxyx(stdscr,row,col);		
	 mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);
	                     
	 getstr(str);

	 sauvegarder(partie, str);

	endwin();
}

int confirm_quitter()
{
	clear();
	char mesg[]="Etes-vous sûr(e) de vouloir quitter ? (Y pour valider)";
	 int row,col, c;				
	 getmaxyx(stdscr,row,col);		
	 mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);

	c=getch();

	if (c=='Y' || c== 'y')
	{
		return 1;
	}
	return 0;
	endwin();
}


int jouer_partie_IA_tigre(Cellule** t2D, Partie partie)
{
	int testclick;	
	// int nbchevres_mortes=0;

	int tour = CHEVRE;
	int x,y;
	int x2, y2;
	int c;

	plateauDepard(getPlateau(partie));

	while(1)
	{
		clear();
		tour = getCoup(getPlateau(partie))%2; 
		// afficher_Grille( getPhase(getPlateau(partie)),getCaptured(getPlateau(partie)),tour, t2D, getPlateau(partie));
		// refresh();

		//Si c'est le tour des chevres
		if(tour==CHEVRE)		
		{
			if(getPhase(getPlateau(partie))==1)
			{	
				do{
					afficher_Grille( getPhase(getPlateau(partie)),getCaptured(getPlateau(partie)),tour, t2D, getPlateau(partie));
					refresh();
					testclick=verifier_click(t2D, &x, &y);
					if (testclick==SAUVEGARDER)//Sauvegarde
						new_sauvegarde(partie);
				}while (testclick!=-1 && testclick!=QUITTER);//Tant qu'il ne click pas sur un endroit vide
					if (testclick==QUITTER)
						if(confirm_quitter())return 1;
				// mvprintw(3,1,"testclick : %d", testclick);refresh();c=getch();
				placerChevre(getPlateau(partie), y, x);				
			}else
			{
				do{ //On selectionne une chevre
					afficher_Grille( getPhase(getPlateau(partie)),getCaptured(getPlateau(partie)),tour, t2D, getPlateau(partie));
					mvprintw(18,1,"Veuillez cliquer d'abord sur une chevre             ");
					refresh();
					testclick=verifier_click(t2D, &x, &y);
					if (testclick==SAUVEGARDER)//Sauvegarde
						new_sauvegarde(partie);
				}while(testclick!=0 && testclick !=QUITTER);
					if (testclick==QUITTER)
						if(confirm_quitter())return 1;
				do{ //On selectionne un emplacement vide
					afficher_Grille( getPhase(getPlateau(partie)),getCaptured(getPlateau(partie)),tour, t2D, getPlateau(partie));
					mvprintw(18,1,"Maintenant sur un emplacement vide               ");
					refresh();
					testclick=verifier_click(t2D, &x2, &y2);
					if (testclick==SAUVEGARDER)//Sauvegarde
						new_sauvegarde(partie);
				}while(testclick!=-1 && testclick !=QUITTER);
					if (testclick==QUITTER)
						if(confirm_quitter())return 1;
				deplacementChevre(getPlateau(partie),y,x,y2,x2);
			}
		}else
		{

			deplacerTigreIA (getPlateau(partie)) ;getch();
			afficher_Grille( getPhase(getPlateau(partie)),getCaptured(getPlateau(partie)),tour, t2D, getPlateau(partie));
			refresh();
			
		}

		//Fin du tour
		if (gagnant(getPlateau(partie))==CHEVRE)
		{
			clear();
			mvprintw(7,40,"Les chevres ont gagnées ! ");
			mvprintw(8,10,"Appuyez sur q pour quitter ");
			do{
				c = getch();
			}while(c!='q');
			clear();
			return 1;
		}else
		{
			if (gagnant(getPlateau(partie))==TIGRE)
			{
				clear();
				mvprintw(7,40,"Les tigres ont gagnées !");
				mvprintw(8,40,"Appuyez sur q pour quitter ");
				do{
					c = getch();
				}while(c!='q');
				clear();
				return 1;
			}
		}
		// mvprintw(22,1,"Valeure retorunée par le click : %d", testclick);
		refresh();
	};
}

Partie charger_partie(void)
{
	Partie p =creerPartie();
	FILE * fichier;

	clear();
	char mesg[]="Veuillez entrer le nom du fichier à charger  : ";
	char mesg2[]="Impossible d'ouvrir le fichier ";
	char str[80];
	 int row,col;				
	 getmaxyx(stdscr,row,col);		
	 mvprintw(row/2,(col-strlen(mesg))/2,"%s",mesg);        
	 getstr(str);
	if((fichier = fopen(str, "r+")))
	{
		lirePlateau (fichier, getPlateau(p));
	}else
		mvprintw(row/2,(col-strlen(mesg2))/2,"%s",mesg2); 

	return(p);
}



//L'IA joue
			// deplacerTigreIA (getPlateau(partie)) ;
			// afficher_Grille( getPhase(getPlateau(partie)),getCaptured(getPlateau(partie)),tour, t2D, getPlateau(partie));
			// refresh();