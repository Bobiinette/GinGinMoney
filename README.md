# GinGinMoney

#==============================================Instalation================================================

Lancer la commande make [nom module] dans la console. Par exemple make grille. La compilation d'un des quatres modules Grille.c, Cases.c, ComposantConnexe.c et ListeComposanteConnexe.c se lance alors. Puis lancer l'executable crée qui permet d'effectuer les tests unitaires. Il faudra penser à le lancer avec valgrind pour observer les fuites de mémoire.

#Cibles du make :
Les différentes cibles de makes sont :

composanteConnexe 
cases 
grille 
listeComposanteConnexe 

	Ces 4 cibles là sont pour la création des programmes de tests unitaires sur chacun des modules.

colorFlood

	Pour créer le jeu color flood.

clean

	Pour supprimer les différents .o et tous les programmes crées.

documentation

	Pour créer la documentation du projet.

#Librairies requises :
Pour compiler le module colorFlood, les librairies libsdl2-dev et libsdl-ttf2.0-dev sont nécessaires.

Il est possible de lancer le jeu avec la prise en charge de valgrind pour la gestion des fuites mémoires en executant le script colorFlood.sh.
Il y a actuellement des fuites mémoires dues à l'utilisation de la SDL que nous ne pouvons pas résoudre.


#=======================================Comment jouer=====================================================

Au lancement du jeu, il sera demandé à l'utilisateur de rentrer dans la console la taille de grille qu'il veut obtenir (exemple 10 pour une grille 10*10), et le nombre de coups qu'il s'impose pour faire la grille (max 70).
A tout moment, le joueur peut quitter le jeu en appuyant sur la touche Echap.

Le joueur doit remplir toute la grille de la même couleur. Pour cela on part du coin en haut à gauche, et le joueur doit cliquer sur les composantes connexes (emsemble de cases adjacentes de la même couleur) adjacentes à la composante connexe en haut à gauche pour changer la couleur de celle ci et la faire grandir. Ainsi, à chaque clic, l'utilisateur agrandi la taille de sa composante connexe en absobant toutes les composantes connexes adjacentes à celle en haut à gauche de la même couleur que la couleur sélectionnée. A chaque clic cepandant, le nombre de coups restants diminue de 1.

Lorsque le joueur a réussit à remplir toute la grille de la même couleur, un message de victoire est affichée. Sinon un message de défaite est affiché. Le joueur doit alors appuyé sur Echap pour quitter le jeu.




