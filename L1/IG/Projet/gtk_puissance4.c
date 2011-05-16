/* _____________________________________________________________________________
 * Jeu Puissance 4 :: fichier Définitions
 *												
 * Mardi 4 Mai 2011.													
 * 
 * Pour plus de détails, consulter les fichier d'entête						
 * _____________________________________________________________________________ */

# include <stdlib.h>		/* fonction 'rand' de génération aléatoire*/
# include <gtk/gtk.h>
#include <string.h>
# include <time.h>	
# include "gtk_puissance4.h"	/* modèle de la chasse au trésor en GTK(constantes symboliques, types, déclaration des fonctions)*/
# include "partie.h"

void construire(ctr_s* ctr)
{
	int i,j;
	char *pch, Tour_Joueur[40];
	FILE* adt;
	if((adt = fopen("users.dat", "r")) == NULL)
	{
		perror("Fichier non ouvert");
		exit (-1);
	}
	/* Creation des noms des joueurs */	
	fseek(adt, 0, SEEK_SET);
	fscanf(adt, "%s", JOUEUR_1->nom);
	fscanf(adt, "%d", &JOUEUR_1->score);
	if(JOUEUR_1->nom == NULL)
	{
		strcpy(JOUEUR_1->nom, "Joueur_1");
		JOUEUR_1->score = 0;
	}
		
	fscanf(adt, "%s", JOUEUR_2->nom);
	fscanf(adt, "%d", &JOUEUR_2->score);
	if(JOUEUR_2->nom == NULL)
	{
		strcpy(JOUEUR_2->nom, "Joueur_2");
		JOUEUR_2->score = 0;
	}
	ctr->IA = 1;
	fclose(adt);
	/* CREATION DE LA FENETRE PRINCIPALE */
	/* Initialisation  Fenetre */ 
	if( (ENV->Fenetre = malloc(20*sizeof(GtkWindow))) == NULL)	
	{
		perror("Memoire Fenetre non alloue");
		exit (-1);
	}
	ENV->Fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title((GtkWindow*)ENV->Fenetre, "Le jeu du Puissance 4 : partie en cours");
	gtk_window_set_resizable(GTK_WINDOW(ENV->Fenetre), FALSE);
	gtk_window_set_position(GTK_WINDOW(ENV->Fenetre), GTK_WIN_POS_CENTER_ALWAYS);	
	
	/* Initialisation : hBoxs */ 
	for( i = 0; i < NB_HBOX; i++)
	{
		if( ((ENV->hBox)[i] = (GtkWidget*)malloc(4*sizeof(GtkWidget))) == NULL)
		{
			printf("Memoire hBox[%d] ", i);
			perror("non alloue");
			exit (-1);
		}
		(ENV->hBox)[i] = gtk_hbox_new(FALSE, 0);	
	}
	
	/* Initialisation : vBox */ 
	for( i = 0; i < NB_VBOX; i++)
	{
		if( ((ENV->vBox)[i] = (GtkWidget*)malloc(4*sizeof(GtkWidget))) == NULL)
		{
			printf("Memoire vBox[%d] ", i);
			perror("non alloue");
			exit (-1);
		}
		(ENV->vBox)[i] = gtk_vbox_new(FALSE, 0);
	}
	
	/* Initialisation du jeu : image des pions et boutons a mettre dans le tableau*/
	ENV->Tableau = gtk_table_new(DIM->row +2, DIM->col +2, 0);
	for(i=0; i< DIM->col; i++)
	{
		for(j=0; j< DIM->row; j++)
		{
			/* Creation des Widget Image en leurs donnant le fichier de depart bleu.gif */
			(ENV->Image)[i][j] = gtk_image_new_from_file(BLEU);
			gtk_table_attach_defaults(GTK_TABLE(ENV->Tableau), (ENV->Image)[i][j], i, i+1, j+1, j+2);
		}
		
		/* Initialisation : Boutons */  
		ENV->Bouton[i] = gtk_button_new_with_mnemonic("");
		/* Connection des boutons a leurs fonctions */
		gtk_signal_connect(GTK_OBJECT(ENV->Bouton[i]), "clicked", G_CALLBACK(gtk_jouer_colonne), ctr);
		/*Fusion des Boutons dans la hBox*/
		gtk_table_attach_defaults(GTK_TABLE(ENV->Tableau), ENV->Bouton[i], i, i+1, DIM->row+1, DIM->row+2);
	}
	
	/* Mise en place du Label Tour_Joueur */
	strcpy(Tour_Joueur, "Au tour de : ");
	/* on utilise pch pour pointer la fin de la phrase */
	pch = &Tour_Joueur[ strlen(Tour_Joueur) ];
	strcpy(pch, JOUEUR_1->nom);
	ENV->Label = gtk_label_new (Tour_Joueur);
	
	/* MENU DE LA FENETRE PRINCIPALE */
	/** BARRE DE MENU **/
	/* Creation de la barre de menu attaché a Fenetre */
	ENV->BarMenu = gtk_menu_bar_new();
	gtk_box_pack_start(GTK_BOX((ENV->vBox)[0]), ENV->BarMenu, TRUE, TRUE, 0);
	
	/** SOUS MENU PARTIE **/
	/* Creation de l'objets MenuPartie attache a BarMenu */
	ENV->MenuPartie = gtk_menu_item_new_with_label("Partie");
	gtk_menu_shell_append(GTK_MENU_SHELL( ENV->BarMenu), ENV->MenuPartie);
	
	/* creation du sous menu Partie attache a l'objet MenuPartie*/
	ENV->Partie = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(ENV->MenuPartie), ENV->Partie);
	
	/* creation de l'objet New attaché a Partie*/
	ENV->New = gtk_menu_item_new_with_label("Nouvelle partie");
	gtk_menu_shell_append(GTK_MENU_SHELL( ENV->Partie), ENV->New);
	
	/* creation de l'objet option attaché a Partie*/
	ENV->Liste = gtk_menu_item_new_with_label("Top 5");
	gtk_menu_shell_append(GTK_MENU_SHELL( ENV->Partie), ENV->Liste);
	
	/* creation de l'objet Score attaché a Partie*/
	ENV->Score = gtk_menu_item_new_with_label("Score");
	gtk_menu_shell_append(GTK_MENU_SHELL( ENV->Partie), ENV->Score);
	
	/* creation de l'objet Save attaché a Partie*/
	ENV->Save = gtk_menu_item_new_with_label("Sauvegarder score");
	gtk_menu_shell_append(GTK_MENU_SHELL( ENV->Partie), ENV->Save);
	
	/* creation de l'objet Quitter attaché a Partie*/
	ENV->Quitter = gtk_menu_item_new_with_label("Quitter");
	gtk_menu_shell_append(GTK_MENU_SHELL( ENV->Partie), ENV->Quitter);
	
	/** SOUS MENU OPTION **/
	/* creation de l'objet option attaché a Partie*/
	ENV->MenuOption = gtk_menu_item_new_with_label("Option");
	gtk_menu_shell_append(GTK_MENU_SHELL( ENV->BarMenu), ENV->MenuOption);
	
	/* creation du sous menu Partie attache a l'objet MenuPartie*/
	ENV->Option = gtk_menu_new();
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(ENV->MenuOption), ENV->Option);
	
	/* creation de l'objet option attaché a Partie*/
	ENV->ChangerNom = gtk_menu_item_new_with_label("Changer Pseudo");
	gtk_menu_shell_append(GTK_MENU_SHELL( ENV->Option), ENV->ChangerNom);
	
	/* creation de l'objet option attaché a Partie*/
	ENV->ChangerDim = gtk_menu_item_new_with_label("Changer la dimension");
	gtk_menu_shell_append(GTK_MENU_SHELL( ENV->Option), ENV->ChangerDim);
	
	/* creation de l'objet option attaché a Partie*/
	ENV->JouerIA = gtk_menu_item_new_with_label("Intelligence Artificielle");
	gtk_menu_shell_append(GTK_MENU_SHELL( ENV->Option), ENV->JouerIA);
	
	
	/* Connection des objets a leurs fonctions toutes definies dans menu.c sauf Quitter*/
	gtk_signal_connect(GTK_OBJECT(ENV->New), "activate", G_CALLBACK(nouvelle_partie), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->ChangerNom), "activate", G_CALLBACK(menu_nom), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->Liste), "activate", G_CALLBACK(Top_5), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->Score), "activate", G_CALLBACK(get_score), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->Save), "activate", G_CALLBACK(sauvegarder_score), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->Quitter), "activate", G_CALLBACK(confirmation), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->ChangerDim), "activate", G_CALLBACK(menu_dim), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->JouerIA), "activate", G_CALLBACK(menu_IA), ctr);
	
	
	
	/* Fusion Label et hBox - vBox
	 * hBox[i] avec i de 0 a NB_ROW_JEU_DEFAULT-1 : Box des Images
	 * hBox[NB_ROW_JEU_DEFAULT] : Box des Boutons */
	gtk_table_attach_defaults(GTK_TABLE(ENV->Tableau), ENV->Label, 0, DIM->col+2, 0, 1);
		gtk_box_pack_start(GTK_BOX((ENV->vBox)[0]), (ENV->Tableau), TRUE, TRUE, 0);	
	
	/* Fusion vBox - Fenetre */
	gtk_container_add(GTK_CONTAINER(ENV->Fenetre), (ENV->vBox)[0]);
	
	
	
	/* Show all*/
	gtk_widget_show_all(ENV->Fenetre);
	gtk_signal_connect(GTK_OBJECT(ENV->Fenetre), "destroy", G_CALLBACK(gtk_main_quit), NULL);
}

void gtk_jouer_colonne(GtkWidget* button, ctr_s *ctr)
{
	int ligne=0,colonne;
	char *pch, Tour_Joueur[40];
	
	/* On cherche le Bouton qui a ete active */
	for(colonne = 0; colonne < NB_COL_JEU_DEFAULT; colonne++)
		if(button == ENV->Bouton[colonne])
			break;
		
		
		
		/* On joue le coup */
		ligne = partie_jouer_colonne(PARTIE, colonne);
	
	/* On remplace l'image de la case joue en fonction du tour actuel joueur */
	if(partie_get_tourjoueur(PARTIE) == CASE_ETAT_JOUEUR_1)
		gtk_image_set_from_file(GTK_IMAGE((ENV->Image)[colonne][ligne]), ROUGE);
	else
		gtk_image_set_from_file(GTK_IMAGE((ENV->Image)[colonne][ligne]), JAUNE);
	
	/* S'il n'y a plus de lignes disponibles sur cette range joue, on enleve la sensibilite du bouton */
	if(ligne == 0)
		gtk_widget_set_sensitive(button, FALSE);
	
	
	/* tour suivant */
	if (partie_get_etat(PARTIE) == PARTIE_ETAT_ENCOURS )
	{
		if(ctr->IA == 0)
			partie_tour_suivant(PARTIE);
		else
			if (ctr->IA == 1)
			{
				if(partie_get_tourjoueur(PARTIE) == CASE_ETAT_JOUEUR_1)
					IA_jouer( ctr, ligne,  colonne);
					
			}
			
		/* Mise a jour du Label Tour Joueur */
		strcpy(Tour_Joueur, "Au tour de : ");
		pch = &Tour_Joueur[ strlen(Tour_Joueur) ];
		
		if(partie_get_tourjoueur(PARTIE) == CASE_ETAT_JOUEUR_1)
			strcpy(pch, JOUEUR_1->nom);
		else
			strcpy(pch, JOUEUR_2->nom);
		gtk_label_set_text (GTK_LABEL(ENV->Label), Tour_Joueur);
	}
	
	/* Si le jeu est fini il y a 3 possibilitees */
	if (partie_get_etat(PARTIE) == PARTIE_ETAT_JOUEUR_12)
		continuer(0,ctr);    
	if (partie_get_etat(PARTIE) == PARTIE_ETAT_JOUEUR_1)
		continuer(1,ctr);
	if (partie_get_etat(PARTIE) == PARTIE_ETAT_JOUEUR_2)
		continuer(2,ctr);
	
	
}

void continuer(int res, ctr_s *ctr)
{
	char Question[200];
	char *pch;
	
	gtk_widget_set_sensitive(ENV->Fenetre, FALSE);
	gtk_window_set_title((GtkWindow*)ENV->Fenetre, "Le jeu du Puissance 4 : partie en terminee");
	
	/* Initialisation Dialog */
	ENV->Dialog = gtk_dialog_new();
	ENV->reponse = GTK_RESPONSE_NONE;
	ENV->dBox = (GTK_DIALOG(ENV->Dialog))->vbox;	
	
	/* Initialisation des Bouttons, 2 reponses possible Oui et Fermer */
	ENV->dBout[0] = gtk_dialog_add_button(GTK_DIALOG(ENV->Dialog), GTK_STOCK_YES, GTK_RESPONSE_YES);
	ENV->dBout[1] = gtk_dialog_add_button(GTK_DIALOG(ENV->Dialog), GTK_STOCK_NO, GTK_RESPONSE_CLOSE);
	
	
	/* joueur 1 a gagne */
	if(res == 1) 
	{
		/* Incrementation du score du joueur */
		JOUEUR_1->score = JOUEUR_1->score + 1;
		/* On copie le nom du joueur dans la variable pour la question de la boite de Dialog */
		strcpy(Question, JOUEUR_1->nom);
		/* On pointe la fin du nom du joueur mis dans la question */
		pch=&Question[strlen(JOUEUR_1->nom)];
		if(ctr->IA == 1)
			partie_tour_suivant(PARTIE);
			
	}
	
	/* joueur 2 a gagne */
	if(res == 2) 
	{
		/* Incrementation du score du joueur */
		JOUEUR_2->score = JOUEUR_2->score + 1;
		/* On copie le nom du joueur dans la variable pour la question de la boite de Dialog */
		strcpy(Question, JOUEUR_2->nom);
		/* On pointe la fin du nom du joueur mis dans la question */
		pch=&Question[strlen(JOUEUR_2->nom)];
	}
	/* match nul*/
	if(res == 0)
		strcpy(Question, "\tMatch nul!\nVoulez-vous continuer?\0");
	else
		/* Sinon on copie la fin de la question a l'endroit pointe */
		strcpy(pch, " a gagne!\n""Voulez-vous continuer?\0");
	/* On met la question dans le label Question */
	ENV->Question = gtk_label_new (Question);
	/* On fusionne le Label dans la vBox */
	gtk_box_pack_start(GTK_BOX(ENV->dBox), ENV->Question, TRUE, TRUE, 5);
	
	/* On affiche le tout */
	gtk_widget_show_all(ENV->Dialog);
	/* Boucle d'attente de reponse */
	while(ENV->reponse == GTK_RESPONSE_NONE)
		ENV->reponse = gtk_dialog_run(GTK_DIALOG(ENV->Dialog));
	
	/* Si les joueurs veulent continuer on reinitialise le jeu */
	if(ENV->reponse == GTK_RESPONSE_YES)
	{
		gtk_widget_destroy(ENV->Dialog);
		reinit( ctr);
		if(ctr->IA == 1 && partie_get_tourjoueur(PARTIE) == PARTIE_ETAT_JOUEUR_2)
		{
			gtk_jouer_colonne( ENV->Bouton[rand()% dim_get_nbcol(&(PARTIE->dim))], ctr);
			/*partie_tour_suivant(PARTIE);*/
		}
	}
	/* S'ils ne veulent pas on demande confirmation de fermeture */
	if(ENV->reponse == GTK_RESPONSE_CLOSE)
	{
		gtk_widget_destroy(ENV->Dialog);
		confirmation(ENV->Fenetre, ctr);
	}
}

void reinit(ctr_s* ctr)
{
	int i,j;
	char *pch, Tour_Joueur[40];
	gtk_widget_set_sensitive(ENV->Fenetre, TRUE);
	
	/* Boutons a nouveaux sensible */
	for(i = 0; i < NB_COL_JEU_DEFAULT; i++)
	{
		gtk_widget_set_sensitive(ENV->Bouton[i], TRUE);
	}
	
	/* Reinitialisation des Images */
	for(i=0; i< NB_COL_JEU_DEFAULT; i++)
		for(j=0; j< NB_ROW_JEU_DEFAULT; j++)
			gtk_image_set_from_file(GTK_IMAGE((ENV->Image)[i][j]), BLEU);
		
		
		
		gtk_window_set_title((GtkWindow*)ENV->Fenetre, "Le jeu du Puissance 4 : partie en cours");
	partie_nouvelle_partie(PARTIE);
	
	/* reinitialisation du Label de tour */
	strcpy(Tour_Joueur, "Au tour de : ");
	pch = &Tour_Joueur[ strlen(Tour_Joueur) ];
	
	if(partie_get_tourjoueur(PARTIE) == CASE_ETAT_JOUEUR_1)
		strcpy(pch, JOUEUR_1->nom);
	else
		strcpy(pch, JOUEUR_2->nom);
	
	gtk_label_set_text (GTK_LABEL(ENV->Label), Tour_Joueur);
	
}

void confirmation(GtkWidget* fenetre, ctr_s* ctr)
{
	gtk_widget_set_sensitive(ENV->Fenetre, FALSE);
	/* Initialisation de la boite de Dialogue */
	ENV->reponse = GTK_RESPONSE_NONE;
	ENV->Dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO, "Vous etes sur le point de quitter le jeu.\n\tVoulez vous vraiment le faire?");
	gtk_window_set_title((GtkWindow*)ENV->Dialog, "Quitter");
	
	/* Connection du bouton Destroy pour retourner au jeu */
	gtk_signal_connect(GTK_OBJECT(ENV->Dialog), "destroy", G_CALLBACK(afficher_fenetre), ctr);
	
	/* Boucle d'attente de reponse */
	while(ENV->reponse == GTK_RESPONSE_NONE)
		ENV->reponse = gtk_dialog_run(GTK_DIALOG(ENV->Dialog));
	
	/* Si les joueurs veulent fermer le jeu, on libere la partie */
	if(ENV->reponse == GTK_RESPONSE_YES)
	{
		gtk_widget_destroy(ENV->Dialog);	
		sauvegarder_score( fenetre, ctr);
		partie_free(&PARTIE);
		free_gtk(ctr);
	}
	/* S'ils veulent continuer on ferme la boite */
	if(ENV->reponse == GTK_RESPONSE_NO)
	{
		gtk_widget_set_sensitive(ENV->Fenetre, TRUE);
		gtk_widget_destroy(ENV->Dialog);
		if(partie_get_etat(PARTIE) != PARTIE_ETAT_ENCOURS)
			reinit(ctr);
	}
}

/* Detruit l'Objet et active la Fenetre principale */
void afficher_fenetre(GtkWidget* Item, ctr_s *ctr)
{
	if(Item == ENV->dBout[2])
		gtk_widget_destroy(ENV->Menu);
	else
		gtk_widget_destroy(Item);
	gtk_widget_set_sensitive(ENV->Fenetre, TRUE);
}

/* Libere l'environnement GTK+ */
void free_gtk(ctr_s *ctr)
{
	
	free(ENV);
	free(ctr);
	free(JOUEUR_1);
	free(JOUEUR_2);
	
	gtk_main_quit();
}