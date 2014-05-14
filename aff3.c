#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>

#define WIDTH 30
#define HEIGHT 10 

#define ENTER 10

int startx = 0;
int starty = 0;

char *choices[] = { 
            "Creer",
            "Jouer",
            "Sauvegarder",
            "Charger",
            "Quitter",
          };
char *choices_creer[] = { 
            "Humain vs humain",
            "Humain vs IA",
            "Retour",
          };          
int n_choices = sizeof(choices) / sizeof(char *);
int nbr_choices_Creer= sizeof(choices_creer) / sizeof(char *);

void print_menu(WINDOW *menu_win, int highlight);
int scroll_menu(WINDOW *items);
void aff_creer_partie(WINDOW* win, int highlight);

int main()
{   WINDOW *menu_win, *win;
    int highlight = 1;
    int choice = 1;
    //int c;

    initscr();
    clear();
    noecho();
    cbreak();   /* Line buffering disabled. pass on everything */
    intrflush(stdscr, FALSE);
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;
        
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    keypad(win, TRUE);
    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
    refresh();
    wclear(menu_win);
    print_menu(menu_win, highlight);
    choice=scroll_menu(menu_win);
    int test=1;
    while(test)
    {
        wclear(menu_win);
        print_menu(menu_win, highlight);
        choice=scroll_menu(menu_win);
        switch(choice)
        {
            case 1:
                wclear(menu_win);
                aff_creer_partie(menu_win, highlight);
                choice=scroll_menu(menu_win);
                if (choice==3)
                {
                    break;
                }
            break;
            case 2:
                
            break;
            case 3:

            break;
            case 4:

            break;
            case 5: //On quitte
                test=0;
            break;
        }
    }
        clrtoeol();
        refresh();
        endwin();
        return 0;
}

void aff_creer_partie(WINDOW* win, int highlight)
{
    int x, y, i;    

    x = 2;
    y = 2;
    box(win, 0, 0);
    for(i = 0; i < nbr_choices_Creer; ++i)
    {   if(highlight == i + 1) /* High light the present choice */
        {   wattron(win, A_REVERSE); 
            mvwprintw(win, y, x, "%s", choices_creer[i]);
            wattroff(win, A_REVERSE);
        }
        else
            mvwprintw(win, y, x, "%s", choices_creer[i]);
        ++y;
    }
    wrefresh(win);
}

void print_menu(WINDOW *menu_win, int highlight)
{
    int x, y, i;    

    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for(i = 0; i < n_choices; ++i)
    {   if(highlight == i + 1) /* High light the present choice */
        {   wattron(menu_win, A_REVERSE); 
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}

// int scroll_menu(WINDOW *items,int count)
// {
//         int key;
//         int selected=0;
//         while (1) {
//                 key=getch();
//                 if (key==KEY_DOWN || key==KEY_UP) {
//                         wnoutrefresh(items);
//                         if (key==KEY_DOWN) {
//                                 selected=(selected+1) % count;
//                         } else {
//                                 selected=(selected+count-1) % count;
//                         }
//                         wnoutrefresh(items);
//                         doupdate();
//                 } else if (key==ENTER) {
//                         return selected;
//                 }
//         }
// }

int scroll_menu(WINDOW *menu_win)
{
    int highlight=0, c;
    while(1)
    {   c = wgetch(menu_win);
        switch(c)
        {   case KEY_UP:
                if(highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == n_choices)
                    highlight = 1;
                else 
                    ++highlight;
                break;
            case 10:
                return (highlight);
                break;
            default:
                mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
                refresh();
                break;
        }
        print_menu(menu_win, highlight);
    }
    
}