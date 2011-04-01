/* ______________________________________________________________________________
	Projet A.S.D.L par MAGLOIRE Jones 11000369 et DELCOURT Rémi 11002398
	Lignes RATP de paris
    
	Version 1.0 :
			- mise en place du projet
			- Création des fonctions de base
			- Creation du mot de passe pour l'agent RATP
			- Recherche itineraire : 
					- Cas de base itineraire sur la meme ligne
					- quitte la fonction si depart = arrivee
			- seulement lignes 1 et 2 implementees
	Version 1.1 :
			- Changement de l'affichage en fonction recursive
			- Ajout des sous choix utilisateur et de l'agent R.A.T.P
			- Fix ::
				- ligne_station
				- get_station_ouverte
				- ligne_ouverte
				- ouvrir_station/fermer_station
				- retirer_station_carte
			- Implantation ligne 3
			- Ajout de securité dans station_dans_ligne et ligne_ouverte
			- reorganisation de projet_asdl.h et projet_asdl.c ::
 				- création de sous fichiers menu.c et lignes.c pour alléger projet_asdl.c
 				
 	Vendredi 1 Avril 2011	
			
______________________________________________________________________________ */

# ifndef PROJET_ASDL_H

#define TRUE 1
#define FALSE 0
#define NB_STATION 6
#define MOTDEPASSE "Joxit"

	typedef struct 
	{
		char* nom; // nom de la station
		int id; // id de la station
		int ouvert; // boolean indiquant si la station est ouverte ou fermee au public 
	} station_t;

	typedef struct liste_pStations_s {
		station_t *s;
		struct liste_pStations_s* next;
	} liste_pStations_t;

	/* DEFINITIONS DANS : projet_adsl.c */ 
	
	/* initialise le tableau toutes_les_lignes avec des NULL */
	liste_pStations_t** initialisation(liste_pStations_t** toutes_les_lignes);
	
	/* Fonctionalitées de l'agent RATP */
	/* Fonction sur les lignes */
	// Ajoute une ligne
	liste_pStations_t* ajout_ligne(int numero_ligne, liste_pStations_t** toutes_les_lignes);
	// Retire une ligne du reseau
	void retirer_ligne(int numero_ligne, liste_pStations_t** toutes_les_lignes);	
	// met 1 a nom_station de la ligne 
	liste_pStations_t* ouvrir_ligne(liste_pStations_t* ligne);
	// met 0 a nom_station de la ligne 	
	liste_pStations_t* fermer_ligne(liste_pStations_t* ligne);
	
	/* Fonctions sur les stations */
	// crée une nouvelle structure station_t rajoute cette structure à toutes_les_stations 
	liste_pStations_t* ajout_station(char* nom_station, liste_pStations_t* ligne,liste_pStations_t** toutes_les_lignes, int* id, int n);
	// Retire une station d'une ligne
	liste_pStations_t* retirer_station(char* nom_station, liste_pStations_t* ligne);
	// Retire une station du reseau
	void retirer_station_carte(char* nom_station, liste_pStations_t** toutes_les_lignes);	
	// met 1 a nom_station de la ligne 
	void ouvrir_station(char* nom_station, liste_pStations_t* ligne);
	// met 0 a nom_station de la ligne 	
	void fermer_station(char* nom_station, liste_pStations_t* ligne);
	
	/* renvoie un pointeur sur la station dont le nom est donnée en paramètre, ou NULL si erreur*/
	station_t* rechercher_station(char* nom_station, liste_pStations_t** toutes_les_lignes);
	
	/* ajoute a la fin de la ligne i la station s. (on suppose que cette station est déjà référencée dans toutes_les_stations */
	station_t ajout_station_en_fin_ligne(station_t* s,int i, liste_pStations_t** toutes_les_lignes);
	 

	// fonctionalitées pour l'utilisateur x :
	// liste stations entre A et B
	void recherche_intineraires(char* depart,char* arriver, liste_pStations_t* ligne); 
	
	/* Fonctions sur Stations */ 
	// Affiche les lignes qui sont ouverte pour nom_station	
	void get_station_ouverte(char* nom_station, liste_pStations_t** toutes_les_lignes);
	// toutes les lignes d'une station
	void ligne_station(char* nom_station, liste_pStations_t** toutes_les_lignes); 

	
	/* Fonctions sur lignes */
	void liste_station(liste_pStations_t** toutes_les_lignes); 
	// Affiche le nom de toutes les stations de toutes les lignes	
	void liste_station_de_toutes_les_lignes(liste_pStations_t** toutes_les_lignes);
	// test la ligne avec 1 si elle est ouverte et 0 si elle est fermée; mini 2 stations ouvertes
	int ligne_ouverte(liste_pStations_t* ligne); 
	// affiche les stations de la ligne ligne
	void station_dans_ligne(liste_pStations_t ligne);
	
	
	// Autorisation des caracteres
	int allow_chaine(char* station);  
	// clean up chaines de caracteres
	char* clean(char* nom);
	// Boolean qui renvoie TRUE si les stations son voisines FALSE sinon
	int est_voisin(char* station1, char* station2, liste_pStations_t** toutes_les_lignes);
	
	liste_pStations_t** set_id(liste_pStations_t** toutes_les_lignes);

	/* DEFINITIONS DANS : lignes.c */ 
		
	liste_pStations_t* ligne1(liste_pStations_t* ligne,liste_pStations_t** toutes_les_lignes, int* id, int n);
	liste_pStations_t* ligne2(liste_pStations_t* ligne,liste_pStations_t** toutes_les_lignes, int* id, int n);
	liste_pStations_t* ligne3(liste_pStations_t* ligne,liste_pStations_t** toutes_les_lignes, int* id, int n);
	liste_pStations_t* ligne4(liste_pStations_t* ligne,liste_pStations_t** toutes_les_lignes, int* id, int n);
	liste_pStations_t* ligne5(liste_pStations_t* ligne,liste_pStations_t** toutes_les_lignes, int* id, int n);
	liste_pStations_t* ligne6(liste_pStations_t* ligne,liste_pStations_t** toutes_les_lignes, int* id, int n);
	
	/* DEFINITIONS DANS : menu.c */ 	
	
	void Menu1(liste_pStations_t** toutes_les_lignes);
	void Menu2(liste_pStations_t** toutes_les_lignes);
	void Info_Ligne(liste_pStations_t** toutes_les_lignes);
	void Info_Station(liste_pStations_t** toutes_les_lignes);
	void Action_Ligne(liste_pStations_t** toutes_les_lignes);
	void Action_Station(liste_pStations_t** toutes_les_lignes);
	void purger ();
#endif

