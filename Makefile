all : composanteConnexe cases grille listeComposanteConnexe
CC = gcc
LIBRARIES = -lcunit -lm -g -O0
CFLAGS = -Wall -Wextra -ansi
SRC = Grille.c Cases.c ComposanteConnexe.c ListeComposanteConnexe.c
OBJ = ${SRC: .c = .o}

.c.o:
	$(CC) $(CFLAGS) -c $< $(LIBRARIES)

composanteConnexe : $(OBJ) ComposanteConnexe-testU.o
	$(CC) $(OBJ) ComposanteConnexe-testU.o -o composanteConnexe $(LIBRARIES)

ComposanteConnexe-testU.o : ComposanteConnexe-testU.c 
	$(CC) $(CFLAGS) $(SRC) ComposanteConnexe-testU.c -c $(LIBRARIES)

cases : $(OBJ) Cases-testU.o
	$(CC) $(OBJ) Cases-testU.o -o cases $(LIBRARIES)

Cases-testU.o : Cases-testU.c 
	$(CC) $(CFLAGS) $(SRC) Cases-testU.c -c $(LIBRARIES)

grille : $(OBJ) Grille-testU.o
	$(CC) $(OBJ) Grille-testU.o -o grille $(LIBRARIES)

Grille-testU.o : Grille-testU.c 
	$(CC) $(CFLAGS) $(SRC) Grille-testU.c -c $(LIBRARIES)

listeComposanteConnexe : $(OBJ) ListeComposanteConnexe-testU.o
	$(CC) $(OBJ) ListeComposanteConnexe-testU.o -o listeComposanteConnexe $(LIBRARIES)

ListeComposanteConnexe-testU.o : ListeComposanteConnexe-testU.c 
	$(CC) $(CFLAGS) $(SRC) ListeComposanteConnexe-testU.c -c $(LIBRARIES)
