/* ____________________________  Action.c  ___________________________________
	Projet A.S.D.L par MAGLOIRE Jones 11000369 et DELCOURT Rémi 11002398  
	Lignes RATP de paris
	
	Ce fichier contient toutes les fonctions nécessaires à la création
	du réseau RATP et des fonctions de l'agent RATP
	
	Dernière modification : Mardi 19 Avril 2011			
	
	pour plus d'informations sur les fonctions voir projet_adsl.h
______________________________________________________________________________ */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "projet_asdl.h"
	
	
	    /* ******************************* *
	     * Mise en place du réseau RATP    *
	     * ******************************* */

	// Création d'une ligne
	liste_pStations_t* ajout_ligne(int numero_ligne, liste_pStations_t* ligne, FILE* adt)
	{
	    int taille;
	    char* nom_station = malloc(100*sizeof(char));
	    ligne = (liste_pStations_t*)malloc(4*sizeof(liste_pStations_t*));
	    
	    while(!feof(adt))
	    {
		// On récupère le nom du fichier mis en argument au lancement
		fgets(nom_station, 100, adt);
		if(nom_station == NULL)
		    perror("La lecture a echoué");	
		
		// fgets met un saut de ligne à la fin de la variable, on le supprime
		taille = strlen(nom_station);
		nom_station[taille-1] = '\0';
		ligne= ajout_station( nom_station, ligne);
	    }
	    *ligne = *ligne->next;
	    
	    return ligne;
	}
	
	// Création de la liste toutes_les_stations
	liste_pStations_t*  liste_station(liste_pStations_t* toutes_les_stations, liste_pStations_t** toutes_les_lignes)
	{
	    int i, j, x;
	    liste_pStations_t ligne;
	    // Boucle principale qui compte les 300 stations du reseau
	    for(i=0; i < 300; i++)
	    {
		j = 0;
		x = FALSE;
		ligne = *toutes_les_lignes[j];
		// Seconde boucle qui fera toutes les lignes du réseau
		while(x == FALSE)
		{
		    if(ligne.s != NULL)
		    {
			if(i == ligne.s->id)
			{
			    // Dès qu'on trouve une id = i on l'ajoute à toutes_les_stations et on quitte
			    toutes_les_stations = ajout_station(ligne.s->nom, toutes_les_stations);
			    toutes_les_stations->s->id = i;
			    x = TRUE;
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
	
	// Création de voisin[][] : fonction qui renvoie TRUE si les stations son voisines FALSE sinon et -1 si c'est les memes id
	int est_voisin(int id1, int id2, liste_pStations_t** toutes_les_lignes)
	{
	    if(id1 == id2)
		return -1;
	    int i = 0;
	    liste_pStations_t ligne;
	    ligne = *toutes_les_lignes[i];
	    // Boucle principale qui fera toutes les lignes du réseau
	    while(i < NB_LIGNES)
	    {
		// si la station éxiste on continue
		if(ligne.next->s != NULL)
		{
		    // si on trouve l'une des id, on compare la suivante avec l'autre
		    if(id1 == ligne.s->id)
		    {
			if(id2 == ligne.next->s->id)
			{
			    return TRUE;
			}  
		    }
		    if(id2 == ligne.s->id)
		    {
			if(id1 == ligne.next->s->id)
			{
			    return TRUE;
			}  
		    }
		}
		// Si la station n'éxiste pas on passe à la ligne suivante
		if( ligne.next->s == NULL)
		{ 
		    i++;    
		    ligne = *toutes_les_lignes[i];
		}
		else
		   ligne = *ligne.next;
		
	    }
	    return FALSE;
	}
	
	// Affecte à toutes les stations de toutes_les_lignes leurs id
	void set_id(liste_pStations_t** toutes_les_lignes)
	{
	    liste_pStations_t ligne;
	    liste_pStations_t ligne2;
	    int i = 0, j = 0, id = 0, boolean = -1;
	    ligne = *toutes_les_lignes[i];
	    ligne2 = *toutes_les_lignes[i];
	    
	    // Premiere boucle : permet de mettre les id sur toutes les lignes
	    while(i < NB_LIGNES)
	    {
		// ligne2 est le pointeur qui prend les modifications pour toutes_les_lignes[]
		if(ligne2.s != NULL)
		{
		    j = 0;
		    ligne = *toutes_les_lignes[j];	
		    boolean = -1;	   // carte de sortie
		    // Deuxième boucle qui permet de vérifier si une station a déjà une id sur toutes les lignes déjà vues 
		    while(boolean == -1)
		    {
			if( ligne.s != NULL)
			{
			    // Si on est sur la meme ligne que ligne2 on quitte
			    if( j == i)
			    {
				boolean = FALSE;	
			    }
			    if(boolean== -1)
			    {
				// Comparaison des deux lignes
				if(strcmp(ligne2.s->nom, ligne.s->nom) == 0 )
				{
				    // Si les noms sont identique on donne l'id de ligne à ligne2 et on quitte
				    ligne2.s->id = ligne.s->id;
				    boolean = TRUE;
				}
				else // Sinon on passe
				    ligne = *ligne.next;	
			    }
			    
			}
			else // Si la station est nul on passe à la ligne suivante
			    if(ligne.s == NULL)
			    {
				j = j + 1;
				ligne = *toutes_les_lignes[j];	
			    }
			
		    }
		    // Si boolean == FALSE c'est qu'on a pas trouvé de station avec la meme  id
		    if(boolean == FALSE )
		    {
			ligne2.s->id = id;	
			id++;
		    }
		    //station suivante
		    ligne2 = *ligne2.next;
		}
		else 
		{
		    i++;
		    ligne2 = *toutes_les_lignes[i];	
		}
	    }
	}
		
	    /* ******************************* *
	     * Fonctionalitées de l'agent RATP *
	     * ******************************* */
	
	// Met ouvert = 1 à toutes les station de la ligne 
	liste_pStations_t* ouvrir_ligne(liste_pStations_t* ligne)
	{
	    if(ligne->s == NULL)
	    {
		puts("Erreur: ligne inexistante");
		return NULL;
	    }
	    liste_pStations_t* ligne2 = ligne;
	    while(ligne->next != NULL)
	    {
		ligne->s->ouvert = 1; 
		ligne = ligne->next;
	    }     
	    return ligne2;
	}
	
	// Met ouvert = 0 à toutes les station de la ligne 	
	liste_pStations_t* fermer_ligne(liste_pStations_t* ligne)
	{
		if(ligne->s == NULL)
	    {
			puts("Erreur: ligne inexistante");
			return NULL;
	    }
	    liste_pStations_t* ligne2 = ligne;
	    while(ligne->next != NULL)
	    {
		ligne->s->ouvert = 0; 
		ligne = ligne->next;
	    }   
	    return ligne2;
	}
	
	
	// Crée une nouvelle structure liste_pStations_t* et l'ajoute à ligne
	liste_pStations_t* ajout_station(char* nom_station, liste_pStations_t* ligne)
	{
	    liste_pStations_t *new_station;
	    
	    new_station = malloc(4*sizeof(liste_pStations_t*));
	    new_station->s = malloc(4*sizeof(station_t*));
	    new_station->s->nom = (char*)malloc(100*sizeof(char));
	    new_station->next = ligne;
	    strcpy(new_station->s->nom, nom_station);
	    
	    new_station->s->ouvert = 1;
	 
	    return new_station;
	}
	
	// Retire une station d'une ligne
	liste_pStations_t* retirer_station(char* nom_station, liste_pStations_t* ligne)
	{
	    liste_pStations_t* ligne2 = ligne;
	    if(ligne->s == NULL)
	    {
			puts("Erreur: ligne inexistante");
			return NULL;
	    }
	    // Tant qu'on ne trouve pas la station on continue
	    while(ligne->s != NULL)
	    {
		if(strcmp(nom_station, ligne->s->nom) == 0)
		{    
		    *ligne = *ligne->next; 
		    return ligne2;
		}
		   else
		    ligne = ligne->next;
	    }  	    
	    puts("La Station n'a pas été trouvée");
	    return ligne2;
	}
	
	// Retire une station du reseau RATP	
	void retirer_station_carte(char* nom_station, liste_pStations_t** toutes_les_lignes)
	{
	    int i = 0;
	    liste_pStations_t *ligne = toutes_les_lignes[i];
	    // Boucle principale qui navigue sur toutes les lignes
	    while( i < NB_LIGNES)
	    {
		if(ligne->s != NULL)
		{
		    // Si on trouve la station, on la supprime en la sautant
		    if(strcmp(nom_station, ligne->s->nom) == 0)
		    {    
			*ligne = *ligne->next; 
			i++;
			ligne = toutes_les_lignes[i];
		    }
		    else
			ligne = ligne->next;
		}
		if(ligne->s == NULL)
		{
		    i++;
		    ligne = toutes_les_lignes[i];
		}
	    }  	    
	}
	
	// met 1 à nom_station de la ligne 
	void ouvrir_station(char* nom_station, liste_pStations_t* ligne)
	{
	    if(ligne->s == NULL)
	    {
			puts("Erreur: ligne inexistante");
			return ;
	    }
	    // Boucle qui parcourt toute la ligne
	    while(ligne->next != NULL)
	    {
		if(strcmp(nom_station, ligne->s->nom) == 0)
		{
		    if(ligne->s->ouvert == 1)
			puts("Station deja ouverte");
		    ligne->s->ouvert = 1; 
		    if(ligne->s->ouvert == 1)
			puts("La station a bien été ouverte");
		    return ;
		}
		   else
		    ligne = ligne->next;
	    }    
	    puts("La station n'a pas été trouvée");
	}
	
	// met 0 à nom_station de la ligne 	
	void fermer_station(char* nom_station, liste_pStations_t* ligne)
	{
	    if(ligne->s == NULL)
	    {
		puts("Erreur: ligne inexistante");
		return ;
	    }
	    // Boucle qui parcourt toute la ligne
	    while(ligne->next != NULL)
	    {
		if(strcmp(nom_station, ligne->s->nom) == 0)
		{
		    if(ligne->s->ouvert == 0)
			puts("Station deja fermée");
		    ligne->s->ouvert = 0; 
		    if(ligne->s->ouvert == 0)
			puts("La station a bien été fermée");
		    return ;
		}
		else
		    ligne = ligne->next;
	    }  
	    puts("La station n'a pas été trouvée");
	}
	
