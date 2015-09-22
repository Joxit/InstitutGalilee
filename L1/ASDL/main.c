/*
 * Copyright (C) 2010-2015  Jones Magloire
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/* ___________________________________________________________________________
 *	Projet A.S.D.L par MAGLOIRE Jones 11000369 et DELCOURT Rémi 11002398       *
 *	Lignes RATP de paris                                                       *
 *	                                                                           *
 *	Mardi 28 Avril 2011	                                                       *
 *	                                                                           *
 *	pour plus d'information sur les fonctions voir projet_adsl.h               *
 * ___________________________________________________________________________ */

/* Declaration de fonctionnalites supplementaire */

#include <stdlib.h> /* EXIT_SUCCSS */
#include <stdio.h> /* Printf */
#include <string.h>
#include <sys/resource.h>
#include <time.h>
#include "projet_asdl.h"

/* Fonction principale */

int main(int argc, char** argv)
{
	double START, END;
	START = temps_CPU();
	int i, k;
	FILE* adt;
	int** voisin = (int**)malloc(400*sizeof(int*));
	int** distance = (int**)malloc(400*sizeof(int*));
	liste_pStations_t* toutes_les_stations = malloc(4*sizeof(liste_pStations_t));
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
		distance[i] = (int*)malloc(400*sizeof(int));
	}
	if(voisin == NULL || distance == NULL)
	{
		perror("Allocation de voisin[][] et distance[][]");
		exit(-1);
	}

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
	{
		perror("Initialisation des lignes");
		exit(-1);
	}


	set_distance(toutes_les_lignes, voisin, distance);
	END = temps_CPU();
	printf("\033[35mTemps de lancement : %.4f s\033[0m\n", END-START);

	// Affichage du programme
	Menu1(toutes_les_lignes,  *toutes_les_stations, voisin, distance);

	return EXIT_SUCCESS;
}
