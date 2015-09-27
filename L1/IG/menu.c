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
 * Jeu Puissance 4 :: fichier Définitions des menus                            *
 *                                                                             *
 * Mardi 17 Mai 2011.                                                          *
 *                                                                             *
 * Pour plus de détails, consulter les fichier d'entête                        *
 * ___________________________________________________________________________ */

#include <stdlib.h>		/* fonction 'rand' de génération aléatoire*/
#include <gtk/gtk.h>
#include <string.h>
#include "puissance4.h"	/* modèle de la chasse au trésor en GTK(constantes symboliques, types, déclaration des fonctions)*/
#include "partie.h"

/* Action lors de la validation du pseudonyme */
void changer_nom(GtkWidget* Item, ctr_s *ctr)
{
	const gchar* nom;
	joueur_s *joueur1 = malloc(13*sizeof(joueur_s));
	joueur_s *joueur2 = malloc(13*sizeof(joueur_s));
	FILE* adt = NULL;

	adt = file_open(adt);

	fseek(adt, 0, SEEK_SET);
	/* On cherche quel est la boite de saisie activee
	 * On met son resultat dans la variable nom
	 * Puis on copie dans la variable nom_joueur correspondante */
	/** Premiere zone de saisie **/
	if(ENV->MenuEntry[0] != NULL && (Item == ENV->MenuEntry[0] || Item == ENV->dBout[0]))
	{
		nom = gtk_entry_get_text(GTK_ENTRY(ENV->MenuEntry[0]));
		/* un pseudo superieur a 4 lettre */
		if(4 < strlen(nom))
			strcpy(JOUEUR_1->nom, nom);
		JOUEUR_1->score = 0;
		/* Mode fichier : Cherche dans le fichier users.dat
		 * le nom du joueur qui vient d'etre entre
		 * s'il existe deja, on recupere son score precedent
		 * sinon on le met a 0 */
		while(!feof(adt))
		{
			fscanf(adt, "%s", joueur1->nom);
			fscanf(adt, "%d", &joueur1->score);
			/* avant de commencer la recherche on verifie que le nom a bien ete pris */
			if(JOUEUR_1->nom!=NULL && joueur1->nom != NULL)
				if(strcmp(JOUEUR_1->nom, joueur1->nom) == 0)
				{
					JOUEUR_1->score = joueur1->score;
					/* si on le trouve on sort */
					break;
				}
		}
	}

	/** Seconde zone de saisie **/
	if(ENV->MenuEntry[1] != NULL && (Item == ENV->MenuEntry[1] || Item == ENV->dBout[0]))
	{
		nom = gtk_entry_get_text(GTK_ENTRY(ENV->MenuEntry[1]));
		/* un pseudo superieur a 4 lettre */
		if(4 < strlen(nom))
			strcpy(JOUEUR_2->nom, nom);
		JOUEUR_2->score = 0;
		/** Mode fichier **/
		while(!feof(adt))
		{
			fscanf(adt, "%s", joueur2->nom);
			fscanf(adt, "%d", &joueur2->score);
			if(JOUEUR_2->nom!=NULL && joueur2->nom != NULL)
				if(strcmp(JOUEUR_2->nom, joueur2->nom) == 0)
				{
					JOUEUR_2->score = joueur2->score;

					/* si on le trouve on sort */
					break;
				}
		}
	}

	maj_pseudo(ctr);

	/* on libere la memoire de joueur */
	free(joueur1);
	free(joueur2);
	gtk_widget_destroy(ENV->Menu);
	if(Item != ENV->dBout[0])
		menu_nom(ENV->Menu, ctr);
	return;

}

/* Fonctin qui sauvegarde les score des deux joueurs actuels dans le fichier*/
void sauvegarder_score(GtkWidget* Item, ctr_s* ctr)
{
	FILE* adt1 = NULL, *adt2 = NULL;
	char* pch;
	joueur_s* joueur = malloc(13*sizeof(joueur_s));

	adt1 = file_open(adt1);

	/* Fichier de substitution */
	if((adt2 = fopen("tmp", "w")) == NULL)
	{
		perror("Fichier tmp non ouvert");
		exit (-1);
	}


	/** On met le nom des joueurs au debut du fichier pour la prochaine partie
	 ** Clean up du nom des joueurs saisi :
 	 ** il ne faut pas d'espaces dans le fichier! **/

	/*  On pointe les espaces et on les remplaces par des '_' jusqu'a la fin de la chaine */
	pch =strchr(JOUEUR_1->nom, ' ');
	while(pch != NULL)
	{
		*pch = '_';
		pch =strchr(JOUEUR_1->nom, ' ');
	}
	/* pui on ecrit dans le fichier */
	fprintf(adt2, "%s %d\n", JOUEUR_1->nom, JOUEUR_1->score);


	/*  On pointe les espaces et on les remplaces par des '_' jusqu'a la fin de la chaine */
	pch =strchr(JOUEUR_2->nom, ' ');
	while(pch != NULL)
	{
		*pch = '_';
		pch =strchr(JOUEUR_2->nom, ' ');
	}
	/* pui on ecrit dans le fichier */
	fprintf(adt2, "%s %d\n", JOUEUR_2->nom, JOUEUR_2->score);



	while(!feof(adt1))
	{
		/* on lit le fichier actuel */
		fscanf(adt1, "%s", joueur->nom);
		fscanf(adt1, "%d", &joueur->score);
		if(joueur->nom != NULL && !feof(adt1))
		{
			/* Comparaison si on tombe sur un joueur existant on ne l'ecrit pas */
			if((strcmp(JOUEUR_1->nom, joueur->nom) !=0) && (strcmp(JOUEUR_2->nom, joueur->nom) != 0))
			{
				/* si le joueur lu n'est aucun des deux on reecrit son nom et son score passé */
				fprintf(adt2, "%s %d\n", joueur->nom, joueur->score);
			}
		}
	}

	/* on fini par un saut de ligne en plus et liberer la memoire des variables */
	fprintf(adt2, "\n");
	fclose(adt1);
	fclose(adt2);
	free(joueur);
	/* on supprime l'ancien fichier et renome le nouveau */
	remove("users.dat");
	rename("tmp", "users.dat");
}

/* renvoit la chaine de char du classement des joueurs pour Top_5 */
char* get_classement()
{
	FILE* adt = NULL;
	char* pch, *liste_classement = malloc(200*sizeof(char));
	int i = 0,j = 0, score[6];
	joueur_s* joueur = malloc(13*sizeof(joueur_s));

	adt = file_open(adt);

	score[0] = 1000;

	/** Deuxieme etage **/
	for(i = 1; i < 6; i = i + 1)
	{
		/* porte de sortie pour eviter que le meme score apparaisse jusqu'a la fin du tableau */
		if(score[i] == score[i-2] && i > 1)
			break;
		/* on se place  au debut du fichier et on lit la premiere ligne et enregistre le score */
		fseek(adt, 0, SEEK_SET);
		score[i] = 0;
		/* suite de la lecture jusqu'a la fin du fichier */
		while(!feof(adt))
		{
			fscanf(adt, "%s", joueur->nom);
			fscanf(adt, "%d", &joueur->score);
			/** Verification : score[i] < joueur->score < score[i-1] pour trouver le vrai suivant
			 ** joueur->nom doit exister pour eviter les bugs **/
			if(score[i] < joueur->score && score[i-1] > joueur->score && joueur->nom != NULL)
				score[i] = joueur->score;
		}
	}
	/* on initialise la variable qui contiendra la liste */
	strcpy(liste_classement, "");
	for(i = 1; i < 6; i = i + 1)
	{
		/* porte de sortie pour eviter l'affichage en plusieur exemplaire des joueurs au meme score */
		if(score[i] == score[i-1])
			break;
		/* on se place au debut du fichier */
		fseek(adt, 0, SEEK_SET);
		while(!feof(adt))
		{
			/* lecture des lignes du fichier */
			fscanf(adt, "%s", joueur->nom);
			fscanf(adt, "%d", &joueur->score);
			/* on cherche si le score lu correspond a clui qu'on veut afficher */
			if(score[i] == joueur->score && !feof(adt) && joueur->nom != NULL)
			{
				pch = NULL;
				/* on pointe la fin de la chaine de caractere liste_classement*/
				pch = &liste_classement[ strlen(liste_classement) ];
				/* et on ecrit le pseudo et le score du joueur */
				sprintf(pch, "%s\t : \t %d\n", joueur->nom, joueur->score);
				j = j + 1;
			}
			/* Quand on est a 5 joueurs affiche on sort des boucles brusquement*/
			if(j == 5)
			{
				i = 6;
				break;
			}
		}
	}
#if (PUISSANCE4_MODELE_DEBUG != 0)
	printf("\tTop_5  i == %d j == %d liste_classement : \n%sScore : %d; %d; %d; %d; %d; %d\n", i, j, liste_classement, score[0], score[1], score[2], score[3], score[4], score[5]);
#endif

	fclose(adt);
	free(joueur);
	return liste_classement;
}


FILE* file_open(FILE* adt)
{
	/* Fichier contenant les scores */
	if((adt = fopen("users.dat", "r")) == NULL)
	{
		perror("Fichier users.dat non ouvert");
		/* si l'utilisateur a supprime le fichier apres l'ouverture du programme on en cree un nouveau */
		if((adt = fopen("users.dat", "w")) == NULL)
		{
			perror("Creation du fichier users.dat impossible");
			exit (-1);
		}
		fclose(adt);
		if((adt = fopen("users.dat", "r")) == NULL)
		{
			perror("Fichier unsers.dat non ouvert");
			exit (-1);
		}
	}
	return adt;
}
