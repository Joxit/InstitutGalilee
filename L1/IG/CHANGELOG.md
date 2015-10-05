Projet Interface Graphique Puissance 4 sous GTK+
===================

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
