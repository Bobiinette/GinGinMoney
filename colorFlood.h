#ifndef COLORFLOOD_H
#define COLORFLOOD_H

void viderBuffer();
int saisirTaille();
int testTaille(int taille);
void afficheLigneDessus(Case **grille, int taille, int ligne);
void afficheInterLigneDessus(int taille);
void afficheGrille(Case **grille, int taille);
void setGrilleTest(Case **grille, ComposanteConnexe *cc);
#endif