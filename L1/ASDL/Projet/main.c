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
 	Version 1.2 :
 			- Création du mode fichier, toutes les stations des lignes sont dans des fichiers
	
 	Vendredi 1 Avril 2011	
 	
	pour plus d'information sur les fonctions voir projet_adsl.h
______________________________________________________________________________ */

/* Declaration de fonctionnalites supplementaire */

	#include <stdlib.h> /* EXIT_SUCCSS */
	#include <stdio.h> /* Printf */
#include <string.h>
#include "projet_asdl.h"


/* Fonction principale */

int main(int argc, char** argv)
{
	int i, taille, x;
	int* id = (int*)malloc(sizeof(int));
	*id = 0;
	FILE* adt;
	char* nom_station = malloc(100*sizeof(char));
	//liste_pStations_t* toutes_les_stations; TODO
	liste_pStations_t* toutes_les_lignes[18];	
	// Allocation dynamique des variables
	//*toutes_les_lignes = malloc(2*NB_LIGNES*sizeof(liste_pStations_t*));
	for(i = 0; i < NB_LIGNES; i++)
		toutes_les_lignes[i] = (liste_pStations_t*)malloc(40*sizeof(liste_pStations_t*));
	
	if( argc-1 != NB_LIGNES)
	{
		printf("Lancez %s à l'aide de ./run.sh", argv[0]);
		printf(" %d\n", argc);
		exit (-1);
	}
	
	i = 1;
	adt = fopen(argv[i], "r");
	if(adt == NULL)
		perror("Fichier non ouvert");
	puts(argv[i]);
	while(i < argc)
	{
		if(!feof(adt))
		{
			fgets(nom_station, 100, adt);
			if(nom_station == NULL)
				perror("La lecture a echoué");	
			
			taille = strlen(nom_station);
			nom_station[taille-1] = '\0';
			toutes_les_lignes[i-1] = ajout_station( nom_station,  toutes_les_lignes[i-1], toutes_les_lignes, id, i-1);
		}
		else
		{
			toutes_les_lignes[i-1] = toutes_les_lignes[i-1]->next;
			x = fclose(adt);
			if(x != 0)
				perror("Fichier non fermé");
			i++;
			if(i == argc)
				break;
			printf("%s %d < %d \n",argv[i], i, argc);
			adt = fopen(argv[i], "r");
			if(adt == NULL)
				perror("Fichier non ouvert");
		}
	}
	
	for(i = 1; i< argc; i++)
	{
		puts(argv[i]);
		station_dans_ligne(*toutes_les_lignes[i-1]);
		puts("");
	}
	
	//set_id(toutes_les_lignes);
	/*while(i<NB_LIGNES)
	{
	    if(( strcmp(toutes_les_lignes[i]->s->nom , "") != 0))
	    {
		printf("%s = %d\n",toutes_les_lignes[i]->s->nom, toutes_les_lignes[i]->s->id);
		toutes_les_lignes[i] = toutes_les_lignes[i]->next;
	    }
	    else i++;
	}*/
	
	Menu1(toutes_les_lignes);
		
		return EXIT_SUCCESS;
}
/* Definitions des fonctions utilisateurs */
