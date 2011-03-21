/* ______________________________________________________________________________
| Projet A.S.D.L par MAGLOIRE Jones																|
| Lignes RATP de paris																				|
|																											|
| Version 1.0 : mise en place du projet														|
|______________________________________________________________________________ */

/* Declaration de fonctionnalites supplementaire */

	#include <stdlib.h> /* EXIT_SUCCSS */
	#include <stdio.h> /* Printf */
#include <string.h>
#include "projet_asdl.h"



/* Fonction principale */

int main(int argc, char** argv)
{
	int i;
	//liste_pStations_t* toutes_les_stations;
	liste_pStations_t* toutes_les_lignes[14];
	char* nom_station = malloc(40*sizeof(char*));
	//char depart[40];
	//char arriver[40];
	*toutes_les_lignes = malloc(20*sizeof(liste_pStations_t*));
	for(i = 0; i < 14; i++)
	    toutes_les_lignes[i] = (liste_pStations_t*)malloc(30*sizeof(liste_pStations_t*));
	toutes_les_lignes[0] = ligne1(toutes_les_lignes[0]);
	toutes_les_lignes[1] = ligne2(toutes_les_lignes[1]);
	//gets(depart);
	//gets(arriver);
	scanf("%s", nom_station);
	printf("%s\n", nom_station);
	//recherche_intineraires( depart, arriver, toutes_les_lignes); // liste stations entre A et B
	
	
	   //liste_station( *toutes_les_lignes[0]);// MARCHE
	//liste_station_de_toutes_les_lignes(toutes_les_lignes); // MARCHE!
	 //get_station_ouverte( nom_station, toutes_les_lignes);
	 //printf("%d", ligne_ouverte( toutes_les_lignes[1])); // mini 2 stations ouvertes Marche!?
	 // station_dans_ligne( nom_station,  toutes_les_lignes); TODO
	 //ligne_station( nom_station,  toutes_les_lignes); // toutes les lignes d'une station MARCHE!
	// clean(nom_station); MARCHE
	
	   /* TODO*/
	 //retirer_station(nom_station,  toutes_les_lignes[0]);
	 //liste_station( *toutes_les_lignes[0]);
	 //ajout_ligne(int numero_ligne, liste_pStations_t** toutes_les_lignes)	
	 //ouvrir_station( nom_station,  toutes_les_lignes[0]);
	  //fermer_station( nom_station,  toutes_les_lignes[0]);
	 //rechercher_station( nom_station,  toutes_les_lignes);
	 
	 
	 printf("%s\n", nom_station);
	 
	 
	 
	 
	 // DONE Affichage1();
	// DONE Affichage2();
		
		return EXIT_SUCCESS;
}
/* Definitions des fonctions utilisateurs */
