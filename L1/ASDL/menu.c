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
 *	Ce fichier contient toutes les fonctions nécessaires aux                   *
 *	menux utilisateur et agent RATP                                            *
 *	                                                                           *
 *	Dernière modification : Mardi 28 Avril 2011	                               *
 *	                                                                           *
 *	pour plus d'information sur les fonctions voir projet_adsl.h               *
 * ___________________________________________________________________________ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projet_asdl.h"

// Menu principal
void Menu1(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations, int** voisin, int** distance)
{
	int  choix = 0, choix2=0;
	char* reponse = malloc(40*sizeof(char*));	
	puts("_____________________________________________________________");
	puts("|                   \033[35mBienvenue chez la RATP\033[0m                   |");
	puts("|                                                            |");
	puts("|     1) Itineraire                                          |");
	puts("|     2) Infos Lignes                                        |");
	puts("|     3) Infos Stations                                      |");
	puts("|     4) Fonction Avancées                                   |");
	puts("|     5) Quitter                                             |");
	puts("|____________________________________________________________|");
		
	scanf("%d" , &choix);
	purger ();
	switch(choix)
	{
	case 1:
		printf("Choississez votre station de depart : ");
		choix = get_id(get_choix_station(toutes_les_stations), toutes_les_stations);
				
		printf("Choississez votre station d'arriver : ");
				
		choix2 = get_id(get_choix_station(toutes_les_stations), toutes_les_stations);
				
		recherche_intineraires(choix, choix2, distance, toutes_les_lignes, toutes_les_stations);
		break;
	case 2:
		Info_Ligne(toutes_les_lignes, toutes_les_stations);
		break;
	case 3:
		Info_Station(toutes_les_lignes, toutes_les_stations);
		break;
	case 4:
		puts("Etes vous un agent de la RATP? Donnez le mot de passe! ");
		gets(reponse);
		if(strcmp(reponse, MOTDEPASSE) == 0)
		{
			Menu2(toutes_les_lignes, toutes_les_stations, voisin, distance);
		}
		else
			puts("Mot de passe incorrecte!");
		break;
	case 5:
		return;	    
	default :
		puts("Choix incorrecte!");
	}
	free(reponse);
	Menu1(toutes_les_lignes, toutes_les_stations, voisin, distance);
}

//Menu de l'agent RATP
void Menu2(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations, int** voisin, int** distance)
{
	int choix = 0;
	
	puts("_____________________________________________________________");
	puts("|            \033[34mFonction Avancees d'Agent RATP\033[0m                  |");
	puts("|                                                            |");
	puts("|     1) Actions sur Lignes                                  |");
	puts("|     2) Actions sur Stations                                |");		
	puts("|     3) Infos Lignes                                        |");
	puts("|     4) Info Stations                                       |");
	puts("|     5) Sauvegarder                                         |");
	puts("|     6) Retourner au menu utilisateur                       |");
	puts("|____________________________________________________________|");
		
	scanf("%d" , &choix);
	purger ();
	switch(choix)
	{
	case 1:
		Action_Ligne(toutes_les_lignes, toutes_les_stations);
		break;
	case 2:	    
		Action_Station(toutes_les_lignes, toutes_les_stations);
		set_distance(toutes_les_lignes, voisin, distance);
		break;
	case 3:
		Info_Ligne(toutes_les_lignes, toutes_les_stations);
		break;
	case 4:
		Info_Station(toutes_les_lignes, toutes_les_stations);
		break;
	case 5:
		puts("Sauvegarde des changements en cours");
		set_distance(toutes_les_lignes, voisin, distance);
		puts("Sauvegarde terminee, passez une bonne journee");
		break;
	case 6:
		return ;	    
	default :
		puts("Choix incorrecte!");
	}
	Menu2(toutes_les_lignes, toutes_les_stations, voisin, distance);
}

// Sous menu d'information sur les lignes
void Info_Ligne(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations)
{
	int choix = 0;
	puts("Quelles sont les Informations que vous voulez?");
	puts("\t 1) Toutes les stations dans la ligne");
	puts("\t 2) Ligne ouverte ou fermee");
	puts("\t 3) Toutes les lignes de la R.A.T.P");
	puts("\t 4) Retour");
	scanf("%d", &choix);
	purger ();
	switch(choix)
	{
	case 1: 
		printf("Quelle ligne voulez vous voir? 1-14 : ");
		choix = get_choix(choix);
		
		// Vérification d'un cas complexe avec les lignes à plusieurs branches
		switch(choix)
		{
		case 7:
			printf("Directon : %s\n", toutes_les_lignes[6]->s->nom);
			station_dans_ligne( *toutes_les_lignes[6]);
			printf("\nDirecton : %s\n", toutes_les_lignes[7]->s->nom);
			station_dans_ligne( *toutes_les_lignes[7]);
			break;
		case 10:
			printf("Directon : %s\n", toutes_les_lignes[10]->s->nom);
			station_dans_ligne( *toutes_les_lignes[10]);
			printf("\nDirecton : %s\n", toutes_les_lignes[11]->s->nom);
			station_dans_ligne( *toutes_les_lignes[11]);
			break;
		case 13:
			puts("Directon : Saint Denis");
			station_dans_ligne( *toutes_les_lignes[14]);
			puts("\nDirecton : Gennevilliers");
			station_dans_ligne( *toutes_les_lignes[15]);
			break;
		default :
			station_dans_ligne( *toutes_les_lignes[choix_num_ligne(choix)]);
			break;
		}
		return ;
	case 2:
		printf("Quelle ligne voulez vous voir? 1-14 : ");		
		choix = get_choix(choix);		
		printf("La ligne %d est ", choix);
		
		// Vérification d'un cas complexe avec les lignes à plusieurs branches
		switch(choix)
		{
		case 7:
			if(ligne_ouverte( *toutes_les_lignes[6]))
				printf("ouverte ");
			else
				printf("fermee ");
			printf("directon Villejuif et ");
			
			
			if(ligne_ouverte( *toutes_les_lignes[7]))
				printf("ouverte ");
			else
				printf("fermee ");
			puts("directon Ivry");
			return;
			
		case 10:			
			if(ligne_ouverte( *toutes_les_lignes[10]))
				printf("ouverte ");
			else
				printf("fermee ");
			printf("directon Boulogne et ");
			
			if(ligne_ouverte( *toutes_les_lignes[11]))
				printf("ouverte ");
			else
				printf("fermee ");
			puts("directon Gare d'Austerlitz");
			return;
			
		case 13:			
			if(ligne_ouverte( *toutes_les_lignes[14]))
				printf("ouverte ");
			else
				printf("fermee ");
			printf("directon Saint Denis et ");
			
			if(ligne_ouverte( *toutes_les_lignes[15]))
				printf("ouverte ");
			else
				printf("fermee ");
			puts("directon Gennevilliers");
			return;
			
		default :
			if(ligne_ouverte( *toutes_les_lignes[choix_num_ligne(choix)]))
				puts("ouverte");
			else
				puts("fermee");
			return;
		}
	case 3: 
		liste_station_de_toutes_les_lignes(toutes_les_lignes);
		return;
	case 4 :
		return ;
	default :
		puts("Choix incorrecte!");
	}
	Info_Ligne(toutes_les_lignes, toutes_les_stations);
}

// Sous menu d'information sur les stations
void Info_Station(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations)
{
	int choix = 0;
	puts("Quelles sont les Informations que vous voulez?");
	puts("\t 1) Toutes les lignes dans la station");
	puts("\t 2) Station ouverte ou fermee");
	puts("\t 3) Toutes les stations du reseau RATP");
	puts("\t 4) Retour");
	scanf("%d", &choix);
	purger ();
	switch(choix)
	{
	case 1: 
		printf("Quelle Station voulez vous voir? : ");
		ligne_station(get_choix_station(toutes_les_stations), toutes_les_lignes);
		return ;
	case 2:
		printf("Quelle Station voulez vous voir? : ");
		get_station_ouverte(get_choix_station(toutes_les_stations), toutes_les_lignes);
		return ;
	case 3: 
		station_dans_ligne(toutes_les_stations);
		return ;
	case 4: 
		return ;
	default :
		puts("Choix incorrecte!");   
	}
	Info_Station(toutes_les_lignes, toutes_les_stations);	
}

// Sous menu d'action sur les lignes
void Action_Ligne(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations)
{
	int choix = 0;
	puts("Quelle action voulez vous faire?");
	puts("\t 1) Fermer une ligne");
	puts("\t 2) Ouvrir une ligne");
	puts("\t 3) Retour");
	scanf("%d", &choix);
	purger ();
	
	switch(choix)
	{
	case 1: 
		printf("Quel est le numero de la ligne que vous voulez fermer ? : ");
		choix = get_choix(choix);
		purger ();
		
		// Vérification d'un cas complexe avec les lignes à plusieurs branches
		switch(choix)
		{
		case 7:
			printf("Sur quele directon?  %s tapez 1 ", toutes_les_lignes[6]->s->nom);
			printf("directon  %s tapez 2\n", toutes_les_lignes[7]->s->nom);
			choix = get_choix(choix);
			if(choix == 1)
				toutes_les_lignes[6] = fermer_ligne(toutes_les_lignes[6]); 
			else
				toutes_les_lignes[7] = fermer_ligne(toutes_les_lignes[7]); 
			break;
		case 10:
			printf("Sur quele directon? %s tapez 1 ", toutes_les_lignes[10]->s->nom);
			printf("directon %s tapez 2\n", toutes_les_lignes[11]->s->nom);
			choix = get_choix(choix);
			if(choix == 1)
				toutes_les_lignes[10] = fermer_ligne(toutes_les_lignes[10]); 
			else
				toutes_les_lignes[11] = fermer_ligne(toutes_les_lignes[11]); 
			break;
		case 13:
			printf("Sur quele directon? Saint Denis tapez 1 ");
			puts("directon Gennevilliers tapez 2");
			choix = get_choix(choix);
			if(choix == 1)
				toutes_les_lignes[14] = fermer_ligne(toutes_les_lignes[14]); 
			else
				toutes_les_lignes[15] = fermer_ligne(toutes_les_lignes[15]); 
			break;
		default :
			toutes_les_lignes[choix_num_ligne(choix)] = fermer_ligne(toutes_les_lignes[choix_num_ligne(choix)]); 
			break;
		}
		return ;
	case 2:
		printf("Quel est le numero de la ligne que vous voulez ouvrir ? : ");
		choix = get_choix(choix);
		purger ();
		
		// Vérification d'un cas complexe avec les lignes à plusieurs branches
		switch(choix)
		{
		case 7:
			printf("Sur quelle directon?  %s tapez 1 ", toutes_les_lignes[6]->s->nom);
			printf("directon  %s tapez 2\n", toutes_les_lignes[7]->s->nom);
			choix = get_choix(choix);
			if(choix == 1)
				toutes_les_lignes[6] = ouvrir_ligne(toutes_les_lignes[6]); 
			else
				toutes_les_lignes[7] = ouvrir_ligne(toutes_les_lignes[7]); 
			break;
		case 10:
			printf("Sur quelle directon? %s tapez 1 ", toutes_les_lignes[10]->s->nom);
			printf("directon %s tapez 2\n", toutes_les_lignes[11]->s->nom);
			choix = get_choix(choix);
			if(choix == 1)
				toutes_les_lignes[10] = ouvrir_ligne(toutes_les_lignes[10]); 
			else
				toutes_les_lignes[11] = ouvrir_ligne(toutes_les_lignes[11]); 
			break;
		case 13:
			printf("Sur quelle directon? Saint Denis tapez 1 ");
			puts("directon Gennevilliers tapez 2");
			choix = get_choix(choix);
			if(choix == 1)
				toutes_les_lignes[14] = ouvrir_ligne(toutes_les_lignes[14]); 
			else
				toutes_les_lignes[15] = ouvrir_ligne(toutes_les_lignes[15]); 
			break;
		default :
			toutes_les_lignes[choix_num_ligne(choix)] = ouvrir_ligne(toutes_les_lignes[choix_num_ligne(choix)]); 
			break;
		}
		return ;
	case 3: 
		return ;
	default :
		puts("Choix incorrecte!");
	}
	Action_Ligne(toutes_les_lignes, toutes_les_stations); 
}

// Sous menu d'action sur les stations
void Action_Station(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations)
{
	int choix = 0;
	char* nom_station = malloc(100*sizeof(char*));
	puts("Quelle action voulez vous faire?");
	puts("\t 1) Ajouter une Station");
	puts("\t 2) Supprimer une Station");
	puts("\t 3) Ouvrir une Station");
	puts("\t 4) Fermer une Station");
	puts("\t 5) Supprimer une Station du reseau");
	puts("\t 6) Retour");
    
    
	scanf("%d", &choix);
	purger ();
	switch(choix)
	{
	case 1: 
		printf("Quel est le nom de la Station que vous voulez ajouter ? : ");
		nom_station = get_choix_station(toutes_les_stations);
		printf("Quel est le numero de la ligne de %s que vous voulez ajouter ? : ", nom_station);
		choix = get_choix(choix);
		purger ();
		
		// Vérification d'un cas complexe avec les lignes à plusieurs branches
		switch(choix)
		{
		case 7:
			printf("Sur quelle directon?  %s tapez 1 ", toutes_les_lignes[6]->s->nom);
			printf("directon  %s tapez 2\n", toutes_les_lignes[7]->s->nom);
			choix = get_choix(choix);
			if(choix == 1)
				toutes_les_lignes[6] = ajout_station(nom_station, toutes_les_lignes[6]); 
			else
				toutes_les_lignes[7] = ajout_station(nom_station, toutes_les_lignes[7]); 
			break;
		case 10:
			printf("Sur quelle directon? %s tapez 1 ", toutes_les_lignes[10]->s->nom);
			printf("directon %s tapez 2\n", toutes_les_lignes[11]->s->nom);
			choix = get_choix(choix);
			if(choix == 1)
				toutes_les_lignes[10] = ajout_station(nom_station, toutes_les_lignes[10]); 
			else
				toutes_les_lignes[11] = ajout_station(nom_station, toutes_les_lignes[11]); 
			break;
		case 13:
			printf("Sur quelle directon? Saint Denis tapez 1 ");
			puts("directon Gennevilliers tapez 2");
			choix = get_choix(choix);
			if(choix == 1)
				toutes_les_lignes[14] = ajout_station(nom_station, toutes_les_lignes[14]); 
			else
				toutes_les_lignes[15] = ajout_station(nom_station, toutes_les_lignes[15]); 
			break;
		default :
			toutes_les_lignes[choix_num_ligne(choix)] = ajout_station(nom_station, toutes_les_lignes[choix_num_ligne(choix)]); 
			break;
		}
		return ;
	case 2:
		printf("Quel est le nom de la Station que vous voulez supprimer ? : ");
		nom_station = get_choix_station(toutes_les_stations);
		printf("Quel est le numero de la ligne de %s que vous voulez supprimer ? : ", nom_station);
		choix = get_choix(choix);
		purger ();
		
		// Vérification d'un cas complexe avec les lignes à plusieurs branches
		switch(choix)
		{
		case 7:
			printf("Sur quelle directon?  %s tapez 1 ", toutes_les_lignes[6]->s->nom);
			printf("directon  %s tapez 2\n", toutes_les_lignes[7]->s->nom);
			choix = get_choix(choix);
			if(choix == 1)
				toutes_les_lignes[6] = retirer_station(nom_station, toutes_les_lignes[6]); 
			else
				toutes_les_lignes[7] = retirer_station(nom_station, toutes_les_lignes[7]); 
			break;
		case 10:
			printf("Sur quelle directon? %s tapez 1 ", toutes_les_lignes[10]->s->nom);
			printf("directon %s tapez 2\n", toutes_les_lignes[11]->s->nom);
			choix = get_choix(choix);
			if(choix == 1)
				toutes_les_lignes[10] = retirer_station(nom_station, toutes_les_lignes[10]); 
			else
				toutes_les_lignes[11] = retirer_station(nom_station, toutes_les_lignes[11]); 
			break;
		case 13:
			printf("Sur quelle directon? Saint Denis tapez 1 ");
			puts("directon Gennevilliers tapez 2");
			choix = get_choix(choix);
			if(choix == 1)
				toutes_les_lignes[14] = retirer_station(nom_station, toutes_les_lignes[14]); 
			else
				toutes_les_lignes[15] = retirer_station(nom_station, toutes_les_lignes[15]); 
			break;
		default :
			toutes_les_lignes[choix_num_ligne(choix)] = retirer_station(nom_station, toutes_les_lignes[choix_num_ligne(choix)]); 
			break;
		}
		return;
	case 3: 
		printf("Quel est le nom de la Station que vous voulez Ouvrir ? : ");
		nom_station = get_choix_station(toutes_les_stations);
		printf("Quel est le numero de la ligne de %s que vous voulez Ouvrir ? : ", nom_station);
		choix = get_choix(choix);
		purger ();
		
		// Vérification d'un cas complexe avec les lignes à plusieurs branches
		switch(choix)
		{
		case 7:
			printf("Sur quelle directon?  %s tapez 1 ", toutes_les_lignes[6]->s->nom);
			printf("directon  %s tapez 2\n", toutes_les_lignes[7]->s->nom);
			choix = get_choix(choix);
			if(choix == 1)
				ouvrir_station(nom_station, toutes_les_lignes[6]); 
			else
				ouvrir_station(nom_station, toutes_les_lignes[7]); 
			break;
		case 10:
			printf("Sur quelle directon? %s tapez 1 ", toutes_les_lignes[10]->s->nom);
			printf("directon %s tapez 2\n", toutes_les_lignes[11]->s->nom);
			choix = get_choix(choix);
			if(choix == 1)
				ouvrir_station(nom_station, toutes_les_lignes[10]); 
			else
				ouvrir_station(nom_station, toutes_les_lignes[11]); 
			break;
		case 13:
			printf("Sur quelle directon? Saint Denis tapez 1 ");
			puts("directon Gennevilliers tapez 2");
			choix = get_choix(choix);
			if(choix == 1)
				ouvrir_station(nom_station, toutes_les_lignes[14]); 
			else
				ouvrir_station(nom_station, toutes_les_lignes[15]); 
			break;
		default :
			ouvrir_station(nom_station, toutes_les_lignes[choix_num_ligne(choix)]); 
			break;
		}
		return ;
	case 4: 
		printf("Quel est le nom de la Station que vous voulez Fermer ? : ");
		nom_station = get_choix_station(toutes_les_stations);
		printf("Quel est le numero de la ligne de %s que vous voulez Fermer ? : ", nom_station);
		choix = get_choix(choix);
		purger ();
		
		// Vérification d'un cas complexe avec les lignes à plusieurs branches
		switch(choix)
		{
		case 7:
			printf("Sur quelle directon?  %s tapez 1 ", toutes_les_lignes[6]->s->nom);
			printf("directon  %s tapez 2\n", toutes_les_lignes[7]->s->nom);
			choix = get_choix(choix);
			if(choix == 1)
				fermer_station(nom_station, toutes_les_lignes[6]); 
			else
				fermer_station(nom_station, toutes_les_lignes[7]); 
			break;
		case 10:
			printf("Sur quelle directon? %s tapez 1 ", toutes_les_lignes[10]->s->nom);
			printf("directon %s tapez 2\n", toutes_les_lignes[11]->s->nom);
			choix = get_choix(choix);
			if(choix == 1)
				fermer_station(nom_station, toutes_les_lignes[10]); 
			else
				fermer_station(nom_station, toutes_les_lignes[11]); 
			break;
		case 13:
			printf("Sur quelle directon? Saint Denis tapez 1 ");
			puts("directon Gennevilliers tapez 2");
			choix = get_choix(choix);
			if(choix == 1)
				fermer_station(nom_station, toutes_les_lignes[14]); 
			else
				fermer_station(nom_station, toutes_les_lignes[15]); 
			break;
		default :
			fermer_station(nom_station, toutes_les_lignes[choix_num_ligne(choix)]); 
			break;
		}
		return;
	case 5:
		printf("Quel est le nom de la Station que vous voulez supprimer du reseau ? : ");
		nom_station = get_choix_station(toutes_les_stations);
		retirer_station_carte(nom_station, toutes_les_lignes); 
		return ;
	case 6:
		return ;
	default :
		puts("Choix incorrecte!");
	}
	free(nom_station);
	Action_Station(toutes_les_lignes, toutes_les_stations);
}

void purger ()
{
	char c;

	while ((c = getchar()) != '\n' && c != EOF)
	{}
}
