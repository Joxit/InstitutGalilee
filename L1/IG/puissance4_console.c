/*
	Puissance4 :: jeu mode console
*/

#include <stdio.h>      /* pour printf          */

#include "partie.h"

/* __________________________
 *    fonctions d'E/S */

/* ____ affichage structure */

/* affichage (console) état case
 *    Pré-condition : une_case != NULL    */
void case_print_etat(s_case* une_case);

/* affichage (console) plateau partie
 *    Pré-condition : partie != NULL    */
void partie_print_etat(s_partie* partie);

/* ____ saisies utilisateur */

/* fonction de vidage du buffer */
void purger();

/* __________________________
 *    programme de jeu */

int main()
{
    int statut_succes = 0, j;
    char c = 'O';
    s_partie* partie = NULL;

    /* ____ construction modèle	*/

    /* modèle :: initialisation du plateau de jeu (coordonnées des cases) */
    /*	partie = partie_new(NB_COL_JEU_DEFAULT, NB_ROW_JEU_DEFAULT, NB_WIN_JEU_DEFAULT, &statut_succes);    */
    partie = partie_new(NB_COL_JEU_DEFAULT, NB_ROW_JEU_DEFAULT, NB_WIN_JEU_DEFAULT, &statut_succes);
    if (partie == NULL)
	printf("puissance4_jeu :: Une erreur s'est produite pendant l'appel à la fonction 'partie_new' statut (%d) '%s' ; obligation d'abréger le programme.\n", statut_succes, partie_get_statut_nom(statut_succes));
    else
    {
	/* ____ lancement du jeu	*/
	while(c == 'O')
	{
	    printf("Nouvelle partie [O pour Oui, toute autre saisie pour Non] ?\t");
	scanf("%c", &c);
	purger();

	if (c == 'O')
	{
	    /* nouvelle partie */
	    partie_nouvelle_partie(partie);

	    while(partie_get_etat(partie) == PARTIE_ETAT_ENCOURS)
	    {
		/* nouveau tour */
		partie_print_etat(partie);

		/* choisir coup */
		j = 0;
		while(j -1 < 0 || j -1 >= partie_get_nbcol(partie) || partie_est_colonne_pleine(partie, j -1) == 1)
		{
		    printf("Saisir colonne parmi : ");
		    for (j = 1 ; j <= partie_get_nbcol(partie) ; j++)
			if (partie_est_colonne_pleine(partie, j -1) == 0)
			    printf("%d ", j);

			printf("\t");
		    scanf("%d", &j);
		    purger();
		}

		/* jouer le coup */
		partie_jouer_colonne(partie, j -1);

		/* tour suivant */
		if (partie_get_etat(partie) == PARTIE_ETAT_ENCOURS)
		    partie_tour_suivant(partie);
	    }

	    /* partie finie */
	    partie_print_etat(partie);
	}
	}

	/* libération partie */
	partie_free(& partie);
    }

    /* on s'en va	*/
    return statut_succes;
}

/* __________________________
 *    fonctions d'E/S */

/* ____ affichage structure */

/* affichage (console) état case
 *    Pré-condition : une_case != NULL    */
void case_print_etat(s_case* une_case)
{
    if (une_case->etat == CASE_ETAT_JOUEUR_1)
	printf("%s", STR_CASE_JOUEUR_1);
    else if (une_case->etat == CASE_ETAT_JOUEUR_2)
	printf("%s", STR_CASE_JOUEUR_2);
    else
	printf("%s", " ");
}

/* affichage (console) partie
 *    Pré-condition : partie != NULL, partie->etat correct à valeur dans PARTIE_ETAT_NONE ,..., PARTIE_ETAT_JOUEUR_12    */
void partie_print_etat(s_partie* partie)
{
    int i, j;

    /* ____ infos état partie */
    if (partie->etat != PARTIE_ETAT_ENCOURS)
	printf("%s\n", partie_get_etat_nom(partie->etat));
    else if (partie->tour_joueur == CASE_ETAT_JOUEUR_1)
	printf("Tour du joueur 1\n");
    else
	printf("Tour du joueur 2\n");

    /* ____ plateau */
    if (partie->etat != PARTIE_ETAT_NONE)
    {
	/* indice colonne (en partant de 1 : plus naturel pour l'utilisateur) */
	for (j = 0 ; j < partie_get_nbcol(partie) ; j ++)
	    printf("%d ", j +1);

	printf("\n");

	/* séparateur */
	printf("_");
	for (j = 0 ; j < partie_get_nbcol(partie) ; j ++)
	    printf("__");

	printf("\n");

	/* état des cases du plateau */
	for (i = 0 ; i < partie_get_nbrow(partie) ; i ++)
	{
	    for (j = 0 ; j <partie_get_nbcol(partie) ; j ++)
	    {
		case_print_etat(partie->plateau[GET_INDICE(partie_get_nbcol(partie), i, j)]);
		printf(" ");
	    }

	    printf("\n");
	}
    }

    printf("\n");
}

/* ____ saisies utilisateur */

/* fonction de vidage du buffer */
void purger ()
{
    char c;

    while ((c = getchar()) != '\n' && c != EOF)
    {}
}
