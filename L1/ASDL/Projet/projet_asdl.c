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
	
	// ajoute a la fin de la ligne i la station s. (on suppose que cette station est déjà référencée dans toutes_les_stations 
	station_t ajout_station_en_fin_ligne(station_t* s,int i, liste_pStations_t** toutes_les_lignes)
	{
	    toutes_les_lignes[i]->s = s;
	    return *toutes_les_lignes[i]->s;
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
	    puts("La station n'a pas été trouvée");
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
	    if(choix != 0)
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
	   
	    puts("La station n'a pas été trouvé");
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