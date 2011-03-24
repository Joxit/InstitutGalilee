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
	int i, choix = 0;
	char* mot_de_passe = malloc(40*sizeof(char*));
	mot_de_passe = "Joxit!";
	char* reponse = malloc(40*sizeof(char*));
	//liste_pStations_t* toutes_les_stations;
	liste_pStations_t* toutes_les_lignes[14];
	char* nom_station = malloc(40*sizeof(char*));
	char* depart = malloc(40*sizeof(char*));
	char* arriver = malloc(40*sizeof(char*));
	*toutes_les_lignes = malloc(20*sizeof(liste_pStations_t*));
	for(i = 0; i < 14; i++)
	    toutes_les_lignes[i] = (liste_pStations_t*)malloc(60*sizeof(liste_pStations_t*));
	toutes_les_lignes[0] = ligne1(toutes_les_lignes[0]);
	toutes_les_lignes[1] = ligne2(toutes_les_lignes[1]);
	//gets(depart);
	//gets(arriver);
	gets(nom_station);
	//recherche_intineraires( depart, arriver, toutes_les_lignes); // liste stations entre A et B
	
	
	   //liste_station( *toutes_les_lignes[0]);// TODO
	//liste_station_de_toutes_les_lignes(toutes_les_lignes); // MARCHE!
	 //get_station_ouverte( nom_station, toutes_les_lignes);
	 //printf("%d", ligne_ouverte( toutes_les_lignes[1])); // mini 2 stations ouvertes Marche!?
	 // station_dans_ligne( nom_station,  toutes_les_lignes); //marche
	 //ligne_station( nom_station,  toutes_les_lignes); // toutes les lignes d'une station MARCHE!
	 clean(nom_station);// MARCHE
	printf("%s\n", nom_station);
	   /* TODO*/
	 //retirer_station(nom_station,  toutes_les_lignes[0]);
	 //liste_station( *toutes_les_lignes[0]);
	 //ajout_ligne(int numero_ligne, liste_pStations_t** toutes_les_lignes)	
	 //ouvrir_station( nom_station,  toutes_les_lignes[0]);
	  //fermer_station( nom_station,  toutes_les_lignes[0]);
	 //rechercher_station( nom_station,  toutes_les_lignes);
	 
	 //recherche_intineraires(depart, arriver, toutes_les_lignes);
	
	 
	 
	 
	 
	  Affichage1();
		    
	    switch(choix)
	    {
		    case 1:
			printf("choississez votre station de depart : ");
			gets(depart);
			printf("choississez votre station d'arriver : ");
			gets(arriver);
			recherche_intineraires(depart, arriver, toutes_les_lignes);
		    case 2:
			printf("Quel ligne voulez vous voir? 1-14");
			scanf("%d", &choix);
			while(choix < 1 || choix > 14)
			{
				printf("Mauvaise ligne!");
				scanf("%d", &choix);
			}
			station_dans_ligne( *toutes_les_lignes[choix-1]);
		    case 3:
			printf("choississez votre station : ");
			gets(nom_station);
			ligne_station( nom_station,  toutes_les_lignes);
		    case 4:
			puts("etes vous un agent de la RATP? Donnez le mot de passe! ");
			gets(reponse);
			if(strcmp(reponse, mot_de_passe) == 0)
			{
				Affichage2();
			}
			else
				puts("Mot de passe incorecte!");
		    case 5:
			return EXIT_SUCCESS;
	    }
	// DONE Affichage2();
		
		return EXIT_SUCCESS;
}
/* Definitions des fonctions utilisateurs */
