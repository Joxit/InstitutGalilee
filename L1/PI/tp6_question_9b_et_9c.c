/* Question 9b et 9c du mini projet
 * Temps recherche sequentielle :
 * 	0.0000s pour film = 1 - 0.0900s pour film = 3952
 * 	 Moyenne = 0.0450s
 * Temps recherche dichotomique :
 * 	0.0000s pour film = 1 - 0.0000s pour film = 3952
 * 	 Moyenne = 0.0000s
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

// Question 9b
long int first_eval_seq(int film, FILE* adt);
long int first_eval_dicho(int film, FILE* adt);
// Question 9c
void repartition_notes(int id_film, FILE* adt, int* tab, int position);

int main(int argc, char * argv[])
{
	double START, END;
	/* verification du nombre de parametres transmis sur la ligne de commande */
	if (2 > argc) {
		printf("USAGE: %s <identifiant du film>\n", argv[0]);
		exit(0);
	}
	int film, position;
	int tab[5] = {0, 0, 0, 0, 0};
	
	FILE* adt;
	adt = fopen("index.bin", "r");
	if (NULL == adt)
	{
		perror("echec ouverture fichier");
		exit(-1);
	}
	
	film = atoi(argv[1]);
	
	START = temps_CPU();
	printf("Evaluation Sequentielle pour %d\n", film);
	position = first_eval_seq(film, adt);
	if(position == -1)
	    printf("Aucunes evaluations n'a eu lieu pour %d\n", film);
	else
	    printf("L'evaluation est en %d eme position\n", position);
	
	repartition_notes(film, adt, tab, position);
	END = temps_CPU();
	printf("\nTemps CPU de la recherche sequentielle : %.4f s\n", END-START);
	
	START = temps_CPU();
	printf("\nEvaluation Dichotomique pour %d\n", film);
	position = first_eval_dicho(film, adt);
	if(position == -1)
	    printf("Aucunes evaluations n'a eu lieu pour %d\n", film);
	else
	    printf("L'evaluation est en %d eme position\n", position);
	
	repartition_notes(film, adt, tab, position);
	END = temps_CPU();
	printf("\nTemps CPU de la recherche dichotomique : %.4f s\n", END-START);
	
	return EXIT_SUCCESS;
}

long int first_eval_seq(int film, FILE* adt)
{
	 int cur_pos = 1;
	
    struct evaluation_s i;
	
	
    fread(&i, sizeof(struct evaluation_s), 1, adt);

    while( !feof(adt))//( i.date < n1 && i.date > n2)||
    {
	if( i.film == film)
	{
	    return cur_pos;
	}

	
	fread(&i, sizeof(struct evaluation_s), 1, adt);
	cur_pos = cur_pos + 1;
    }
	
    return -1;
}

long int first_eval_dicho(int film, FILE* adt)
{
	 int	mil = 0,
		set=0,
		end;
	
    struct evaluation_s i;
	
    fseek(adt, mil*sizeof(struct evaluation_s), SEEK_END);
    end = ftell(adt)/sizeof(struct evaluation_s);
    mil = set + (end - set)/2;
    fseek(adt, mil*sizeof(struct evaluation_s), SEEK_SET);

    fread(&i, sizeof(struct evaluation_s), 1, adt);

    while( !feof(adt))
    {
	
	
	    if(i.film >= film && i.film <= film)
	    {
		end = mil + 1;
	    }
	    if(i.film < film)
	    {
		set = mil+1;
	    }
	    if(i.film > film)
	    {
		end = mil + 1;
	    }
	
	if(mil == set+1 && mil == end - 1 && i.film == film)
	{
	    // on verifie si nous avons rien oublie avant
	    fseek(adt, -2*sizeof(struct evaluation_s), SEEK_CUR);
	    fread(&i, sizeof(struct evaluation_s), 1, adt);
	    if(i.film < film)
		fread(&i, sizeof(struct evaluation_s), 1, adt);
	
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


void repartition_notes(int film, FILE* adt, int* tab, int position)
{
	tab[0] = 0;
	tab[1] = 0;
	tab[2] = 0;
	tab[3] = 0;
	tab[4] = 0;
	struct evaluation_s i;
	fseek(adt, -sizeof(struct evaluation_s), SEEK_CUR);
	fread(&i, sizeof(struct evaluation_s), 1, adt);
	while(i.film == film)
	{
	        switch(i.note)
		{
		    case 1:
			tab[0] = tab[0] + 1;
			break;
		    case 2:
			tab[1] = tab[1] + 1;
			break;
		    case 3:
			tab[2] = tab[2] + 1;
			break;
		    case 4:
			tab[3] = tab[3] + 1;
			break;
		    case 5:
			tab[4] = tab[4] + 1;
			break;
		}
		if(feof(adt))
		    break;
	
	fread(&i, sizeof(struct evaluation_s), 1, adt);
	}
	
	printf("Il y a eu %d votes : \n", tab[0]+tab[1]+tab[2]+tab[3]+tab[4]);
	    printf("\t 1/5 : %d votes\n", tab[0]);
	    printf("\t 2/5 : %d votes\n", tab[1]);
	    printf("\t 3/5 : %d votes\n", tab[2]);
	    printf("\t 4/5 : %d votes\n", tab[3]);
	    printf("\t 5/5 : %d votes\n", tab[4]);
}