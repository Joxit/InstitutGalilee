/* Question 4 du mini-projet
 *
 * - L'énoncé autorise plusieurs choix pour la déclaration de la fonctions ; les
 *   plus naturels sont doute :
 *      . void evaluation_txt2bin(char *, char *);
 *      . void evaluation_txt2bin(FILE *, FILE *);
 *   C'est la deuxième possibilité qui est retenue ici car elle permet la
 *   lecture des données au clavier via l'adresse de tampon prédéfinie "stdin".
 *
 * - Quand on manipule des fichiers, il ne faut pas oublier les points suivants
 *      . la fonction feof ne renvoie "vrai" qu'après une tentative d'accès au
 *        dela de la fin du fichier
 *      . fscanf renvoie le nombre d'elements correctement lus
 *      . fwrite renvoie le nombre d'éléments correctement écrits et pas le
 *        nombre d'octets écrits !
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

void evaluation_txt2bin(FILE *, FILE *);


int main(int argc, char * argv[]) {
	FILE *fbin, *ftxt;

	/* verification du nombre de parametres transmis sur la ligne de commande */
	if (3 > argc) {
		printf("USAGE: %s <fichier.txt> <fichier.bin>\n", argv[0]);
		exit(0);
	}
	
	/* ouverture du fichier texte */
	ftxt = fopen(argv[1], "r");
	if (NULL == ftxt) {
		perror("echec ouverture fichier texte");
		exit(-1);
	}
	/* ouverture du fichier binaire */
	fbin = fopen(argv[2], "w");
	if (NULL == fbin) {
		perror("echec ouverture fichier binaire");
		exit(-1);
	}
	
	/* appel de la fonction de conversion */
	evaluation_txt2bin(ftxt, fbin);

	/* fermeture des fichiers prealablement ouverts */	
	fclose(fbin);
	fclose(ftxt);
	
	return EXIT_SUCCESS;
}


void evaluation_txt2bin(FILE * ftxt, FILE * fbin) {
	struct evaluation_s e;
	int lu, ecrit;
	lu = fscanf(ftxt, "%u %u %u %u", &(e.utilisateur), &(e.film), &(e.note), &(e.date));
	while ( (4 == lu) && ! feof(ftxt) ) {
		ecrit = fwrite(&e, sizeof(struct evaluation_s), 1, fbin);
		if (1 > ecrit) {
			perror("echec de l'ecriture dans le fichier binaire");
			exit(-1);
		}
		lu = fscanf(ftxt, "%u %u %u %u", &(e.utilisateur), &(e.film), &(e.note), &(e.date));
	}
}

