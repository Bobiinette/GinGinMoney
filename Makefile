CC = gcc
APPLI = grille
LIBRARIES = -lcunit -lm -g -O0
CFLAGS = -Wall -Wextra -ansi
SRC = Grille.c Cases.c ComposanteConnexe.c ListeComposanteConnexe.c ComposanteConnexe-testU.c
OBJ = ${SRC: .c = .o}

.c.o:
	$(CC) $(CFLAGS) -c $< $(LIBRARIES)

$(APPLI) : $(OBJ)
	$(CC) $(OBJ) -o $(APPLI) $(LIBRARIES)

