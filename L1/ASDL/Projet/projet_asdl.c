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
	#include "projet_asdl.h"

	/* initialise le tableau toutes_les_lignes avec des NULL */
	liste_pStations_t** initialisation(liste_pStations_t** toutes_les_lignes)
	{
		/*int i;
		for(i = 0; i < NB_STATION; i++)
			toutes_les_lignes[i] = (liste_pStations_t*)malloc(60*sizeof(liste_pStations_t*));
		toutes_les_lignes[0] = ligne1(toutes_les_lignes[0]);
		toutes_les_lignes[1] = ligne2(toutes_les_lignes[1]);*/
		return toutes_les_lignes;
	}
	/* Fonctionalitées de l'agent RATP */
	// Ajoute une ligne
	liste_pStations_t* ajout_ligne(int numero_ligne, liste_pStations_t** toutes_les_lignes)
	{
	    return toutes_les_lignes[numero_ligne-1] = (liste_pStations_t*)malloc(32*sizeof(liste_pStations_t*));
	    
	}
	// Retire une ligne du reseau
	void retirer_ligne(int numero_ligne, liste_pStations_t** toutes_les_lignes)
	{
	    free(toutes_les_lignes[numero_ligne-1]);
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
	    
	    new_station = malloc(2*sizeof(liste_pStations_t*));
	    new_station->s = malloc(2*sizeof(liste_pStations_t*));
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
	    while((strcmp(ligne->s->nom , "") != 0))
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
	    
	    while( i < NB_STATION)
	    {
		if(strcmp(nom_station, ligne->s->nom) == 0)
		{    
		    *ligne = *ligne->next; 
		    i++;
		    ligne = toutes_les_lignes[i];
		}
		   else
		    ligne = ligne->next;
	    }  	    
	}
	// Retire une ligne completement
	/*liste_pStations_t* retirer_une_ligne(liste_pStations_t* ligne)
	{
	    if(ligne->next != NULL)
	    {
		ligne = retirer_une_ligne(ligne);
	    }
	    ligne->next = NULL;
	    return ligne;
	}*/
	// met 1 a nom_station de la ligne 
	void ouvrir_station(char* nom_station, liste_pStations_t* ligne)
	{
		if(ligne->s == NULL)
	    {
			puts("Erreur: ligne inexistante");
			return ;
	    }
	    while((strcmp(nom_station, ligne->s->nom) != 0)||(ligne->next != NULL))
	    {
		if(strcmp(nom_station, ligne->s->nom))
		{
		    if(ligne->s->ouvert == 1)
			puts("Station deja ouverte");
		    ligne->s->ouvert = 1; 
		    return ;
		}
		   else
		    *ligne = *ligne->next;
	    }    
	}
	// met 0 a nom_station de la ligne 	
	void fermer_station(char* nom_station, liste_pStations_t* ligne)
	{
		if(ligne->s == NULL)
	    {
			puts("Erreur: ligne inexistante");
			return ;
	    }
	    while((strcmp(nom_station, ligne->s->nom) != 0)||(ligne->next != NULL))
	    {
		if(strcmp(nom_station, ligne->s->nom))
		{
		    if(ligne->s->ouvert == 0)
			puts("Station deja fermée");
		    ligne->s->ouvert = 0; 
		    return ;
		}
		   else
		    *ligne = *ligne->next;
	    }    
	}
	
	// renvoie un pointeur sur la station dont le nom est donnée en paramètre, ou NULL si erreur
	station_t* rechercher_station(char* nom_station, liste_pStations_t** toutes_les_lignes)
	{
	    int i = 0;
	    //clean(nom_station);
	    //char* station_clean = malloc(60*sizeof(char*));
	    while(i < NB_STATION)
	    {
		if(toutes_les_lignes[i]->s == NULL)
		       i++;	
		if(i == NB_STATION)
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
	// ajoute a la fin de la ligne i la station s. (on suppose que cette station est déjà référencée dans toutes_les_stations 
	station_t ajout_station_en_fin_ligne(station_t* s,int i, liste_pStations_t** toutes_les_lignes)
	{
	    toutes_les_lignes[i]->s = s;
	    return *toutes_les_lignes[i]->s;
	}
	

	// fonctionalitées pour l'utilisateur x :
	// liste stations entre A et B CAS de base : A et B sur la meme ligne
	void recherche_intineraires(char* depart,char* arrivee, liste_pStations_t* ligne)
	{
	    int i = 1; int bool = FALSE;
		if(strcmp(depart , arrivee) == 0)
		{
			puts("ERREUR : vous avez choisi la meme station!");
			return;
		}
		while((strcmp(ligne->s->nom , "") != 0) || (bool == FALSE))
		{
			if((strcmp(depart, ligne->s->nom) == 0) || (strcmp(arrivee, ligne->s->nom) == 0))
			{
				while(bool == FALSE || (strcmp(ligne->s->nom , "") != 0))
				{
					ligne = ligne->next;
					printf("%s", ligne->s->nom);
					if((strcmp(depart, ligne->s->nom) == 0) || (strcmp(arrivee, ligne->s->nom) == 0))
					{
						bool = TRUE;
						break;
					}
					i = i + 1;
				}
			}
			ligne = ligne->next;				
		}
	    printf("\nLa station %s est a %d arrets de %s\n", depart, i, arrivee);
	}

	void liste_station(liste_pStations_t** toutes_les_lignes)
	{
		int i;
		for(i = 0; i < NB_STATION; i++)
		{
			while(toutes_les_lignes[i]->next != NULL)
			{
				printf("%s ", toutes_les_lignes[i]->s->nom);
				toutes_les_lignes[i] = toutes_les_lignes[i]->next;
			}
		
		}

	}
	// Affiche le nom de toutes les stations de toutes les lignes
	void liste_station_de_toutes_les_lignes(liste_pStations_t** toutes_les_lignes)
	{
	    int i;

	    for(i = 0; i < NB_STATION; i++)
	    {

		printf("Les Station de la ligne %d sont : \n", i+1);
		while(toutes_les_lignes[i]->next != NULL)
		{
		    printf("%s ", toutes_les_lignes[i]->s->nom);
		    toutes_les_lignes[i] = toutes_les_lignes[i]->next;
		}
		
	    }
	    
	}
	// Affiche les lignes qui sont ouverte pour nom_station
	void get_station_ouverte(char* nom_station, liste_pStations_t** toutes_les_lignes)
	{
	    int i = 0;
		
	    while(i < NB_STATION)
	    {
			if(toutes_les_lignes[i]->s == NULL)
			{
				i++;
			}
			if(strcmp(nom_station, toutes_les_lignes[i]->s->nom) == 0)
			{
			    if(toutes_les_lignes[i]->s->ouvert == 1)
			    {
				printf("La station %s est ouverte pour la ligne %d \n", nom_station, i+1);   
			    }
			    else 
					printf("La station %s est fermée pour la ligne %d \n", nom_station, i+1);
			    // une station n'est pas deux fois sur la meme ligne
			    i++;
			}
			else
			{
				if( strcmp(toutes_les_lignes[i]->s->nom , "") == 0)
				{ 
				    i++;    
				}
				else
				    toutes_les_lignes[i] = toutes_les_lignes[i]->next;
			}
	    }
	}
	// test la ligne avec 1 si elle est ouverte et 0 si elle est fermée; mini 2 stations ouvertes
	int ligne_ouverte(liste_pStations_t* ligne) // toutes_les_lignes[i] en argument!
	{
	    int cmp = 0;
	    if(ligne->s == NULL)
	    {
		puts("Erreur: ligne inexistante");
		return 0;
	    }

	    while(( strcmp(ligne->s->nom , "") != 0) || cmp < 2)
	    {
		if(ligne->s->ouvert == 1) // ouvert
		{
		    cmp++;
		}
		if(strcmp(ligne->s->nom , "") == 0) 
		{
		    return 0;
		}
		else
		    ligne = ligne->next;
	    }
	    
	    return 2 <= cmp;
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
	void ligne_station(char* nom_station, liste_pStations_t** toutes_les_lignes)
	{
	    int i = 0;
	    
		printf("Ligne(s) passant par la station %s : ", nom_station);
	    while(i < NB_STATION)
	    {
			if(toutes_les_lignes[i]->s == NULL)
			{
				i++;
			}
			if(strcmp(nom_station, toutes_les_lignes[i]->s->nom)==0)
			{
			    // une station n'est pas deux fois sur la meme ligne
			   i++;
			    printf("%d ", i);		    
			}
			else
			{
			    if( strcmp(toutes_les_lignes[i]->s->nom , "") == 0)
			    { 
					i++;    
			    }
			    else
			    {
					//printf("ok %d %s\n", i, toutes_les_lignes[i]->s->nom );
					toutes_les_lignes[i] = toutes_les_lignes[i]->next;
			    }
			}
	    }
	    puts("");
	}

	int est_voisin(char* station1, char* station2, liste_pStations_t** toutes_les_lignes)
	{
	    int i = 0;
	    while(i < NB_STATION)
	    {
		if(strcmp(station1, toutes_les_lignes[i]->s->nom)==0)
		{
		    if(strcmp(station2, toutes_les_lignes[i]->next->s->nom)==0)
		    {
			return TRUE;
		    }  
		}
		if(strcmp(station2, toutes_les_lignes[i]->s->nom)==0)
		{
		    if(strcmp(station1, toutes_les_lignes[i]->next->s->nom)==0)
		    {
			return TRUE;
		    }  	    
		}
		if( strcmp(toutes_les_lignes[i]->s->nom , "") == 0)
		{ 
		    i++;    
		}
		else
		{
		    toutes_les_lignes[i] = toutes_les_lignes[i]->next;
		}
	    }
	    return FALSE;
	}
	
	void set_id(liste_pStations_t** toutes_les_lignes)
	{
		liste_pStations_t** toutes_les_lignes2 = toutes_les_lignes;
		liste_pStations_t** toutes_les_lignes3 = toutes_les_lignes;
		int i = 0, j = 0, id = 0, Bool = FALSE;
		
		while(i < NB_STATION)
		{
			j = 0;
			toutes_les_lignes3 = toutes_les_lignes;
			Bool = FALSE;				
			if(toutes_les_lignes2[i]->s == NULL)
			{
				i++;
			}
			while(j < i || Bool == FALSE)
			{				
				if(toutes_les_lignes3[j]->s == NULL)
				{
					j++;
				}
				else
				if(strcmp(toutes_les_lignes2[i]->s->nom, toutes_les_lignes3[j]->s->nom) == 0 )
				{
					Bool = TRUE;
					toutes_les_lignes2[i]->s->id = toutes_les_lignes3[j]->s->id;
				}
			}
			if(Bool == FALSE )
			{
					toutes_les_lignes2[i]->s->id = id;	
					id++;
			}		
			toutes_les_lignes2[i] = toutes_les_lignes2[i]->next;			
		}
	}
	// Autorisation des caracteres	
	int allow_chaine(char* station)
	{
	    int i;
	    int p = strlen(station);
	    
	    for(i = 0; i <= p; i++)
	    {
		if(('a' < station[i]  && station[i] < 'z' ) || ('A' < station[i] && station[i] < 'Z') || station[i] != '_'  )
		{

		}
		else
		{
		    puts("Nom de station non valide!");
		    return 0;		    
		}
	   }
	    return 1;
	}
	
	char* clean(char* nom)
	{
	    int i=0, j=0;
	    printf("%d\n", j);
	    while(nom[i] != '\0')
	    {
		puts("ok");
		puts(nom);
		if((nom[i] >= 'a') && (nom[i] <= 'z'))
		{
			puts("fail");
			//nom[i] = toupper(nom[i]);
		}
		i++;
	    }
	    puts("ok2");
	    i = 0;
	    while(nom[i] != '\0')
	    {
			if('A' <= nom[i] && nom[i] <= 'Z')
			{
			    nom[j] = nom[i];
			    j = j + 1;
			}
			i = i +1;
	   }
	   nom[j] = '\0';

	    return nom;
	}
