CC = gcc
APPLI = grille
LIBRARIES = -lm
CFLAGS = -Wall -Wextra -ansi
SRC = Grille.c Cases.c ComposanteConnexe.c ListeComposanteConnexe.c main.c
OBJ = ${SRC: .c = .o}

.c.o:
	$(CC) $(CFLAGS) -c $< $(LIBRARIES)

$(APPLI) : $(OBJ)
	$(CC) $(OBJ) -o $(APPLI) $(LIRARIES)

