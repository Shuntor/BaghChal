#makefile pile 
CC=gcc
OPT=-Wall -g -lm 
EXEC= bc

all : $(EXEC)
#compile Element
elements.o: elements.c
	$(CC) -o elements.o -c elements.c $(OPT)

#compile plateau
plateau.o : plateau.c
	$(CC) -o plateau.o -c plateau.c $(OPT)

#compile affichage
affichage.o : affichage.c
	$(CC) -o affichage.o -c affichage.c $(OPT)

#compile partie
partie.o : partie.c
	$(CC) -o partie.o -c partie.c $(OPT)
	
#compile main
main.o : main.c
	$(CC) -o main.o -c main.c $(OPT)

#link element, plateau, partie et main

$(EXEC): elements.o plateau.o partie.o affichage.o main.o
	$(CC) elements.o plateau.o partie.o affichage.o main.o -o $(EXEC) -lcurses

clean:
	rm -rf *.o *.exe *.out $(EXEC) 

