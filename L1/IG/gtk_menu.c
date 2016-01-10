/*
 * Copyright (C) 2010-2016  Jones Magloire
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
 * Jeu Puissance 4 :: fichier Définitions des menus                            *
 *                                                                             *
 * Mardi 17 Mai 2011.                                                          *
 *                                                                             *
 * Pour plus de détails, consulter les fichier d'entête                        *
 * ___________________________________________________________________________ */

# include <stdlib.h>		/* fonction 'rand' de génération aléatoire*/
# include <gtk/gtk.h>
#include <string.h>
# include "puissance4.h"	/* modèle de la chasse au trésor en GTK(constantes symboliques, types, déclaration des fonctions)*/
# include "partie.h"

/* Menu pour le changement de pseudo des joueurs */
void menu_nom(GtkWidget* MenuItem, ctr_s *ctr)
{

	gtk_widget_set_sensitive(ENV->Fenetre, FALSE);

	/** Creation de la fenetre Menu_nom et ses composants **/
	ENV->Menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	ENV->MenuvBox = gtk_vbox_new(FALSE, 0);
	ENV->MenuhBox[0] = gtk_hbox_new(TRUE, 0);
	ENV->MenuhBox[1] = gtk_hbox_new(TRUE, 0);
	gtk_window_set_position(GTK_WINDOW(ENV->Menu), GTK_WIN_POS_CENTER_ALWAYS);

	gtk_window_set_title((GtkWindow*)ENV->Menu, "Changer les pseudo");

	/** Premiere etage **/
	ENV->MenuLabel[0] = gtk_label_new(	"Choisissez votre nouveau pseudonyme\n"
										"Attention 5 lettres minimum\n"
										"laisser vide pour ne pas enregistrer ");

	/** Deuxieme etage **/
	/* Affichage du nom du joueur 1 dans le label mise dans MenuhBox */
	ENV->MenuLabel[1] = gtk_label_new(JOUEUR_1->nom);
	gtk_box_pack_start(GTK_BOX((ENV->MenuhBox[0])), ENV->MenuLabel[1], TRUE, TRUE, 0);
	/* Creation de la boite de saisie avec 20 lettres max mise dans MenuhBox */
	ENV->MenuEntry[0] = gtk_entry_new_with_max_length(20);
	gtk_box_pack_start(GTK_BOX((ENV->MenuhBox[0])), ENV->MenuEntry[0], TRUE, TRUE, 0);

	if(ctr->IA == FALSE)
	{
		/** Troisieme etage **/
		/* Affichage du nom du joueur 2 dans le label mise dans MenuhBox */
		ENV->MenuLabel[2] = gtk_label_new(JOUEUR_2->nom);
		gtk_box_pack_start(GTK_BOX((ENV->MenuhBox[1])), ENV->MenuLabel[2], TRUE, TRUE, 0);
		/* Creation de la boite de saisie avec 20 lettres max mise dans MenuhBox */
		ENV->MenuEntry[1] = gtk_entry_new_with_max_length(20);
		gtk_box_pack_start(GTK_BOX((ENV->MenuhBox[1])), ENV->MenuEntry[1], TRUE, TRUE, 0);
	}


	/** Quatrieme etage **/
	ENV->dBout[0] = gtk_button_new_with_mnemonic(" Enregistrer et Fermer ");

	/** Rassemblement **/
	/* Fusions des Widgets dans la MenuvBox On ne peut pas changer le pseudo de l'IA */
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuLabel[0], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuhBox[0], TRUE, TRUE, 10);
	if(ctr->IA == FALSE)
		gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuhBox[1], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->dBout[0], FALSE, FALSE, 10);

	/* Fusion MenuvBox dans la Fenetre */
	gtk_container_add(GTK_CONTAINER(ENV->Menu), ENV->MenuvBox);

	gtk_widget_show_all(ENV->Menu);

	/* Connection des Boites de saisie avec la fonction changer nom et du bouton Destroy */
	gtk_signal_connect(GTK_OBJECT(ENV->Menu), "destroy", G_CALLBACK(afficher_fenetre), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->MenuEntry[0]), "activate", G_CALLBACK(changer_nom), ctr);
	if(ctr->IA == FALSE)
		gtk_signal_connect(GTK_OBJECT(ENV->MenuEntry[1]), "activate", G_CALLBACK(changer_nom), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->dBout[0]), "clicked", G_CALLBACK(changer_nom), ctr);

}
/* Fenetre de dialogue affichant le score des deux joueurs */
void get_score(GtkWidget* MenuItem, ctr_s *ctr)
{
	gtk_widget_set_sensitive(ENV->Fenetre, FALSE);
	/* Initialisation de la boite de Dialog */
	ENV->reponse = GTK_RESPONSE_NONE;
	ENV->Dialog = gtk_message_dialog_new(NULL,
										 GTK_DIALOG_MODAL,
										 GTK_MESSAGE_INFO,
										 GTK_BUTTONS_OK,
										 "\n"
										 "\n%s :\t\t\t\t\n"
										 "\t\t\t\t\t%d points\n"
										 "\n%s :\t\t\t\t\n"
										 "\t\t\t\t\t%d points",
										 JOUEUR_1->nom, JOUEUR_1->score,
										 JOUEUR_2->nom, JOUEUR_2->score );
	gtk_window_set_title((GtkWindow*)ENV->Dialog, "Score Partie");

	/* Connection du bouton Destroy pour retourner au jeu */
	gtk_signal_connect(GTK_OBJECT(ENV->Dialog), "destroy", G_CALLBACK(afficher_fenetre), ctr);

	/* Boucle d'attente de reponse */
	while(ENV->reponse == GTK_RESPONSE_NONE)
		ENV->reponse = gtk_dialog_run(GTK_DIALOG(ENV->Dialog));

	if(ENV->reponse == GTK_RESPONSE_OK)
		afficher_fenetre(ENV->Dialog, ctr);

}

/* Menu pour recommencer une partie et affiche les scores */
void nouvelle_partie(GtkWidget* MenuItem, ctr_s *ctr)
{

	gtk_widget_set_sensitive(ENV->Fenetre, FALSE);
	/* Initialisation de la boite de Dialog */
	ENV->reponse = GTK_RESPONSE_NONE;
	ENV->Dialog = gtk_message_dialog_new(NULL,
										 GTK_DIALOG_MODAL,
										 GTK_MESSAGE_WARNING,
										 GTK_BUTTONS_YES_NO,
										 "Vous etes sur le point de commencer une nouvelle partie.\n"
										 "\t\tVoulez vous vraiment le faire?\n");
	gtk_window_set_title((GtkWindow*)ENV->Dialog, "Nouvelle Partie");

	/* Connection du bouton Destroy pour retourner au jeu */
	g_signal_connect(G_OBJECT(ENV->Dialog), "destroy", G_CALLBACK(afficher_fenetre), ctr);

	/* Boucle d'attente de reponse */
	while(ENV->reponse == GTK_RESPONSE_NONE)
		ENV->reponse = gtk_dialog_run(GTK_DIALOG(ENV->Dialog));

	/* Si les joueurs veulent commencer un nouveau jeu */
	if(ENV->reponse == GTK_RESPONSE_YES)
	{
		gtk_widget_destroy(ENV->Dialog);
		reinit( ctr);
	}
	/* S'ils veulent continuer on ferme la boite */
	if(ENV->reponse == GTK_RESPONSE_NO)
	{
		afficher_fenetre(ENV->Dialog, ctr);
	}
}

/* Menu Top5 pour afficher les noms des 5 meilleurs joueurs */
void Top_5(GtkWidget* MenuItem, ctr_s *ctr)
{
	gtk_widget_set_sensitive(ENV->Fenetre, FALSE);

	/** Creation de la fenetre Menu Top_5 et ses composants **/
	ENV->Menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	ENV->MenuvBox = gtk_vbox_new(FALSE, 0);
	gtk_window_set_position(GTK_WINDOW(ENV->Menu), GTK_WIN_POS_CENTER_ALWAYS);

	gtk_window_set_title((GtkWindow*)ENV->Menu, "Top 5 des joueurs");

	/** Premiere etage **/
	ENV->MenuLabel[0] = gtk_label_new("Liste des 5 meilleurs joueurs inscrit");

	ENV->MenuLabel[1] = gtk_label_new( get_classement() );

	/** Troisieme etage **/
	ENV->dBout[0] = gtk_button_new_with_mnemonic(" Sortir ");

	/** Rassemblement **/
	/* Fusions des Widgets dans la MenuvBox */
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuLabel[0], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuLabel[1], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->dBout[0], FALSE, FALSE, 10);

	/* Fusion MenuvBox dans la Fenetre */
	gtk_container_add(GTK_CONTAINER(ENV->Menu), ENV->MenuvBox);

	gtk_widget_show_all(ENV->Menu);

	/* Connection du bouton et du bouton Destroy */
	gtk_signal_connect(GTK_OBJECT(ENV->Menu), "destroy", G_CALLBACK(afficher_fenetre), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->dBout[0]), "clicked", G_CALLBACK(afficher_fenetre), ctr);

}

/* Menu pour activer ou desactiver le joueur artificiel */
void menu_IA(GtkWidget* MenuItem, ctr_s *ctr)
{
	FILE* adt = NULL;
	gtk_widget_set_sensitive(ENV->Fenetre, FALSE);

	adt = file_open(adt);

	/* Initialisation de la boite de Dialog */
	ENV->reponse = GTK_RESPONSE_NONE;
	/** Si l'IA  est off **/
	if(ctr->IA == FALSE)
	{
		ENV->Dialog = gtk_message_dialog_new(NULL,
											 GTK_DIALOG_MODAL,
											 GTK_MESSAGE_QUESTION,
											 GTK_BUTTONS_YES_NO,
											 "Beta : Intelligence Artificielle.\n"
											 "Voulez vous jouer contre l'ordinateur?\n");

	}
	else
		/** Si l'IA  est on **/
		if(ctr->IA == TRUE)
		{
			/* Initialisation de la boite de Dialog */
			ENV->reponse = GTK_RESPONSE_NONE;
			ENV->Dialog = gtk_message_dialog_new(NULL,
												 GTK_DIALOG_MODAL,
												 GTK_MESSAGE_INFO,
												 GTK_BUTTONS_YES_NO,
												 "Beta : Intelligence Artificielle.\n"
												 "Voulez vous arreter de jouer contre l'ordinateur?\n");
		}
	gtk_window_set_title((GtkWindow*)ENV->Dialog, "Beta Intelligence Artificielle");

	/* Connection du bouton Destroy pour retourner au jeu */
	gtk_signal_connect(GTK_OBJECT(ENV->Dialog), "destroy", G_CALLBACK(afficher_fenetre), ctr);

	/* Boucle d'attente de reponse */
	while(ENV->reponse == GTK_RESPONSE_NONE)
		ENV->reponse = gtk_dialog_run(GTK_DIALOG(ENV->Dialog));

	/* Si les joueurs veulent demarrer/arreter le joueur artificiel */
	if(ENV->reponse == GTK_RESPONSE_YES)
	{
		gtk_widget_destroy(ENV->Dialog);
		reinit( ctr);
		ctr->IA = !ctr->IA;
		if(ctr->IA == TRUE)
		{
			gtk_menu_item_set_label(GTK_MENU_ITEM(ENV->JouerIA), "Joueur Artificiel : On");
			JOUEUR_2->score = 0;
			while(!feof(adt))
			{
				fscanf(adt, "%s", JOUEUR_2->nom);
				fscanf(adt, "%d", &JOUEUR_2->score);
				if(JOUEUR_2->nom != NULL)
					if(strcmp("Int._Art.", JOUEUR_2->nom) ==0)
					{
						/* si on le trouve on sort */
						break;
					}
			}

			if(strcmp("Int._Art.", JOUEUR_2->nom) !=0)
			{
				strcpy(JOUEUR_2->nom, "Int._Art.");
				JOUEUR_2->score = 0;
			}
			if(partie_get_tourjoueur(PARTIE) == CASE_ETAT_JOUEUR_2)
				gtk_jouer_colonne( ENV->Bouton[rand()% dim_get_nbcol(&(PARTIE->dim))], ctr);
		}
		if(ctr->IA == FALSE)
		{
			gtk_menu_item_set_label(GTK_MENU_ITEM(ENV->JouerIA), "Joueur Artificiel : Off");
			sauvegarder_score(MenuItem, ctr);
			/* Creation des noms des joueurs */
			/* joueur 1*/
			fscanf(adt, "%s", JOUEUR_2->nom);
			fscanf(adt, "%d", &JOUEUR_2->score);
			/* Int. Art. */
			fscanf(adt, "%s", JOUEUR_2->nom);
			fscanf(adt, "%d", &JOUEUR_2->score);
			/* joueur 2 */
			fscanf(adt, "%s", JOUEUR_2->nom);
			fscanf(adt, "%d", &JOUEUR_2->score);
			if(JOUEUR_2->nom == NULL)
			{
				strcpy(JOUEUR_2->nom, "Joueur_2");
				JOUEUR_2->score = 0;
			}
		}
	}
	/* S'ils veulent rien changer on ferme la boite */
	if(ENV->reponse == GTK_RESPONSE_NO)
	{
		afficher_fenetre(ENV->Dialog, ctr);
	}
	fclose(adt);

}

void menu_about(GtkWidget* Item, ctr_s* ctr)
{
	gtk_widget_set_sensitive(ENV->Fenetre, FALSE);
	/* Initialisation de la boite de Dialog */
	ENV->reponse = GTK_RESPONSE_NONE;
	ENV->Dialog = gtk_message_dialog_new(NULL,
										 GTK_DIALOG_MODAL,
										 GTK_MESSAGE_INFO,
										 GTK_BUTTONS_CLOSE,
										 "Puissance 4\n\n"
										 "Version 1.6\n\n"
										 "Copyright (C) 2010-2016  Jones Magloire\n"
										 "This program comes with ABSOLUTELY NO WARRANTY.\n"
										 "This is free software, and you are welcome to\n"
										 "redistribute it under certain conditions.\n"
										 "Auteur : MAGLOIRE Jones\n"
										 "Dans le cadre du projet d'interface graphique\n"
										 "des Licences 1 de l'Institut Galilee,\n"
										 "Universite Paris 13, Villetaneuse\n"
										 "http://www-galilee.univ-paris13.fr/\n\n"
										 "Compatible GTK+ 2.16 et plus\n");
	gtk_window_set_title((GtkWindow*)ENV->Dialog, "A propos de puissance 4");

	/* Connection du bouton Destroy pour retourner au jeu */
	gtk_signal_connect(GTK_OBJECT(ENV->Dialog), "destroy", G_CALLBACK(afficher_fenetre), ctr);

	/* Boucle d'attente de reponse */
	while(ENV->reponse == GTK_RESPONSE_NONE)
		ENV->reponse = gtk_dialog_run(GTK_DIALOG(ENV->Dialog));

	if(ENV->reponse == GTK_RESPONSE_CLOSE)
		afficher_fenetre(ENV->Dialog, ctr);

}

/* definition de gtk_menu_item_set_label qui est arrivé apres GTK+ 2.16
 * pour compatibilité avec GTK+ 2.10
 * GTK_MENU_ITEM_GET_CLASS a verifier */
void gtk_menu_item_set_label (GtkMenuItem *menu_item, const gchar *label)
{
	g_return_if_fail (GTK_IS_MENU_ITEM (menu_item));

	GTK_MENU_ITEM_GET_CLASS (menu_item)->set_label (menu_item, label);
}
