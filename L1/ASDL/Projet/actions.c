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

	/* Fonctionalitées de l'agent RATP */
	// Ajoute une ligne
	liste_pStations_t* ajout_ligne(int numero_ligne, liste_pStations_t* ligne, FILE* adt)
	{
	    int taille;
	    char* nom_station = malloc(100*sizeof(char));
	    ligne = (liste_pStations_t*)malloc(4*sizeof(liste_pStations_t*));
	    
	    while(!feof(adt))
	    {
		fgets(nom_station, 100, adt);
		if(nom_station == NULL)
		    perror("La lecture a echoué");	
		
		taille = strlen(nom_station);
		nom_station[taille-1] = '\0';
		ligne= ajout_station( nom_station, ligne);
	    }
	    *ligne = *ligne->next;
	    
	    return ligne;
	}
	
	// met ouvert = 1 a toutes les station de la ligne 
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
	
	// met ouvert = 0 a toutes les station de la ligne 	
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
	
	
	// crée une nouvelle structure station_t rajoute cette structure à toutes_les_stations MARCHE 
	liste_pStations_t* ajout_station(char* nom_station, liste_pStations_t* ligne)
	{
	    liste_pStations_t *new_station;
	   // int i = 0;
	    
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
	
	void retirer_station_carte(char* nom_station, liste_pStations_t** toutes_les_lignes)
	{
	    int i = 0;
	    liste_pStations_t* ligne = toutes_les_lignes[i];
	    
	    while( i < NB_LIGNES)
	    {
		if(strcmp(nom_station, ligne->s->nom) == 0)
		{    
		    puts("ok");
		    *ligne = *ligne->next; 
		    i++;
		    ligne = toutes_les_lignes[i];
		}
		   else
		    ligne = ligne->next;
	    }  	    
	}
	
	// met 1 a nom_station de la ligne 
	void ouvrir_station(char* nom_station, liste_pStations_t* ligne)
	{
		if(ligne->s == NULL)
	    {
			puts("Erreur: ligne inexistante");
			return ;
	    }
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
	// met 0 a nom_station de la ligne 	
	void fermer_station(char* nom_station, liste_pStations_t* ligne)
	{
	    if(ligne->s == NULL)
	    {
		puts("Erreur: ligne inexistante");
		return ;
	    }
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
	
		// ajoute a la fin de la ligne i la station s. (on suppose que cette station est déjà référencée dans toutes_les_stations 
	station_t ajout_station_en_fin_ligne(station_t* s,int i, liste_pStations_t** toutes_les_lignes)
	{
	    toutes_les_lignes[i]->s = s;
	    return *toutes_les_lignes[i]->s;
	}
	


	int est_voisin(int id1, int id2, liste_pStations_t** toutes_les_lignes)
	{
	    if(id1 == id2)
		return -1;
	    int i = 0;
	    liste_pStations_t ligne;
	    ligne = *toutes_les_lignes[i];
	    while(i < NB_LIGNES)
	    {
		if(ligne.next->s != NULL)
		{
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
		
		if( ligne.next->s == NULL)
		{ 
		    i++;    
		    ligne = *toutes_les_lignes[i];
		}
		else
		   ligne = *ligne.next;
		
	    }
	    return 0;
	}
	void set_id(liste_pStations_t** toutes_les_lignes)
	{
	    liste_pStations_t ligne;
	    liste_pStations_t ligne2;
	    int i = 0, j = 0, id = 0, boolean = -1;
	    ligne = *toutes_les_lignes[i];
	    ligne2 = *toutes_les_lignes[i];
	    
	    // premiere boucle : permet de mettre les id sur toutes les lignes
	    while(i < NB_LIGNES)
	    {
		// ligne2 est le pointeur qui prend les modifications pour toutes_les_lignes[18]
		if(ligne2.s != NULL)
		{
		    j = 0;
		    ligne = *toutes_les_lignes[j];	
		    boolean = -1;	   // carte de sortie
		    // Deuxieme boucle qui permet de verifier si une station a deja une id sur toutes les lignes deja vue 
		    while(boolean == -1)
		    {
			if( ligne.s != NULL)
			{
			    // si on est sur la meme ligne que ligne2 on quitte
			    if( j == i)
			    {
				boolean = FALSE;	
			    }
			    if(boolean== -1)
			    {
				// comparaison des deux lignes
				if(strcmp(ligne2.s->nom, ligne.s->nom) == 0 )
				{
				    // si les noms sont identique on donne l'id de ligne a ligne2 et on quitte
				    ligne2.s->id = ligne.s->id;
				    boolean = TRUE;
				}
				else // sinon on passe
				    ligne = *ligne.next;	
			    }
			    
			}
			else // si la station est nul on passe a la ligne suivante
			    if(ligne.s == NULL)
			    {
				j = j + 1;
				ligne = *toutes_les_lignes[j];	
			    }
			
		    }
		    // si boolean == FALSE c'est qu'on a pas trouvé de station avec la meme  id
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
	