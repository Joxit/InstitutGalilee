/* _____________________________________________________________________________
 * Jeu Puissance 4 :: fichier Définitions des menus
 *												
 * Mardi 17 Mai 2011.													
 * 
 * Pour plus de détails, consulter les fichier d'entête						
 * _____________________________________________________________________________ */

# include <stdlib.h>		/* fonction 'rand' de génération aléatoire*/
# include <gtk/gtk.h>
#include <string.h>
# include <time.h>	
# include "gtk_puissance4.h"	/* modèle de la chasse au trésor en GTK(constantes symboliques, types, déclaration des fonctions)*/
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
	
	/** Troisieme etage **/
	/* Affichage du nom du joueur 2 dans le label mise dans MenuhBox */ 
	ENV->MenuLabel[2] = gtk_label_new(JOUEUR_2->nom);
	gtk_box_pack_start(GTK_BOX((ENV->MenuhBox[1])), ENV->MenuLabel[2], TRUE, TRUE, 0);
	/* Creation de la boite de saisie avec 20 lettres max mise dans MenuhBox */ 
	ENV->MenuEntry[1] = gtk_entry_new_with_max_length(20);
	gtk_box_pack_start(GTK_BOX((ENV->MenuhBox[1])), ENV->MenuEntry[1], TRUE, TRUE, 0);
	
	if(ctr->IA == TRUE)
		gtk_widget_set_sensitive(ENV->MenuEntry[1], FALSE);
	else
		gtk_widget_set_sensitive(ENV->MenuEntry[1], TRUE);
	/** Quatrieme etage **/
	ENV->dBout[0] = gtk_button_new_with_mnemonic(" Enregistrer et Fermer ");
	
	/** Rassemblement **/
	/* Fusions des Widgets dans la MenuvBox */
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuLabel[0], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuhBox[0], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuhBox[1], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->dBout[0], FALSE, FALSE, 10);
	
	/* Fusion MenuvBox dans la Fenetre */
	gtk_container_add(GTK_CONTAINER(ENV->Menu), ENV->MenuvBox);
	
	gtk_widget_show_all(ENV->Menu);
	
	/* Connection des Boites de saisie avec la fonction changer nom et du bouton Destroy */
	gtk_signal_connect(GTK_OBJECT(ENV->Menu), "destroy", G_CALLBACK(afficher_fenetre), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->MenuEntry[0]), "activate", G_CALLBACK(changer_nom), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->MenuEntry[1]), "activate", G_CALLBACK(changer_nom), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->dBout[0]), "clicked", G_CALLBACK(changer_nom), ctr);
	
}
/* Action lors de la validation du pseudonyme */
void changer_nom(GtkWidget* Item, ctr_s *ctr)
{
	const gchar* nom;
	joueur_s *joueur1 = malloc(13*sizeof(joueur_s));
	joueur_s *joueur2 = malloc(13*sizeof(joueur_s));
	FILE* adt;
	if((adt = fopen("users.dat", "r")) == NULL)
	{
		perror("Fichier users.dat non ouvert");
		/* si l'utilisateur a supprime le fichier apres l'ouverture du programme on en cree un nouveau */
		if((adt = fopen("users.dat", "w")) == NULL)
		{
			perror("Creation du fichier users.dat impossible");
			exit (-1);
		}
		fclose(adt);
		if((adt = fopen("users.dat", "r")) == NULL)
		{
			perror("Fichier unsers.dat non ouvert");
			exit (-1);
		}
	}
	fseek(adt, 0, SEEK_SET);
	/* On cherche quel est la boite de saisie activee 
	 * On met son resultat dans la variable nom
	 * Puis on copie dans la variable nom_joueur correspondante */
	 /** Premiere zone de saisie **/
	if(Item == ENV->MenuEntry[0] || Item == ENV->dBout[0])
	{
		nom = gtk_entry_get_text(GTK_ENTRY(ENV->MenuEntry[0]));
		/* un pseudo superieur a 4 lettre */
		if(4 < strlen(nom))
			strcpy(JOUEUR_1->nom, nom);
		JOUEUR_1->score = 0;
		/* Mode fichier : Cherche dans le fichier users.dat 
		 * le nom du joueur qui vient d'etre entre
		 * s'il existe deja, on recupere son score precedent
		 * sinon on le met a 0 */
		while(!feof(adt))
		{
			fscanf(adt, "%s", joueur1->nom);
			fscanf(adt, "%d", &joueur1->score);
			/* avant de commencer la recherche on verifie que le nom a bien ete pris */
			if(JOUEUR_1->nom!=NULL && joueur1->nom != NULL)
				if(strcmp(JOUEUR_1->nom, joueur1->nom) ==0)
				{
					 JOUEUR_1->score = joueur1->score;
					/* si on le trouve on sort */
					break;
				}
		}
	}
	
	 /** Seconde zone de saisie **/
	if(Item == ENV->MenuEntry[1] || Item == ENV->dBout[0])
	{
		nom = gtk_entry_get_text(GTK_ENTRY(ENV->MenuEntry[1]));
		/* un pseudo superieur a 4 lettre */
		if(4 < strlen(nom))
			strcpy(JOUEUR_2->nom, nom);
		JOUEUR_2->score = 0;
		/** Mode fichier **/
		while(!feof(adt))
		{
			fscanf(adt, "%s", joueur2->nom);
			fscanf(adt, "%d", &joueur2->score);
			if(JOUEUR_2->nom!=NULL && joueur2->nom != NULL)
				if(strcmp(JOUEUR_2->nom, joueur2->nom) ==0)
				{
					JOUEUR_2->score = joueur2->score;
					
					/* si on le trouve on sort */
					break;
				}
		}
	}
	
	/* on libere la memoire de joueur */
	free(joueur1);
	free(joueur2);
	gtk_widget_destroy(ENV->Menu);
	if(Item != ENV->dBout[0])
		menu_nom(ENV->Menu, ctr);
	return;
	
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
	gtk_signal_connect(GTK_OBJECT(ENV->Dialog), "destroy", G_CALLBACK(afficher_fenetre), ctr);
	
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
	FILE* adt = NULL;
	char* pch, liste_classement[200];
	int i = 0,j = 0, score[6];
	joueur_s* joueur = malloc(13*sizeof(joueur_s));
	
	/* Fichier contenant les scores */
	if((adt = fopen("users.dat", "r")) == NULL)
	{
		perror("Fichier users.dat non ouvert");
		/* si l'utilisateur a supprime le fichier apres l'ouverture du programme on en cree un nouveau */
		if((adt = fopen("users.dat", "w")) == NULL)
		{
			perror("Creation du fichier users.dat impossible");
			exit (-1);
		}
		fclose(adt);
		if((adt = fopen("users.dat", "r")) == NULL)
		{
			perror("Fichier unsers.dat non ouvert");
			exit (-1);
		}
	}
	
	gtk_widget_set_sensitive(ENV->Fenetre, FALSE);
	
	/** Creation de la fenetre Menu Top_5 et ses composants **/
	ENV->Menu = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	ENV->MenuvBox = gtk_vbox_new(FALSE, 0);
	gtk_window_set_position(GTK_WINDOW(ENV->Menu), GTK_WIN_POS_CENTER_ALWAYS);		
	
	gtk_window_set_title((GtkWindow*)ENV->Menu, "Top 5 des joueurs");
	
	/** Premiere etage **/
	ENV->MenuLabel[0] = gtk_label_new("Liste des 5 meilleurs joueurs inscrit");
	score[0] = 1000;
	
	/** Deuxieme etage **/
	for(i = 1; i < 6; i = i + 1)
	{
		/* porte de sortie pour eviter que le meme score apparaisse jusqu'a la fin du tableau */
		if(score[i] == score[i-2])
			break;
			/* on se place  au debut du fichier et on lit la premiere ligne et enregistre le score */
		fseek(adt, 0, SEEK_SET);
		score[i] = 0;
		/* suite de la lecture jusqu'a la fin du fichier */
		while(!feof(adt))
		{
			fscanf(adt, "%s", joueur->nom);
			fscanf(adt, "%d", &joueur->score);
			/** Verification : score[i] < joueur->score < score[i-1] pour trouver le vrai suivant 
			 ** joueur->nom doit exister pour eviter les bugs **/
			if(score[i] < joueur->score && score[i-1] > joueur->score && joueur->nom != NULL)
				score[i] = joueur->score;
		}
	}
	/* on initialise la variable qui contiendra la liste */
	strcpy(liste_classement, "");
	for(i = 1; i < 6; i = i + 1)
	{
		/* porte de sortie pour eviter l'affichage en plusieur exemplaire des joueurs au meme score */
		if(score[i] == score[i-1])
			break;
		/* on se place au debut du fichier */
		fseek(adt, 0, SEEK_SET);
		while(!feof(adt))
		{
			/* lecture des lignes du fichier */
			fscanf(adt, "%s", joueur->nom);
			fscanf(adt, "%d", &joueur->score);
			/* on cherche si le score lu correspond a clui qu'on veut afficher */
			if(score[i] == joueur->score && !feof(adt) && joueur->nom != NULL)
			{
				pch = NULL;
				/* on pointe la fin de la chaine de caractere liste_classement*/
				pch = &liste_classement[ strlen(liste_classement) ];
				/* et on ecrit le pseudo et le score du joueur */
				sprintf(pch, "%s\t : \t %d\n", joueur->nom, joueur->score);
				j = j + 1;
			}
			/* Quand on est a 5 joueurs affiche on sort des boucles brusquement*/
			if(j == 5)
			{
				i = 6;
				break;
			}
		}
	}
	#if (PUISSANCE4_MODELE_DEBUG != 0)
		printf("\tTop_5  i == %d j == %d liste_classement : \n%sScore : %d; %d; %d; %d; %d; %d\n", i, j, liste_classement, score[0], score[1], score[2], score[3], score[4], score[5]); 
	#endif
	ENV->MenuLabel[1] = gtk_label_new(liste_classement);
	
	/** Troisieme etage **/
	ENV->dBout[2] = gtk_button_new_with_mnemonic(" Sortir ");
	
	/** Rassemblement **/
	/* Fusions des Widgets dans la MenuvBox */
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuLabel[0], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->MenuLabel[1], TRUE, TRUE, 10);
	gtk_box_pack_start(GTK_BOX((ENV->MenuvBox)), ENV->dBout[2], FALSE, FALSE, 10);
	
	/* Fusion MenuvBox dans la Fenetre */
	gtk_container_add(GTK_CONTAINER(ENV->Menu), ENV->MenuvBox);
	
	gtk_widget_show_all(ENV->Menu);
	
	/* Connection du bouton et du bouton Destroy */
	gtk_signal_connect(GTK_OBJECT(ENV->Menu), "destroy", G_CALLBACK(afficher_fenetre), ctr);
	gtk_signal_connect(GTK_OBJECT(ENV->dBout[2]), "clicked", G_CALLBACK(afficher_fenetre), ctr);
	
	fclose(adt);
	free(joueur);
}

/* Fonctin qui sauvegarde les score des deux joueurs actuels dans le fichier*/
void sauvegarder_score(GtkWidget* Item, ctr_s* ctr)
{
	FILE* adt1, *adt2;
	char* pch;
	joueur_s* joueur = malloc(13*sizeof(joueur_s));
	
	/* Fichier contenant les scores */
	if((adt1 = fopen("users.dat", "r")) == NULL)
	{
		perror("Fichier unsers.dat non ouvert");
		/* si l'utilisateur a supprime le fichier apres l'ouverture du programme on en cree un nouveau */
		if((adt1 = fopen("users.dat", "w")) == NULL)
		{
			perror("Creation du fichier users.dat impossible");
			exit (-1);
		}
		fclose(adt1);
		if((adt1 = fopen("users.dat", "r")) == NULL)
		{
			perror("Fichier unsers.dat non ouvert");
			exit (-1);
		}
	}
	/* Fichier de substitution */
	if((adt2 = fopen("tmp", "w")) == NULL)
	{
		perror("Fichier tmp non ouvert");
		exit (-1);
	}
	
		
	/** On met le nom des joueurs au debut du fichier pour la prochaine partie
	 ** Clean up du nom des joueurs saisi :
 	 ** il ne faut pas d'espaces dans le fichier! **/
	
		/*  On pointe les espaces et on les remplaces par des '_' jusqu'a la fin de la chaine */
		pch =strchr(JOUEUR_1->nom, ' ');
		while(pch != NULL)
		{
			*pch = '_';
			pch =strchr(JOUEUR_1->nom, ' ');
		}
		/* pui on ecrit dans le fichier */
		fprintf(adt2, "%s %d\n", JOUEUR_1->nom, JOUEUR_1->score);
	

		/*  On pointe les espaces et on les remplaces par des '_' jusqu'a la fin de la chaine */
		pch =strchr(JOUEUR_2->nom, ' ');
		while(pch != NULL)
		{
			*pch = '_';
			pch =strchr(JOUEUR_2->nom, ' ');
		}
		/* pui on ecrit dans le fichier */
		fprintf(adt2, "%s %d\n", JOUEUR_2->nom, JOUEUR_2->score);
	
		
	
	while(!feof(adt1))
	{
		/* on lit le fichier actuel */
		fscanf(adt1, "%s", joueur->nom);
		fscanf(adt1, "%d", &joueur->score);
		if(joueur->nom != NULL && !feof(adt1))
		{
			/* Comparaison si on tombe sur un joueur existant on ne l'ecrit pas */
			if((strcmp(JOUEUR_1->nom, joueur->nom) !=0) && (strcmp(JOUEUR_2->nom, joueur->nom) !=0))
			{
					/* si le joueur lu n'est aucun des deux on reecrit son nom et son score passé */
					fprintf(adt2, "%s %d\n", joueur->nom, joueur->score);
			}
		}
	}
	
	/* on fini par un saut de ligne en plus et liberer la memoire des variables */
	fprintf(adt2, "\n");
	fclose(adt1);
	fclose(adt2);
	free(joueur);
	/* on supprime l'ancien fichier et renome le nouveau */
	remove("users.dat");
	rename("tmp", "users.dat");
}

/* Menu pour activer ou desactiver le joueur artificiel */
void menu_IA(GtkWidget* MenuItem, ctr_s *ctr)
{
	FILE* adt;
	gtk_widget_set_sensitive(ENV->Fenetre, FALSE);
	
	if((adt = fopen("users.dat", "r")) == NULL)
	{
		perror("Fichier users.dat non ouvert");
		/* si l'utilisateur a supprime le fichier apres l'ouverture du programme on en cree un nouveau */
		if((adt = fopen("users.dat", "w")) == NULL)
		{
			perror("Creation du fichier users.dat impossible");
			exit (-1);
		}
		fclose(adt);
		if((adt = fopen("users.dat", "r")) == NULL)
		{
			perror("Fichier unsers.dat non ouvert");
			exit (-1);
		}
	}
	
	
	
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
				
				if(strcmp("Int. Art.", JOUEUR_2->nom) !=0)
				{
					strcpy(JOUEUR_2->nom, "Int._Art.");
					JOUEUR_2->score = 0;
				}
				if(partie_get_tourjoueur(PARTIE) == CASE_ETAT_JOUEUR_2)
					gtk_jouer_colonne( ENV->Bouton[rand()% dim_get_nbcol(&(PARTIE->dim))], ctr);
			}
			if(ctr->IA == FALSE)
			{
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