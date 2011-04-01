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

	liste_pStations_t* ligne1(liste_pStations_t* ligne,liste_pStations_t** toutes_les_lignes0, int* id, int n)
	{
	    int i;
	    	liste_pStations_t** toutes_les_lignes = (liste_pStations_t**)malloc(2*NB_STATION*sizeof(liste_pStations_t*));
		for(i = 0; i < NB_STATION; i++)
		{
		    toutes_les_lignes[i] = (liste_pStations_t*)malloc(32*sizeof(liste_pStations_t*));
		    toutes_les_lignes[i] = toutes_les_lignes0[i];
		}
	    
	    ligne = malloc(2*sizeof(liste_pStations_t*));
	   ligne = ajout_station("", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("La Defense", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Grande Arche ", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Esplanade de la Défense ", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Pont de Neuilly", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Les Sablons", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Jardin d'Acclimatation", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Porte Maillot", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Argentine", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Charles de Gaulle - Étoile", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("George V", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Franklin D. Roosevelt", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Champs-Élysées - Clemenceau", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Concorde", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Tuileries", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Palais Royal - Musée du Louvre", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Louvre - Rivoli", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Châtelet", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Hôtel de Ville", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Saint-Paul", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Bastille", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Gare de Lyon", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Reuilly - Diderot", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Nation", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Porte de Vincennes", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Saint-Mandé", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Bérault", ligne, toutes_les_lignes, id, n);
	   ligne = ajout_station("Château de Vincennes", ligne, toutes_les_lignes, id, n);
	   
	   return ligne;
	}
	
	liste_pStations_t* ligne2(liste_pStations_t* ligne,liste_pStations_t** toutes_les_lignes0, int* id, int n)
	{
	    int i;
	    	liste_pStations_t** toutes_les_lignes = (liste_pStations_t**)malloc(2*NB_STATION*sizeof(liste_pStations_t*));
		for(i = 0; i < NB_STATION; i++)
		{
		    toutes_les_lignes[i] = (liste_pStations_t*)malloc(32*sizeof(liste_pStations_t*));
		    toutes_les_lignes[i] = toutes_les_lignes0[i];
		}
	    
	    ligne = malloc(2*sizeof(liste_pStations_t*));
	    ligne = ajout_station("", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Porte Dauphine", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Victor Hugo", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Charles de Gaulle - Étoile", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Ternes", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Courcelles", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Monceau", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Villiers", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Rome", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Place de Clichy", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Blanche", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Pigalle", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("AnversSacré-Cœur", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Barbès - Rochechouart", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("La Chapelle", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Stalingrad", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Jaurès", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Colonel Fabien", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Belleville", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Couronnes", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Ménilmontant", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Père Lachaise", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Philippe Auguste", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Alexandre Dumas", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Avron", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Nation", ligne, toutes_les_lignes, id, n);
	    return ligne;
	}

	liste_pStations_t* ligne3(liste_pStations_t* ligne,liste_pStations_t** toutes_les_lignes0, int* id, int n)
	{
	    int i;
	    	liste_pStations_t** toutes_les_lignes = (liste_pStations_t**)malloc(2*NB_STATION*sizeof(liste_pStations_t*));
		for(i = 0; i < NB_STATION; i++)
		{
		    toutes_les_lignes[i] = (liste_pStations_t*)malloc(32*sizeof(liste_pStations_t*));
		    toutes_les_lignes[i] = toutes_les_lignes0[i];
		}
	    ligne = malloc(2*sizeof(liste_pStations_t*));
	    ligne = ajout_station("", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Pont de Levallois - Bécon", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Anatole France", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Louise Michel", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Porte de Champerret", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Pereire", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Wagram", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Malesherbes", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Villiers", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Europe", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Saint-Lazare", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Havre - Caumartin", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Opéra", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Quatre-Septembre", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Bourse", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Sentier", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Réaumur - Sébastopol", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Arts et Métiers", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Temple", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("République", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Parmentier", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Rue Saint-Maur", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Père Lachaise", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Gambetta", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Porte de Bagnolet", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Gallieni", ligne, toutes_les_lignes, id, n);
	    return ligne;
	}

	liste_pStations_t* ligne4(liste_pStations_t* ligne,liste_pStations_t** toutes_les_lignes0, int* id, int n)
	{
	    int i;
	    liste_pStations_t** 	toutes_les_lignes = (liste_pStations_t**)malloc(2*NB_STATION*sizeof(liste_pStations_t*));
		for(i = 0; i < NB_STATION; i++)
		{
		    toutes_les_lignes[i] = (liste_pStations_t*)malloc(32*sizeof(liste_pStations_t*));
		    toutes_les_lignes[i] = toutes_les_lignes0[i];
		}	
	    ligne = malloc(2*sizeof(liste_pStations_t*));
	    ligne = ajout_station("", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Porte de Clignancourt", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Simplon", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Marcadet – Poissonniers", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Château Rouge", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Barbès – Rochechouart", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Gare du Nord", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Gare de l'Est", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Château d'Eau", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Strasbourg – Saint-Denis", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Réaumur – Sébastopol", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Étienne Marcel", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Les Halles", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Châtelet", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Cité", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Saint-Michel", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Odéon", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Saint-Germain-des-Prés", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Saint-Sulpice", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Saint-Placide", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Montparnasse – Bienvenüe", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Vavin", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Raspail", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Denfert-Rochereau", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Mouton-Duvernet", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Alésia", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Porte d'Orléans", ligne, toutes_les_lignes, id, n);
	    return ligne;
	}

	liste_pStations_t* ligne5(liste_pStations_t* ligne,liste_pStations_t** toutes_les_lignes0, int* id, int n)
	{
	    int i;
	    	liste_pStations_t** toutes_les_lignes = (liste_pStations_t**)malloc(2*NB_STATION*sizeof(liste_pStations_t*));
		for(i = 0; i < NB_STATION; i++)
		{
		    toutes_les_lignes[i] = (liste_pStations_t*)malloc(32*sizeof(liste_pStations_t*));
		    toutes_les_lignes[i] = toutes_les_lignes0[i];
		}	
	    ligne = malloc(2*sizeof(liste_pStations_t*));
		ligne = ajout_station("", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Bobigny - Pablo Picasso", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Bobigny - Pantin - Raymond Queneau", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Église de Pantin", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Hoche", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Porte de Pantin", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Ourcq", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Laumière", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Jaurès", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Stalingrad", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Gare du Nord", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Gare de l'Est", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Jacques Bonsergent", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("République", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Oberkampf", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Richard-Lenoir", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Bréguet - Sabin", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Bastille", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Quai de la Rapée", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Gare d'Austerlitz", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Saint-Marcel", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Campo-Formio", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Place d'Italie", ligne, toutes_les_lignes, id, n);
	    return ligne;
	}
	
	liste_pStations_t* ligne6(liste_pStations_t* ligne,liste_pStations_t** toutes_les_lignes0, int* id, int n)
	{	
	    int i;
	    	liste_pStations_t** toutes_les_lignes = (liste_pStations_t**)malloc(2*NB_STATION*sizeof(liste_pStations_t*));
		for(i = 0; i < NB_STATION; i++)
		{
		    toutes_les_lignes[i] = (liste_pStations_t*)malloc(32*sizeof(liste_pStations_t*));
		    toutes_les_lignes[i] = toutes_les_lignes0[i];
		}
	    ligne = malloc(2*sizeof(liste_pStations_t*));
		ligne = ajout_station("", ligne, toutes_les_lignes, id, n);
		ligne = ajout_station("Charles de Gaulle - Étoile", ligne, toutes_les_lignes, id, n);
		ligne = ajout_station("Kléber", ligne, toutes_les_lignes, id, n);
		ligne = ajout_station("Boissière", ligne, toutes_les_lignes, id, n);
		ligne = ajout_station("Trocadéro", ligne, toutes_les_lignes, id, n);
		ligne = ajout_station("Passy", ligne, toutes_les_lignes, id, n);
		ligne = ajout_station("Bir-Hakeim", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Dupleix", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("La Motte-Picquet - Grenelle", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Cambronne", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Sèvres - Lecourbe", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Pasteur", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Montparnasse - Bienvenüe", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Edgar Quinet", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Raspail", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Denfert-Rochereau", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Saint-Jacques", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Glacière", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Corvisart", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Place d'Italie", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Nationale", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Chevaleret", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Quai de la Gare", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Bercy", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Dugommier", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Daumesnil", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Bel-Air", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Picpus", ligne, toutes_les_lignes, id, n);
	    ligne = ajout_station("Nation", ligne, toutes_les_lignes, id, n);
		return ligne;
	}
