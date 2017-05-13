all : composanteConnexe cases grille listeComposanteConnexe colorFlood
APPLIS = composanteConnexe cases grille listeComposanteConnexe colorFlood
CC = gcc
LIBRARIES = -lcunit -lm -g -O0 -lSDL -lSDLmain -lSDL_ttf
CFLAGS = -Wall -Wextra -ansi
SRC = Grille.c Cases.c ComposanteConnexe.c ListeComposanteConnexe.c solveurTableau2.c solveur2.c
HEADERS = Grille.h Cases.h ComposanteConnexe.h ListeComposanteConnexe.h solveurTableau2.h solveur2.h
DOXYSRC = $(SRC) $(HEADERS) colorFlood.c colorFlood.h
OBJ = ${SRC: .c = .o}

.c.o:
	$(CC) $(CFLAGS) -c $< $(LIBRARIES)

composanteConnexe : $(OBJ) ComposanteConnexe-testU.o
	$(CC) $(OBJ) ComposanteConnexe-testU.o -o composanteConnexe $(LIBRARIES)

ComposanteConnexe-testU.o : ComposanteConnexe-testU.c
	$(CC) $(CFLAGS) ComposanteConnexe-testU.c -c

cases : $(OBJ) Cases-testU.o
	$(CC) $(OBJ) Cases-testU.o -o cases $(LIBRARIES)

Cases-testU.o : Cases-testU.c
	$(CC) $(CFLAGS) Cases-testU.c -c

grille : $(OBJ) Grille-testU.o
	$(CC) $(OBJ) Grille-testU.o -o grille $(LIBRARIES)

Grille-testU.o : Grille-testU.c
	$(CC) $(CFLAGS) Grille-testU.c -c

listeComposanteConnexe : $(OBJ) ListeComposanteConnexe-testU.o
	$(CC) $(OBJ) ListeComposanteConnexe-testU.o -o listeComposanteConnexe $(LIBRARIES)

ListeComposanteConnexe-testU.o : ListeComposanteConnexe-testU.c
	$(CC) $(CFLAGS) ListeComposanteConnexe-testU.c -c

colorFlood : $(OBJ) colorFlood.o colorFlood_SDL.o
	$(CC) $(OBJ) colorFlood.o colorFlood_SDL.o -o colorFlood $(LIBRARIES)

colorFlood.o : colorFlood.c
	$(CC) $(CFLAGS) colorFlood.c -c

colorFlood_SDL.o : colorFlood_SDL.c
	$(CC) $(CFLAGS) colorFlood_SDL.c -c

clean :
	-rm *.o $(APPLIS)

doc : Doxyfile $(DOXYSRC)
	doxygen Doxyfile
