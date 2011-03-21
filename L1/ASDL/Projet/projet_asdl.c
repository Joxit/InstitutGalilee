/* ______________________________________________________________________________
	Projet A.S.D.L par MAGLOIRE Jones
	Lignes RATP de paris
    
	Version 1.0 : 	- mise en place du projet
			- Création des fonctions de base
______________________________________________________________________________ */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "projet_asdl.h"

	/* initialise le tableau toutes_les_lignes avec des NULL */
	void initialisation(liste_pStations_t** toutes_les_lignes)
	{
	    toutes_les_lignes = malloc(14*sizeof(liste_pStations_t*));
	}
	// Fonctionalitées de l'agent RATP
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
	    while((strcmp(ligne->s->nom , "") != 0))
	    {
		if(strcmp(nom_station, ligne->s->nom))
		{    
		    while(strcmp(ligne->s->nom , "") != 0)
		    {
		    *ligne->s = *ligne->next->s; 
		    ligne = ligne->next;
		    }
		    return ligne;
		}
		   else
		    ligne = ligne->next;
	    }  	    
	    return ligne;
	}
	// Ajoute une ligne
	void ajout_ligne(int numero_ligne, liste_pStations_t** toutes_les_lignes)
	{
	    toutes_les_lignes[numero_ligne-1] = NULL;
	}
	
	void retirer_station_carte(char* nom_station, liste_pStations_t** toutes_les_lignes);	
	// Retire une ligne completement
	liste_pStations_t* retirer_une_ligne(liste_pStations_t* ligne)
	{
	    if(ligne->next != NULL)
	    {
		ligne = retirer_une_ligne(ligne);
	    }
	    ligne->next = NULL;
	    return ligne;
	}
	// met 1 a nom_station de la ligne 
	void ouvrir_station(char* nom_station, liste_pStations_t* ligne)
	{
	    while((strcmp(nom_station, ligne->s->nom) != 0)||(ligne->next != NULL))
	    {
		if(strcmp(nom_station, ligne->s->nom))
		{
		    ligne->s->ouvert = 1; 
		}
		   else
		    *ligne = *ligne->next;
	    }    
	}
	// met 0 a nom_station de la ligne 	
	void fermer_station(char* nom_station, liste_pStations_t* ligne)
	{
	    while((strcmp(nom_station, ligne->s->nom) != 0)||(ligne->next != NULL))
	    {
		if(strcmp(nom_station, ligne->s->nom))
		{
		    ligne->s->ouvert = 0; 
		}
		   else
		    *ligne = *ligne->next;
	    }    
	}
	
	// renvoie un pointeur sur la station dont le nom est donnée en paramètre, ou NULL si erreur
	station_t* rechercher_station(char* nom_station, liste_pStations_t** toutes_les_lignes)
	{
	    int i = 0;
	    while((strcmp(nom_station, toutes_les_lignes[i]->s->nom) != 0)|| i < 14)
	    {
		if(strcmp(nom_station, toutes_les_lignes[i]->s->nom))
		{
		    return toutes_les_lignes[i]->s; 
		}
		if(toutes_les_lignes[i]->next == NULL)
		       i++;
		else
		    *toutes_les_lignes[i] = *toutes_les_lignes[i]->next;

	    }
	    return NULL;
	}
	// ajoute a la fin de la ligne i la station s. (on suppose que cette station est déjà référencée dans toutes_les_stations 
	station_t ajout_station_en_fin_ligne(station_t* s,int i, liste_pStations_t** toutes_les_lignes)
	{
	    toutes_les_lignes[i]->s = s;
	    return *toutes_les_lignes[i]->s;
	}
	

	// fonctionalitées pour l'utilisateur x :
	// liste stations entre A et B
	void recherche_intineraires(char* depart,char* arriver, liste_pStations_t** toutes_les_lignes)
	{
	    
	}
	// affiche les stations de la ligne ligne  MARCHE
	void liste_station(liste_pStations_t ligne)
	{
	    puts("Les Station de cette ligne sont : ");
	    while(ligne.next != NULL)
	    {
		printf("%s\n", ligne.s->nom);
		ligne = *ligne.next;
	    }
	    puts("");
	}
	// Affiche le nom de toutes les stations de toutes les lignes
	void liste_station_de_toutes_les_lignes(liste_pStations_t** toutes_les_lignes)
	{
	    int i;

	    for(i = 0; i < 14; i++)
	    {

		printf("Les Station de la ligne %d sont : \n", i+1);
		while(toutes_les_lignes[i]->next != NULL)
		{
		    printf("%s ", toutes_les_lignes[i]->s->nom);
		    toutes_les_lignes[i] = toutes_les_lignes[i]->next;
		}
		puts("");
		
	    }
	    
	}
	// Affiche les lignes qui sont ouverte pour nom_station
	void get_station_ouverte(char* nom_station, liste_pStations_t** toutes_les_lignes)
	{
	    int i = 0;
	    while((toutes_les_lignes[i]->next != NULL) && (i < 14))
	    {
		printf("%s ", toutes_les_lignes[i]->s->nom);
		if(strcmp(nom_station, toutes_les_lignes[i]->s->nom) == 0)
		{
		    // une station n'est pas deux fois sur la meme ligne
		    i++;
		    if(toutes_les_lignes[i]->s->ouvert == 1)
		    {
			printf("La station %s est ouverte pour la ligne %d \n", nom_station, i);   
		    }
		    else 
			printf("La station %s est fermée pour la ligne %d \n", nom_station, i);
		}
		else
		{
		if( toutes_les_lignes[i]->next == NULL)
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

	    while(ligne->next != NULL || cmp < 2)
	    {
		if(ligne->s->ouvert == 1) // ouvert
		{
		    cmp++;
		}
		    ligne = ligne->next;
	    }
	    
	    return 2 <= cmp;
	}
	
	void station_dans_ligne(char* nom_station, liste_pStations_t** toutes_les_lignes)	
	{
	    int i = 0;
	    while(toutes_les_lignes[i]->next != NULL)
	    {
	    }
	}
	
	// toutes les lignes d'une station	
	void ligne_station(char* nom_station, liste_pStations_t** toutes_les_lignes)
	{
	    int i = 0;
	    printf("Ligne(s) passant par la station %s : ", nom_station);
	    while((strcmp(toutes_les_lignes[i]->s->nom , "") == 0) && (i < 14))
	    {
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
			printf("ok %d %s\n", i, toutes_les_lignes[i]->s->nom );
			toutes_les_lignes[i] = toutes_les_lignes[i]->next;
		    }
		}
	    }
	    puts("");
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
	    int i=0, j=0, p;
	    p = strlen(nom);
	    
	    while(i < p)
	    {
		if(nom[i] > 'Z')
		{
		nom[i] = nom[i] + 'A' - 'a';
		}
		i++;
	    }
	    i = 0;
	    while(i < p)
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
	
	void Affichage1()
	{
		puts("_____________________________________________________________");
		puts("|                       Itineraire RATP                      |");
		puts("|                                                            |");
		puts("|     1) Itineraire                                          |");
		puts("|     2) Info Lignes                                         |");
		puts("|     3) Info Stations                                       |");
		puts("|     4) Fonction Avancées                                   |");
		puts("|     5) Quitter                                             |");
		puts("|____________________________________________________________|");
	}

	void Affichage2()
	{
		puts("_____________________________________________________________");
		puts("|            Fonction Avancées d'Agent RATP                  |");
		puts("|                                                            |");
		puts("|     1) Station en Maintenance                              |");
		puts("|     2) Ajouter Station                                     |");
		puts("|     3) Supprimer Station                                   |");
		puts("|     4) Ajouter Ligne                                       |");
		puts("|     5) Supprimer Ligne                                     |");
		puts("|     6) Info Stations                                       |");
		puts("|     7) Fonction Avancées                                   |");
		puts("|     8) Quitter                                             |");
		puts("|____________________________________________________________|");
	}

	// MARCHE
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

