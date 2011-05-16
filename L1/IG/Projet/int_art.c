
# include <stdlib.h>		/* fonction 'rand' de génération aléatoire*/
# include <gtk/gtk.h>
#include <string.h>
# include <time.h>	
# include "gtk_puissance4.h"	/* modèle de la chasse au trésor en GTK(constantes symboliques, types, déclaration des fonctions)*/
# include "partie.h"

/* _____________________
 *   sous-routines de 'partie_jouer_coup' */

/* Renvoie 1 si le joueur partie->tour_joueur détient partie->dim.nb_win cases successives sur la ligne i, 0 sinon
 *   Pré-conditions :
 *       - partie instanciée (=> dont le tableau partie->plateau) et en cours
 *       - la case de coordonnées (i,j) vient d'être jouée par le joueur partie->tour_joueur
 *           (et l'état de cette case vaut la valeur correspondant à ce joueur) */
int IA_tester_ligne(s_partie* partie, int i, int j)
{
	int ind_col, nb_coup_joueur = 1;
	
	#if (PUISSANCE4_MODELE_DEBUG != 0)
	printf("%s : partie_tester_ligne IN partie == %p i == %d j == %d\n", PUISSANCE4_MODELE_TRACE, (void*)partie, i, j);
	#endif
	
	/* cases détenues par le joueur dont c'est le tour à gauche de '(i,j)'    */
	for (ind_col = j -1 ; ind_col >= 0 && nb_coup_joueur < ( dim_get_nbwin(&(partie->dim)) - 1 ) ; ind_col --)
		if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i, ind_col)]) == partie->tour_joueur)
			nb_coup_joueur ++;
		else
			break;
		
		/* cases détenues par le joueur dont c'est le tour à droite de '(i,j)'    */
		for (ind_col = j +1 ; ind_col < dim_get_nbcol(&(partie->dim)) && nb_coup_joueur < ( dim_get_nbwin(&(partie->dim)) - 1 ) ; ind_col ++)
			if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i, ind_col)]) == partie->tour_joueur)
				nb_coup_joueur ++;
			else
				break;
			
			#if (PUISSANCE4_MODELE_DEBUG != 0)
				printf("%s : partie_tester_ligne OUT nb_coup_joueur == %d\n", PUISSANCE4_MODELE_TRACE, nb_coup_joueur);
				#endif
				
				/* on retourne le resultat  */
				return (nb_coup_joueur == dim_get_nbwin(&(partie->dim))-1 ? 1 : 0);
}

/* Renvoie 1 si le joueur partie->tour_joueur détient partie->dim.nb_win cases successives sur la colonne j, 0 sinon
 *   Pré-conditions :
 *       - partie instanciée (=> dont le tableau partie->plateau) et en cours
 *       - la case de coordonnées (i,j) vient d'être jouée par le joueur partie->tour_joueur
 *           (et l'état de cette case vaut la valeur correspondant à ce joueur) */
int IA_tester_colonne(s_partie* partie, int i, int j)
{
	int ind_row, nb_coup_joueur = 1;
	
	#if (PUISSANCE4_MODELE_DEBUG != 0)
	printf("%s : partie_tester_colonne IN partie == %p j == %d\n", PUISSANCE4_MODELE_TRACE, (void*)partie, j);
	#endif
	
	/* cases détenues par le joueur dont c'est le tour en-dessous de '(i,j)'    */
	for (ind_row = i +1 ; ind_row < dim_get_nbrow(&(partie->dim)) && nb_coup_joueur < dim_get_nbwin(&(partie->dim))-1 ; ind_row ++)
		if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), ind_row, j)]) == partie->tour_joueur)
			nb_coup_joueur ++;
		else
			break;
		
		#if (PUISSANCE4_MODELE_DEBUG != 0)
			printf("%s : partie_tester_colonne OUT nb_coup_joueur == %d\n", PUISSANCE4_MODELE_TRACE, nb_coup_joueur);
			#endif
			
			/* on retourne le resultat  */
			return (nb_coup_joueur == dim_get_nbwin(&(partie->dim))-1 ? 1 : 0);
}

/* Renvoie 1 si le joueur partie->tour_joueur détient partie->dim.nb_win cases successives
 *       sur la diagonale 'NordOuest-SudEst' passant par la case (i, j), 0 sinon
 *   Pré-conditions :
 *       - partie instanciée (=> dont le tableau partie->plateau) et en cours
 *       - la case de coordonnées (i,j) vient d'être jouée par le joueur partie->tour_joueur
 *           (et l'état de cette case vaut la valeur correspondant à ce joueur) */
int IA_tester_diagonale_NO_SE(s_partie* partie, int i, int j)
{
	int ind_row, ind_col, nb_coup_joueur = 1;
	
	#if (PUISSANCE4_MODELE_DEBUG != 0)
	printf("%s : partie_tester_diagonale_NO_SE IN partie == %p i == %d j == %d\n", PUISSANCE4_MODELE_TRACE, (void*)partie, i, j);
	#endif
	/* cases détenues par le joueur dont c'est le tour 'en haut -- à gauche' de '(i,j)'    */
	ind_row = i -1;
	ind_col = j -1;
	while (ind_row >= 0 && ind_col >= 0 && nb_coup_joueur < dim_get_nbwin(&(partie->dim))-1)
	{
		if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), ind_row, ind_col)]) == partie->tour_joueur)
			nb_coup_joueur ++;
		
		ind_row --;
		ind_col --;
	}
	
	/* cases détenues par le joueur dont c'est le tour 'en bas -- à droite' de '(i,j)'    */
	ind_row = i +1;
	ind_col = j +1;
	while (ind_row < dim_get_nbrow(&(partie->dim)) && ind_col < dim_get_nbcol(&(partie->dim)) && nb_coup_joueur < dim_get_nbwin(&(partie->dim))-1)
	{
		if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), ind_row, ind_col)]) == partie->tour_joueur)
			nb_coup_joueur ++;
		
		
		ind_row ++;
		ind_col ++;
	}
	
	#if (PUISSANCE4_MODELE_DEBUG != 0)
	printf("%s : partie_tester_diagonale_NO_SE OUT nb_coup_joueur == %d\n", PUISSANCE4_MODELE_TRACE, nb_coup_joueur);
	#endif
	
	/* on retourne le resultat  */
	return (nb_coup_joueur == dim_get_nbwin(&(partie->dim))-1 ? 1 : 0);
}

/* Renvoie 1 si le joueur partie->tour_joueur détient partie->dim.nb_win cases successives
 *       sur la diagonale 'NordEst-SudOuest'' passant par la case (i, j), 0 sinon
 *   Pré-conditions :
 *       - partie instanciée (=> dont le tableau partie->plateau) et en cours
 *       - la case de coordonnées (i,j) vient d'être jouée par le joueur partie->tour_joueur
 *           (et l'état de cette case vaut la valeur correspondant à ce joueur) */
int IA_tester_diagonale_NE_SO(s_partie* partie, int i, int j)
{
	int ind_row, ind_col, nb_coup_joueur = 1;
	
	#if (PUISSANCE4_MODELE_DEBUG != 0)
	printf("%s : partie_tester_diagonale_NE_SO IN partie == %p i == %d j == %d\n", PUISSANCE4_MODELE_TRACE, (void*)partie, i, j);
	#endif
	/* cases détenues par le joueur dont c'est le tour 'en bas -- à gauche' de '(i,j)'    */
	ind_row = i +1;
	ind_col = j -1;
	while (ind_row < dim_get_nbrow(&(partie->dim)) && ind_col >= 0 && nb_coup_joueur < dim_get_nbwin(&(partie->dim))-1)
	{
		if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), ind_row, ind_col)]) == partie->tour_joueur)
			nb_coup_joueur ++;
		else
			break;
		
		ind_row ++;
		ind_col --;
	}
	
	/* cases détenues par le joueur dont c'est le tour 'en haut -- à droite' de '(i,j)'    */
	ind_row = i -1;
	ind_col = j +1;
	while (ind_row >= 0 && ind_col < dim_get_nbcol(&(partie->dim)) && nb_coup_joueur < dim_get_nbwin(&(partie->dim))-1)
	{
		if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), ind_row, ind_col)]) == partie->tour_joueur)
			nb_coup_joueur ++;
		else
			break;
		
		ind_row --;
		ind_col ++;
	}
	
	#if (PUISSANCE4_MODELE_DEBUG != 0)
	printf("%s : partie_tester_diagonale_NE_SO OUT nb_coup_joueur == %d\n", PUISSANCE4_MODELE_TRACE, nb_coup_joueur);
	#endif
	
	/* on retourne le resultat  */
	return (nb_coup_joueur == dim_get_nbwin(&(partie->dim))-1 ? 1 : 0);
}

void IA_jouer(ctr_s* ctr, int i, int j)
{
	
	int jouer_colonne=j, colonne = j;
	#if (PUISSANCE4_MODELE_DEBUG != 0)
		printf("\n\tIA_jouer IN:: i == %d j== %d\n",i,j);
	#endif
	
	if(IA_tester_colonne(PARTIE, i, j))
	{
		if(i+1 < dim_get_nbrow(&(PARTIE->dim)))
			if (case_get_etat(PARTIE->plateau[GET_INDICE(dim_get_nbcol(&(PARTIE->dim)), i+1, j)]) == CASE_ETAT_JOUEUR_NONE)
				jouer_colonne = j;
		#if (PUISSANCE4_MODELE_DEBUG != 0)
			printf("\tIA_tester_colonne colonne == %d jouer_colonne == %d\n", colonne, jouer_colonne); 
		#endif
	}
	else
		if (IA_tester_ligne(PARTIE, i, j))
		{
			if(j < dim_get_nbcol(&PARTIE->dim))
				for(colonne = j+1; colonne < dim_get_nbcol(&PARTIE->dim) ; colonne ++ )
					if (case_get_etat(PARTIE->plateau[GET_INDICE(dim_get_nbcol(&(PARTIE->dim)), i, colonne)]) == CASE_ETAT_JOUEUR_NONE)
					{
						if(i + 1 < dim_get_nbrow(&(PARTIE->dim)))
						{
							if(case_get_etat(PARTIE->plateau[GET_INDICE(dim_get_nbcol(&(PARTIE->dim)), i+1, colonne)]) != CASE_ETAT_JOUEUR_NONE)
								jouer_colonne = colonne;
							else
								jouer_colonne = rand()% dim_get_nbcol(&(PARTIE->dim));
						}
						else
							if( i == 5)
								jouer_colonne = colonne;
							break;
					}
			#if (PUISSANCE4_MODELE_DEBUG != 0)
				printf("\tIA_tester_ligne 1 colonne == %d jouer_colonne == %d\n", colonne, jouer_colonne); 
			#endif
					if( j > 0 )
						for(colonne = j-1; colonne >= 0; colonne--)
							if (case_get_etat(PARTIE->plateau[GET_INDICE(dim_get_nbcol(&(PARTIE->dim)), i, colonne)]) == CASE_ETAT_JOUEUR_NONE)
							{
								if(i + 1 < dim_get_nbrow(&(PARTIE->dim)))
								{
									if(case_get_etat(PARTIE->plateau[GET_INDICE(dim_get_nbcol(&(PARTIE->dim)), i+1, colonne)]) != CASE_ETAT_JOUEUR_NONE)
										jouer_colonne = colonne;
									else
										jouer_colonne = rand()% dim_get_nbcol(&(PARTIE->dim));
								}
								else
									if( i == 5)
										jouer_colonne = colonne;
									
									break;
							}
					#if (PUISSANCE4_MODELE_DEBUG != 0)
						printf("\tIA_tester_ligne 2 colonne == %d jouer_colonne == %d\n", colonne, jouer_colonne); 
					#endif
		}
		
		
		
		else
		{
			jouer_colonne = rand()% dim_get_nbcol(&(PARTIE->dim));
			#if (PUISSANCE4_MODELE_DEBUG != 0)
			printf("\tIA_random colonne == %d jouer_colonne == %d\n", colonne, jouer_colonne); 
			#endif
		}
		
		partie_tour_suivant(PARTIE);
		
		if(gtk_widget_get_sensitive(ENV->Bouton[jouer_colonne]) == TRUE && colonne < NB_COL_JEU_DEFAULT)
		{
			#if (PUISSANCE4_MODELE_DEBUG != 0)
			printf("\tIA_jouer OUT :: colonne == %d jouer_colonne == %d\n", colonne, jouer_colonne); 
			#endif
			gtk_jouer_colonne( ENV->Bouton[jouer_colonne], ctr);
		}
		else
		{
			jouer_colonne = 0;
			while(gtk_widget_get_sensitive(ENV->Bouton[jouer_colonne]) == FALSE || colonne > NB_COL_JEU_DEFAULT)
			{
				jouer_colonne = rand()% dim_get_nbcol(&(PARTIE->dim));
				
			}
			#if (PUISSANCE4_MODELE_DEBUG != 0)
			printf("\tIA_jouer OUT 2 :: colonne == %d jouer_colonne == %d\n", colonne, jouer_colonne); 
			#endif
			gtk_jouer_colonne( ENV->Bouton[jouer_colonne], ctr);
		}
		
		partie_tour_suivant(PARTIE);
		#if (PUISSANCE4_MODELE_DEBUG != 0)
		puts("Tour du joueur");
		#endif
		
		
}