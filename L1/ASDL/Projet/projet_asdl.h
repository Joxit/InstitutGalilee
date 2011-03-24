/* ______________________________________________________________________________
	Projet A.S.D.L par MAGLOIRE Jones
	Lignes RATP de paris
    
	Version 1.0 : 	- mise en place du projet
			- Création des fonctions de base
______________________________________________________________________________ */

# ifndef PROJET_ASDL_H

	typedef struct 
	{
		char* nom;
		int ouvert; // boolean indiquant si la station est ouverte ou fermee au public 
	} station_t;

	typedef struct liste_pStations_s {
		station_t *s;
		struct liste_pStations_s* next;
	} liste_pStations_t;

	/* initialise le tableau toutes_les_lignes avec des NULL */
	void initialisation(liste_pStations_t** toutes_les_lignes);
	// Fonctionalitées de l'agent RATP
	/* crée une nouvelle structure station_t rajoute cette structure à toutes_les_stations */
	liste_pStations_t* ajout_station(char* nom_station, liste_pStations_t* ligne);
	// Retire une station d'une ligne
	liste_pStations_t* retirer_station(char* nom_station, liste_pStations_t* ligne);
	// Ajoute une ligne
	void ajout_ligne(int numero_ligne, liste_pStations_t** toutes_les_lignes);
	
	void retirer_station_carte(char* nom_station, liste_pStations_t** toutes_les_lignes);	
	// Retire une ligne completement
	liste_pStations_t* retirer_une_ligne(liste_pStations_t* ligne);
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
	void recherche_intineraires(char* depart,char* arriver, liste_pStations_t** toutes_les_lignes); 
	// affiche les stations de la ligne ligne
	void liste_station(liste_pStations_t** toutes_les_lignes); 
	// Affiche le nom de toutes les stations de toutes les lignes	
	void liste_station_de_toutes_les_lignes(liste_pStations_t** toutes_les_lignes);
	// Affiche les lignes qui sont ouverte pour nom_station	
	void get_station_ouverte(char* nom_station, liste_pStations_t** toutes_les_lignes);
	// test la ligne avec 1 si elle est ouverte et 0 si elle est fermée; mini 2 stations ouvertes
	int ligne_ouverte(liste_pStations_t* lignes); 
	
	void station_dans_ligne(liste_pStations_t ligne);
	// toutes les lignes d'une station
	void ligne_station(char* nom_station, liste_pStations_t** toutes_les_lignes); 
	// Autorisation des caracteres
	int allow_chaine(char* station);  
	// clean up chaines de caracteres
	char* clean(char* nom);
	
	int est_voisin(char* station1, char* station2, liste_pStations_t** toutes_les_lignes);

	
	liste_pStations_t* ligne1(liste_pStations_t* ligne);
	liste_pStations_t* ligne2(liste_pStations_t* ligne);
	
	void Affichage1();
	void Affichage2();
#endif

