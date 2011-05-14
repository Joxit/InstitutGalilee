/* _____________________________________________________________________________
 *	Jeu Puissance 4 :: fichier déclarations									
 *												
 *	Mardi 4 Mai 2011.													
 *																		
 *	Pour plus de détails, consulter les fichier d'entête						
 * _____________________________________________________________________________ */
#include "partie.h"
# ifndef GTK_PUISSANCE4_H

/* Declaration des constantes et types utilisateurs */
#define GTK_PUISSANCE4_H
/* Constantes symboliques pour passer directement aux structures voulues */
#define ENV ctr->env
#define PARTIE ctr->partie
#define JOUEUR_1 ctr->Joueur1
#define JOUEUR_2 ctr->Joueur2
/* Constantes symboliques pour les Boites GTK+ */
#define NB_HBOX NB_COL_JEU_DEFAULT+1
#define NB_VBOX 2
/* Constantes symboliques pour l'emplacement des images */
#define ROUGE "img/rouge.gif"
#define JAUNE "img/jaune.gif"
#define BLEU "img/bleu.gif"

/* Structure de l'environement GTK+*/
typedef struct gtk_s 
{
	/* WIDGETS POUR LA FENETRE PRINCIPALE!!!! */
	/*Widgets pour la fenetre */
	GtkWidget* Fenetre;		/* Fenetre principale*/	
	/* 0 < NB_COL_JEU_DEFAULT : Box pour les cases
	 * NB_COL_JEU_DEFAULT : Box pour les boutons 
	 * NB_COL_JEU_DEFAULT+1 : Box du label */	
	GtkWidget* hBox[NB_HBOX];	
	/* 0 : vBox de la fenetre 
	 * 1 : inutilise*/
	GtkWidget* vBox[NB_VBOX];
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
	GtkWidget* Option;
	GtkWidget* Liste;
	GtkWidget* Score;
	GtkWidget* Save;
	GtkWidget* Quitter;
	
	/* WIDGETS POUR LE FENETRE MENU */
	GtkWidget* Menu;				/* Fenetre pour les menus */
	GtkWidget* MenuhBox[2];
	GtkWidget* MenuvBox;
	GtkWidget* MenuEntry[2];		/* Zone de saisie pour les nouveaux noms des joueurs */
	GtkWidget* MenuLabel[3];		/* Labels utilises pour les menus */
	
	
	/* WIDGETS DE LA FENETRE DE DIALOGUE*/
	GtkWidget* Dialog;			/* boite de dialogue*/
	GtkWidget* Question;			/* Question pour continuer une nouvelle partie ou confirmation de fermeture */
	GtkWidget* dBox;
	GtkWidget* dBout[3];			/* Boutons de choix (Ok, Oui, Non, Sortir ) */
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
	
}
ctr_s;


/** Fonctions definis dans gtk_puissance4.c **/
/* Construction de l'environement du jeu */
void construire(ctr_s* ctr);
/* Action des boutons pour jouer sur une colonne */
void gtk_jouer_colonne(GtkWidget* button, ctr_s *ctr);
/* Fin de jeu, demande aux joueurs s'ils continuent */
void continuer(int res, ctr_s *ctr); 
/* Reinitialisation de la partie */
void reinit(ctr_s* ctr);
/* Confirmation aux joueurs s'ils veulent quitter le jeu */
void confirmation(GtkWidget* fenetre, ctr_s* ctr);
/* Action des Widgets pour reactiver la fenetre principale */
void afficher_fenetre();
/* fin de partie on liber la memoire */
void free_gtk(ctr_s *ctr);


/** Fonctions definis dans menu.c **/
/* Action des Widgets entry pour changer le nom d'un joueur */
void nouvelle_partie(GtkWidget* MenuItem, ctr_s *ctr);
/* Menu Option pour change les noms des joueurs */
void set_option(GtkWidget* MenuItem, ctr_s *ctr);
/* Action des Widgets entry pour changer le nom d'un joueur */
void changer_nom(GtkWidget* Item, ctr_s *ctr);
/* Menu Liste pour afficher les noms des joueurs */
void Top_5(GtkWidget* MenuItem, ctr_s *ctr);
/* Menu Score pour afficher le score des joueurs */
void get_score(GtkWidget* MenuItem, ctr_s *ctr);
/* Sauvegare les scores des joueurs actifs */
void sauvegarder_score(GtkWidget* Item, ctr_s* ctr);

#endif

