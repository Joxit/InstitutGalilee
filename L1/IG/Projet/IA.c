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
# include <time.h>	
# include "puissance4.h"	/* modèle de la chasse au trésor en GTK(constantes symboliques, types, déclaration des fonctions)*/
# include "partie.h"

/* _____________________
 *   sous-routines de 'partie_jouer_coup' */

/* Renvoie 1 si le joueur Case_Joueur_joueur détient > (partie->dim.nb_win)-2 cases successives sur la ligne
 * et si les cases aux extremitees de la ligne en dessous sont vides, 0 sinon
 *   Pré-conditions :
 *       - partie instanciée (=> dont le tableau partie->plateau) et en cours
 *       - la case de coordonnées (i,j) vient d'être jouée par le vrai joueur
 *           (et l'état de cette case vaut la valeur correspondant à ce joueur) */
int IA_tester_ligne(s_partie* partie, int i, int j, e_etat_case Case_Joueur)
{
	int ind_col, nb_coup_joueur = 1,  ind_col2, ind_col3;
	
	#if (PUISSANCE4_MODELE_DEBUG != 0)
	printf("%s : IA_tester_ligne IN i == %d j == %d Joueur %d\n", PUISSANCE4_MODELE_TRACE, i, j, Case_Joueur);
	#endif
	
	/* cases détenues par le joueur dont c'est le tour à gauche de '(i,j)'    */
	for (ind_col = j -1 ; ind_col >= 0 && nb_coup_joueur < ( dim_get_nbwin(&(partie->dim)) - 1 ) ; ind_col --)
		if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i, ind_col)]) == Case_Joueur)
			nb_coup_joueur ++;
		else
			break;
		ind_col2 = ind_col;
		
			
		/* cases détenues par le joueur dont c'est le tour à droite de '(i,j)'    */
		for (ind_col = j +1 ; ind_col < dim_get_nbcol(&(partie->dim)) && nb_coup_joueur < ( dim_get_nbwin(&(partie->dim)) - 1 ) ; ind_col ++)
			if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i, ind_col)]) == Case_Joueur)
				nb_coup_joueur ++;
			else
				break;
		ind_col3 = ind_col;
			
			#if (PUISSANCE4_MODELE_DEBUG != 0)
				printf("%s : IA_tester_ligne OUT nb_coup_joueur == %d\n", PUISSANCE4_MODELE_TRACE, nb_coup_joueur);
			#endif
				
				
		/* Si les cases aux extremitees ne sont pas prises on pas besoin de regarder */
		if(i + 1 < dim_get_nbrow(&(partie->dim)) && ind_col2 >= 0 && ind_col3 < dim_get_nbcol(&(partie->dim)))
			if(case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i+1, ind_col2)]) == CASE_ETAT_JOUEUR_NONE
			&& case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i+1, ind_col3)]) == CASE_ETAT_JOUEUR_NONE)
				nb_coup_joueur = 0;
				
				
				/* on retourne le resultat  */
				return (nb_coup_joueur >= dim_get_nbwin(&(partie->dim))-2 ? 1 : 0);
}

/* Renvoie 1 si le joueur Case_Joueur détient (partie->dim.nb_win)-1 cases successives sur la colonne j, 0 sinon
 *   Pré-conditions :
 *       - partie instanciée (=> dont le tableau partie->plateau) et en cours
 *       - la case de coordonnées (i,j) vient d'être jouée par le vrai joueur
 *           (et l'état de cette case vaut la valeur correspondant à ce joueur) */
int IA_tester_colonne(s_partie* partie, int i, int j, e_etat_case Case_Joueur)
{
	int ind_row, nb_coup_joueur = 1;
	
	#if (PUISSANCE4_MODELE_DEBUG != 0)
	printf("%s : IA_tester_colonne IN j == %d Joueur %d\n", PUISSANCE4_MODELE_TRACE, j, Case_Joueur);
	#endif
	
	/* cases détenues par le joueur dont c'est le tour en-dessous de '(i,j)'    */
	for (ind_row = i +1 ; ind_row < dim_get_nbrow(&(partie->dim)) && nb_coup_joueur < dim_get_nbwin(&(partie->dim))-1 ; ind_row ++)
		if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), ind_row, j)]) == Case_Joueur)
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
 * Renvoie la colonne que l'IA peut jouer sur une ligne, 
 * La fonction verifie si il y a des pions en dessous des extremitees pour jouer 
 *  Pré-conditions :
 *       - partie instanciée (=> dont le tableau partie->plateau) et en cours
 *       - la case de coordonnées (i,j) existe */
int IA_jouer_ligne(s_partie* partie, int i, int j, int jouer_colonne, e_etat_case Case_Joueur)
{
	int colonne = j;
	#if (PUISSANCE4_MODELE_DEBUG != 0)
	printf("%s : IA_jouer_ligne IN i == %d j == %d jouer_colonne == %d Joueur %d\n", PUISSANCE4_MODELE_TRACE, i, j, jouer_colonne, Case_Joueur);
	#endif
	
	/* Il regarde si la case de droite de la chaine existe, si elle est libre et s'il y a une case prise en dessous  */
	if(j < dim_get_nbcol(&partie->dim))
		for(colonne = j+1; colonne < dim_get_nbcol(&partie->dim) ; colonne ++ )
			if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i, colonne)]) != Case_Joueur)
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
			/* Il regarde si la case de gauche de la chaine existe, si elle est libre et s'il y a une case prise en dessous  */
			if( j > 0 )
				for(colonne = j-1; colonne >= 0; colonne--)
					if (case_get_etat(partie->plateau[GET_INDICE(dim_get_nbcol(&(partie->dim)), i, colonne)]) != Case_Joueur)
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
 *  Gere tout le jeu de l'IA en plusieurs etapes:
 * 	- Verification si il n'a pas une colonne de 3 pions sur tout le plateau,
 *	     si oui il joue
 * 	- Verification si l'autre joueur n'a pas une colonne de 3 pions sur 
 * 	     la colonne qui vient d'etre joué, si oui il joue pour le bloquer
 * 	- Verification si l'autre joueur n'a pas une ligne de 2 pions sur 
 * 	     la ligne qui vient d'etre joué, si oui il joue pour le bloquer et
 *	     evite les 3 pions en ligne imparables
 * 	- Verification si il n'a pas une ligne de 2 pions sur tout le plateau, 
 * 	     si oui il joue pour en avoir 3 s'il peut
 * 	- Si toutes ses verifications ne sont pas vraies il joue aleatoirement */
void IA_jouer(ctr_s* ctr, int i, int j)
{
	
	int jouer_colonne = -1, ind_col, ind_row;
	#if (PUISSANCE4_MODELE_DEBUG != 0)
	printf("\n\tIA_jouer IN:: i == %d j== %d\n",i,j);
	#endif
	
	/* on regarde au debut si on peut gagner */
	if(jouer_colonne < 0)
	{
		for(ind_row = dim_get_nbrow(&(PARTIE->dim)) - 1; ind_row >= 0 ; ind_row--)
			for(ind_col = 0; ind_col < dim_get_nbcol(&(PARTIE->dim)); ind_col++)
				if (case_get_etat(PARTIE->plateau[GET_INDICE(dim_get_nbcol(&(PARTIE->dim)), ind_row, ind_col)]) == CASE_ETAT_JOUEUR_2)
					if (IA_tester_colonne(PARTIE, ind_row, ind_col, CASE_ETAT_JOUEUR_2))
					{
						jouer_colonne = ind_col;
						break;
					}
	}	
	
	#if (PUISSANCE4_MODELE_DEBUG != 0)
			printf("\tIA_tester_colonne Joueur %d jouer_colonne == %d\n", CASE_ETAT_JOUEUR_2, jouer_colonne); 
	#endif
	
	/* Premier test : sur la colonne, si vrai il verifie si la case du dessus est libre pour jouer */
	if(IA_tester_colonne(PARTIE, i, j, CASE_ETAT_JOUEUR_1) && (i > 0) && jouer_colonne < 0)
	{
		if (case_get_etat(PARTIE->plateau[GET_INDICE(dim_get_nbcol(&(PARTIE->dim)), i-1, j)]) == CASE_ETAT_JOUEUR_NONE)
				jouer_colonne = j;
		#if (PUISSANCE4_MODELE_DEBUG != 0)
			printf("\tIA_tester_colonne Joueur %d jouer_colonne == %d\n", CASE_ETAT_JOUEUR_1, jouer_colonne); 
		#endif
	}
	else
		/* Deuxieme test : sur la ligne, si vrai, il regarde si la case de droite de la chaine est libre, si elle ne sort pas du plateau, et s'il y a une case prise en dessous  */
		if (IA_tester_ligne(PARTIE, i, j, CASE_ETAT_JOUEUR_1) && jouer_colonne < 0)
			jouer_colonne = IA_jouer_ligne(PARTIE, i, j, jouer_colonne, CASE_ETAT_JOUEUR_1);
		
		/* sinon on joue au hasard */
		if(jouer_colonne < 0)
		{
			jouer_colonne = -1;
			for(ind_row = dim_get_nbrow(&(PARTIE->dim)) - 1; ind_row >= 0 ; ind_row--)
				for(ind_col = 0; ind_col < dim_get_nbcol(&(PARTIE->dim)); ind_col++)
					if (case_get_etat(PARTIE->plateau[GET_INDICE(dim_get_nbcol(&(PARTIE->dim)), ind_row, ind_col)]) == CASE_ETAT_JOUEUR_1)
						if (IA_tester_ligne(PARTIE, ind_row, ind_col, CASE_ETAT_JOUEUR_1))
						{
							jouer_colonne = IA_jouer_ligne(PARTIE, ind_row, ind_col, jouer_colonne, CASE_ETAT_JOUEUR_1);
							break;
						}
						
						#if (PUISSANCE4_MODELE_DEBUG != 0)
						printf("\tIA_jouer_ligne final Joueur %d jouer_colonne == %d\n", CASE_ETAT_JOUEUR_1, jouer_colonne); 
					#endif
					
			if(jouer_colonne < 0)
			{
				for(ind_row = dim_get_nbrow(&(PARTIE->dim)) - 1; ind_row >= 0 ; ind_row--)
					for(ind_col = 0; ind_col < dim_get_nbcol(&(PARTIE->dim)); ind_col++)
						if (case_get_etat(PARTIE->plateau[GET_INDICE(dim_get_nbcol(&(PARTIE->dim)), ind_row, ind_col)]) == CASE_ETAT_JOUEUR_2)
							if (IA_tester_ligne(PARTIE, ind_row, ind_col, CASE_ETAT_JOUEUR_2))
							{
								jouer_colonne = IA_jouer_ligne(PARTIE, ind_row, ind_col, jouer_colonne, CASE_ETAT_JOUEUR_2);
								break;
							}
				#if (PUISSANCE4_MODELE_DEBUG != 0)
					printf("\tIA_jouer_ligne final Joueur %d jouer_colonne == %d\n", CASE_ETAT_JOUEUR_2, jouer_colonne); 
				#endif	
				if(jouer_colonne < 0)
				{
					jouer_colonne = rand()% dim_get_nbcol(&(PARTIE->dim));
					#if (PUISSANCE4_MODELE_DEBUG != 0)
					printf("\tIA_random colonne == %d jouer_colonne == %d\n", colonne, jouer_colonne); 
					#endif
				}
				
			}
			
		}
		/* On donne la main a l'IA */
		partie_tour_suivant(PARTIE);
		
		/* on verifie si la colonne est pleine et si on ne sort pas du plateau, s'ellel'est l'IA peut pas jouer ici */
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
		puts("\n\tTour du joueur");
		#endif
}