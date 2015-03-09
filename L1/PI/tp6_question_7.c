/* Question 7 du mini projet
 * Temps recherche sequentiel :
 * 0.0000s - 0.0800s 
 * 	Moyenne : 0.0400s
 * 
 * Temps recherche dichotomique :
 * 0.0000s - 0.0040s 
 * 	Moyenne : 0.0020s
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
	#include <sys/resource.h>
	#include <unistd.h>

struct evaluation_s {
	unsigned int utilisateur;
	unsigned int film;
	unsigned int note;
	unsigned int date;
};

double temps_CPU()
{
	struct rusage usage;

	getrusage(RUSAGE_SELF, &usage);
	return usage.ru_utime.tv_sec + (usage.ru_utime.tv_usec / 1000000.0);
}

void annee2nbsec( int, time_t *);
void nbsec2date(time_t, int *, int *, int *);
long int first_eval_seq(int debut, FILE* adt);
long int first_eval_dicho(int debut, FILE* adt);

int main(int argc, char * argv[]) 
{
	double START, END;
	START = temps_CPU();
	/* verification du nombre de parametres transmis sur la ligne de commande */
	if (3 > argc) {
		printf("USAGE: %s <ficher d'evaluation trie.bin> <annee du film>\n", argv[0]);
		exit(0);
	}
	int annee, position;
	
	FILE* adt;
	adt = fopen(argv[1], "r");
	if (NULL == adt) 
	{
		perror("echec ouverture fichier");
		exit(-1);
	}
	
	annee = atoi(argv[2]);
	
	puts("Evaluation Sequentielle");
	position = first_eval_seq(annee, adt);
	if(position == -1)
	    printf("Aucunes evaluations n'a eu lieu en %d\n", annee);
	else
	    printf("L'evaluation est en %d eme position\n", position);
	END = temps_CPU();
	printf("\nTemps CPU de la recherche sequentielle : %.4f s\n", END-START);
	
	START = temps_CPU();
	puts("Evaluation Dichotomique");
	position = first_eval_dicho(annee, adt);
	if(position == -1)
	    printf("Aucunes evaluations n'a eu lieu en %d\n", annee);
	else
	    printf("L'evaluation est en %d eme position\n", position);
	
	END = temps_CPU();
	printf("\nTemps CPU de la recherche dichotomique : %.4f s\n", END-START);
	
	return EXIT_SUCCESS;
}

long int first_eval_seq(int debut, FILE* adt)
{
    time_t n1, n2;
	 int j, m, a, cur_pos = 1;
	 int fin = debut + 1;
	
    struct evaluation_s i;
    annee2nbsec(debut, &n1);
    annee2nbsec(fin, &n2);
    nbsec2date( n1,  &j,  &m,  &a);
	n2 = n2-1;
    nbsec2date( n2,  &j,  &m,  &a);
	
	
    fread(&i, sizeof(struct evaluation_s), 1, adt);
    
    while( !feof(adt))
    {
	if( i.date >= n1)
	{
	    nbsec2date( i.date,  &j,  &m,  &a);
	    printf("La premiere evaluation a eu lieu le : %d/%d/%d\n", j, m, a);
	    return cur_pos;
	}

	    
	fread(&i, sizeof(struct evaluation_s), 1, adt);
	cur_pos = cur_pos + 1;
    }
	
    return -1;
}

long int first_eval_dicho(int debut, FILE* adt)
{
    time_t n1, n2, n3;
	 int j, m, a, 
		fin = debut + 1,
		mil = 0,
		set=0, 
		end;
	
    struct evaluation_s i;
    annee2nbsec(debut, &n1);
    annee2nbsec(fin, &n2);
    nbsec2date( n1,  &j,  &m,  &a);
	n2 = n2-1;
    nbsec2date( n2,  &j,  &m,  &a);
	
    fseek(adt, mil*sizeof(struct evaluation_s), SEEK_END);
    end = ftell(adt)/sizeof(struct evaluation_s);
    mil = set + (end - set)/2;
    fseek(adt, mil*sizeof(struct evaluation_s), SEEK_SET);
    
    n3 = n2;
    fread(&i, sizeof(struct evaluation_s), 1, adt);
    
    while( !feof(adt))
    {
	
	
	    if(i.date >= n1 && i.date <= n3)
	    {
		end = mil + 1;
		n3 = i.date;
	    }
	    if(i.date < n1)
	    {
		set = mil+1;
	    }
	    if(i.date > n3) 
	    {
		end = mil + 1;
	    }
	    
	if(mil == set+1 && mil == end - 1 && (i.date >= n1 && i.date <= n2))
	{
	    // on verifie si nous avons rien oublie avant
	    fseek(adt, -2*sizeof(struct evaluation_s), SEEK_CUR);
	    fread(&i, sizeof(struct evaluation_s), 1, adt);
	    if(i.date < n1)
		fread(&i, sizeof(struct evaluation_s), 1, adt);
	    
	    nbsec2date( i.date,  &j,  &m,  &a);
	    printf("La premiere evaluation a eu lieu le : %d/%d/%d\n", j, m, a);
	    return ftell(adt)/sizeof(struct evaluation_s);
	    
	}
	
	mil = set + ((end - set)/2);
	fseek(adt, mil*sizeof(struct evaluation_s), SEEK_SET);
	    
	fread(&i, sizeof(struct evaluation_s), 1, adt);
	if(feof(adt))
	    break;
	
    }
    
    
	
    return -1;
}

void annee2nbsec(int a, time_t * n) {
	struct tm t;
	t.tm_sec   = 0;        /* secondes */
	t.tm_min   = 0;        /* minutes */
	t.tm_hour  = 1;        /* heures */
	t.tm_mday  = 1;        /* jour */
	t.tm_mon   = 0;    /* nb mois depuis janvier */
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

