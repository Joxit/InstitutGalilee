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
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "projet_asdl.h"

void Menu1(liste_pStations_t** toutes_les_lignes)
{
	    int  choix = 0;
	char* mot_de_passe = malloc(40*sizeof(char*));
	mot_de_passe = MOTDEPASSE;
	char* reponse = malloc(40*sizeof(char*));	
	char* depart = malloc(40*sizeof(char*));
	char* arriver = malloc(40*sizeof(char*));
	depart = "Nation";
	arriver = "La Defense";
		puts("_____________________________________________________________");
		puts("|                       Itineraire RATP                      |");
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
				printf("choississez votre station de depart : ");
				//gets(depart);
				puts(depart);
				printf("choississez votre station d'arriver : ");
				//gets(arriver);
				puts(arriver);
				recherche_intineraires(depart, arriver, toutes_les_lignes[0]);
				break;
		    case 2:
				Info_Ligne(toutes_les_lignes);
				break;
		    case 3:
				Info_Station(toutes_les_lignes);
				break;
		    case 4:
				puts("etes vous un agent de la RATP? Donnez le mot de passe! ");
				gets(reponse);
				if(strcmp(reponse, mot_de_passe) == 0)
				{
					Menu2(toutes_les_lignes);
				}
				else
					puts("Mot de passe incorrecte!");
				break;
		    case 5:
				return;	    
	    default :
		puts("Choix incorrecte!");
	    }
	Menu1(toutes_les_lignes);
}

void Menu2(liste_pStations_t** toutes_les_lignes)
{
	int choix = 0;
	
		puts("_____________________________________________________________");
		puts("|            Fonction Avancées d'Agent RATP                  |");
		puts("|                                                            |");
		puts("|     1) Actions sur Lignes                                  |");
		puts("|     2) Actions sur Stations                                |");		
		puts("|     3) Infos Lignes                                        |");
		puts("|     4) Info Stations                                       |");
		puts("|     5) Retourner au menu utilisateur                       |");
		puts("|____________________________________________________________|");
		
	scanf("%d" , &choix);
	purger ();
	    switch(choix)
	    {
		case 1:
		    Action_Ligne(toutes_les_lignes);
			break;
		case 2:	    
		    Action_Station(toutes_les_lignes);
			break;
		case 3:
		    Info_Ligne(toutes_les_lignes);
			break;
		case 4:
		    Info_Station(toutes_les_lignes);
			break;
		case 5:
		    return ;	    
	    default :
		puts("Choix incorrecte!");
	    }
	Menu2(toutes_les_lignes);
}

void Info_Ligne(liste_pStations_t** toutes_les_lignes)
{
    int choix = 0;
	puts("Quelles sont les Informations que vous voulez?");
	puts("\t 1) Toutes les stations dans la ligne");
	puts("\t 2) Ligne ouverte ou fermée");
	puts("\t 3) retour");
	scanf("%d", &choix);
	purger ();
	switch(choix)
	{
	   case 1: 
		printf("Quel ligne voulez vous voir? 1-14 : ");
		scanf("%d", &choix);
		while(choix < 1 || choix > NB_STATION)
		{
		    printf("Mauvaise ligne!");
		    scanf("%d", &choix);
		}
		station_dans_ligne( *toutes_les_lignes[choix-1]);
		return ;
	    case 2:
		printf("Quel ligne voulez vous voir? 1-14 : ");
		scanf("%d", &choix);
		while(choix < 1 || choix > NB_STATION)
		{
		    printf("Mauvaise ligne!");
		    scanf("%d", &choix);
		}
		printf("La ligne %d est ", choix);
		if(ligne_ouverte(toutes_les_lignes[choix-1]))
		    puts("ouverte");
		else
		    puts("fermée");
		return ;
	    case 3: 
			return ;
	    default :
		puts("Choix incorrecte!");
	}
		Info_Ligne(toutes_les_lignes);
}
void Info_Station(liste_pStations_t** toutes_les_lignes)
{
	int choix = 0;
	char* nom_station = malloc(40*sizeof(char*));
	nom_station = "Nation";
	puts("Quelles sont les Informations que vous voulez?");
	puts("\t 1) Toutes les lignes dans la station");
	puts("\t 2) Station ouverte ou fermée");
	puts("\t 3) retour");
	scanf("%d", &choix);
	purger ();
	switch(choix)
	{
	    case 1: 
			printf("Quel Station voulez vous voir? : ");
			// gets(nom_station); 
			puts(nom_station); 
			/*while(rechercher_station(nom_station, toutes_les_lignes) == NULL)
			{
			    printf("Mauvaise Station!");purger();
			    gets(nom_station); 
			}*/ // TODO
			ligne_station(nom_station, toutes_les_lignes);
			return ;
	    case 2:
			printf("Quel Station voulez vous voir? : ");
			//gets(nom_station);
			puts(nom_station);
			/*while(rechercher_station(nom_station, toutes_les_lignes) == NULL)
			{
			    printf("Mauvaise Station!");
			    gets(nom_station);
			}*/ // TODO
			get_station_ouverte(nom_station, toutes_les_lignes);
			return ;
	    case 3: 
			return ;
	    default :
			puts("Choix incorrecte!");   
	}
	Info_Station(toutes_les_lignes);	
}
void Action_Ligne(liste_pStations_t** toutes_les_lignes)
{
    int choix = 0;
    puts("Quelle action voulez vous faire?");
    puts("\t 1) Ajouter une ligne");
    puts("\t 2) Supprimer une ligne");
    puts("\t 3) Fermer une ligne");
    puts("\t 4) Ouvrir une ligne");
    puts("\t 5) Retour");
	scanf("%d", &choix);
	purger ();
	switch(choix)
	{
	    case 1: 
		printf("Quel est le numero de la ligne que vous voulez ajouter ? : ");
		scanf("%d", &choix);
		purger ();
		toutes_les_lignes[choix-1] = ajout_ligne(choix, toutes_les_lignes);
		    return ;
	    case 2:
		printf("Quel est le numero de la ligne que vous voulez supprimer ? : ");
		scanf("%d", &choix);
		purger ();
		retirer_ligne(choix, toutes_les_lignes); 
		    return ;
	    case 3: 
		printf("Quel est le numero de la ligne que vous voulez fermer ? : ");
		scanf("%d", &choix);
		purger ();
		toutes_les_lignes[choix-1] = fermer_ligne(toutes_les_lignes[choix-1]);
		    return ;
	    case 4: 
		printf("Quel est le numero de la ligne que vous voulez ouvrir ? : ");
		scanf("%d", &choix);
		purger ();
		toutes_les_lignes[choix-1] = ouvrir_ligne(toutes_les_lignes[choix-1]); 
		    return ;
	    case 5:
		    return ;
	    default :
		puts("Choix incorrecte!");
	}
	Action_Ligne(toutes_les_lignes);
    
}
void Action_Station(liste_pStations_t** toutes_les_lignes)
{
    int choix = 0;
    char* nom_station = malloc(40*sizeof(char*));
    nom_station = "Nation";
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
		//gets(nom_station);
		puts(nom_station);
		printf("Quel est le numero de la ligne de %s que vous voulez ajouter ? : ", nom_station);
		scanf("%d", &choix);
		purger ();
		toutes_les_lignes[choix-1] = ajout_station(nom_station, toutes_les_lignes[choix-1]);
		    return ;
	    case 2:
		printf("Quel est le nom de la Station que vous voulez supprimer ? : ");
		//gets(nom_station);
		puts(nom_station);
		printf("Quel est le numero de la ligne de %s que vous voulez supprimer ? : ", nom_station);
		scanf("%d", &choix);
		purger ();
		toutes_les_lignes[choix-1] = retirer_station(nom_station, toutes_les_lignes[choix-1]); 
		    return ;
	    case 3: 
		printf("Quel est le nom de la Station que vous voulez Ouvrir ? : ");
		//gets(nom_station);
		puts(nom_station);
		printf("Quel est le numero de la ligne de %s que vous voulez Ouvrir ? : ", nom_station);
		scanf("%d", &choix);
		purger ();
		ouvrir_station(nom_station, toutes_les_lignes[choix-1]); 
		    return ;
	    case 4: 
		printf("Quel est le nom de la Station que vous voulez Fermer ? : ");
		//gets(nom_station);
		puts(nom_station);
		printf("Quel est le numero de la ligne de %s que vous voulez Fermer ? : ", nom_station);
		scanf("%d", &choix);
		purger ();
		fermer_station(nom_station, toutes_les_lignes[choix-1]); 
		    return ;
	    case 5:
		printf("Quel est le nom de la Station que vous voulez supprimer du reseau ? : ");
		//gets(nom_station);
		puts(nom_station);
		retirer_station_carte(nom_station, toutes_les_lignes); 
		    return ;
	    case 6:
		    return ;
	    default :
		puts("Choix incorrecte!");
	}
	Action_Station(toutes_les_lignes);
}

void purger ()
{
	char c;

	while ((c = getchar()) != '\n' && c != EOF)
	{}
}
