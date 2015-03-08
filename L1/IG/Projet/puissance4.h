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
 *  Jeu Puissance 4 :: fichier déclarations                                    *
 *                                                                             *
 *  Mardi 17 Mai 2011.                                                         *
 *                                                                             *
 *  Pour plus de détails, consulter les fichier d'entete                       *
 * ___________________________________________________________________________ */
#include "partie.h"
# ifndef PUISSANCE4_H

/* Declaration des constantes et types utilisateurs */
#define PUISSANCE4_H
/* Constantes symboliques pour passer directement aux structures voulues */
#define ENV ctr->env
#define PARTIE ctr->partie
#define JOUEUR_1 ctr->Joueur1
#define JOUEUR_2 ctr->Joueur2
/* Constantes symboliques pour l'emplacement des images */
#define ROUGE "img/rouge.gif"
#define JAUNE "img/jaune.gif"
#define BLEU "img/bleu.gif"

/* Structure de l'environement GTK+ */
typedef struct gtk_s 
{
	/* WIDGETS POUR LA FENETRE PRINCIPALE!!!! */
	/*Widgets pour la fenetre */
	GtkWidget* Fenetre;		/* Fenetre principale*/
	/* Disposition du tableau[NB_ROW_JEU_DEFAULT + 1][NB_COL_JEU_DEFAULT]: 
	 * sur la premiere ligne il contient le Label
	 * 1*0 a NB_ROW_JEU_DEFAULT+1*NB_COL_JEU_DEFAULT le tableau contient les images du jeu
	 * sur la ligne NB_ROW_JEU_DEFAULT + 1 il contient les boutons */
	GtkWidget* Tableau;
	GtkWidget* vBox;
	/* Label du tour joueur */	
	GtkWidget* Label;
	
	/* Widgets pour les bouttons*/
	GtkWidget* Bouton[NB_COL_JEU_DEFAULT];		 /* Bouttons pour jouer une colonne */
	GtkWidget* Image[NB_COL_JEU_DEFAULT][NB_ROW_JEU_DEFAULT];	/* 	Images des Cases */
	
	/* WIDGETS POUR LE MENU */
	GtkWidget* BarMenu;
	GtkWidget* MenuPartie;
	GtkWidget* Partie;
	GtkWidget* New;
	GtkWidget* Liste;
	GtkWidget* Score;
	GtkWidget* Save;
	GtkWidget* Quitter;
	GtkWidget* MenuOption;
	GtkWidget* Option;
	GtkWidget* ChangerNom;
	GtkWidget* JouerIA;
	GtkWidget* MenuHelp;
	GtkWidget* Help;
	GtkWidget* About;
	
	/* WIDGETS POUR LES FENETRES MENU */
	GtkWidget* Menu;				/* Fenetre pour les menus */
	GtkWidget* MenuhBox[2];
	GtkWidget* MenuvBox;
	GtkWidget* MenuEntry[2];		/* Zone de saisie pour les nouveaux noms des joueurs */
	GtkWidget* MenuLabel[3];		/* Labels utilises pour les menus */
	
	
	/* WIDGETS DE LES FENETRES DE DIALOGUE */
	GtkWidget* Dialog;			/* boite de dialogue*/
	GtkWidget* Question;			/* Question pour continuer une nouvelle partie ou confirmation de fermeture */
	GtkWidget* dBox;
	GtkWidget* dBout[2];			/* Boutons de choix (Ok, Oui, Non, Sortir ) */
	guint reponse;					/* Reception si l'utilisateur clique sur un bouton */
}
	gtk;


typedef struct joueur_s
{
	/* Taille maximal d'un pseudo est de 20 characters */
	char nom[21];
	/* Score du joueur actuel */
	int score;
	
}
	joueur_s;

typedef struct controlleur_s
{
	struct gtk_s* env;
	struct S_PARTIE* partie;
	struct joueur_s* Joueur1;
	struct joueur_s* Joueur2;
	int IA;
}
	ctr_s;


/** Fonctions definies dans gtk_puissance4.c **/
/* Construction de l'environement du jeu */
void construire(ctr_s* ctr);
/* Action des boutons pour jouer sur une colonne */
void gtk_jouer_colonne(GtkWidget* button, ctr_s *ctr);
/* Fin de jeu, demande aux joueurs s'ils continuent */
void continuer(ctr_s *ctr); 
/* Reinitialisation de la partie */
void reinit(ctr_s* ctr);
/* Confirmation aux joueurs s'ils veulent quitter le jeu */
void confirmation(GtkWidget* fenetre, ctr_s* ctr);
/* Action des Widgets pour reactiver la fenetre principale */
void afficher_fenetre();
/* fin de partie on liber la memoire */
void free_gtk(ctr_s *ctr);

void maj_pseudo(ctr_s* ctr);


/** Fonctions definies dans menu.c **/
/* Action lors de la validation du pseudonyme */
void changer_nom(GtkWidget* Item, ctr_s *ctr);
/* Sauvegare les scores des joueurs actifs */
void sauvegarder_score(GtkWidget* Item, ctr_s* ctr);
/* renvoit la chaine de char du classement des joueurs pour Top_5 */
char* get_classement();
/* ouverture et verification du fichier user.dat :
 * Si le fichier n'existe pas il en créé un nouveau
 * Renvoit l'adresse en memoire du fichier*/
FILE* file_open(FILE* adt);

/** Fonctions definies dans gtk_menu.c **/
/* Demande aux utilisateur s'ils veulent créer une nouvelle partie */
void nouvelle_partie(GtkWidget* MenuItem, ctr_s *ctr);
/* Menu Option pour change les noms des joueurs */
void menu_nom(GtkWidget* MenuItem, ctr_s *ctr);
/* Menu Top_5 pour afficher le classement des 5 premiers joueurs */
void Top_5(GtkWidget* MenuItem, ctr_s *ctr);
/* Menu Score pour afficher le score des 2 joueurs */
void get_score(GtkWidget* MenuItem, ctr_s *ctr);
/* Menu pour activer ou desactiver l'IA */
void menu_IA(GtkWidget* MenuItem, ctr_s *ctr);
/* menu A propos */
void menu_about(GtkWidget* Item, ctr_s* ctr);
/* definition de gtk_menu_item_set_label qui est arrivé apres GTK+ 2.16
 * pour compatibilité avec GTK+ 2.10  */
void gtk_menu_item_set_label (GtkMenuItem *menu_item, const gchar *label);

/** Fonctions definies dans IA.c **/

/* Renvoie 1 si le joueur Case_Joueur détient > (partie->dim.nb_win)-2 cases successives sur la ligne
 * et si les cases aux extremitees de la ligne en dessous sont vides, 0 sinon
 *   Pré-conditions :
 *       - partie instanciée (=> dont le tableau partie->plateau) et en cours
 *       - la case de coordonnées (i,j) vient d'être jouée par le vrai joueur
 *           (et l'état de cette case vaut la valeur correspondant à ce joueur) */
int IA_tester_ligne(s_partie* partie, int i, int j, e_etat_case Case_Joueur);

/* Renvoie 1 si le joueur Case_Joueur détient (partie->dim.nb_win)-1 cases successives sur la colonne j, 0 sinon
 *   Pré-conditions :
 *       - partie instanciée (=> dont le tableau partie->plateau) et en cours
 *       - la case de coordonnées (i,j) vient d'être jouée par le vrai joueur
 *           (et l'état de cette case vaut la valeur correspondant à ce joueur) */

int IA_tester_colonne(s_partie* partie, int i, int j, e_etat_case Case_Joueur);
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
void IA_jouer(ctr_s* ctr, int i, int j);

/* renvoit la colonne que l'IA peut jouer sur une ligne
 * La fonction verifie si il y a des pions en dessous des extremitees pour jouer */
int IA_jouer_ligne(s_partie* partie, int i, int j,  int jouer_colonne, e_etat_case Case_Joueur);

#endif

