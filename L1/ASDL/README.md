# Projet - L1 Algorithmique des Structures de Données Linéaires (ASDL) - 2011

## Consignes
On veut représenter et utiliser un réseau de transport urbain. On prendra ici l'exemple du métro de Paris, mais il est évident que les mêmes structures peuvent servir à représenter un réseau d'autobus, de train, ...

Dans notre cas, on supposera qu'il y a au total 14 lignes de métro exactement. Au départ, le
logiciel ne connait pas les différentes stations ni les interconnections du réseau RATP.

### Les fonctionnalités attendues du logiciel seront les suivantes:

1. L'interface avec l'utilisateur se fera en mode texte.
   * Il y aura donc au lancement du logiciel une liste d'actions possibles, parmi lesquelles l'utilisateur fera un choix.

2. L'utilisateur sera soit un agent RATP, soit un usager.

3. Si l'utilisateur est un agent RATP, il devra pouvoir modifier le réseau.
   * En particulier, il pourra ajouter ou retirer des stations, et indiquer à quelles lignes appartiennent ces stations, et éventuellement marquer certaines stations comme «fermées au public»

4. Si l'utilisateur est un usager, il devra pouvoir demander au logiciel de lui calculer un
itinéraire.
	* Plus précisément, l'usager indiquera une station de départ, une station d'arrivée, et le programme devra lui indiquer s'il y a un itinéraire entre ces deux stations **avec au plus une correspondance** (le cas plus difficile avec plusieurs correspondances est optionnel)

### Fonctionnalités optionnelles (en bonus):

1. Une interface graphique
   	* Par exemple, un dessin du réseau avec GTK.

2. Une sauvegarde des stations et lignes de métro dans un fichier, ainsi qu'un chargement du
fichier en mémoire.

3. Un calcul du meilleur itinéraire pour se rendre d'une station A à une station B du réseau, impliquant éventuellement plusieurs correspondances.

### Implémentation - Structures de données

Les étudiants peuvent utiliser les structures de données qu'ils souhaitent. Néanmoins, voici une
suggestion de structure de données.
Une station pourra être représentée par la structure suivante:
```C
typedef struct {
	char nom [100];
	int ouvert; /* boolean indiquant si la station est ouverte ou fermee au public */
} station_t;
```

On stockera l'ensemble des stations dans une structure nommée «toutes_les_stations», et on
stockera la description des lignes de métro dans un tableau « toutes_les_lignes[14] »

Ces deux structures peuvent être représentées par exemple sous forme de listes chainées de
pointeurs:
```C
typedef struct liste_pStations_s {
	station_t *s;
	struct liste_pStations_s* next;
} liste_pStations_t;

liste_pStations_t* toutes_les_stations;
liste_pStations_t* toutes_les_lignes[14];
```

### Implémentation - Structures de données ultra-simplifiée

Pour les étudiants ayant vraiment du mal avec les listes chainées, on peut les orienter vers une
version simplifiée du projet. Par exemple, en n'utilisant que des tableaux et la structure `station_t`, le réseau de stations pourrait être représenté comme suit:
```C
station_t toutes_les_stations[200]; /* On prévoit au plus 200 stations*/
int nombre_de_stations;

/* On stocke dans toutes_les_lignes[i][j] le numéro de la jième station de la ligne i */
int toutes_les_lignes[14][20];
int nombre_de_stations_par_ligne[14];
```
##Fonctions à implémenter - (partie «agent RATP», dans le cas des listes chainées)
```C
/* initialise le tableau toutes_les_lignes avec des NULL */
void initialisation();

/* crée une nouvelle structure station_t rajoute cette structure à toutes_les_stations */
void ajout_station(char *nom_station);

/* renvoie un pointeur sur la station dont le nom est donnée en paramètre, ou NULL si erreur*/
station_t* rechercher_station(char* nom)

/* ajoute a la fin de la ligne i la station s. (on suppose que cette station est déjà référencée dans toutes_les_stations */
station_t ajout_station_en_fin_ligne(station_t* s,int i);

/* affiche les stations de la ligne i */
void afficher_stations(int i);

/* créer un main qui propose a lʼagent RATP de rentrer de nouvelles stations et de les connecter à des lignes */
int main();
```

## Comment ça marche

Bienvenue et merci de me lire.

Programme réalisé par MAGLOIRE Jones pour le projet d'Algorithmique des Structures de Données Linéaires.

### ORGANISATION

Le programme est séparé en plusieurs fichiers ::

* main.c : Fonction principale du programme

* projet_asdl.h : Déclaration des fonctions de projet_asdl.c; lignes.c; menu.c

* actions.c : Définitions des fonctions pour la création du réseau RATP et des fonctions de l'agent RATP

* infos.c : Définitions des fonctions pour l'interface utilisateur

* aide.c : Définitions des fonctions pour la cumunication entre le programme et l'utilisateur

* menu.c : Définitions des fonctions pour l'affichage du menu

* makefile.sh : compilateur

* run.sh commande de lancement du programme incluant toutes les lignes dans les fichiers

* Dossier Lignes : contient toutes les lignes de la R.A.T.P

### COMPILATION

Vous pouvez compiler en tapant
```sh
make
```
### LANCEMENT

Pour lancer le programme tapez
```sh
./run.sh
```
Il faut un code pour pour accéder aux options avancés

### RANGER

Pour suprimer les *.o
```sh
make clean
```
