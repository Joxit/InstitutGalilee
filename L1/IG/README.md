# Projet - L1 Initiation aux Interfaces Graphiques (IIG) - 2011

## Règles du jeu
Source : wikipedia http://fr.wikipedia.org/wiki/Puissance_4
“Le but du jeu est d’aligner 4 pions sur une grille comptant 6 rangées et 7 colonnes. Chaque joueur dispose de 21 pions d’une couleur (par convention, en général jaune ou rouge). Tour à tour les deux joueurs placent un pion dans la colonne de leur choix, le pion coulisse alors jusqu’à la position la plus basse possible dans ladite colonne suite à quoi c’est à l’adversaire de jouer. Le vainqueur est le joueur qui réalise le premier un alignement (horizontal, vertical ou diagonal) d’au moins quatre pions de sa couleur. Si alors que toutes les cases de la grille de jeu sont remplies aucun des deux joueurs n’a réalisé un tel alignement, la partie est déclarée nulle.”

## Code source puissance 4
### Ce qu’il faut utiliser
Un code source permettant de représentant le jeu de puissance 4 et d’y jouer est fourni. Il est organisé comme suit :

* case.h : représentation d’une case du jeu (coordonnées de la case dans le jeu, état de la case au cours d’une partie, coup de la partie au cours duquel la case a éventuellement été jouée) ;
* dim.h : représentation des dimensions du jeu (nombre de lignes, nombre de colonnes, taille d’un alignement gagnant) ;
* partie.h : représentation d’une partie du jeu (dimensions du jeu, ensemble de cases, état d’une partie en cours, joueur dont c’est le tour de jouer dans une partie en cours, nombre de coups joués dans une partie en cours).

L’application à développer utilisera donc les 6 fichiers case.h, case.c, dim.h, dim.c, partie.h et partie.c. Néanmoins, **seules les fonctions de l'interface "partie.h" sont amenées à être directement appelées par votre programme** :

* Construction / destruction : `partie_new`, `partie_free`
* Consultation paramètres du jeu : `partie_get_nbcol`, `partie_get_nbrow`, `partie_get_size`
* Consultation partie en cours : `partie_get_etat`, `partie_get_tourjoueur`, `partie_get_nbcoup`, `partie_est_colonne_pleine`, `partie_get_case_etat`
* Fonctions de jeu : `partie_nouvelle_partie`, `partie_jouer_colonne`, `partie_tour_suivant`
* Fonctions annexes : `partie_get_etat_nom`, `partie_get_statut_nom`

### Guide de lecture
**Toutes ces fonctions sont documentées dans le fichier partie.h**. Quelques précisions néanmoins :

* Par “pré-condition”, on entend condition vérifiée par les paramètres en entrée de fonction et qui n’est donc pas testée par la fonction. Par exemple, pour la fonction `partie_est_colonne_pleine` :
```C
/* Pré-conditions : 
- partie instanciée (=> dont le tableau partie->plateau)
- 0 <= j < partie->n */
int partie_est_colonne_pleine(s_partie* partie, int j);
```
Si jamais par exemple `partie == NULL` ou `j == -1`, le programme sort sans aucun doute en erreur (car la fonction tentera des accès du genre `partie->dim et partie->plateau[-1]` qui sont invalides).
Pour bien utiliser la biliothèque, il faut donc s’assurer de toujours satisfaire les pré-conditions qui sont indiquées.

* Par “post-condition”, on entend condition vérifiée par les arguments une fois la fonction terminée,
lorsque tout s’est bien passé.
Enfin, quelques précisions sur les fonctions de jeu :
* il n’est pas besoin de faire appel à `partie_nouvelle_partie` avant de lancer la première partie (mais
ce n’est évidemment pas gênant de le faire) ;
* après avoir joué un coup, si la partie n’est pas finie à l'issue de ce coup, il faut absolument faire appel
à la fonction `partie_tour_suivant` (sinon c’est le joueur qui vient de jouer qui aura de nouveau la
main au tour suivant) ;
* après avoir joué un coup, si la partie est finie à l'issue de ce coup, il ne faut pas faire appel à la fonction `partie_tour_suivant` (sinon la fonction la fonction `partie_nouvelle_partie` fera commencer
l'éventuelle partie suivante par le mauvais joueur).

Pour illustration, un programme permettant de dérouler le jeu en mode console est également proposé :
il s’agit du fichier “puissance4_console.c”. Pour générer l’'exécutable, utiliser le fichier `makefile` fourni :
`make -f makefile_console`

### Travail demandé

Il s’agit de permettre à un utilisateur de jouer au jeu de puissance 4 via une interface graphique. Il faut donc (contrat de base) :

1. D’abord concevoir une interface d’un point de vue purement graphique : quels composants graphiques utiliser, comment les imbriquer entre-eux, quelles sont leurs modalités d’affichage. Ex. pour s’authentifier : il faut une boîte de dialogue, un bouton de validation, un libellé (indiquant “pseudo :”) et une zone de saisie pour saisir son pseudo côte à côte, une boite horizontale pour ordonner le libellé et la zone de saisie.
2. Ensuite définir comment cette interface doit interagir avec l’utilisateur : à quel moment du jeu l’utilisateur doit-il ou ne doit-il pas avoir accès à tel ou tel composant de l’interface (que cet accès concerne la capacité de voir ou d’agir). Ex. pour s’authentifier : le bouton ne peut être cliqué que lorsque la zone de saisie comporte au moins 8 caractères.
3. Enfin définir comment cette interface intéragit avec le jeu : quand l’interface doit-elle déclencher une action sur le modèle, comment l’inerface se met-elle à jour suite à une modification du modèle. Ex. pour s’authentifier : lorsque l’utilisateur clique sur le bouton, l’application vérifie que le pesudo saisi fait partie de la liste des peusdo du modèle (imaginons en effet que le modèle comporte un tel annuaire) ; si le pseudo est accepté par le modèle, la fenêtre principale qui aura lancé la boîte de dialogue se personnalise en fonction de ce pseudonyme (mise à jour de la vue suite à l’action de
validation demandée au modèle).

## Comment ca marche

Bienvenue et merci de me lire.

Programme réalisé par MAGLOIRE Jones pour le projet d'Interface Graphique.

### ORGANISATION

Le programme est séparé en plusieurs fichiers ::

- gtk_puissance4.c : Fonction principale du programme
- gtk_puissance4.h : Déclaration des fonctions de projet_asdl.c; lignes.c; menu.c
- menu.c : Définitions des fonctions pour l'affichage du menu
- makefile : compilateur
- Dossier img : contient toutes les images de l'interface
- Code source du modèle : dim.h, dim.c, case.h, case.c, partie.h, partie.c
- user.dat : Contient toutes les données des joueurs enregistrés
- CHANGELOG.md : note des versions effectuées lors du projet

### COMPILATION

Vous pouvez compiler en tapant
```sh
make projet
```
### LANCEMENT

Pour lancer le programme tapez
```sh
./projet
```
### RANGER

Pour suprimer les *.o
```sh
make clean
```