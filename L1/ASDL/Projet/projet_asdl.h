/* ______________________________________________________________________________
	Projet A.S.D.L par MAGLOIRE Jones 11000369 et DELCOURT Rémi 11002398
	Lignes RATP de paris
    
 	Vendredi 1 Avril 2011	
			
______________________________________________________________________________ */

# ifndef PROJET_ASDL_H

#define TRUE 1
#define FALSE 0
#define NB_LIGNES 17
#define MOTDEPASSE "Elodie"

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

	/* DEFINITIONS DANS : actions.c */ 
	
	// création de la liste de totues les stations
	liste_pStations_t*  liste_station(liste_pStations_t* toutes_les_stations, liste_pStations_t** toutes_les_lignes); 
	
	/* Fonctionalitées de l'agent RATP */
	/* Fonction sur les lignes */
	// Ajoute une ligne
	liste_pStations_t* ajout_ligne(int numero_ligne, liste_pStations_t* toutes_les_lignes,FILE* adt);
	// met 1 a nom_station de la ligne 
	liste_pStations_t* ouvrir_ligne(liste_pStations_t* ligne);
	// met 0 a nom_station de la ligne 	
	liste_pStations_t* fermer_ligne(liste_pStations_t* ligne);
	
	
	/* Fonctions sur les stations */
	// crée une nouvelle structure station_t rajoute cette structure à toutes_les_stations 
	liste_pStations_t* ajout_station(char* nom_station, liste_pStations_t* ligne);
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
	 
	/* DEFINITIONS DANS : infos.c */ 
	// fonctionalitées pour l'utilisateur x :
	// Itineraire entre A et B
	void  recherche_intineraires(int depart, int arrivee,int** voisin, int** distance, liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations); 
	
	/* Fonctions sur Stations */ 
	// Affiche les lignes qui sont ouverte pour nom_station	
	void get_station_ouverte(char* nom_station, liste_pStations_t** toutes_les_lignes);
	// toutes les lignes d'une station
	int ligne_station(char* nom_station, liste_pStations_t** toutes_les_lignes); 

	
	/* Fonctions sur lignes */
	// Affiche le nom de toutes les stations de toutes les lignes	
	void liste_station_de_toutes_les_lignes(liste_pStations_t** toutes_les_lignes);
	// test la ligne avec 1 si elle est ouverte et 0 si elle est fermée; mini 2 stations ouvertes
	int ligne_ouverte(liste_pStations_t ligne); 
	// affiche les stations de la ligne ligne
	void station_dans_ligne(liste_pStations_t ligne);
	
	
	/* DEFINITIONS DANS : proget_asdl.c */ 
	/* Fonctions Interface Homme - Machine */
	// prend en argument la valeur du tableau toutes_les_lignes et renvoie le vrais numero_ligne
	int get_num_ligne(int i);
	// prend en argument le vrais numero_ligne et renvoie la valeur pour le tableau toutes_les_lignes 
	int choix_num_ligne(int i);
	// demande le choix de la ligne a l'utilisateur
	int get_choix(int choix);
	char* get_choix_station(int choix, liste_pStations_t toutes_les_stations);
	
	/* Fonctions basées sur les id des stations */
	// Boolean qui renvoie TRUE si les stations son voisines FALSE sinon
	int est_voisin(int id1, int id2, liste_pStations_t** toutes_les_lignes);
	// Affecte a toutes les stations de toutes les lignes leurs id
	void set_id(liste_pStations_t** toutes_les_lignes);
	// prend le nom_station et renvoie l'id de celle ci
	int get_id(char* nom_station, liste_pStations_t toutes_les_stations);
	// prend une id et renvoie le nom_station de celle ci
	char* get_nom_station(int id, liste_pStations_t toutes_les_stations);
	// renvoie l'id de la station la plus proche d'arrivee sur la ligne de depart
	int id_proche(int depart, int arrivee, liste_pStations_t ligne, int** distance);

	/* DEFINITIONS DANS : menu.c 
	 * Interface Utilisateur */ 	
	// Menu principal et de l'agent R.A.T.P
	void Menu1(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations, int**, int**);
	void Menu2(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations);
	// Sous-Menus Info et Action (R.A.T.P) pour les lignes et stations
	void Info_Ligne(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations);
	void Info_Station(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations);
	void Action_Ligne(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations);
	void Action_Station(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations);
	void purger ();
#endif

