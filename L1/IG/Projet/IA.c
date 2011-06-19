/* _____________________________________________________________________________
 *	Jeu Puissance 4 :: fichier déclarations de l'IA
 *			Basé sur les fonctions de partie.c
 *
 *	Mardi 17 Mai 2011
 *	
 *	Pour plus de détails, consulter les fichier d'entête
 * _____________________________________________________________________________ */
# include <stdlib.h>		/* fonction 'rand' de génération aléatoire*/
# include <gtk/gtk.h>
#include <string.h>
# include <time.h>	
# include "gtk_puissance4.h"	/* modèle de la chasse au trésor en GTK(constantes symboliques, types, déclaration des fonctions)*/
# include "partie.h"

/* _____________________
 *   sous-routines de 'partie_jouer_coup' */

/* Renvoie 1 si le joueur partie->tour_joueur détient (partie->dim.nb_win)-1 cases successives sur la ligne i, 0 sinon
 *   Pré-conditions :
 *       - partie instanciée (=> dont le tableau partie->plateau) et en cours
 *       - la case de coordonnées (i,j) vient d'être jouée par le vrai joueur
 *           (et l'état de cette case vaut la valeur correspondant à ce joueur) */
int IA_tester_ligne(s_partie* partie, int i, int j)
{
	int ind_col, nb_coup_joueur = 1,  ind_col2, ind_col3;
	
	#if (PUISSANCE4_MODELE_DEBUG != 0)
	printf("%s : IA_tester_ligne IN partie == %p i == %d j == %d\n", PUISSANCE4_MODELE_TRACE, (void*)partie, i, j);
	#endif
	
	/* cases détenues par le joueur dont c'est le tour à gauche de '(i,j)'    */
	for (ind_col = j -1 ; ind_col >= 0 && nb_coup_joueur < ( dim_get_nbwin(&(partie->dim)) - 1 ) ; ind_col --)
		if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i, ind_col)]) == partie->tour_joueur)
			nb_coup_joueur ++;
		else
			break;
		ind_col2 = ind_col;
		
			
		/* cases détenues par le joueur dont c'est le tour à droite de '(i,j)'    */
		for (ind_col = j +1 ; ind_col < dim_get_nbcol(&(partie->dim)) && nb_coup_joueur < ( dim_get_nbwin(&(partie->dim)) - 1 ) ; ind_col ++)
			if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i, ind_col)]) == partie->tour_joueur)
				nb_coup_joueur ++;
			else
				break;
		ind_col3 = ind_col;
			
			#if (PUISSANCE4_MODELE_DEBUG != 0)
				printf("%s : IA_tester_ligne OUT nb_coup_joueur == %d\n", PUISSANCE4_MODELE_TRACE, nb_coup_joueur);
			#endif
				
				
				
		if(i + 1 < dim_get_nbrow(&(partie->dim)) && ind_col2 >= 0 && ind_col3 < dim_get_nbcol(&(partie->dim)))
			if(case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i+1, ind_col2)]) == CASE_ETAT_JOUEUR_NONE
			&& case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i+1, ind_col3)]) == CASE_ETAT_JOUEUR_NONE)
				nb_coup_joueur = 0;
				
				
				/* on retourne le resultat  */
				return (nb_coup_joueur == dim_get_nbwin(&(partie->dim))-1 ? 1 : 0);
}

/* Renvoie 1 si le joueur partie->tour_joueur détient (partie->dim.nb_win)-1 cases successives sur la colonne j, 0 sinon
 *   Pré-conditions :
 *       - partie instanciée (=> dont le tableau partie->plateau) et en cours
 *       - la case de coordonnées (i,j) vient d'être jouée par le vrai joueur
 *           (et l'état de cette case vaut la valeur correspondant à ce joueur) */
int IA_tester_colonne(s_partie* partie, int i, int j)
{
	int ind_row, nb_coup_joueur = 1;
	
	#if (PUISSANCE4_MODELE_DEBUG != 0)
	printf("%s : IA_tester_colonne IN partie == %p j == %d\n", PUISSANCE4_MODELE_TRACE, (void*)partie, j);
	#endif
	
	/* cases détenues par le joueur dont c'est le tour en-dessous de '(i,j)'    */
	for (ind_row = i +1 ; ind_row < dim_get_nbrow(&(partie->dim)) && nb_coup_joueur < dim_get_nbwin(&(partie->dim))-1 ; ind_row ++)
		if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), ind_row, j)]) == partie->tour_joueur)
			nb_coup_joueur ++;
		else
			break;
		
		#if (PUISSANCE4_MODELE_DEBUG != 0)
			printf("%s : IA_tester_colonne OUT nb_coup_joueur == %d\n", PUISSANCE4_MODELE_TRACE, nb_coup_joueur);
			#endif
			
			/* on retourne le resultat  */
			return (nb_coup_joueur == dim_get_nbwin(&(partie->dim))-1 ? 1 : 0);
}

/* Prend en argument la partie, la ligne et la colonne teste et la variable jouer_colonne
 * Renvoie la colonne qu'il faut jouer, si la ligne testé n'est pas prete de gagner, elle renvoie jouer_colonne de depart
 *   Pré-conditions :
 *       - partie instanciée (=> dont le tableau partie->plateau) et en cours
 *       - la case de coordonnées (i,j) existe */
int IA_jouer_ligne(s_partie* partie, int i, int j, int jouer_colonne)
{
	int colonne = j;
	#if (PUISSANCE4_MODELE_DEBUG != 0)
	printf("%s : IA_jouer_ligne IN partie == %p i == %d j == %d jouer_colonne == %d\n", PUISSANCE4_MODELE_TRACE, (void*)partie, i, j, jouer_colonne);
	#endif
	if(j < dim_get_nbcol(&partie->dim))
		for(colonne = j+1; colonne < dim_get_nbcol(&partie->dim) ; colonne ++ )
			if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i, colonne)]) != CASE_ETAT_JOUEUR_1)
			{
				if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i, colonne)]) == CASE_ETAT_JOUEUR_NONE)
				{
					if(i + 1 < dim_get_nbrow(&(partie->dim)))
					{
						/* si la case du dessous est prise on joue pour empecher le joueur de jouer, sinon ca ne sert a rien de jouer la et on joue au hasard */
						if(case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i+1, colonne)]) != CASE_ETAT_JOUEUR_NONE)
							jouer_colonne = colonne;
					}
					else
						/* si on est a la premiere ligne du plateau, pas besoin de s'inquieter et on joue */
						if( i == 5)
							jouer_colonne = colonne;
						break;
				}
				else
					break;
			}
			#if (PUISSANCE4_MODELE_DEBUG != 0)
			printf("\tIA_tester_ligne 1 colonne == %d jouer_colonne == %d\n", colonne, jouer_colonne); 
			#endif
			/* Il regarde si la case de gauche de la chaine existe et si elle est libre et s'il y a une case prise en dessous  */
			if( j > 0 )
				for(colonne = j-1; colonne >= 0; colonne--)
					if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i, colonne)]) != CASE_ETAT_JOUEUR_1)
					{
						if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i, colonne)]) == CASE_ETAT_JOUEUR_NONE)
						{
							if(i + 1 < dim_get_nbrow(&(partie->dim)))
							{
								/* si la case du dessous est prise on joue pour empecher le joueur de jouer, sinon ca ne sert a rien de jouer la et on joue au hasard */
								if(case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i+1, colonne)]) != CASE_ETAT_JOUEUR_NONE)
									jouer_colonne = colonne;
							}
							else
								/* si on est a la premiere ligne du plateau, pas besoin de s'inquieter et on joue */
								if( i == 5)
									jouer_colonne = colonne;
								
								break;
						}
						else
							break;
					}
					#if (PUISSANCE4_MODELE_DEBUG != 0)
					printf("\tIA_tester_ligne 2 colonne == %d jouer_colonne == %d\n", colonne, jouer_colonne); 
					#endif
					#if (PUISSANCE4_MODELE_DEBUG != 0)
					printf("%s : IA_jouer_ligne OUT jouer_colonne == %d\n", PUISSANCE4_MODELE_TRACE, jouer_colonne);
					#endif
					return jouer_colonne;
}


/*  Fonction de l'IA 
 *   Pré-conditions :
 *       - partie instanciée (=> dont le tableau partie->plateau) et en cours
 *       - la case de coordonnées (i,j) vient d'être jouée par le vrai joueur
 *           (et l'état de cette case vaut la valeur correspondant à ce joueur) 
 *   Teste si le prochain coup que va jouer le joueur est un coup final ou non
 *  Si ca l'est l'IA joue a sa place, sinon il joue au hasard
 */
void IA_jouer(ctr_s* ctr, int i, int j)
{
	
	int jouer_colonne = -1, colonne = j, ind_col, ind_row;
	#if (PUISSANCE4_MODELE_DEBUG != 0)
		printf("\n\tIA_jouer IN:: i == %d j== %d\n",i,j);
	#endif
	/* Premier test : sur la colonne, si vrai il verifie si la case du dessus est libre pour jouer */
	if(IA_tester_colonne(PARTIE, i, j) && (i > 0))
	{
		if (case_get_etat(PARTIE->plateau[GET_INDICE(dim_get_nbcol(&(PARTIE->dim)), i-1, j)]) == CASE_ETAT_JOUEUR_NONE)
				jouer_colonne = j;
		#if (PUISSANCE4_MODELE_DEBUG != 0)
			printf("\tIA_tester_colonne colonne == %d jouer_colonne == %d\n", colonne, jouer_colonne); 
		#endif
	}
	else
		/* Deuxieme test : sur la ligne, si vrai, il regarde si la case de droite de la chaine est libre, si elle ne sort pas du plateau, et s'il y a une case prise en dessous  */
		if (IA_tester_ligne(PARTIE, i, j))
			jouer_colonne = IA_jouer_ligne(PARTIE, i, j, jouer_colonne);
		
		/* sinon on joue au hasard */
		if(jouer_colonne == -1)
		{
			jouer_colonne = -1;
			for(ind_row = dim_get_nbrow(&(PARTIE->dim)) - 1; ind_row >= 0 ; ind_row--)
				for(ind_col = 0; ind_col < dim_get_nbcol(&(PARTIE->dim)); ind_col++)
					if (case_get_etat(PARTIE->plateau[GET_INDICE(dim_get_nbcol(&(PARTIE->dim)), ind_row, ind_col)]) == CASE_ETAT_JOUEUR_1)
						if (IA_tester_ligne(PARTIE, ind_row, ind_col))
						{
							jouer_colonne = IA_jouer_ligne(PARTIE, ind_row, ind_col, jouer_colonne);
							break;
						}
					
			#if (PUISSANCE4_MODELE_DEBUG != 0)
			printf("\tIA_jouer_ligne final jouer_colonne == %d\n", jouer_colonne); 
			#endif
			if(jouer_colonne == -1)
			{
				jouer_colonne = rand()% dim_get_nbcol(&(PARTIE->dim));
				#if (PUISSANCE4_MODELE_DEBUG != 0)
					printf("\tIA_random colonne == %d jouer_colonne == %d\n", colonne, jouer_colonne); 
				#endif
			}
		}
		/* On donne la main a l'IA */
		partie_tour_suivant(PARTIE);
		
		/* on verifie si le bouton est sensible et si on ne sort pas du plateau, s'il ne l'est pas l'IA peut pas jouer ici */
		if(partie_est_colonne_pleine(PARTIE, jouer_colonne) == FALSE
		&& jouer_colonne < NB_COL_JEU_DEFAULT && jouer_colonne >= 0)
		{
			#if (PUISSANCE4_MODELE_DEBUG != 0)
			printf("\tIA_jouer OUT :: colonne == %d jouer_colonne == %d\n", colonne, jouer_colonne); 
			#endif
			gtk_jouer_colonne( ENV->Bouton[jouer_colonne], ctr);
		}
		
		else
		{
			/* sinon on va chercher un autre nombre aleatoire */
			jouer_colonne = 0;
			while(partie_est_colonne_pleine(PARTIE, jouer_colonne) == TRUE
				|| jouer_colonne > NB_COL_JEU_DEFAULT || jouer_colonne < 0)
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
		puts("\tTour du joueur");
		#endif
}