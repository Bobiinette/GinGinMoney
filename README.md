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


#=======================================solveur=====================================================

Au lancement du jeu, une nouvelle fenêtre apparait et demande à l'utilisateur de rentrer la taille de grille qu'il veut obtenir (exemple 10 pour une grille 10*10), et le nombre de coups qu'il s'impose pour faire la grille (max 70).
A tout moment, le joueur peut quitter le jeu en appuyant la petite croix en haut à gauche.

Une fois que le joueur a entré les paramètre de configuration du jeu, deux solveur sont lancés. Le premier donne sa solution obtimale dans solutionTableau.txt. Le deuxième dans solution.txt. Il suffit d'ouvrir les fichier pour pouvoir voir les solutions proposées.

Le solveur tableau donne aussi en console le nombre de coups minimal trouvé et le nombre d'appel effectué.




