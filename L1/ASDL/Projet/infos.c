/* ______________________________________________________________________________
	Projet A.S.D.L par MAGLOIRE Jones 11000369 et DELCOURT Rémi 11002398
	Lignes RATP de paris
	
	Ce fichier contient toutes les fonctions nécessaires à 
	l'interface utilisateur
	
	Dernière modification : Mardi 19 Avril 2011				
	
	pour plus d'information sur les fonctions voir projet_adsl.h
______________________________________________________________________________ */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <math.h>
	#include <sys/resource.h>
	#include <time.h>
	#include "projet_asdl.h"

	   /* ************************************** *
	    * Fonctionalitées pour l'utilisateur x : *
	    * ************************************** */
	    
	// Affiche l'itineraire entre depart et arrivee. la fonction prend les id des stations
	void recherche_intineraires(int depart, int arrivee, int** distance, liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations)
	{
	    int i = 0;
	    liste_pStations_t ligne;
	    int		n = 0, 		// nombre binaire convertit qui renvoie les lignes de la station
			numero_ligne;
	    int 	cur_id, 	// id de parcour 
			sub_id,		// id de test à la sortie de id_proche
			id;		// id final le plus près d'arrivee
	    
		if(depart == arrivee)
		{
			puts("ERREUR : vous avez choisi la meme station!");
			return;
		}
		
		id = depart;
		while(id != arrivee)
		{
		    // ligne_station convertit les numeros de la station de binaire à décimal 
		    n = ligne_station( get_nom_station(id, toutes_les_stations), toutes_les_lignes);
		    i = 0;
		    cur_id = id;
		    while (n > 0) 
		    {
			// Si on a bien n%2 la station passe par la ligne i
			if (n % 2) 
			{
			    ligne = *toutes_les_lignes[i];
			    sub_id = id_proche(id, arrivee, ligne, distance);
			    // Si on trouve une id station plus proche que la précédente
			    if(distance[sub_id][arrivee] <= distance[cur_id][arrivee] && sub_id != id)
			    {
				// on retien son id et son numero_ligne
				cur_id = sub_id;
				numero_ligne = i;
			    }
			}
			i = i + 1;
			n = n / 2;
			// Si on est arrivé on quitte la boucle
			if(cur_id == arrivee)
			    break;
		    }	
		    printf("\tPrendre la ligne %d\n", get_num_ligne(numero_ligne));
		    id = cur_id;
		    ligne = *toutes_les_lignes[numero_ligne];
		}
		printf("%s est a %d stations de %s\n", get_nom_station(depart, toutes_les_stations), distance[depart][arrivee], get_nom_station(arrivee, toutes_les_stations));
	}

	// Affiche le nom de toutes les stations de toutes les lignes
	void liste_station_de_toutes_les_lignes(liste_pStations_t** toutes_les_lignes)
	{
	    int i;
	    liste_pStations_t ligne;
	    
	    // Boucle principale : parcourt toutes les lignes du réseau
	    for(i = 0; i < NB_LIGNES; i++)
	    {
		ligne = *toutes_les_lignes[i];
		// Vérification d'un cas complexe avec les lignes à plusieurs branches
		switch(i)
		{
		    case 6:
			printf("Les Station de la ligne %d directon Villejuif : \n", get_num_ligne(i));
			break;
		    case 7:
			printf("Les Station de la ligne %d directon Ivry : \n", get_num_ligne(i));
			break;
		    case 10:	
			printf("Les Station de la ligne %d directon Boulogne : \n", get_num_ligne(i));
			break;
		    case 11:	
			printf("Les Station de la ligne %d directon Gare d'Austerlitz : \n", get_num_ligne(i));
			break;
		    case 14:	
			printf("Les Station de la ligne %d directon Saint Denis : \n", get_num_ligne(i));
			break;
		    case 15:	
			printf("Les Station de la ligne %d directon Gennevilliers : \n", get_num_ligne(i));
			break;
		    default : 
			printf("Les Station de la ligne %d sont : \n", get_num_ligne(i));
			break;
		}
		// Boucle secondaire qui affiche les noms des stations
		while(ligne.next != NULL)
		{
		    printf("%s; ", ligne.s->nom);
		    ligne = *ligne.next;
		}
		puts("\n");
	    }
	}
	
	// Test la ligne avec 1 si elle est ouverte et 0 si elle est fermée; mini 2 stations ouvertes
	int ligne_ouverte(liste_pStations_t ligne) // toutes_les_lignes[i] en argument!
	{
	    int cmp = 0;
	    if(ligne.s == NULL)
	    {
		puts("Erreur: ligne inexistante");
		return 0;
	    }
	    
	    while(ligne.next != NULL)
	    {
		if(ligne.s->ouvert == 1) // ouvert
		{
		    cmp = cmp +1;
		}
		if(cmp == 2)
		    return 1;
		
		ligne = *ligne.next;
	    }
	    
	    return 0;
	}
	
	// Affiche les stations de ligne
	void station_dans_ligne(liste_pStations_t ligne)
	{
	    if(ligne.s == NULL)
	    {
		puts("Erreur: ligne inexistante");
		return ;
	    }
	    
	    puts("Les Station de cette ligne sont : ");
	    while(ligne.next != NULL)
	    {
		printf("%s; ", ligne.s->nom);
		ligne = *ligne.next;
	    }
		puts("");
	}
	
	// Affiche les lignes qui sont ouverte pour nom_station
	void get_station_ouverte(char* nom_station, liste_pStations_t** toutes_les_lignes)
	{
	    int i = 0;
	    liste_pStations_t ligne;
	    ligne = *toutes_les_lignes[i];
	    
	    // Boucle principale : parcourt toutes les lignes du réseau
	    while(i < NB_LIGNES)
	    {
		// Securité pour les erreurs de segmentation
		if(ligne.s != NULL)
		{
		    // compare le nom_station au nom de la ligne
		    if(strcmp(nom_station, ligne.s->nom) == 0)
		    {
			if(ligne.s->ouvert == 1)
			{
			    printf("La station %s est ouverte pour la ligne %d ", nom_station, get_num_ligne(i));   
			}
			else 
			    printf("La station %s est fermée pour la ligne %d ", nom_station, get_num_ligne(i));
			
			// une station n'est pas deux fois sur la meme ligne mais erreur avec  ligne = *ligne.next; qui suit
			    //i++;
			    //ligne = *toutes_les_lignes[i];
			    // Vérification d'un cas complexe avec les lignes à plusieurs branches
			    switch(i)
			    {
				case 6:
				    printf("directon Villejuif\n");
				    break;
				case 7:
				    printf("directon Ivry\n");
				    break;
				case 10:	
				    printf("directon Boulogne\n");
				    break;
				case 11:	
				    printf("directon Gare d'Austerlitz\n");
				    break;
				case 14:	
				    printf("directon Saint Denis\n");
				    break;
				case 15:	
				    printf("directon Gennevilliers\n");
				    break;
				default : 
				    printf("\n");
				    break;
			    }
		    }
		}
		
		if(ligne.s  == NULL)
		{ 
		    i++;
		    ligne = *toutes_les_lignes[i];    
		}
		else
		    ligne = *ligne.next;
		
		
	    }
	}
	
	// Toutes les lignes d'une station	
	int ligne_station(char* nom_station, liste_pStations_t** toutes_les_lignes)
	{
	    int i = 0;
	    liste_pStations_t ligne;
	    ligne = *toutes_les_lignes[i];
	    int numero_lignes = 0;
	    
	    printf("Ligne(s) passant par la station %s : ", nom_station);
	    while(i < NB_LIGNES)
	    {
		if(ligne.s != NULL)
		{
		    // compare le nom_station au nom de la ligne
		    if(strcmp(nom_station, ligne.s->nom)==0)
		    {
			printf("%d ", get_num_ligne(i));
			// codage en binaire pour une vérification dans recherche_intineraires
			numero_lignes = numero_lignes + (int)pow(2, (double)i);
			// une station n'est pas deux fois sur la meme ligne mais erreur avec  ligne = *ligne.next; qui suit
			    //i++;
			    //ligne = *toutes_les_lignes[i];
		    }
		}
		if( ligne.s == NULL)
		{ 
		    i++;    
		    ligne = *toutes_les_lignes[i];
		}
		else
		{
		    ligne = *ligne.next;
		}
		
	    }
	    puts("");
	    return numero_lignes;
	}

    double temps_CPU()
    {
	struct rusage usage;

	getrusage(RUSAGE_SELF, &usage);
	return usage.ru_utime.tv_sec + (usage.ru_utime.tv_usec / 1000000.0);
    }