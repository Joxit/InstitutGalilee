/* Question 1 du mini-projet
 *
 * - La déclaration de la fonction est imposée par l'énoncé.
 *
 * - La fonction prend en argument un pointeur. Si on modifie le champs "genre"
 *   de la structure dont l'adresse est passée en argument, ces modifications
 *   seront "visibles" à l'extérieur de la fonction ; cet effet de bord n'est
 *   pas souhaitable et on commence par affecter la valeur de ce champs à une
 *   variable locale g.
 *
 * - On déclare ensuite un tableau de chaînes de caractères pour stocker le
 *   nom des genres à afficher. Le nom le plus long est "Documentary" qui
 *   compte 11 caractères auquel s'ajoute le caractère '\0' de fin de chaine ;
 *   on aurait pu indiquer que le tableau des genres avait 18 lignes mais il
 *   est permis de l'omettre car on initialise le tableau à sa déclaration.
 *
 * - On remarque le mot-clef "static" devant la déclaration du tableau ; cela
 *   indique que les donnees de ce tableau seront placées dans la zone mémoire
 *   réservée aux données statiques. Si on omet le mot clef "static", le tableau
 *   est placé sur la pile comme toutes les variables locales, et il faut
 *   l'initialiser à chaque appel de la fonction afficher_genre ; cela peut
 *   être coûteux s'il y a beaucoup d'appels...
 *
 * - La variable "i" est utilisée pour connaitre le numéro du bit qu'on est en
 *   train de tester ; le bit de poids faible porte le numéro 0.
 *
 * - Pour le decodage du champs genre, on s'intéresse au 18 bits de poids
 *   faibles ; on accède au bit de poids faible en regardant la valeur de
 *   l'entier modulo 2 et on divise par 2 pour effectuer un décalage de tous
 *   les bits d'un position vers la droite (le bit de poids faible est perdu).
 *   On aurait pu utiliser une boucle "for" car on connait le nombre
 *   d'itérations avant de rentrer dans la boucle. Néanmoins, en remarquant que
 *   lorsque l'entier vaut 0, tous les bits de sa représentation sont à 0 et
 *   qu'il est alors inutile de continuer à chercher un bit à 1, on préfère
 *   utiliser une boucle "while".
 *
 * - En langage C, il n'y a pas de type booléen/logique et on utilise des
 *   entiers pour représenter "vrai" et "faux" ; la valeur 0 correspond à "faux"
 *   et toutes les autres valeurs correspondent à "vrai". Ainsi, "(g % 2u)" (qui
 *   vaut soit 0 soit 1) correspond à "vrai" lorsque le bit de poids faible de
 *   g est positionné à 1 ; il faut afficher le nom du genre correspondant.
 *
 * - A chaque tour de boucle, on divise g par 2 pour décaler tous les bits d'une
 *   position vers la droite et on incrémente la variable pour i pour savoir à
 *   quel bit du champs "genre" correspond le bit de poids faible de g.
 *
 * - On remarque aussi le suffixe "u" utilisé avec les entiers pour éviter les
 *   conversions implicites de type...
 *
 * - La fonction main permet de tester si la fonction est correcte.
 */

#include <stdlib.h>
#include <stdio.h>

#define LGMAX_TITRE 84

struct film_s {
	unsigned int annee;
	unsigned int id;
	unsigned int genre;
	char titre[LGMAX_TITRE];
};

void afficher_genre(struct film_s *);


int main(int argc, char * argv[]) {
	struct film_s f;
	
	if (2 > argc) {
		printf("USAGE: %s <genres_codes>\n", argv[0]);
		exit(0);
	}
	
	f.genre = atoi(argv[1]);
	afficher_genre(&f);
	putchar('\n');
	
	return EXIT_SUCCESS;
}


void afficher_genre(struct film_s * f) {
	unsigned int g = f->genre;
	static char genres[][12] = { "Action",      "Adventure", "Animation",
	                             "Children's",  "Comedy",    "Crime",
	                             "Documentary", "Drama",     "Fantasy",
	                             "Film-Noir",   "Horror",    "Musical",
	                             "Mystery",     "Romance",   "Sci-Fi",
	                             "Thriller",    "War",       "Western" };
	int i = 0;
	
	while (g > 0u) {
		if (g % 2u) {
			printf("%s ", genres[i]);
		}
		i = i + 1;
		g = g / 2u;
	}
}

