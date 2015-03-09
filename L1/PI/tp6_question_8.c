/* Question 8 du mini projet
 * Repartition des notes d'un film
 * Fonction qui prend en argument : 
 *	- l'identification du film
 * 	- l'adresse du tampon du fichier binaire
 * 	- un tableau d'evaluation
 * Il met entre 0.0700 s et 0.0900 sc
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
	#include <sys/resource.h>
	#include <time.h>

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

void repartition_notes(int id_film, FILE* adt, int* tab);

int main(int argc, char * argv[]) {
	double START, END;
	START = temps_CPU();
	
	/* verification du nombre de parametres transmis sur la ligne de commande */
	if (3 > argc) {
		printf("USAGE: %s <ficher d'evaluation.bin> <identification du film>\n", argv[0]);
		exit(0);
	}
	
	int tab[5] = {0, 0, 0, 0, 0};
	FILE* adt;
	int id_film;
	
	id_film = atoi(argv[2]);
	
	adt = fopen(argv[1], "r");
	if (NULL == adt) 
	{
		perror("echec ouverture fichier");
		exit(-1);
	}
	

	repartition_notes(id_film, adt, tab);
	
	fclose(adt);
	END = temps_CPU();
	printf("\nCPU time : %.4f s\n", END-START);
	return EXIT_SUCCESS;
}

void repartition_notes(int id_film, FILE* adt, int* tab)
{
    
	struct evaluation_s i;
	fread(&i, sizeof(struct evaluation_s), 1, adt);
	while(!feof(adt))
	{
	    if( i.film == id_film)
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
	    
	    }
	    
	fread(&i, sizeof(struct evaluation_s), 1, adt);
	}
	
	printf("Il y a eu %d votes : \n", tab[0]+tab[1]+tab[2]+tab[3]+tab[4]);
	    printf("\t 1/5 : %d votes\n", tab[0]);
	    printf("\t 2/5 : %d votes\n", tab[1]);
	    printf("\t 3/5 : %d votes\n", tab[2]);
	    printf("\t 4/5 : %d votes\n", tab[3]);
	    printf("\t 5/5 : %d votes\n", tab[4]);
}

