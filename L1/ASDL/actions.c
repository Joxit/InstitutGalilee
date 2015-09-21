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
/* ____________________________  Action.c  ___________________________________
 *  Projet A.S.D.L par MAGLOIRE Jones 11000369 et DELCOURT Rémi 11002398       *
 *  Lignes RATP de paris                                                       *
 *                                                                             *
 *  Ce fichier contient toutes les fonctions nécessaires à la création         *
 *  du réseau RATP et des fonctions de l'agent RATP                            *
 *                                                                             *
 *  Dernière modification : Mardi 28 Avril 2011                                *
 *                                                                             *
 *  pour plus d'informations sur les fonctions voir projet_adsl.h              *
 * ___________________________________________________________________________ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projet_asdl.h"


/* ******************************* *
 * Mise en place du réseau RATP    *
 * ******************************* */

// Création d'une ligne
liste_pStations_t* ajout_ligne(int numero_ligne, liste_pStations_t* ligne, FILE* adt)
{
	int taille;
	char* nom_station = malloc(100*sizeof(char));
	ligne = (liste_pStations_t*)malloc(4*sizeof(liste_pStations_t*));

	while(!feof(adt))
	{
		// On récupère le nom du fichier mis en argument au lancement
		fgets(nom_station, 100, adt);
		if(nom_station == NULL)
			perror("La lecture a echoue");

		// fgets met un saut de ligne à la fin de la variable, on le supprime
		taille = strlen(nom_station);
		nom_station[taille-1] = '\0';
		ligne= ajout_station( nom_station, ligne);
	}
	*ligne = *ligne->next;

	free(nom_station);
	return ligne;
}

/* Creation de la matrice voisin[][] et initialisation de distance[][] */
void est_voisin(int id1, int id2, liste_pStations_t** toutes_les_lignes,int** voisin, int** distance)
{
	int i = 0;
	liste_pStations_t ligne = *toutes_les_lignes[i];
	// Boucle principale qui navigue sur toutes les lignes
	while( i < NB_LIGNES)
	{
		if(ligne.s != NULL)
		{
			// Si on trouve la station, on la supprime en la sautant
			if(is_open(ligne) == 1)
			{
				id1 = ligne.s->id;
				ligne = *ligne.next;
				while(is_open(ligne) == 0)
				{
					ligne = *ligne.next;
					if(ligne.s == NULL)
						break;
				}
				if(is_open(ligne) == 1)
				{
					voisin[id1][ligne.s->id] = 1;
					voisin[ligne.s->id][id1] = 1;
					distance[id1][ligne.s->id] = 1;
					distance[ligne.s->id][id1] = 1;
				}
			}
			else
				if(is_open(*ligne.next) == 0)
				{
					id1 = ligne.s->id;
					ligne = *ligne.next;
					while(is_open(ligne) == 0)
					{
						ligne = *ligne.next;
						if(ligne.s == NULL)
							break;
					}
					if(is_open(ligne) == 1)
					{
						voisin[id1][ligne.s->id] = 1;
						voisin[ligne.s->id][id1] = 1;
						distance[id1][ligne.s->id] = 1;
						distance[ligne.s->id][id1] = 1;
					}
				}
				else
					ligne = *ligne.next;
		}
		if(ligne.s == NULL)
		{
			i++;
			// Vérification pour les erreures de ségmentations
			if( i != NB_LIGNES)
				ligne = *toutes_les_lignes[i];
		}
	}
}

// Création de la liste toutes_les_stations
liste_pStations_t*  liste_station(liste_pStations_t* toutes_les_stations, liste_pStations_t** toutes_les_lignes)
{
	int i, j, x;
	liste_pStations_t ligne;
	// Boucle principale qui compte les 300 stations du reseau
	for(i=0; i < 300; i++)
	{
		j = 0;
		x = FALSE;
		ligne = *toutes_les_lignes[j];
		// Seconde boucle qui fera toutes les lignes du réseau
		while(x == FALSE)
		{
			if(ligne.s != NULL)
			{
				if(i == ligne.s->id)
				{
					// Dès qu'on trouve une id = i on l'ajoute à toutes_les_stations et on quitte
					toutes_les_stations = ajout_station(ligne.s->nom, toutes_les_stations);
					toutes_les_stations->s->id = i;
					x = TRUE;
				}
				else
					ligne = *ligne.next;
			}
			if(ligne.s == NULL)
			{
				j = j + 1;
				// Vérification pour les erreures de ségmentations
				if(j != NB_LIGNES)
					ligne = *toutes_les_lignes[j];
			}
		}
	}
	return toutes_les_stations;
}


// Affecte à toutes les stations de toutes_les_lignes leurs id
void set_id(liste_pStations_t** toutes_les_lignes)
{
	liste_pStations_t ligne;
	liste_pStations_t ligne2;
	int i = 0, j = 0, id = 0, boolean = -1;
	ligne = *toutes_les_lignes[i];
	ligne2 = *toutes_les_lignes[i];

	// Premiere boucle : permet de mettre les id sur toutes les lignes
	while(i < NB_LIGNES)
	{
		// ligne2 est le pointeur qui prend les modifications pour toutes_les_lignes[]
		if(ligne2.s != NULL)
		{
			j = 0;
			ligne = *toutes_les_lignes[j];
			boolean = -1;	   // carte de sortie
			// Deuxième boucle qui permet de vérifier si une station a déjà une id sur toutes les lignes déjà vues
			while(boolean == -1)
			{
				if( ligne.s != NULL)
				{
					// Si on est sur la meme ligne que ligne2 on quitte
					if( j == i)
					{
						boolean = FALSE;
					}
					if(boolean== -1)
					{
						// Comparaison des deux lignes
						if(strcmp(ligne2.s->nom, ligne.s->nom) == 0 )
						{
							// Si les noms sont identique on donne l'id de ligne à ligne2 et on quitte
							ligne2.s->id = ligne.s->id;
							boolean = TRUE;
						}
						else // Sinon on passe
							ligne = *ligne.next;
					}

				}
				else // Si la station est nul on passe à la ligne suivante
					if(ligne.s == NULL)
					{
						j = j + 1;
						// Vérification pour les erreures de ségmentations
						if(j != NB_LIGNES)
							ligne = *toutes_les_lignes[j];
					}

			}
			// Si boolean == FALSE c'est qu'on a pas trouvé de station avec la meme  id
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
			if(i != NB_LIGNES)
				ligne2 = *toutes_les_lignes[i];
		}
	}
}

/* ******************************* *
 * Fonctionalitées de l'agent RATP *
 * ******************************* */

// Met ouvert = 1 à toutes les station de la ligne
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

// Met ouvert = 0 à toutes les station de la ligne
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


// Crée une nouvelle structure liste_pStations_t* et l'ajoute à ligne
liste_pStations_t* ajout_station(char* nom_station, liste_pStations_t* ligne)
{
	liste_pStations_t *new_station;

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
	// Tant qu'on ne trouve pas la station on continue
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
	puts("La Station n'a pas ete trouvee");
	return ligne2;
}

// Retire une station du reseau RATP
void retirer_station_carte(char* nom_station, liste_pStations_t** toutes_les_lignes)
{
	int i = 0;
	liste_pStations_t *ligne = toutes_les_lignes[i];
	// Boucle principale qui navigue sur toutes les lignes
	while( i < NB_LIGNES)
	{
		if(ligne->s != NULL)
		{
			// Si on trouve la station, on la supprime en la sautant
			if(strcmp(nom_station, ligne->s->nom) == 0)
			{
				*ligne = *ligne->next;
				i++;
				// Vérification pour les erreures de ségmentations
				if( i != NB_LIGNES)
					ligne = toutes_les_lignes[i];
			}
			else
				ligne = ligne->next;
		}
		if(ligne->s == NULL)
		{
			i++;
			// Vérification pour les erreures de ségmentations
			if( i != NB_LIGNES)
				ligne = toutes_les_lignes[i];
		}
	}
}

// met 1 à nom_station de la ligne
void ouvrir_station(char* nom_station, liste_pStations_t* ligne)
{
	if(ligne->s == NULL)
	{
		puts("Erreur: ligne inexistante");
		return ;
	}
	// Boucle qui parcourt toute la ligne
	while(ligne->next != NULL)
	{
		if(strcmp(nom_station, ligne->s->nom) == 0)
		{
			if(is_open(*ligne))
				puts("Station deja ouverte");
			ligne->s->ouvert = 1;
			if(is_open(*ligne))
				puts("La station a bien ete ouverte");
			return ;
		}
		else
			ligne = ligne->next;
	}
	puts("La station n'a pas ete trouvee");
}

// met 0 à nom_station de la ligne
void fermer_station(char* nom_station, liste_pStations_t* ligne)
{
	if(ligne->s == NULL)
	{
		puts("Erreur: ligne inexistante");
		return ;
	}
	// Boucle qui parcourt toute la ligne
	while(ligne->next != NULL)
	{
		if(strcmp(nom_station, ligne->s->nom) == 0)
		{
			if(!is_open(*ligne))
				puts("Station deja fermée");
			ligne->s->ouvert = 0;
			if(!is_open(*ligne))
				puts("La station a bien ete fermee");
			return ;
		}
		else
			ligne = ligne->next;
	}
	puts("La station n'a pas ete trouvee");
}


void set_distance(liste_pStations_t* toutes_les_lignes[], int** voisin, int** distance)
{
	double START, END;
	START = temps_CPU();
	puts("\tCreation des matrices");
	int i,j, k;
	for(i = 0; i < 300; i++)
	{
		for(j = 0; j < 150; j++)
		{
			if(i != j)
			{
				// premiere moitie
				voisin[i][j] = 0;
				voisin[j][i] = 0;
				distance[j][i] = 1000;
				distance[i][j] = 1000;
				// deuxieme moitie
				voisin[i][150+j] = 0;
				voisin[150+j][i] = 0;
				distance[150+j][i] = 1000;
				distance[i][150+j] = 1000;
			}
		}
		voisin[i][i] = -1;
		distance[i][i] = 0;
	}
	est_voisin(i,j,toutes_les_lignes, voisin, distance);
	// Premier passage de la boucle distance
	for(i = 0; i < 300; i++){
		for(j = 0; j < 300; j++){
			for(k = 0; k < 300; k++){
				if(distance[i][k] + distance[k][j] < distance[i][j]){
					distance[i][j] = distance[i][k] + distance[k][j];
					distance[j][i] = distance[i][k] + distance[k][j];
				}
			}
		}
	}
	// Deuxièmme passage pour les élements de fin oublié
	for(i = 299; i >= 0; i--){
		for(j = 299; j >= 0; j--){
			for(k = 299; k >= 0; k--){
				if(distance[i][k] + distance[k][j] < distance[i][j]){
					distance[i][j] = distance[i][k] + distance[k][j];
					distance[j][i] = distance[i][k] + distance[k][j];
				}
			}
		}
	}
	END  = temps_CPU();
	printf("\tTemps de creation des matrices : %.4f s\n", END-START);
}
