#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>


void placer_chevre(int x, int y)
    {
        attron( A_BOLD);
        mvprintw((x*3)+4, (y*5)+16, "C");
        attroff( A_BOLD);
        refresh();
    }

void placer_tigre(int x, int y)
    {
        attron( A_BOLD);
        mvprintw((x*3)+4, (y*5)+16, "T");
        attroff( A_BOLD);
        refresh();
    } 

void recuperer_positon(int* x, int* y)
    {
        *x = (*x/3)-4;
        *y = (*y/5)-16;
    }


int main(int argc, char const *argv[])
{

    initscr();
    clear();
    noecho();
    cbreak();   /* Line buffering disabled. pass on everything */
    intrflush(stdscr, FALSE); 
    keypad(stdscr, TRUE);


    //Données
    int phase=1, nbchevres_mortes=0;
    char* tour="chevres";

    while(1)
    {
        attron(A_BOLD);
        mvprintw(1,10,"Bienvenue sur le jeu de Bag-CHal");
        attroff(A_BOLD);        
        box(stdscr, 0,0);

        //Menu
        mvprintw(5,50,"Charger");
        mvprintw(6,50,"Sauvegarder");
        mvprintw(7,50,"Quitter");

        //Tour Phase
        mvprintw(9, 50, "Phase : %d", phase);
        mvprintw(10, 50, "Tour : %s", tour);

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
        placer_tigre(0,0);
        placer_tigre(0,4);
        placer_tigre(4,0);
        placer_tigre(4,4);
        

        // mvprintw(20,50," ");

        refresh();
    }

    return 0;
}

// void afficher_Grille( Cellule **t2D, int highlightX, int highlightY)
// {
//     int X=0,Y=0;
//     int li;
//     int col;
//     char* tab[9]={ "|\\|/|\\|/|",
//                     "|/|\\|/|\\|",
//                     };
//     for(li=0;li<9;li++)
//     {
//         if (li%2==1) //Cas où on n'affichera jamais de valeur
//         {
//             col=0;
//             switch(li)
//             {
//                 case 1 :
//                     mvprintw( YMIN_GRILLE+li, XMIN_GRILLE+col, "%s", tab[0] );
//                 break;
//                 case 5 :
//                     mvprintw( YMIN_GRILLE+li, XMIN_GRILLE+col, "%s", tab[0] );
//                 break;
//                 case 3 :
//                     mvprintw( YMIN_GRILLE+li, XMIN_GRILLE+col, "%s", tab[1] );
//                 break;
//                 case 7 :
//                     mvprintw( YMIN_GRILLE+li, XMIN_GRILLE+col, "%s", tab[1] );
//                 break;
//             }
//         }else //Sinon c'est toujours le même affichage
//         {
//             X=0;
//             for (col = 0; col < 9; ++col)
//             {
//                 if (col%2==0)//On va chercher la valeure
//                 {
//                     if (t2D[li][col].type==0)//Chevre
//                     {
//                         mvprintw( YMIN_GRILLE+li, XMIN_GRILLE+col, "%s", "c");
//                     }
//                     else{
//                         if (t2D[li][col].type==1)//tigre
//                         {
//                             mvprintw( YMIN_GRILLE+li, XMIN_GRILLE+col, "%s", "t");
//                         }else
//                         {
//                             mvprintw( YMIN_GRILLE+li, XMIN_GRILLE+col, "%s", ".");
//                         }
//                     }
//                     X++;
//                 }else
//                 {
//                     mvprintw( YMIN_GRILLE+li, XMIN_GRILLE+col, "%c", '-');
//                 }
//             }
//             Y++;
//         }
//     }
//     refresh();
// }