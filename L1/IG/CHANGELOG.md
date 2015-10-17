Projet Interface Graphique Puissance 4 sous GTK+
===================
**Version 1.5**

- Clean up :
	- séparation de menu.c :
		- gtk_menu.c contient toutes les fonctions de création GTK+
		- menu.c contient toutes les fonctions qui n'utilise pas d'objet GTK+
	- `get_classement` : qui renvoie la chaine de caractère du classement (dans menu.c) utilisé par Top_5 (dans gtk_menu.c)
	- `file_open` : renvoie l'adresse du fichier users.dat en ayant fait une vérification et création si besoin.
- Mise à jour :
	- l'IA bloque dès que le joueur a 2 pions alignés pour anticiper avant qu'il en ait 3.
	- l'IA cherche au début s'il a 3 pions en colonne dans le plateau pour gagner
	- avant de jouer aléatoirement, l'IA regarde s'il a +2 pions sur une ligne dans le plateau pour jouer
	- remplacement des "jouer_colonne == -1" par "jouer_colonne < 0"
	- nouveaux pions
- Ajout :
	- `menu_about` : dialogue des droits et compatibilité

**Version 1.4**

- Mise à jour :
	- Meilleure tenue de l'IA, il peut contrer les coups sur les lignes a tout moment, il verifie a chaques tour si le joueur n'a pas une serie de 3 pions sur lignes dans le jeu
	- Suppresion de `gtk_widget_get_sensitive` qui n'existe pas avant GTK+ 2.18
	- enleve la sensibilité du 2eme GtkEntry contre l'IA
- Ajout :
	- fonction IA_jouer_ligne pour alleger IA_jouer
	- nom Int. Art. pour l'IA, il aura ses scores

**Version 1.3**

- Ajout :
	- securité lors de la recherche des pseudos, si le fichier a été supprimé, on en créé un autre
- Clean up du code
- Version envoyé aux professeurs

**Version 1.2**

- Mise a jour :
	- `gtk_jouer_colonne` && continuer pour gerer l'IA
	- Barre des menus sous menu Partie et Option
	- Utilisation de `GtkTable` à la place des `GtkBox`
- Ajout	:
	- Création d'une Intelligence Artificielle :
		- fonctions de l'IA dans int_art.c basées sur les fonctions de partie.c :
			- `IA_tester_ligne`
			- `IA_tester_colonne`
			- `IA_jouer`
		- Menu de l'IA dans menu.c :
			- `menu_IA`
		- L'IA  ne fait que contrer les  coups du vrai joueur et joue aléatoirement

**Version 1.1 :**

- Mise a jour :
	- Reorganisation des fichiers :
		- Separations des fonctions du menu et celles du jeu
	- `changer_nom` : lors du changement de nom, la fonction cherche dans user.dat s'il existe déja
	- construire :
		- ajout des nouveaux menus
		- Lecture des deux premiers pseudos pour les noms des joueurs
	- sauvegarde : gère les pseudos, met en premier les joueurs qui ont sauvegardé la dernière partie
- Ajout :
	- `get_score` : ouvre une boite de dialogue affichant les scores
	- Création de la structure joueur_s pour les joueurs, mis dans ctr
	- Mode Fichier (`users.dat`) : Sauvegarde des joueurs et leurs parcours
		- Top_5 : ouvre une fenetre affichant le Top 5 des joueurs
		- `sauvegarder_score` : sauvegarde les scores dans le fichier user.dat

**Version 1.0 :**

- Implementation du jeu simple avec des Images crées sous photoshop
- Mises à jour :
	- construire et renit :
		- Mode image accepté
		- Création du label qui affiche le tour du joueur
- Ajout ;
	- confirmer : confirme la sortie du jeu
	- `free_gtk` : liber la mémoire de l'environnement GTK+
	- `nom_joueur` et `score_joueur` 1 et 2 dans la structure ctr
	- Barre de menu :
		- `set_option` : affichage du menu pour changer de pseudo
		- `changer_nom` : changement du pseudo
		- Quitter : quitte la partie
	- `afficher_fenetre` : qui ferme le menu pour re afficher la fenêtre principale

**Beta :**

- Création des Widgets l'interface dans la structure gtk
- Mise en place du controlleur qui rassemble la partie et l'environement
- Labels utilisés pour afficher les pions avec X et O et changement de couleurs
- Création de fonctions :
	- construire  : construit l'environement GTK+
	- gtk_jouer_colonne : fonction attribué aux boutons, le jeu du puissance 4
	- continuer : à la fin de la partie demande si on continue
	- reinit : reinitialise la partie si on continue de jouer
*
