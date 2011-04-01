/* ______________________________________________________________________________
	Projet A.S.D.L par MAGLOIRE Jones 11000369 et DELCOURT Rémi 11002398
	Lignes RATP de paris
    
	Version 1.0 :
			- mise en place du projet
			- Création des fonctions de base
			- Creation du mot de passe pour l'agent RATP
			- Recherche itineraire : 
					- Cas de base itineraire sur la meme ligne
					- quitte la fonction si depart = arrivee
			- seulement lignes 1 et 2 implementees
	Version 1.1 :
			- Changement de l'affichage en fonction recursive
			- Ajout des sous choix utilisateur et de l'agent R.A.T.P
			- Fix ::
				- ligne_station
				- get_station_ouverte
				- ligne_ouverte
				- ouvrir_station/fermer_station
				- retirer_station_carte
			- Implantation ligne 3
			- Ajout de securité dans station_dans_ligne et ligne_ouverte
			- reorganisation de projet_asdl.h et projet_asdl.c ::
 				- création de sous fichiers menu.c et lignes.c pour alléger projet_asdl.c
 				
 	Vendredi 1 Avril 2011		
	
	pour plus d'information sur les fonctions voir projet_adsl.h
______________________________________________________________________________ */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <ctype.h>
	#include "projet_asdl.h"

	liste_pStations_t* ligne1(liste_pStations_t* ligne)
	{
	    
	    ligne = malloc(2*sizeof(liste_pStations_t*));
	   ligne = ajout_station("", ligne);
	   ligne = ajout_station("La Defense", ligne);
	   ligne = ajout_station("Grande Arche ", ligne);
	   ligne = ajout_station("Esplanade de la Défense ", ligne);
	   ligne = ajout_station("Pont de Neuilly", ligne);
	   ligne = ajout_station("Les Sablons", ligne);
	   ligne = ajout_station("Jardin d'Acclimatation", ligne);
	   ligne = ajout_station("Porte Maillot", ligne);
	   ligne = ajout_station("Argentine", ligne);
	   ligne = ajout_station("Charles de Gaulle - Étoile", ligne);
	   ligne = ajout_station("George V", ligne);
	   ligne = ajout_station("Franklin D. Roosevelt", ligne);
	   ligne = ajout_station("Champs-Élysées - Clemenceau", ligne);
	   ligne = ajout_station("Concorde", ligne);
	   ligne = ajout_station("Tuileries", ligne);
	   ligne = ajout_station("Palais Royal - Musée du Louvre", ligne);
	   ligne = ajout_station("Louvre - Rivoli", ligne);
	   ligne = ajout_station("Châtelet", ligne);
	   ligne = ajout_station("Hôtel de Ville", ligne);
	   ligne = ajout_station("Saint-Paul", ligne);
	   ligne = ajout_station("Bastille", ligne);
	   ligne = ajout_station("Gare de Lyon", ligne);
	   ligne = ajout_station("Reuilly - Diderot", ligne);
	   ligne = ajout_station("Nation", ligne);
	   ligne = ajout_station("Porte de Vincennes", ligne);
	   ligne = ajout_station("Saint-Mandé", ligne);
	   ligne = ajout_station("Bérault", ligne);
	   ligne = ajout_station("Château de Vincennes", ligne);
	   
	   return ligne;
	}
	
	liste_pStations_t* ligne2(liste_pStations_t* ligne)
	{
	    
	    ligne = malloc(2*sizeof(liste_pStations_t*));
	    ligne = ajout_station("", ligne);
	    ligne = ajout_station("Porte Dauphine", ligne);
	    ligne = ajout_station("Victor Hugo", ligne);
	    ligne = ajout_station("Charles de Gaulle - Étoile", ligne);
	    ligne = ajout_station("Ternes", ligne);
	    ligne = ajout_station("Courcelles", ligne);
	    ligne = ajout_station("Monceau", ligne);
	    ligne = ajout_station("Villiers", ligne);
	    ligne = ajout_station("Rome", ligne);
	    ligne = ajout_station("Place de Clichy", ligne);
	    ligne = ajout_station("Blanche", ligne);
	    ligne = ajout_station("Pigalle", ligne);
	    ligne = ajout_station("AnversSacré-Cœur", ligne);
	    ligne = ajout_station("Barbès - Rochechouart", ligne);
	    ligne = ajout_station("La Chapelle", ligne);
	    ligne = ajout_station("Stalingrad", ligne);
	    ligne = ajout_station("Jaurès", ligne);
	    ligne = ajout_station("Colonel Fabien", ligne);
	    ligne = ajout_station("Belleville", ligne);
	    ligne = ajout_station("Couronnes", ligne);
	    ligne = ajout_station("Ménilmontant", ligne);
	    ligne = ajout_station("Père Lachaise", ligne);
	    ligne = ajout_station("Philippe Auguste", ligne);
	    ligne = ajout_station("Alexandre Dumas", ligne);
	    ligne = ajout_station("Avron", ligne);
	    ligne = ajout_station("Nation", ligne);
	    return ligne;
	}

	liste_pStations_t* ligne3(liste_pStations_t* ligne)
	{
	    ligne = malloc(2*sizeof(liste_pStations_t*));
	    ligne = ajout_station("", ligne);
	    ligne = ajout_station("Pont de Levallois - Bécon", ligne);
	    ligne = ajout_station("Anatole France", ligne);
	    ligne = ajout_station("Louise Michel", ligne);
	    ligne = ajout_station("Porte de Champerret", ligne);
	    ligne = ajout_station("Pereire", ligne);
	    ligne = ajout_station("Wagram", ligne);
	    ligne = ajout_station("Malesherbes", ligne);
	    ligne = ajout_station("Villiers", ligne);
	    ligne = ajout_station("Europe", ligne);
	    ligne = ajout_station("Saint-Lazare", ligne);
	    ligne = ajout_station("Havre - Caumartin", ligne);
	    ligne = ajout_station("Opéra", ligne);
	    ligne = ajout_station("Quatre-Septembre", ligne);
	    ligne = ajout_station("Bourse", ligne);
	    ligne = ajout_station("Sentier", ligne);
	    ligne = ajout_station("Réaumur - Sébastopol", ligne);
	    ligne = ajout_station("Arts et Métiers", ligne);
	    ligne = ajout_station("Temple", ligne);
	    ligne = ajout_station("République", ligne);
	    ligne = ajout_station("Parmentier", ligne);
	    ligne = ajout_station("Rue Saint-Maur", ligne);
	    ligne = ajout_station("Père Lachaise", ligne);
	    ligne = ajout_station("Gambetta", ligne);
	    ligne = ajout_station("Porte de Bagnolet", ligne);
	    ligne = ajout_station("Gallieni", ligne);
	    return ligne;
	}

	liste_pStations_t* ligne4(liste_pStations_t* ligne)
	{	
	    ligne = malloc(2*sizeof(liste_pStations_t*));
	    ligne = ajout_station("", ligne);
	    ligne = ajout_station("Porte de Clignancourt", ligne);
	    ligne = ajout_station("Simplon", ligne);
	    ligne = ajout_station("Marcadet – Poissonniers", ligne);
	    ligne = ajout_station("Château Rouge", ligne);
	    ligne = ajout_station("Barbès – Rochechouart", ligne);
	    ligne = ajout_station("Gare du Nord", ligne);
	    ligne = ajout_station("Gare de l'Est", ligne);
	    ligne = ajout_station("Château d'Eau", ligne);
	    ligne = ajout_station("Strasbourg – Saint-Denis", ligne);
	    ligne = ajout_station("Réaumur – Sébastopol", ligne);
	    ligne = ajout_station("Étienne Marcel", ligne);
	    ligne = ajout_station("Les Halles", ligne);
	    ligne = ajout_station("Châtelet", ligne);
	    ligne = ajout_station("Cité", ligne);
	    ligne = ajout_station("Saint-Michel", ligne);
	    ligne = ajout_station("Odéon", ligne);
	    ligne = ajout_station("Saint-Germain-des-Prés", ligne);
	    ligne = ajout_station("Saint-Sulpice", ligne);
	    ligne = ajout_station("Saint-Placide", ligne);
	    ligne = ajout_station("Montparnasse – Bienvenüe", ligne);
	    ligne = ajout_station("Vavin", ligne);
	    ligne = ajout_station("Raspail", ligne);
	    ligne = ajout_station("Denfert-Rochereau", ligne);
	    ligne = ajout_station("Mouton-Duvernet", ligne);
	    ligne = ajout_station("Alésia", ligne);
	    ligne = ajout_station("Porte d'Orléans", ligne);
	    return ligne;
	}

	liste_pStations_t* ligne5(liste_pStations_t* ligne)
	{	
	    ligne = malloc(2*sizeof(liste_pStations_t*));
		ligne = ajout_station("", ligne);
	    ligne = ajout_station("Bobigny - Pablo Picasso", ligne);
	    ligne = ajout_station("Bobigny - Pantin - Raymond Queneau", ligne);
	    ligne = ajout_station("Église de Pantin", ligne);
	    ligne = ajout_station("Hoche", ligne);
	    ligne = ajout_station("Porte de Pantin", ligne);
	    ligne = ajout_station("Ourcq", ligne);
	    ligne = ajout_station("Laumière", ligne);
	    ligne = ajout_station("Jaurès", ligne);
	    ligne = ajout_station("Stalingrad", ligne);
	    ligne = ajout_station("Gare du Nord", ligne);
	    ligne = ajout_station("Gare de l'Est", ligne);
	    ligne = ajout_station("Jacques Bonsergent", ligne);
	    ligne = ajout_station("République", ligne);
	    ligne = ajout_station("Oberkampf", ligne);
	    ligne = ajout_station("Richard-Lenoir", ligne);
	    ligne = ajout_station("Bréguet - Sabin", ligne);
	    ligne = ajout_station("Bastille", ligne);
	    ligne = ajout_station("Quai de la Rapée", ligne);
	    ligne = ajout_station("Gare d'Austerlitz", ligne);
	    ligne = ajout_station("Saint-Marcel", ligne);
	    ligne = ajout_station("Campo-Formio", ligne);
	    ligne = ajout_station("Place d'Italie", ligne);
	    return ligne;
	}
	
	liste_pStations_t* ligne6(liste_pStations_t* ligne)
	{	
	    ligne = malloc(2*sizeof(liste_pStations_t*));
		ligne = ajout_station("", ligne);
		ligne = ajout_station("Charles de Gaulle - Étoile", ligne);
		ligne = ajout_station("Kléber", ligne);
		ligne = ajout_station("Boissière", ligne);
		ligne = ajout_station("Trocadéro", ligne);
		ligne = ajout_station("Passy", ligne);
		ligne = ajout_station("Bir-Hakeim", ligne);
	    ligne = ajout_station("Dupleix", ligne);
	    ligne = ajout_station("La Motte-Picquet - Grenelle", ligne);
	    ligne = ajout_station("Cambronne", ligne);
	    ligne = ajout_station("Sèvres - Lecourbe", ligne);
	    ligne = ajout_station("Pasteur", ligne);
	    ligne = ajout_station("Montparnasse - Bienvenüe", ligne);
	    ligne = ajout_station("Edgar Quinet", ligne);
	    ligne = ajout_station("Raspail", ligne);
	    ligne = ajout_station("Denfert-Rochereau", ligne);
	    ligne = ajout_station("Saint-Jacques", ligne);
	    ligne = ajout_station("Glacière", ligne);
	    ligne = ajout_station("Corvisart", ligne);
	    ligne = ajout_station("Place d'Italie", ligne);
	    ligne = ajout_station("Nationale", ligne);
	    ligne = ajout_station("Chevaleret", ligne);
	    ligne = ajout_station("Quai de la Gare", ligne);
	    ligne = ajout_station("Bercy", ligne);
	    ligne = ajout_station("Dugommier", ligne);
	    ligne = ajout_station("Daumesnil", ligne);
	    ligne = ajout_station("Bel-Air", ligne);
	    ligne = ajout_station("Picpus", ligne);
	    ligne = ajout_station("Nation", ligne);
		return ligne;
	}
