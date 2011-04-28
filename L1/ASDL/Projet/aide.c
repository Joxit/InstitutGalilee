/* ____________________________  Aide.c  ____________________________________
	Projet A.S.D.L par MAGLOIRE Jones 11000369 et DELCOURT Rémi 11002398
	Lignes RATP de paris
	
	Ce fichier contient toutes les fonctions nécessaires pour la 
	cumunication entre le programme et l'utilisateur
	
	Dernière modification : Mardi 19 Avril 2011				
	
	pour plus d'information sur les fonctions voir projet_adsl.h
______________________________________________________________________________ */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "projet_asdl.h"
	
	    /* **************************************** *
	     * Fonctions basées sur les id des stations *
	     * **************************************** */
	
	// Renvoie l'id de la station la plus proche d'arrivee sur la ligne de depart
	int id_proche(int depart, int arrivee, liste_pStations_t ligne, int** distance)
	{
		while(ligne.s != NULL)
		{
			// Pour connaitre le plus court chemin, on parcourt toute la ligne
			// à la recherche de la station qui le moins de stations jusqu'à l'arrivee
			// en étant évidement différente de depart 
			// la formule etant basé sur la regle de l'inegalité triangulaire de distance[][]
			if((distance[depart][ligne.s->id] + distance[ligne.s->id][arrivee]) == (distance[depart][arrivee]) && (ligne.s->id != depart) && (is_open(ligne) == 1))
			{
				depart = ligne.s->id;
			}
			ligne = *ligne.next;
		}
		return depart;
	}
	
	// Prend le nom_station et renvoie l'id de celle ci
	int get_id(char* nom_station, liste_pStations_t toutes_les_stations)
	{    
	    liste_pStations_t stations = toutes_les_stations;
		char* pointeur;
		int choix = -1;
		if(stations.s == NULL)
		{
			puts("Erreur: liste des stations inexistante");
			return -1;
		}
	    // Premier passage sur toutes_les_stations 
	    // Principalement utile pour avoir l'id d'une station entres les autres fonctions
		while(stations.s != NULL)
		{
		// S'il n'y a pas de fautes on peut retourner l'id
			if(strcmp(stations.s->nom, nom_station) == 0)
				return stations.s->id;
			else
				stations = *stations.next;
		}
	    
	    // Si la station n'a pas été trouvée l'utilisateur doit intervenir
		printf("La station %s n'a pas ete trouvee\n", nom_station);
		stations = toutes_les_stations;
	    // Deuxième passage sur toutes_les_stations
		while(stations.s != NULL)
		{
	    // On compare le nom_station à chaque parties de stations.s->nom
			pointeur = strstr(stations.s->nom, nom_station);
			if(pointeur != NULL)
			{
		    // Si on trouve une partie qui correspond on donne l'id à l'utilisateur
				printf("Tapez %d pour %s\n", stations.s->id, stations.s->nom);
				choix = 1;
				stations = *stations.next;
			}
			else
				stations = *stations.next;
		}
		if(choix != -1)
		{
			scanf("%d", &choix);
			purger ();
			if(choix < 0 || 300 <= choix)
				puts("Mauvais choix, saisissez une nouvelle station"); 
		}
		return choix;
	}
	
	// Prend une id et renvoie le nom_station de celle ci
	char* get_nom_station(int id, liste_pStations_t toutes_les_stations)
	{    
	    liste_pStations_t stations = toutes_les_stations;
	    
		if(stations.s == NULL)
		{
			puts("Erreur: liste des stations inexistante");
			exit(0);
		}
	    
		while(stations.s != NULL)
		{
			if(id == stations.s->id )
				return stations.s->nom;
			else
				stations = *stations.next;
		}
		puts("Erreur: la station n'a pas ete trouvee");
		exit(0);
	}
	

	    /* ********************************************** *
	    * Fonctions de lecture du choix de l'utilisateur *
	    * ********************************************** */
	    
	// Demande le numero de la ligne a l'utilisateur
	int get_choix()
	{
		int choix;
	    scanf("%d", &choix);
	    while(choix < 1 || choix > 14)
		{
		    puts("Mauvaise ligne! Il y a 14 lignes");
		    scanf("%d", &choix);
		}
		return choix;
	}
	
	// Demande le nom de la station a l'utilisateur
	char* get_choix_station(liste_pStations_t toutes_les_stations)
	{
		int choix;
	    char* nom_station = (char*)malloc(100*sizeof(char));
		gets(nom_station); 
		choix = get_id(nom_station, toutes_les_stations);
	    // Si son choix est hors du nombre d'id on boucle
		while((choix < 0) || (300 <= choix))
		{
			gets(nom_station);
			choix = get_id(nom_station, toutes_les_stations); 
		}
	    free(nom_station);
		return get_nom_station(choix, toutes_les_stations);
	}
		
	    /* ******************************************* *
	    * Fonctions de retranscription du numero_ligne *
	    * ******************************************** */
	    
	// Prend en argument la valeur du tableau toutes_les_lignes et renvoie le vrais numero_ligne
	int get_num_ligne(int i)
	{
	    switch(i)
	    {
		case 0:
		    return 1;
		case 1:
		    return 2;
		case 2:
		    return 3;
		case 3:
		    return 4;
		case 4:
		    return 5;
		case 5:
		    return 6;
		case 6:
		    return 7;
		case 7:
		    return 7;
		case 8:
		    return 8;
		case 9:
		    return 9;
		case 10:
		    return 10;
		case 11:
		    return 10;
		case 12:
		    return 11;
		case 13:
		    return 12;
		case 14:
		    return 13;
		case 15:
		    return 13;
		case 16:
		    return 14;
		default :
		    return 0;
	    }
	}

	// Prend en argument le vrais numero_ligne et renvoie la valeur pour le tableau toutes_les_lignes 
	int choix_num_ligne(int i)
	{
	    switch(i)
	    {		
		case 1:
		    return 0; 
		case 2:
		    return 1;
		case 3:
		    return 2;
		case 4:
		    return 3;
		case 5:
		    return 4;
		case 6:
		    return 5;
		case 7: // devrait retourner 6 puis 7 reglé dans les menus
		    return 6;
		case 8:
		    return 8;
		case 9:
		    return 9;
		case 10: // devrait retourner 10 puis 11 reglé dans les menus
		    return 10;
		case 11:
		    return 12;
		case 12:
		    return 13;
		case 13: // devrait retourner 14 puis 15 reglé dans les menus
		    return 14;
		case 14:
		    return 16;
		default :
		    return -1;
	    }
	}

	
	int is_open(liste_pStations_t ligne)
	{
		if(ligne.s != NULL)
			return ligne.s->ouvert == 1;
		else
			return -1;
	}