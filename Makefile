all : composanteConnexe cases grille listeComposanteConnexe
CC = gcc
LIBRARIES = -lcunit -lm -g -O0 -lSDL -lSDLmain
CFLAGS = -Wall -Wextra -ansi
SRC = Grille.c Cases.c ComposanteConnexe.c ListeComposanteConnexe.c
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

colorFlood : $(OBJ) colorFlood.o
	$(CC) $(OBJ) colorFlood.o -o colorFlood $(LIBRARIES)

colorFood.o : colorFlood.c 
	$(CC) $(CFLAGS) colorFlood.c -c

colorFloodSDL : $(OBJ) colorFlood_SDL.o
	$(CC) $(OBJ) colorFlood_SDL.o -o colorFloodSDL $(LIBRARIES)

colorFood_SDL.o : colorFlood_SDL.c 
	$(CC) $(CFLAGS) colorFlood_SDL.c -c
