Projet A.S.D.L Lignes RATP de paris
===================

**Version 1.2 :**

* Création du mode fichier :
	* Toutes les stations des lignes sont dans des fichiers
	* Suppression de lignes.c
	* Les 14 lignes sont présentes
* Mise en fonction des id des stations
* Fix ::
	* Les séparations de lignes en deux (les branches des lignes)
	* Stations accessibles que dans un sens (ligne 10 qui n'a des stations que pour une direction)
* Amélioration de la recherche de stations : propose les stations avec une récurrence du mot recherché

**Version 1.1 :**

* Changement de l'affichage en fonction récursive
* Ajout des sous choix utilisateurs et de l'agent R.A.T.P
* Fix ::
	* `ligne_station`
	* `get_station_ouverte`
	* `ligne_ouverte`
	* `ouvrir_station`/`fermer_station`
	* `retirer_station_carte`
* Implementation ligne 3
* Ajout d'une securitée : vérifie si les lignes existent
* Réorganisation de projet_asdl.h et projet_asdl.c ::
	* Création de sous fichiers menu.c et lignes.c pour alléger projet_asdl.c

**Version 1.0 :**

* Mise en place du projet
* Création des fonctions de base
* Création du mot de passe pour l'agent RATP
* Recherche itineraire :
	* Cas de base itinéraire sur la meme ligne
	* Quitte la fonction si depart = arrivee
* Lignes 1 et 2 implémentées
