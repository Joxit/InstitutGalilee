/* ______________________________________________________________________________
	Projet A.S.D.L par MAGLOIRE Jones 11000369 et DELCOURT Rémi 11002398
	Lignes RATP de paris
	
	Vendredi 1 Avril 2011	
	
	pour plus d'information sur les fonctions voir projet_adsl.h
______________________________________________________________________________ */

/* Declaration de fonctionnalites supplementaire */

	#include <stdlib.h> /* EXIT_SUCCSS */
	#include <stdio.h> /* Printf */
	#include <string.h>
	#include <sys/resource.h>
	#include <time.h>
	#include "projet_asdl.h"

double temps_CPU()
{
	struct rusage usage;

	getrusage(RUSAGE_SELF, &usage);
	return usage.ru_utime.tv_sec + (usage.ru_utime.tv_usec / 1000000.0);
}

/* Fonction principale */

int main(int argc, char** argv)
{
    double START, END;
    START = temps_CPU();
    int i, j, k;
    FILE* adt;
    int** voisin = (int**)malloc(400*sizeof(int*));
    int** distance = (int**)malloc(400*sizeof(int*));
    liste_pStations_t* toutes_les_stations = malloc(2*sizeof(liste_pStations_t));
    liste_pStations_t* toutes_les_lignes[18];
    
    if( argc-1 != NB_LIGNES)
    {
	printf("Lancez %s à l'aide de ./run.sh", argv[0]);
	printf(" %d\n", argc);
	exit (-1);
    }
    
    // Allocation dynamique des variables
	for(i = 0; i <= 300; i++)
	{
	    voisin[i] = (int*)malloc(400*sizeof(int));
	    voisin[i][i] = 0;
	    distance[i] = (int*)malloc(400*sizeof(int));
	    distance[i][i] = 0;	    
	}
	if(voisin == NULL || distance == NULL)
	    perror("Allocation de voisin[][] et distance[][]");
    
    // Initialisation des liges
	for(i = 0; i < NB_LIGNES; i++)
	{
	    adt = fopen(argv[i+1], "r");
	    if(adt == NULL)
		perror("Fichier non ouvert");
	    toutes_les_lignes[i] = ajout_ligne(i+1, toutes_les_lignes[i], adt);
	
	    k = fclose(adt);
	    if(k != 0)
		perror("Fichier non fermé");
	}
    // Initialisation du mode id
	set_id(toutes_les_lignes);
    // Initialisation de la liste des stations
	toutes_les_stations = liste_station(toutes_les_stations,  toutes_les_lignes);
	if(toutes_les_stations == NULL || toutes_les_lignes == NULL)
	    perror("Initialisation des lignes");
    
    for(i = 0; i < 300; i++){
	for(j = 0; j < 300; j++){
	    voisin[i][j] = est_voisin(i,j,toutes_les_lignes);
	    if(voisin[i][j] > 0)
		distance[i][j] = voisin[i][j];
	    else
		if(i !=j)
		    distance[i][j] = 1000;
	}
    }
    
    for(i = 0; i < 300; i++){
   	for(j = 0; j < 300; j++){
	    for(k = 0; k < 300; k++){
		if(distance[i][k] + distance[k][j] < distance[i][j]){
		    distance[i][j] = distance[i][k] + distance[k][j];
		}
	    }
	}
    }
    
    END = temps_CPU();
    printf("\tCPU time : %.4f s\n", END-START);
    // Affichage du programme
    Menu1(toutes_les_lignes,  *toutes_les_stations, voisin, distance);
    
    return EXIT_SUCCESS;
}
