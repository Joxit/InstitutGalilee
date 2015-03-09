/* Questions 2 et 3 du mini-projet
 *
 * - Avant de répondre à ces deux questions, il faut lire attentivement la page
 *   de manuel de la "ctime" dans la section 3 ; elle contient toutes les
 *   informations nécessaires :
 *      . gmtime : permet de convertir un "timestamp" en date
 *      . mktime : permet de convertir une date en "timestamp"
 *   Il est aussi possible d'utiliser "ctime" et "sscanf" pour décoder la
 *   chaine de caractères renvoyée.
 *
 * - La déclaration des fonctions est imposée en partie par l'énoncé et en
 *   partie par les informations de la page de manuel mentionnée ci-dessus.
 *
 * - La fonction main permet de tester si la fonction est correcte ; elle met
 *   en évidence une subtilité du fonctionnement de la fonction mktime : son
 *   argument et la valeur renvoyée ne sont pas toujours exprimés sur le même
 *   fuseau horaire...  
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void date2nbsec(int, int, int, time_t *);
void nbsec2date(time_t, int *, int *, int *);


int main(int argc, char * argv[]) {
	int a, j, m;
	time_t n;
	
	if (2 > argc) {
		printf("USAGE: %s <timestamp>\n", argv[0]);
		exit(0);
	}
	
	n = atoi(argv[1]);
	
	nbsec2date(n, & j, & m, & a);
	printf("nbsec2date(%ld) : %d/%d/%d\n", n, j, m, a);
	
	date2nbsec(j, m, a, & n);
	printf("date2nbsec(%d/%d/%d) : %ld\n", j, m, a, n);
	
	return EXIT_SUCCESS;
}


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

