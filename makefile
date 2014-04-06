#makefile pile 
CC=gcc
OPT=-Wall -g
EXEC= bc

all : $(EXEC)
#compile Element
elements.o: elements.c
	$(CC) -o elements.o -c elements.c $(OPT)

#compile pdc
plateau.o : plateau.c
	$(CC) -o plateau.o -c plateau.c $(OPT)

	
#compile main
main.o : main.c
	$(CC) -o main.o -c main.c $(OPT)

#link Element,pile et main

$(EXEC): elements.o plateau.o main.o
	$(CC) elements.o plateau.o main.o -o $(EXEC)

clean:
	rm -rf *.o *.exe *.out $(EXEC)

