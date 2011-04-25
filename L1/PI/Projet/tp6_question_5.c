/* Question 5 du mini-projet
 *
 * - La déclaration de la fonctions est imposée par l'énoncé.
 *
 * - L'instruction "return" met fin à l'exécution des instructions d'une
 *   fonction pour reprendre l'exécution de la séquences d'instructions de la
 *   fonction appelante ; il n'est pas nécessaire de mettre de "else" si un
 *   "return" est placé dans la partie "alors" d'une structure de contrôle
 *   conditionnelle.
 *
 * - La fonction main permet de tester si la fonction s'exécute correctement.
 */

#include <stdlib.h>
#include <stdio.h>

struct evaluation_s {
	unsigned int utilisateur;
	unsigned int film;
	unsigned int note;
	unsigned int date;
};

int comparer_evaluation(struct evaluation_s *, struct evaluation_s *);


int main(int argc, char * argv[]) {
	struct evaluation_s x, y;

	/* initialisation de la 1ere structure évaluation */
	x.utilisateur = 1;
	x.film        = 1;
	x.note        = 2;
	x.date        = 86400000;
	
	/* initialisation de la 1ere structure évaluation */
	y.utilisateur = 1;
	y.film        = 1;
	y.note        = 4;
	y.date        = 86400000;
	
	/* affichage des valeurs de valeurs de x et y */
	printf("user : %u ; film : %u ; note : %u ; date : %u\n", x.utilisateur, x.film, x.note, x.date);
	printf("user : %u ; film : %u ; note : %u ; date : %u\n", y.utilisateur, y.film, y.note, y.date);
	
	/* affichage des valeurs de retour de la fonction de comparaison */
	printf("x < x : %d\n", comparer_evaluation(&x, &x));
	printf("y < y : %d\n", comparer_evaluation(&y, &y));
	printf("x < y : %d\n", comparer_evaluation(&x, &y));
	printf("y < x : %d\n", comparer_evaluation(&y, &x));	
	
	return EXIT_SUCCESS;
}


int comparer_evaluation(struct evaluation_s * e1, struct evaluation_s * e2) {
	if (e1->date < e2->date) {
		return 1;
	}
	if (e1->date > e2->date) {
		return (-1);
	}
	/* egalite des dates */
	if (e1->film < e2->film) {
		return 1;
	}
	if (e1->film > e2->film) {
		return (-1);
	}
	/* egalite des dates et des identifiants de film */
	if (e1->utilisateur < e2->utilisateur) {
		return 1;
	}
	if (e1->utilisateur > e2->utilisateur) {
		return (-1);
	}
	/* egalite des dates, des identifiants de film et d'utilisateur */
	if (e1->note < e2->note) {
		return 1;
	}
	if (e1->note > e2->note) {
		return (-1);
	}
	/* egalite de tous les champs */
	return 0;
}

