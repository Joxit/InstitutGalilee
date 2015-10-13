/* MAGLOIRE JONES
 * Version 1.0
 * Mardi 29 mars
 */

#include <stdio.h>   /* printf et puts */
#include <stdlib.h>  /* EXIT_SUCCESS */
#define LGMAX_TITRE 84
struct film
{
	unsigned int annee;
	unsigned int id;
	unsigned int genre;
	char titre[LGMAX_TITRE];
};

struct evaluation_s {
	unsigned int utilisateur;
	unsigned int film;
	unsigned int note;
	unsigned int date;
};

// Question 1
void afficher_genre(struct film_s *);

// Question 2
void date2nbsec(int, int, int, time_t *);

// Question 3
void nbsec2date(time_t, int *, int *, int *);

// Question 4
void evaluation_txt2bin(FILE *, FILE *);

// Question 5
int comparer_evaluation(struct evaluation_s *, struct evaluation_s *);


/*==========================================  definition de la fonction main */
int main(int argc, char * argv[])
{
	struct film* film = (struct film*)malloc(sizeof(struct film));
	film->annee = 1995;
	film->id = 1;
	film->genre = (unsigned int)malloc(sizeof(unsigned int));
	film->genre = 57344; // 2^13+2^14+2^15
	
	show_genre(film);
	
	
	return EXIT_SUCCESS;
}
// Affichage des genres
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

// Transforme une date en nombre de secondes
void date2nbsec(int j, int m, int a, time_t * n) {
	struct tm t;
	t.tm_sec   = 0;        /* secondes */
	t.tm_min   = 0;        /* minutes */
	t.tm_hour  = 0;        /* heures */
	t.tm_mday  = j;        /* jour */
	t.tm_mon   = m - 1;    /* nb mois depuis janvier */
	t.tm_year  = a - 1900; /* nb annees depuis 1900 */
	t.tm_isdst = -1;       /* info inconnue */
	*n = mktime(& t);
}

// Transforme un nombre de seconde en date
void nbsec2date(time_t n, int * pj, int * pm, int * pa) {
	struct tm * t = gmtime(& n);
	if (NULL == t) {
		puts("nbsec2date : erreur de conversion");
		return;
	}
	*pj = t->tm_mday;
	*pm = t->tm_mon  + 1;
	*pa = t->tm_year + 1900;
}

// Transforme un fichier texte en binaire
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

// compare deyx evaluations de deux personnes
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














