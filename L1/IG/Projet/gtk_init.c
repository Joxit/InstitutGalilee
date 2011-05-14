/* _____________________________________________________________________________
 J *eu Puissance 4 : Fichier Principal									
 
 Mardi 4 Mai 2011.												
 
 Pour plus de détails, consulter les fichier d'entête						
 _____________________________________________________________________________ */

/* Declaration de fonctionnalites supplementaire */

#include <stdlib.h> /* EXIT_SUCCSS */
#include <stdio.h> /* Printf */	
#include <gtk/gtk.h>	
#include <time.h>		/*fonction 'time', utilisée pour la génération aléatoire*/
#include "gtk_puissance4.h"	/* modèle de la chasse au trésor en GTK(constantes symboliques, types, déclaration des fonctions)*/
#include "partie.h"

/* Fonction principale */

int main(int argc, char** argv)
{
	ctr_s* ctr;
	int statut_succes;
	if( (ctr = malloc(6*sizeof(gtk*)+6*sizeof(s_partie*)+12*sizeof(joueur_s*))) == NULL)
	{
		perror("Memoire ctr non alloué");
		exit (-1);
	}
	if( (PARTIE = (s_partie*)malloc(2*sizeof(s_partie))) == NULL)
	{
		perror("Memoire P4 non alloué");
		exit (-1);
	}
	
	/* initialisation de l'environnement*/
	if( (ENV = (gtk*)malloc(5*sizeof(gtk))) == NULL)
	{
		perror("Memoire ENV non alloué");
		exit (-1);
	}
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
	
	gtk_init(&argc, &argv);
	construire(ctr);
	PARTIE = partie_new(NB_COL_JEU_DEFAULT, NB_ROW_JEU_DEFAULT, NB_WIN_JEU_DEFAULT, &statut_succes);
	if (PARTIE == NULL)
		printf("puissance4_jeu :: Une erreur s'est produite pendant l'appel à la fonction 'partie_new' statut (%d) '%s' ; obligation d'abréger le programme.\n", statut_succes, partie_get_statut_nom(statut_succes));
	
	
	/* nouvelle partie */
	partie_nouvelle_partie(PARTIE);
	
	
	
	
	/* DEMARRAGE DE LA BOUCLE*/
	gtk_main();
	
	
	return EXIT_SUCCESS;
}