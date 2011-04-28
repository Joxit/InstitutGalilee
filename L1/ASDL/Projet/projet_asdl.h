/* ______________________________________________________________________________
	Projet A.S.D.L par MAGLOIRE Jones 11000369 et DELCOURT Rémi 11002398
	Lignes RATP de paris
    
 	Mardi 19 Avril 2011	
			
______________________________________________________________________________ */

# ifndef PROJET_ASDL_H

#define TRUE 1
#define FALSE 0
#define NB_LIGNES 17
#define MOTDEPASSE "Elodie"

	typedef struct 
	{
		char* nom;	 // nom de la station
		int id;		 // id de la station
		int ouvert;	 // boolean indiquant si la station est ouverte(1) ou fermee(0) au public 
	} station_t;

	typedef struct liste_pStations_s {
		station_t *s;
		struct liste_pStations_s* next;
	} liste_pStations_t;

	
	
	/* ****************************** *
	 * DEFINITIONS DANS : actions.c   * 
	 *   Fonctions de creation et     *
	 *     d'action pour l'agent      *
	 * ****************************** */ 
	
	    /* ****************** *
	     * Mise en place du   *
	     *    réseau RATP     *
	     * ****************** */
	    
	// Création d'une ligne
	liste_pStations_t* ajout_ligne(int numero_ligne, liste_pStations_t* toutes_les_lignes,FILE* adt);
	// Création de la liste de totues les stations
	liste_pStations_t*  liste_station(liste_pStations_t* toutes_les_stations, liste_pStations_t** toutes_les_lignes); 
	
	void est_voisin(int id1, int id2, liste_pStations_t** toutes_les_lignes,int** voisin,int**  distance);
	
	// Affecte à toutes les stations de toutes_les_lignes leurs id
	void set_id(liste_pStations_t** toutes_les_lignes);
	
	void set_distance(liste_pStations_t* toutes_les_lignes[], int** voisin, int** distance);
	
	
	    /* ********************* *
	     * Fonctionalitees pour  *
	     *      l'agent RATP     *
	     * ********************* */
	    
	/* Fonction sur les lignes */
	// Met ouvert = 1 à toutes les stations de la ligne 
	liste_pStations_t* ouvrir_ligne(liste_pStations_t* ligne);
	// Met ouvert = 0 à toutes les stations de la ligne 	
	liste_pStations_t* fermer_ligne(liste_pStations_t* ligne);
		
	/* Fonctions sur les stations */
	// Crée une nouvelle structure liste_pStations_t* et l'ajoute à ligne
	liste_pStations_t* ajout_station(char* nom_station, liste_pStations_t* ligne);
	// Retire une station d'une ligne
	liste_pStations_t* retirer_station(char* nom_station, liste_pStations_t* ligne);
	// Retire une station du réseau RATP
	void retirer_station_carte(char* nom_station, liste_pStations_t** toutes_les_lignes);	
	// Met 1 à nom_station de la ligne 
	void ouvrir_station(char* nom_station, liste_pStations_t* ligne);
	// Met 0 à nom_station de la ligne 	
	void fermer_station(char* nom_station, liste_pStations_t* ligne);
	
	
	
	/* ****************************** 
	 * DEFINITIONS DANS : infos.c   *
	 *   Fonctions d'information    *
	 *       pour l'agent et        *
	 *        l'utilisateur         *
	 * ******************************/ 
	
	    /* ********************* *
	    * Fonctionalitées pour   *
	    *   l'utilisateur x :    *
	    * ********************** */
	 
	// Affiche l'itineraire entre depart et arrivee. la fonction prend les id des stations
	void  recherche_intineraires(int depart, int arrivee,/*int** voisin,*/ int** distance, liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations); 
	
	/* Fonctions sur lignes */
	// Affiche le nom de toutes les stations de toutes les lignes	
	void liste_station_de_toutes_les_lignes(liste_pStations_t** toutes_les_lignes);
	// Test la ligne avec 1 si elle est ouverte et 0 si elle est fermée; mini 2 stations ouvertes
	int ligne_ouverte(liste_pStations_t ligne); 
	// affiche les stations de ligne
	void station_dans_ligne(liste_pStations_t ligne);	
	
	/* Fonctions sur les stations */ 
	// Affiche toutes les lignes qui sont ouverte pour nom_station	
	void get_station_ouverte(char* nom_station, liste_pStations_t** toutes_les_lignes);
	// Toutes les lignes d'une station
	int ligne_station(char* nom_station, liste_pStations_t** toutes_les_lignes); 
	
	// Calcul du temps CPU
	double temps_CPU();
	
	
	
	/* *************************** *
	 * DEFINITIONS DANS : aide.c   *
	 * Fonctions de comunication   *
	 *    entre la machine et      *
	 *        l'utilisateur        *
	 * *************************** */ 
	
	
	    /* ********************* *
	     * Fonctions basées sur  *
	     * les id des stations   *
	     * ********************* */
	    
	// renvoie l'id de la station la plus proche d'arrivee sur la ligne de depart
	int id_proche(int depart, int arrivee, liste_pStations_t ligne, int** distance);
	// prend le nom_station et renvoie l'id de celle ci
	int get_id(char* nom_station, liste_pStations_t toutes_les_stations);
	// prend une id et renvoie le nom_station de celle ci
	char* get_nom_station(int id, liste_pStations_t toutes_les_stations);
	
	    /* ************************* *
	    * Fonctions de lecture  du   *
	    *  choix de l'utilisateur    *
	    * ************************** */
	    
	// demande le choix de la ligne a l'utilisateur
	int get_choix();
	// Demande le choix du nom de la station a l'utilisateur
	char* get_choix_station(liste_pStations_t toutes_les_stations);
	
	    /* ***************************** *
	    * Fonctions de retranscription   *
	    *        du numero_ligne         *
	    * ****************************** */
	    
	// Prend en argument la valeur du tableau toutes_les_lignes et renvoie le vrais numero_ligne
	int get_num_ligne(int i);
	// Prend en argument le vrais numero_ligne et renvoie la valeur pour le tableau toutes_les_lignes 
	int choix_num_ligne(int i);
	
	int is_open(liste_pStations_t ligne);
	
	/* *************************** *
	 * DEFINITIONS DANS : menu.c   *
	 *   Fonctions d'interface     *
	 *   pour les utilisateurs     *
	 * *************************** */ 
	
	// Menu principal et de l'agent R.A.T.P
	void Menu1(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations, int** voisin, int** distance);
	void Menu2(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations, int** voisin, int** distance);
	// Sous-Menus Info et Action (R.A.T.P) pour les lignes et stations
	void Info_Ligne(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations);
	void Info_Station(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations);
	void Action_Ligne(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations);
	void Action_Station(liste_pStations_t** toutes_les_lignes, liste_pStations_t toutes_les_stations);
	void purger ();
#endif

