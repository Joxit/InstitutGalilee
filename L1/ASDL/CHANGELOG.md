Projet A.S.D.L Lignes RATP de paris
===================

**Version 1.4 :**
	
* Séparation de projet_asdl.c en 3 fichiers
	* actions.c contenant toutes les fonctions nécessaires à la création du réseau RATP et des fonctions de l'agent RATP
	* infos.c contenant toutes les fonctions nécessaires à l'interface utilisateur
	* aide.c contenant les fonctions nécessaires pour la cumunication entre le programme et l'utilisateur
* Fix ::
	* `retirer_station_carte` : plantait quand il ne trouvait pas de stations
	* `distance[][]` : ne donnait pas toutes les distances de toutes les stations doit repasser de la fin jusqu'au début pour compléter le tableau (CPU Time +0.5)

**Version 1.3 :**

* Recherche itinéraire :
	* Cas normal itinéraire sur tout le reseau avec le plus court chemin (autant de corréspondances qu'il le faut)
	* Utilisation des id pour arrivee et depart ainsi que de `distance[][]`
* Création de fonctions :
	* `get_id` qui prend un `nom_station` et renvoie un id
	* `get_nom_station` qui prend un id et renvoie le nom
	* `id_proche` qui indique l'id de la station la plus proche de arrivee
	* `get_choix_statio`n qui demande le nom de la station a l'utilisateur
* Suppression de fonctions :
	* `retirer_ligne` inutile et improbable dans la vie réele
	* `ajout_ligne` n'est plus disponible pour l'agent RATP
* Fix ::
	* `Action_station` : donne les vrais lignes à la machine grace à `choix_num_ligne`

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
