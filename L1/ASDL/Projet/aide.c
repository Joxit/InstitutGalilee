/* ______________________________________________________________________________
	Projet A.S.D.L par MAGLOIRE Jones 11000369 et DELCOURT Rémi 11002398
	Lignes RATP de paris
    

 	Vendredi 1 Avril 2011			
	
	pour plus d'information sur les fonctions voir projet_adsl.h
______________________________________________________________________________ */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "projet_asdl.h"

	

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
	    while(stations.s != NULL)
	    {
		if(strcmp(stations.s->nom, nom_station) == 0)
		    return stations.s->id;
		else
		    stations = *stations.next;
	    }
	    printf("La station %s n'a pas été trouvée\n", nom_station);
	    stations = toutes_les_stations;
	    
	    while(stations.s != NULL)
	    {
		pointeur = strstr(stations.s->nom, nom_station);
		if(pointeur != NULL)
		{
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
	    }
	    return choix;
	}
	
	char* get_nom_station(int id, liste_pStations_t toutes_les_stations)
	{    
	    liste_pStations_t stations = toutes_les_stations;
	    
	    if(stations.s == NULL)
	    {
		puts("Erreur: liste des stations inexistante");
		return NULL;
	    }
	    
	    while(stations.s != NULL)
	    {
		if(id == stations.s->id )
		    return stations.s->nom;
		else
		    stations = *stations.next;
	    }
	    puts("La station n'a pas été trouvée");
	    return NULL;
	}
	
	int id_proche(int depart, int arrivee, liste_pStations_t ligne, int** distance)
	{
	    while(ligne.s != NULL)
	    {
		if((distance[depart][ligne.s->id] + distance[ligne.s->id][arrivee]) == (distance[depart][arrivee]) && (ligne.s->id != depart))
		{
		    depart = ligne.s->id;
		}
		ligne = *ligne.next;
	    }
	    return depart;
	}
		
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
		case 7: // devrait retourner 6 puis 7
		    return -1;
		case 8:
		    return 8;
		case 9:
		    return 9;
		case 10: // devrait retourner 10 puis 11
		    return -1;
		case 11:
		    return 12;
		case 12:
		    return 13;
		case 13: // devrait retourner 14 puis 15
		    return -1;
		case 14:
		    return 16;
		default :
		    return -1;
	    }
	}
	// Demande le numero de la ligne a l'utilisateur
	int get_choix(int choix)
	{
	    scanf("%d", &choix);
	    while(choix < 1 || choix > 14)
		{
		    puts("Mauvaise ligne! Il y a 14 lignes");
		    scanf("%d", &choix);
		}
		return choix;
	}
	
	// Demande le nom de la station a l'utilisateur
	char* get_choix_station(int choix, liste_pStations_t toutes_les_stations)
	{
	    char* nom_station = (char*)malloc(100*sizeof(char));
	    gets(nom_station); 
	    choix = get_id(nom_station, toutes_les_stations);
			while((choix < 0) && (300 >= choix))
			{
			    gets(nom_station);
			    choix = get_id(nom_station, toutes_les_stations); 
			}
			
		return get_nom_station(choix, toutes_les_stations);
	}