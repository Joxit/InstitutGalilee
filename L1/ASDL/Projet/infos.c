/* ______________________________________________________________________________
	Projet A.S.D.L par MAGLOIRE Jones 11000369 et DELCOURT Rémi 11002398
	Lignes RATP de paris
    

 	Vendredi 1 Avril 2011			
	
	pour plus d'information sur les fonctions voir projet_adsl.h
______________________________________________________________________________ */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <math.h>
	#include "projet_asdl.h"

	// renvoie un pointeur sur la station dont le nom est donnée en paramètre, ou NULL si erreur
	station_t* rechercher_station(char* nom_station, liste_pStations_t** toutes_les_lignes)
	{
	    int i = 0;
	    //clean(nom_station);
	    //char* station_clean = malloc(60*sizeof(char*));
	    while(i < NB_LIGNES)
	    {
		if(toutes_les_lignes[i]->s == NULL)
		       i++;	
		if(i == NB_LIGNES)
			return NULL;
		if(strcmp(nom_station, toutes_les_lignes[i]->s->nom)==0)
		{
		    return toutes_les_lignes[i]->s; 
		}
		
		else
		    toutes_les_lignes[i] = toutes_les_lignes[i]->next;

	    }
	    printf("\n la station %s n'existe pas", nom_station);
	    return NULL;
	}
	

	// fonctionalitées pour l'utilisateur x :
	// liste stations entre A et B CAS de base : A et B sur la meme ligne
	void recherche_intineraires(int depart, int arrivee,int** voisin, int** distance, liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations)
	{
	    int i = 0;
	    liste_pStations_t ligne;
	    int n = 0, numero_ligne;
	    int cur_id, sub_id, id;
		if(depart == arrivee)
		{
			puts("ERREUR : vous avez choisi la meme station!");
			return;
		}
		id = depart;
		while(id != arrivee)
		{
		n = ligne_station( get_nom_station(id, toutes_les_stations), toutes_les_lignes);
		    i = 0;
		    cur_id = id;
		    while (n > 0) 
		    {
			if (n % 2) 
			{
			    ligne = *toutes_les_lignes[i];
			    sub_id = id_proche(id, arrivee, ligne, distance);
			    if(distance[sub_id][arrivee] <= distance[cur_id][arrivee])
			    {
				cur_id = sub_id;
				numero_ligne = i;
			    }
			}
			i = i + 1;
			n = n / 2;
			if(cur_id == arrivee)
			    break;
		    }	
		    printf("\tPrendre la ligne %d\n", get_num_ligne(numero_ligne));
		    id = cur_id;
		    ligne = *toutes_les_lignes[numero_ligne];
		}
		printf("%s est a %d stations de %s\n", get_nom_station(depart, toutes_les_stations), distance[depart][arrivee], get_nom_station(arrivee, toutes_les_stations));
	}
	   
	// création de la liste de totues les stations
	liste_pStations_t*  liste_station(liste_pStations_t* toutes_les_stations, liste_pStations_t** toutes_les_lignes)
	{
	    int i, j, x;
	    liste_pStations_t ligne;
	    for(i=0; i < 300; i++)
	    {
		j = 0;
		x = 0;
		ligne = *toutes_les_lignes[j];
		while(x == 0)
		{
		    if(ligne.s != NULL)
		    {
			if(i == ligne.s->id)
			{
			    toutes_les_stations = ajout_station(ligne.s->nom,  toutes_les_stations);
			    toutes_les_stations->s->id = i;
			    x = 1;
			}
			else
			    ligne = *ligne.next;
		    }
		    if(ligne.s == NULL)
		    {
			j = j + 1;
			ligne = *toutes_les_lignes[j];
		    }
		}
		
	    }
	    return toutes_les_stations;
	}

	// Affiche le nom de toutes les stations de toutes les lignes
	void liste_station_de_toutes_les_lignes(liste_pStations_t** toutes_les_lignes)
	{
	    int i;
	    liste_pStations_t ligne;
	    
	    for(i = 0; i < NB_LIGNES; i++)
	    {
		ligne = *toutes_les_lignes[i];
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
		while(ligne.next != NULL)
		{
		    printf("%s; ", ligne.s->nom);
		    ligne = *ligne.next;
		}
		puts("\n");
	    }
	}
	// Affiche les lignes qui sont ouverte pour nom_station
	void get_station_ouverte(char* nom_station, liste_pStations_t** toutes_les_lignes)
	{
	    int i = 0;
	    liste_pStations_t ligne;
	    ligne = *toutes_les_lignes[i];
	    while(i < NB_LIGNES)
	    {
		if(ligne.s != NULL)
		{
		    if(strcmp(nom_station, ligne.s->nom) == 0)
		    {
			if(ligne.s->ouvert == 1)
			{
			    printf("La station %s est ouverte pour la ligne %d \n", nom_station, get_num_ligne(i));   
			}
			else 
			    printf("La station %s est fermée pour la ligne %d \n", nom_station, get_num_ligne(i));
			    // une station n'est pas deux fois sur la meme ligne mais erreur avec  ligne = *ligne.next; qui suit
			    //i++;
			    //ligne = *toutes_les_lignes[i];
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
	// test la ligne avec 1 si elle est ouverte et 0 si elle est fermée; mini 2 stations ouvertes
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
		// affiche les stations de la ligne ligne  MARCHE
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
	
	// toutes les lignes d'une station	
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
		    if(strcmp(nom_station, ligne.s->nom)==0)
		    {
			printf("%d ", get_num_ligne(i));
			// codage en binaire pour une verification dans recherche_intineraires
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
