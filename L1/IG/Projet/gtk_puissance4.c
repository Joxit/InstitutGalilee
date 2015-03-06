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
	/* Creation des noms des joueurs */
	strcpy(ctr->nom_joueur1, "Joueur 1");
	strcpy(ctr->nom_joueur2, "Joueur 2");
	
	/* Initialisation des Scores */
	ctr->score_joueur1 = 0;
	ctr->score_joueur2 = 0;
	
	/* CREATION DE LA FENETRE PRINCIPALE */
	/* Initialisation  Fenetre */ 
	if( (ENV->Fenetre = malloc(20*sizeof(GtkWindow))) == NULL)	
	{
		perror("Memoire Fenetre non alloue");
		exit (-1);
	}
	ENV->Fenetre = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title((GtkWindow*)ENV->Fenetre, "Le jeu du Puissance 4 : partie en cours");
	/*gtk_window_set_default_size((GtkWindow*)ENV->Fenetre, 350, 350);*/
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
	
	/* Initialisation : Boutons */   
	for(i = 0; i < NB_COL_JEU_DEFAULT; i++)
	{
		if( (ENV->Bouton[i] = (GtkWidget*)malloc(4*sizeof(GtkWidget))) == NULL)
		{
			printf("Memoire boutton[%d] ", i);
			perror("non alloue");
			exit (-1);
		}
		ENV->Bouton[i] = gtk_button_new_with_mnemonic("");
		/* Connection des boutons a leurs fonctions */
		gtk_signal_connect(GTK_OBJECT(ENV->Bouton[i]), "clicked", G_CALLBACK(gtk_jouer_colonne), ctr);
		/*Fusion des Boutons dans la hBox*/
		gtk_box_pack_start(GTK_BOX((ENV->hBox)[NB_ROW_JEU_DEFAULT]), (ENV->Bouton)[i], TRUE, TRUE, 0);
	}
	
	/* Initialisation du jeu : Image des pions */
	for(i=0; i< NB_COL_JEU_DEFAULT; i++)
	{
		for(j=0; j< NB_ROW_JEU_DEFAULT; j++)
		{
			if( ((ENV->Image)[i][j] = (GtkWidget*)malloc(2*sizeof(GtkWidget))) == NULL)
			{
				printf("Memoire Image[%d][%d] ", i,j);
				perror("non alloue");
				exit (-1);
			}
			/* Creation des Widget Image en leurs donnant le fichier de depart bleu.gif */
			(ENV->Image)[i][j] = gtk_image_new_from_file(BLEU);
			/* Fusion des Images dans leurs hBox respectives */
			gtk_box_pack_start(GTK_BOX((ENV->hBox)[j]), (ENV->Image)[i][j], TRUE, FALSE, 0);
		}
	}
	
	/* Mise en place du Label Tour_Joueur */
	strcpy(Tour_Joueur, "Au tour de : ");
	pch = &Tour_Joueur[ strlen(Tour_Joueur) ];
	strcpy(pch, ctr->nom_joueur1);
	ENV->Label = gtk_label_new (Tour_Joueur);
	
	/* MENU DE LA FENETRE PRINCIPALE */
	
	/* Creation de la barre de menu attaché a Fenetre */
	ENV->BarMenu = gtk_menu_bar_new();
	gtk_box_pack_start(GTK_BOX((ENV->vBox)[0]), ENV->BarMenu, TRUE, TRUE, 0);
	
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
	ENV->Option = gtk_menu_item_new_with_label("Option");
	gtk_menu_shell_append(GTK_MENU_SHELL( ENV->Partie), ENV->Option);
	
	/* creation de l'objet Score attaché a Partie*/
	ENV->Score = gtk_menu_item_new_with_label("Score");
	gtk_menu_shell_append(GTK_MENU_SHELL( ENV->Partie), ENV->Score);
	
	/* creation de l'objet Quitter attaché a Partie*/
	ENV->Quitter = gtk_menu_item_new_with_label("Quitter");
	gtk_menu_shell_append(GTK_MENU_SHELL( ENV->Partie), ENV->Quitter);
	
	/* Connection des objets a leurs fonctions */
	gtk_signal_connect(GTK_OBJECT(ENV->New), "activate", G_CALLBACK(nouvelle_partie), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->Option), "activate", G_CALLBACK(set_option), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->Score), "activate", G_CALLBACK(get_score), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->Quitter), "activate", G_CALLBACK(confirmation), ctr);
	
	
	
	/* Fusion Label et hBox - vBox
	 * hBox[i] avec i de 0 a NB_ROW_JEU_DEFAULT-1 : Box des Images
	 * hBox[NB_ROW_JEU_DEFAULT] : Box des Boutons */
	gtk_box_pack_start(GTK_BOX((ENV->vBox)[0]), ENV->Label, TRUE, TRUE, 7);
	for(i = 0; i < NB_ROW_JEU_DEFAULT; i++)
	{
		gtk_box_pack_start(GTK_BOX((ENV->vBox)[0]), (ENV->hBox)[i], TRUE, TRUE, 0);
	}
	gtk_box_pack_start(GTK_BOX((ENV->vBox)[0]), (ENV->hBox)[NB_ROW_JEU_DEFAULT], TRUE, TRUE, 5);
	
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
	if (partie_get_etat(PARTIE) == PARTIE_ETAT_ENCOURS)
	{
		partie_tour_suivant(PARTIE);
		
		/* Mise a jour du Label Tour Joueur */
		strcpy(Tour_Joueur, "Au tour de : ");
		pch = &Tour_Joueur[ strlen(Tour_Joueur) ];
		
		if(partie_get_tourjoueur(PARTIE) == CASE_ETAT_JOUEUR_1)
			strcpy(pch, ctr->nom_joueur1);
		else
			strcpy(pch, ctr->nom_joueur2);
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
	
	/* match nul*/
	if(res == 0)
		ENV->Question = gtk_label_new ("Match nul!\nVoulez-vous continuer?\0");
	
	/* joueur 1 a gagne */
	if(res == 1) 
	{
		/* Incrementation du score du joueur */
		ctr->score_joueur1 = ctr->score_joueur1 + 1;
		/* On copie le nom du joueur dans la variable pour la question de la boite de Dialog */
		strcpy(Question, ctr->nom_joueur1);
		/* On pointe la fin du nom du joueur mis dans la question */
		pch=&Question[strlen(ctr->nom_joueur1)];
	}
	
	/* joueur 2 a gagne */
	if(res == 2) 
	{
		/* Incrementation du score du joueur */
		ctr->score_joueur2 = ctr->score_joueur2 + 1;
		/* On copie le nom du joueur dans la variable pour la question de la boite de Dialog */
		strcpy(Question, ctr->nom_joueur2);
		/* On pointe la fin du nom du joueur mis dans la question */
		pch=&Question[strlen(ctr->nom_joueur2)];
	}
	
	/* On copie la fin de la question a l'endroit pointe */
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
		strcpy(pch, ctr->nom_joueur1);
	else
		strcpy(pch, ctr->nom_joueur2);
	
	gtk_label_set_text (GTK_LABEL(ENV->Label), Tour_Joueur);
	
}

void confirmation(GtkWidget* fenetre, ctr_s* ctr)
{
	gtk_widget_set_sensitive(ENV->Fenetre, FALSE);
	/* Initialisation de la boite de Dialog */
	ENV->reponse = GTK_RESPONSE_NONE;
	ENV->Question = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO, "Vous etes sur le point de quitter le jeu.\n\tVoulez vous vraiment le faire?");
	gtk_window_set_title((GtkWindow*)ENV->Question, "Quitter");
	
	/* Connection du bouton Destroy pour retourner au jeu */
	gtk_signal_connect(GTK_OBJECT(ENV->Question), "destroy", G_CALLBACK(afficher_fenetre), ctr);
		
	/* Boucle d'attente de reponse */
	while(ENV->reponse == GTK_RESPONSE_NONE)
		ENV->reponse = gtk_dialog_run(GTK_DIALOG(ENV->Question));
	
	/* Si les joueurs veulent fermer le jeu, on libere la partie */
	if(ENV->reponse == GTK_RESPONSE_YES)
	{
		gtk_widget_destroy(ENV->Question);	
		partie_free(&PARTIE);
		free_gtk(ctr);
	}
	/* S'ils veulent continuer on ferme la boite */
	if(ENV->reponse == GTK_RESPONSE_NO)
	{
		gtk_widget_set_sensitive(ENV->Fenetre, TRUE);
		gtk_widget_destroy(ENV->Question);			
	}
}

void set_option(GtkWidget* MenuItem, ctr_s *ctr)
{
	
	gtk_widget_set_sensitive(ENV->Fenetre, FALSE);
	
	ENV->Menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	ENV->MenuvBox = gtk_vbox_new(FALSE, 0);
	ENV->MenuhBox[0] = gtk_hbox_new(TRUE, 0);
	ENV->MenuhBox[1] = gtk_hbox_new(TRUE, 0);
	gtk_window_set_position(GTK_WINDOW(ENV->Menu), GTK_WIN_POS_CENTER_ALWAYS);	
	
	
	
	gtk_window_set_title((GtkWindow*)ENV->Menu, "Option");
	
	ENV->MenuLabel[0] = gtk_label_new("Choisissez votre nouveau nom de joueur");
	
	/* Affichage du nom du joueur 1 dans le label mise dans MenuhBox */ 
	ENV->MenuLabel[1] = gtk_label_new(ctr->nom_joueur1);
	gtk_box_pack_start(GTK_BOX((ENV->MenuhBox[0])), ENV->MenuLabel[1], TRUE, TRUE, 0);
	/* Creation de la boite de saisie avec 24 lettres max mise dans MenuhBox */ 
	ENV->MenuEntry[0] = gtk_entry_new_with_max_length(24);
	gtk_box_pack_start(GTK_BOX((ENV->MenuhBox[0])), ENV->MenuEntry[0], TRUE, TRUE, 0);
	ENV->dBout[0] = gtk_button_new_with_mnemonic(" Ok ");
	gtk_box_pack_start(GTK_BOX((ENV->MenuhBox[0])), ENV->dBout[0], FALSE, FALSE, 5);
	
	/* Affichage du nom du joueur 2 dans le label mise dans MenuhBox */ 
	ENV->MenuLabel[2] = gtk_label_new(ctr->nom_joueur2);
	gtk_box_pack_start(GTK_BOX((ENV->MenuhBox[1])), ENV->MenuLabel[2], TRUE, TRUE, 0);
	/* Creation de la boite de saisie avec 24 lettres max mise dans MenuhBox */ 
	ENV->MenuEntry[1] = gtk_entry_new_with_max_length(24);
	gtk_box_pack_start(GTK_BOX((ENV->MenuhBox[1])), ENV->MenuEntry[1], TRUE, TRUE, 0);
	ENV->dBout[1] = gtk_button_new_with_mnemonic(" Ok ");
	gtk_box_pack_start(GTK_BOX((ENV->MenuhBox[1])), ENV->dBout[1], FALSE, FALSE, 5);
	
	
	/* Fusions des Widgets dans la MenuvBox */
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuLabel[0], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuhBox[0], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuhBox[1], TRUE, TRUE, 10);
	
	/* Fusion MenuvBox dans la Fenetre */
	gtk_container_add(GTK_CONTAINER(ENV->Menu), ENV->MenuvBox);
	
	gtk_widget_show_all(ENV->Menu);
	
	/* Connection des Boites de saisie avec la fonction changer nom et du bouton Destroy */
	gtk_signal_connect(GTK_OBJECT(ENV->Menu), "destroy", G_CALLBACK(afficher_fenetre), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->MenuEntry[0]), "activate", G_CALLBACK(changer_nom), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->MenuEntry[1]), "activate", G_CALLBACK(changer_nom), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->dBout[0]), "clicked", G_CALLBACK(changer_nom), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->dBout[1]), "clicked", G_CALLBACK(changer_nom), ctr);
	
}

void changer_nom(GtkWidget* Item, ctr_s *ctr)
{
	const gchar* nom;
	/* On cherche quel est la boite de saisie activee 
	 * On met son resultat dans la variable nom
	 * Puis on copie dans la variable nom_joueur correspondant */
	if(Item == ENV->MenuEntry[0] || Item == ENV->dBout[0])
	{
		nom = gtk_entry_get_text(GTK_ENTRY(ENV->MenuEntry[0]));
		/* un pseudo superieur a 4 lettre */
		if(4 < strlen(nom))
			strcpy(ctr->nom_joueur1, nom);
	}
	
	if(Item == ENV->MenuEntry[1] || Item == ENV->dBout[1])
	{
		nom = gtk_entry_get_text(GTK_ENTRY(ENV->MenuEntry[1]));
		/* un pseudo superieur a 4 lettre */
		if(4 < strlen(nom))
			strcpy(ctr->nom_joueur2, nom);
	}
	
	gtk_widget_destroy(ENV->Menu);
	set_option(ENV->Menu, ctr);
	
}

void get_score(GtkWidget* MenuItem, ctr_s *ctr)
{
	char score_joueur1[100], score_joueur2[100];
	
	gtk_widget_set_sensitive(ENV->Fenetre, FALSE);
	
	ENV->Menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	ENV->MenuvBox = gtk_vbox_new(TRUE, 0);
	ENV->MenuhBox[0] = gtk_hbox_new(TRUE, 0);
	ENV->MenuhBox[1] = gtk_hbox_new(TRUE, 0);
	gtk_window_set_position(GTK_WINDOW(ENV->Menu), GTK_WIN_POS_CENTER_ALWAYS);	
	
	gtk_window_set_title((GtkWindow*)ENV->Menu, "Score");
	
	ENV->MenuLabel[0] = gtk_label_new("Score des matchs :");
	
	/* Affichage du nom du joueur 1 et son score a mettre dans son label */ 
	sprintf(score_joueur1, "%s : \t %d", ctr->nom_joueur1, ctr->score_joueur1);
	ENV->MenuLabel[1] = gtk_label_new(score_joueur1);
	/* Fusion du label dans sa box */
	gtk_box_pack_start(GTK_BOX((ENV->MenuhBox[0])), ENV->MenuLabel[1], TRUE, TRUE, 30);
	
	/* Affichage du nom du joueur 2 et son score a mettre dans son label */ 
	sprintf(score_joueur2, "%s : \t %d", ctr->nom_joueur2, ctr->score_joueur2);
	ENV->MenuLabel[2] = gtk_label_new(score_joueur2);
	/* Fusion du label dans sa box */
	gtk_box_pack_start(GTK_BOX((ENV->MenuhBox[1])), ENV->MenuLabel[2], TRUE, TRUE, 30);
	
	
	/* Fusions des Widgets dans la MenuvBox */
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuLabel[0], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuhBox[0], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuhBox[1], TRUE, TRUE, 10);
	
	/* Fusion MenuvBox dans la Fenetre */
	gtk_container_add(GTK_CONTAINER(ENV->Menu), ENV->MenuvBox);
	
	gtk_widget_show_all(ENV->Menu);
	
	/* Connection du bouton destroy a afficher_fenetre */
	gtk_signal_connect(GTK_OBJECT(ENV->Menu), "destroy", G_CALLBACK(afficher_fenetre), ctr);
	
	
	
}

void nouvelle_partie(GtkWidget* MenuItem, ctr_s *ctr)
{
	
	gtk_widget_set_sensitive(ENV->Fenetre, FALSE);
	/* Initialisation de la boite de Dialog */
	ENV->reponse = GTK_RESPONSE_NONE;
	ENV->Question = gtk_message_dialog_new(NULL, 
					       GTK_DIALOG_MODAL, 
					       GTK_MESSAGE_WARNING, 
					       GTK_BUTTONS_YES_NO, 
					       "Vous etes sur le point de commencer une nouvelle partie.\n"
					       "\t\tVoulez vous vraiment le faire?\n"
					       "\t\t\t%s : %d points\n"
					       "\t\t\t%s : %d points",
					       ctr->nom_joueur1, ctr->score_joueur1,
					       ctr->nom_joueur2, ctr->score_joueur2 );
	gtk_window_set_title((GtkWindow*)ENV->Question, "Nouvelle Partie");
	
	/* Connection du bouton Destroy pour retourner au jeu */
	gtk_signal_connect(GTK_OBJECT(ENV->Question), "destroy", G_CALLBACK(afficher_fenetre), ctr);
		
	/* Boucle d'attente de reponse */
	while(ENV->reponse == GTK_RESPONSE_NONE)
		ENV->reponse = gtk_dialog_run(GTK_DIALOG(ENV->Question));
	
	/* Si les joueurs veulent fermer le jeu, on libere la partie */
	if(ENV->reponse == GTK_RESPONSE_YES)
	{
		gtk_widget_destroy(ENV->Question);	
		partie_free(&PARTIE);
		free_gtk(ctr);
	}
	/* S'ils veulent continuer on ferme la boite */
	if(ENV->reponse == GTK_RESPONSE_NO)
	{
		gtk_widget_set_sensitive(ENV->Fenetre, TRUE);
		gtk_widget_destroy(ENV->Question);			
	}
}

/* Detrui l'Objet et active la Fenetre principale */
void afficher_fenetre(GtkWidget* Item, ctr_s *ctr)
{
	gtk_widget_destroy(Item);
	gtk_widget_set_sensitive(ENV->Fenetre, TRUE);
}

void free_gtk(ctr_s *ctr)
{
	
	free(ENV);
	free(ctr);
	
	gtk_main_quit();
}