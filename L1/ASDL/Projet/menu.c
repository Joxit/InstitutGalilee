/* ______________________________________________________________________________
	Projet A.S.D.L par MAGLOIRE Jones 11000369 et DELCOURT Rémi 11002398
	Lignes RATP de paris
    
 	Vendredi 1 Avril 2011	
	
	pour plus d'information sur les fonctions voir projet_adsl.h
______________________________________________________________________________ */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "projet_asdl.h"

void Menu1(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations, int** voisin, int** distance)
{
	    int  choix = 0, choix2=0;
	char* mot_de_passe = malloc(40*sizeof(char*));
	mot_de_passe = MOTDEPASSE;
	char* reponse = malloc(40*sizeof(char*));	
	char* depart = malloc(100*sizeof(char*));
	char* arriver = malloc(100*sizeof(char*));
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
				printf("Choississez votre station de depart : ");
				gets(depart);
				choix = get_id(depart, toutes_les_stations);
				/*while( choix == -1 && choix > 300)
				{
				    gets(depart);
				    choix = get_id(depart, toutes_les_stations); 
				}*/
				depart = get_nom_station(choix, toutes_les_stations);
				printf("Choississez votre station d'arriver : ");
				gets(arriver);
				choix2 = get_id(arriver, toutes_les_stations);
				/*while( choix2 == -1 && choix > 300)
				{
				    gets(arriver);
				    choix2 = get_id(arriver, toutes_les_stations); 
				}*/
				arriver = get_nom_station(choix2, toutes_les_stations);
				recherche_intineraires(choix, choix2, voisin, distance, toutes_les_lignes, toutes_les_stations);
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
				if(strcmp(reponse, mot_de_passe) == 0)
				{
					Menu2(toutes_les_lignes, toutes_les_stations);
				}
				else
					puts("Mot de passe incorrecte!");
				break;
		    case 5:
				return;	    
	    default :
		puts("Choix incorrecte!");
	    }
	Menu1(toutes_les_lignes, toutes_les_stations, voisin, distance);
}

void Menu2(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations)
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
		    Action_Ligne(toutes_les_lignes, toutes_les_stations);
			break;
		case 2:	    
		    Action_Station(toutes_les_lignes, toutes_les_stations);
			break;
		case 3:
		    Info_Ligne(toutes_les_lignes, toutes_les_stations);
			break;
		case 4:
		    Info_Station(toutes_les_lignes, toutes_les_stations);
			break;
		case 5:
		    return ;	    
	    default :
		puts("Choix incorrecte!");
	    }
	Menu2(toutes_les_lignes, toutes_les_stations);
}

void Info_Ligne(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations)
{
    int choix = 0;
	puts("Quelles sont les Informations que vous voulez?");
	puts("\t 1) Toutes les stations dans la ligne");
	puts("\t 2) Ligne ouverte ou fermée");
	puts("\t 3) Toutes les lignes de la R.A.T.P");
	puts("\t 4) Retour");
	scanf("%d", &choix);
	purger ();
	switch(choix)
	{
	   case 1: 
		printf("Quel ligne voulez vous voir? 1-14 : ");
		choix = get_choix(choix);
		switch(choix)
		{
		    case 7:
			printf("Directon : %s\n", toutes_les_lignes[6]->s->nom);
			station_dans_ligne( *toutes_les_lignes[6]);
			printf("Directon : %s\n", toutes_les_lignes[7]->s->nom);
			station_dans_ligne( *toutes_les_lignes[7]);
			break;
		    case 10:
			printf("Directon : %s\n", toutes_les_lignes[10]->s->nom);
			station_dans_ligne( *toutes_les_lignes[10]);
			printf("Directon : %s\n", toutes_les_lignes[11]->s->nom);
			station_dans_ligne( *toutes_les_lignes[11]);
			break;
		    case 13:
			puts("Directon : Saint Denis");
			station_dans_ligne( *toutes_les_lignes[14]);
			puts("Directon : Gennevilliers");
			station_dans_ligne( *toutes_les_lignes[15]);
			break;
		    default :
			station_dans_ligne( *toutes_les_lignes[choix_num_ligne(choix)]);
			break;
		}
		return ;
	    case 2:
		printf("Quel ligne voulez vous voir? 1-14 : ");		
		choix = get_choix(choix);		
		printf("La ligne %d est ", choix);
		switch(choix)
		{
		    case 7:
			if(ligne_ouverte( *toutes_les_lignes[6]))
			    printf("ouverte ");
			else
			    printf("fermée ");
			printf("directon Villejuif et ");
			
			
			if(ligne_ouverte( *toutes_les_lignes[7]))
			    printf("ouverte ");
			else
			    printf("fermée ");
			puts("directon Ivry");
			return;
			
		    case 10:			
			if(ligne_ouverte( *toutes_les_lignes[10]))
			    printf("ouverte ");
			else
			    printf("fermée ");
			printf("directon Boulogne et ");
			
			if(ligne_ouverte( *toutes_les_lignes[11]))
			    printf("ouverte ");
			else
			    printf("fermée ");
			puts("directon Gare d'Austerlitz");
			return;
			
		    case 13:			
			if(ligne_ouverte( *toutes_les_lignes[14]))
			    printf("ouverte ");
			else
			    printf("fermée ");
			printf("directon Saint Denis et ");
			
			if(ligne_ouverte( *toutes_les_lignes[15]))
			    printf("ouverte ");
			else
			    printf("fermée ");
			puts("directon Gennevilliers");
			return;
			
		    default :
			if(ligne_ouverte( *toutes_les_lignes[choix_num_ligne(choix)]))
			    puts("ouverte");
			else
			    puts("fermée");
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
void Info_Station(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations)
{
	int choix = 0;
	char* nom_station = (char*)malloc(100*sizeof(char));
	puts("Quelles sont les Informations que vous voulez?");
	puts("\t 1) Toutes les lignes dans la station");
	puts("\t 2) Station ouverte ou fermée");
	puts("\t 3) Retour");
	scanf("%d", &choix);
	purger ();
	switch(choix)
	{
	    case 1: 
			printf("Quel Station voulez vous voir? : ");
			gets(nom_station);
			puts(nom_station); 
			choix = get_id(nom_station, toutes_les_stations);
			while( choix == -1)
			{
			    gets(nom_station);purger();
			    choix = get_id(nom_station, toutes_les_stations); 
			}
			ligne_station(get_nom_station(choix, toutes_les_stations), toutes_les_lignes);
			return ;
	    case 2:
			printf("Quel Station voulez vous voir? : ");
			gets(nom_station);
			choix = get_id(nom_station, toutes_les_stations);
			while( choix == -1)
			{
			    gets(nom_station);purger();
			    choix = get_id(nom_station, toutes_les_stations); 
			}
			get_station_ouverte(get_nom_station(choix, toutes_les_stations), toutes_les_lignes);
			return ;
	    case 3: 
			return ;
	    default :
			puts("Choix incorrecte!");   
	}
	Info_Station(toutes_les_lignes, toutes_les_stations);	
}
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
		if(choix_num_ligne(choix) != -1)
		    toutes_les_lignes[choix_num_ligne(choix)] = fermer_ligne(toutes_les_lignes[choix_num_ligne(choix)]);
		    return ;
	    case 2:
		printf("Quel est le numero de la ligne que vous voulez ouvrir ? : ");
		choix = get_choix(choix);
		purger ();
		if(choix_num_ligne(choix) != -1)
		   toutes_les_lignes[choix_num_ligne(choix)] = ouvrir_ligne(toutes_les_lignes[choix_num_ligne(choix)]); 
		    return ;
	    case 3: 
		    return ;
	    default :
		puts("Choix incorrecte!");
	}
	Action_Ligne(toutes_les_lignes, toutes_les_stations); 
}
void Action_Station(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations)
{
    int choix = 0;
    char* nom_station = malloc(40*sizeof(char*));
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
		gets(nom_station);
			choix = get_id(nom_station, toutes_les_stations);
			while( choix == -1)
			{
			    gets(nom_station);purger();
			    choix = get_id(nom_station, toutes_les_stations); 
			}
		nom_station = get_nom_station(choix, toutes_les_stations);
		printf("Quel est le numero de la ligne de %s que vous voulez ajouter ? : ", nom_station);
		choix = get_choix(choix);
		purger ();
		switch(choix)
		{
		    case 7:
			printf("Sur quel directon?  %s tapez 1 ", toutes_les_lignes[6]->s->nom);
			printf("directon  %s tapez 2\n", toutes_les_lignes[7]->s->nom);
			choix = get_choix(choix);
			    if(choix == 1)
				toutes_les_lignes[6] = ajout_station(nom_station, toutes_les_lignes[6]); 
			    else
				toutes_les_lignes[7] = ajout_station(nom_station, toutes_les_lignes[7]); 
			break;
		    case 10:
			printf("Sur quel directon? %s tapez 1 ", toutes_les_lignes[10]->s->nom);
			printf("directon %s tapez 2\n", toutes_les_lignes[11]->s->nom);
			choix = get_choix(choix);
			    if(choix == 1)
				toutes_les_lignes[10] = ajout_station(nom_station, toutes_les_lignes[10]); 
			    else
				toutes_les_lignes[11] = ajout_station(nom_station, toutes_les_lignes[11]); 
			break;
		    case 13:
			printf("Sur quel directon? Saint Denis tapez 1 ");
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
		gets(nom_station);
			choix = get_id(nom_station, toutes_les_stations);
			while( choix == -1)
			{
			    gets(nom_station);
			    choix = get_id(nom_station, toutes_les_stations); 
			}
		nom_station = get_nom_station(choix, toutes_les_stations);
		printf("Quel est le numero de la ligne de %s que vous voulez supprimer ? : ", nom_station);
		choix = get_choix(choix);
		purger ();
		switch(choix)
		{
		    case 7:
			printf("Sur quel directon?  %s tapez 1 ", toutes_les_lignes[6]->s->nom);
			printf("directon  %s tapez 2\n", toutes_les_lignes[7]->s->nom);
			choix = get_choix(choix);
			    if(choix == 1)
				toutes_les_lignes[6] = retirer_station(nom_station, toutes_les_lignes[6]); 
			    else
				toutes_les_lignes[7] = retirer_station(nom_station, toutes_les_lignes[7]); 
			break;
		    case 10:
			printf("Sur quel directon? %s tapez 1 ", toutes_les_lignes[10]->s->nom);
			printf("directon %s tapez 2\n", toutes_les_lignes[11]->s->nom);
			choix = get_choix(choix);
			    if(choix == 1)
				toutes_les_lignes[10] = retirer_station(nom_station, toutes_les_lignes[10]); 
			    else
				toutes_les_lignes[11] = retirer_station(nom_station, toutes_les_lignes[11]); 
			break;
		    case 13:
			printf("Sur quel directon? Saint Denis tapez 1 ");
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
		gets(nom_station);
			choix = get_id(nom_station, toutes_les_stations);
			while( choix == -1)
			{
			    gets(nom_station);purger();
			    choix = get_id(nom_station, toutes_les_stations); 
			}
		nom_station = get_nom_station(choix, toutes_les_stations);
		printf("Quel est le numero de la ligne de %s que vous voulez Ouvrir ? : ", nom_station);
		choix = get_choix(choix);
		purger ();
		switch(choix)
		{
		    case 7:
			printf("Sur quel directon?  %s tapez 1 ", toutes_les_lignes[6]->s->nom);
			printf("directon  %s tapez 2\n", toutes_les_lignes[7]->s->nom);
			choix = get_choix(choix);
			    if(choix == 1)
				ouvrir_station(nom_station, toutes_les_lignes[6]); 
			    else
				ouvrir_station(nom_station, toutes_les_lignes[7]); 
			break;
		    case 10:
			printf("Sur quel directon? %s tapez 1 ", toutes_les_lignes[10]->s->nom);
			printf("directon %s tapez 2\n", toutes_les_lignes[11]->s->nom);
			choix = get_choix(choix);
			    if(choix == 1)
				ouvrir_station(nom_station, toutes_les_lignes[10]); 
			    else
				ouvrir_station(nom_station, toutes_les_lignes[11]); 
			break;
		    case 13:
			printf("Sur quel directon? Saint Denis tapez 1 ");
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
		gets(nom_station);
			choix = get_id(nom_station, toutes_les_stations);
			while( choix == -1)
			{
			    gets(nom_station);purger();
			    choix = get_id(nom_station, toutes_les_stations); 
			}
		nom_station = get_nom_station(choix, toutes_les_stations);
		printf("Quel est le numero de la ligne de %s que vous voulez Fermer ? : ", nom_station);
		choix = get_choix(choix);
		purger ();
		switch(choix)
		{
		    case 7:
			printf("Sur quel directon?  %s tapez 1 ", toutes_les_lignes[6]->s->nom);
			printf("directon  %s tapez 2\n", toutes_les_lignes[7]->s->nom);
			choix = get_choix(choix);
			    if(choix == 1)
				fermer_station(nom_station, toutes_les_lignes[6]); 
			    else
				fermer_station(nom_station, toutes_les_lignes[7]); 
			break;
		    case 10:
			printf("Sur quel directon? %s tapez 1 ", toutes_les_lignes[10]->s->nom);
			printf("directon %s tapez 2\n", toutes_les_lignes[11]->s->nom);
			choix = get_choix(choix);
			    if(choix == 1)
				fermer_station(nom_station, toutes_les_lignes[10]); 
			    else
				fermer_station(nom_station, toutes_les_lignes[11]); 
			break;
		    case 13:
			printf("Sur quel directon? Saint Denis tapez 1 ");
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
		gets(nom_station);
			choix = get_id(nom_station, toutes_les_stations);
			while( choix == -1)
			{
			    gets(nom_station);purger();
			    choix = get_id(nom_station, toutes_les_stations); 
			}
		nom_station = get_nom_station(choix, toutes_les_stations);
		retirer_station_carte(nom_station, toutes_les_lignes); 
		    return ;
	    case 6:
		    return ;
	    default :
		puts("Choix incorrecte!");
	}
	Action_Station(toutes_les_lignes, toutes_les_stations);
}

void purger ()
{
	char c;

	while ((c = getchar()) != '\n' && c != EOF)
	{}
}
