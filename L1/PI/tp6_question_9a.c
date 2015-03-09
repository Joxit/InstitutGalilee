/* Question 6 du mini projet
 * Le resultat du tri se trouve dans f1
 * Renomage de f1 pour l'utilisateur
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

int comparer_evaluation(struct evaluation_s , struct evaluation_s );

void tri_externe(char nom[]);
int eclate(char nom[], char nom1[], char nom2[]);
void selon_n(int n, FILE* adt1, FILE* adt2, struct evaluation_s i);
int interclate(char nom1[], char nom2[],char nom3[], char nom4[], int lg);

int main(int argc, char * argv[]) 
{
	double START, END;
	START = temps_CPU();
	int boolean;
	
	if (2 > argc) {
		printf("USAGE: %s <fichier a trier.bin>\n", argv[0]);
		exit(0);
	}
	
	tri_externe(argv[1]);
	
	boolean = rename("f1", "index.bin");
	if( 0 != boolean)
	    perror("le renomage a echoue");
	boolean = remove("f2");
	if( 0 != boolean)
	    perror("la suppression a echoue");
	boolean = remove("f3");
	if( 0 != boolean)
	    perror("la suppression a echoue");
	boolean = remove("f4");
	if( 0 != boolean)
	    perror("la suppression a echoue");

	END = temps_CPU();
	printf("Tri execute avec succes. CPU time : %.4f s\n", END-START);
	return EXIT_SUCCESS;
}


void tri_externe(char nom[])
{
	int nb, n=0, L=1;
	nb = eclate(nom, "f1", "f2");
	
	while(nb>1)
	{
		n = !n;
		if(n)
			nb = interclate("f1","f2", "f3", "f4", L);
		else
			nb = interclate("f3","f4", "f1", "f2", L);
		L=L*2;
	}
}

int eclate(char nom[], char nom1[], char nom2[])
{
	FILE* adt, *adt1, *adt2;
	//unsigned int i1, i2, i3, i4;
	struct evaluation_s i;
	int n=0;
	
	adt1 = fopen(nom1, "w");
	if (NULL == adt1) 
	{
		perror("echec ouverture fichier");
		exit(-1);
	}
	adt2 = fopen(nom2, "w");
	if (NULL == adt2) 
	{
		perror("echec ouverture fichier");
		exit(-1);
	}
	adt = fopen(nom, "r");
	if (NULL == adt) 
	{
		perror("echec ouverture fichier");
		exit(-1);
	}
	
	fread(&i, sizeof(struct evaluation_s), 1, adt);
	//fscanf(adt, "%u", &i1, "%u", &i2 , "%u", &i3, "%u", &i4);
	
	while(!feof(adt))
	{
		n = n+1;
		selon_n(n, adt1, adt2, i);		
		//selon_n(n, adt1, adt2, i1, i2, i3, i4);
		fread(&i, sizeof(struct evaluation_s), 1, adt);
		//fscanf(adt, "%u", &i1, "%u", &i2 , "%u", &i3, "%u", &i4);
	}
	fclose(adt);
	fclose(adt1);
	fclose(adt2);
	
	return n;
}

int interclate(char nom1[], char nom2[],char nom3[], char nom4[], int lg)
{
	FILE *adt1, *adt2, *adt3, *adt4;
	int l1, l2, n = 0;
	struct evaluation_s x, y;
		
	adt1 = fopen(nom1,"r");
	if (NULL == adt1) 
	{
		perror("echec ouverture fichier");
		exit(-1);
	}
	adt2 = fopen(nom2,"r");
	if (NULL == adt2) 
	{
		perror("echec ouverture fichier");
		exit(-1);
	}
	adt3 = fopen(nom3,"w");
	if (NULL == adt3) 
	{
		perror("echec ouverture fichier");
		exit(-1);
	}
	adt4 = fopen(nom4,"w");
	if (NULL == adt4) 
	{
		perror("echec ouverture fichier");
		exit(-1);
	}
	
	
	
	fread(&x, sizeof(struct evaluation_s), 1, adt1);	
	fread(&y, sizeof(struct evaluation_s), 1, adt2);
	//fscanf(adt1, "%u", &x.utilisateur, "%u", &x.film , "%u", &x.note, "%u", &x.date);
	//fscanf(adt2, "%u", &y.utilisateur, "%u", &y.film , "%u", &y.note, "%u", &y.date);
	
	do
	{
	n++;
	l1 = 0; 
	l2 = 0;
		while(l1< lg && l2< lg && !feof(adt1) && !feof(adt2))
		{
			if( comparer_evaluation(x, y) > 0)
			{
			//selon_n(n, adt3, adt4, x.utilisateur, x.film, x.note, x.date);
			selon_n(n, adt3, adt4, x);
			l1++;
			//fscanf(adt1, "%u", &x.utilisateur, "%u", &x.film , "%u", &x.note, "%u", &x.date);
			fread(&x, sizeof(struct evaluation_s), 1, adt1);
			}
			else
			{
				//selon_n(n, adt3, adt4, y.utilisateur, y.film, y.note, y.date);
				selon_n(n, adt3, adt4, y);
				l2++;
				//fscanf(adt2, "%u", &y.utilisateur, "%u", &y.film , "%u", &y.note, "%u", &y.date);
				fread(&y, sizeof(struct evaluation_s), 1, adt2);
			}
		}
		while(l1< lg && !feof(adt1))
		{
			//selon_n(n, adt3, adt4, x.utilisateur, x.film, x.note, x.date);
			selon_n(n, adt3, adt4, x);
			l1++;
			//fscanf(adt1, "%u", &x.utilisateur, "%u", &x.film , "%u", &x.note, "%u", &x.date);
			fread(&x, sizeof(struct evaluation_s), 1, adt1);
		}
		while(l2< lg && !feof(adt2))
		{
			//selon_n(n, adt3, adt4, y.utilisateur, y.film, y.note, y.date);
			selon_n(n, adt3, adt4, y);
			l2++;
			//fscanf(adt2, "%u", &y.utilisateur, "%u", &y.film , "%u", &y.note, "%u", &y.date);
			fread(&y, sizeof(struct evaluation_s), 1, adt2);
		}
	}while(!feof(adt1)&&!feof(adt2));
		
	if(!feof(adt1))
	{
		n++;
		while(!feof(adt1))
		{
			//selon_n(n, adt3, adt4, x.utilisateur, x.film, x.note, x.date);
			selon_n(n, adt3, adt4, x);
			//fscanf(adt1, "%u", &x.utilisateur, "%u", &x.film , "%u", &x.note, "%u", &x.date);
			fread(&x, sizeof(struct evaluation_s), 1, adt1);
		}
	}
	fclose(adt1);
	fclose(adt2);
	fclose(adt3);
	fclose(adt4);
		
	return n;		
}
void selon_n(int n, FILE* adt1, FILE* adt2, struct evaluation_s i)
{
	if(n%2)		
		fwrite(&i, sizeof(struct evaluation_s), 1, adt1);
		//fprintf(adt1, "%u", &i1, "%u", &i2 , "%u", &i3, "%u", &i4);
	else
		fwrite(&i, sizeof(struct evaluation_s), 1, adt2);
		//fprintf(adt2, "%u", &i1, "%u", &i2 , "%u", &i3, "%u", &i4);

}


int comparer_evaluation(struct evaluation_s e1, struct evaluation_s e2) {
    
	if (e1.film < e2.film) {
		return 1;
	}
	if (e1.film > e2.film) {
		return (-1);
	}
	/* egalite des dates et des identifiants de film */
	if (e1.date < e2.date) {
		return 1;
	}
	if (e1.date > e2.date) {
		return (-1);
	}
	/* egalite des dates */
	if (e1.utilisateur < e2.utilisateur) {
		return 1;
	}
	if (e1.utilisateur > e2.utilisateur) {
		return (-1);
	}
	/* egalite des dates, des identifiants de film et d'utilisateur */
	if (e1.note < e2.note) {
		return 1;
	}
	if (e1.note > e2.note) {
		return (-1);
	}
	/* egalite de tous les champs */
	return 0;
}

