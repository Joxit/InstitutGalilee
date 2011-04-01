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

/* Declaration de fonctionnalites supplementaire */

	#include <stdlib.h> /* EXIT_SUCCSS */
	#include <stdio.h> /* Printf */
#include <string.h>
#include "projet_asdl.h"


/* Fonction principale */

int main(int argc, char** argv)
{
	int i;
	int* id = (int*)malloc(sizeof(int));
	*id = 0;
	//liste_pStations_t* toutes_les_stations; TODO
	liste_pStations_t* toutes_les_lignes[14];	
	// Allocation dynamique des variables
	*toutes_les_lignes = malloc(2*NB_STATION*sizeof(liste_pStations_t*));
	for(i = 0; i < NB_STATION; i++)
		toutes_les_lignes[i] = (liste_pStations_t*)malloc(32*sizeof(liste_pStations_t*));
	toutes_les_lignes[0] = ligne1(toutes_les_lignes[0], toutes_les_lignes, id, 0);
	toutes_les_lignes[1] = ligne2(toutes_les_lignes[1], toutes_les_lignes, id, 1);
	toutes_les_lignes[2] = ligne3(toutes_les_lignes[2], toutes_les_lignes, id, 2);
	toutes_les_lignes[3] = ligne4(toutes_les_lignes[3], toutes_les_lignes, id, 3);
	toutes_les_lignes[4] = ligne5(toutes_les_lignes[4], toutes_les_lignes, id, 4);
	toutes_les_lignes[5] = ligne6(toutes_les_lignes[5], toutes_les_lignes, id, 5);
	i = 0;
	//set_id(toutes_les_lignes);
	while(i<NB_STATION)
	{
	    if(( strcmp(toutes_les_lignes[i]->s->nom , "") != 0))
	    {
		printf("%s = %d\n",toutes_les_lignes[i]->s->nom, toutes_les_lignes[i]->s->id);
		toutes_les_lignes[i] = toutes_les_lignes[i]->next;
	    }
	    else i++;
	}
		
		return EXIT_SUCCESS;
}
/* Definitions des fonctions utilisateurs */
