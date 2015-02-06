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
/* _____________________________________________________________________________
 * J *eu Puissance 4 : Fichier Principal									
 *
 * Mardi 17 Mai 2011.												
 *
 * Pour plus de détails, consulter les fichier d'entête						
 * ____________________________________________________________________________ */

/* Declaration de fonctionnalites supplementaire */

#include <stdlib.h> /* EXIT_SUCCSS */
#include <stdio.h> /* Printf */	
#include <gtk/gtk.h>	
#include <time.h>		/*fonction 'time', utilisée pour la génération aléatoire*/
#include "puissance4.h"	/* modèle de la chasse au trésor en GTK(constantes symboliques, types, déclaration des fonctions)*/
#include "partie.h"

/* Fonction principale */

int main(int argc, char** argv)
{
	ctr_s* ctr;
	int statut_succes;
	FILE* adt;
	/** Allocation memoire **/
	/* Controlleur */
	if( (ctr = malloc(6*sizeof(gtk*)+6*sizeof(s_partie*)+12*sizeof(joueur_s*))) == NULL)
	{
		perror("Memoire ctr non alloué");
		exit (-1);
	}
	/* Partie */
	if( (PARTIE = (s_partie*)malloc(2*sizeof(s_partie))) == NULL)
	{
		perror("Memoire P4 non alloué");
		exit (-1);
	}
	
	/* Environnement GTK */
	if( (ENV = (gtk*)malloc(5*sizeof(gtk))) == NULL)
	{
		perror("Memoire ENV non alloué");
		exit (-1);
	}
	/* Joueurs */
	if( (JOUEUR_1 = (joueur_s*)malloc(5*sizeof(joueur_s))) == NULL)
	{
		perror("Memoire Joueur1 non alloué");
		exit (-1);
	}
	if( (JOUEUR_2 = (joueur_s*)malloc(5*sizeof(joueur_s))) == NULL)
	{
		perror("Memoire Joueur2 non alloué");
		exit (-1);
	}
	/* Si le fichier a ete supprime on en cree un nouveau */
	if((adt = fopen("users.dat", "r")) == NULL)
	{
		perror("Fichier unsers.dat inexistant");
		if((adt = fopen("users.dat", "w")) == NULL)
		{
			perror("Creation du fichier users.dat impossible");
			exit (-1);
		}
	}
	fclose(adt);
	gtk_init(&argc, &argv);
	/* Construction de l'environnement GTK */
	construire(ctr);
	/* Creation de la partie */
	PARTIE = partie_new(NB_COL_JEU_DEFAULT, NB_ROW_JEU_DEFAULT, NB_WIN_JEU_DEFAULT, &statut_succes);
	if (PARTIE == NULL)
		printf("puissance4_jeu :: Une erreur s'est produite pendant l'appel à la fonction 'partie_new' statut (%d) '%s' ; obligation d'abréger le programme.\n", statut_succes, partie_get_statut_nom(statut_succes));
	
	
	/* nouvelle partie */
	partie_nouvelle_partie(PARTIE);
	
	/* DEMARRAGE DE LA BOUCLE*/
	gtk_main();
	
	/* Sauvegarde du score a la sortie du programme */
	sauvegarder_score(ENV->Fenetre, ctr);
	
	return EXIT_SUCCESS;
}
