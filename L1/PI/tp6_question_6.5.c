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

int comparer_evaluation(struct evaluation_s , struct evaluation_s );

void tri_externe(char nom[]);
int eclate(char nom[], char nom1[], char nom2[]);
void selon_n(int n, FILE* adt1, FILE* adt2, struct evaluation_s i);
int interclate(char nom[], char nom1[],char nom2[], int lg);

int main(int argc, char * argv[])
{
	
	tri_externe(argv[1]);
	return EXIT_SUCCESS;
}


void tri_externe(char nom[])
{
	int nb, n=0, L=1;
	nb = eclate(nom, "f3", "f4");
	perror("eclate");
	while(nb>1)
	{
		n = !n;
		if(n)
			nb = interclate(nom, "f3","f4", L);
		else
			nb = interclate(nom, "f3","f4", L);
		L=L*2;
	}
}

int eclate(char nom[], char nom1[], char nom2[])
{
	FILE* adt, *adt1, *adt2;
	//unsigned int i1, i2, i3, i4;
	struct evaluation_s i;
	int n=0;
	
	adt1 = fopen(nom1, "r");
	adt2 = fopen(nom2, "r");
	adt = fopen(nom, "w");
	
	//fread(&i, sizeof(struct evaluation_s), 1, adt1);
	//fscanf(adt, "%u", &i1, "%u", &i2 , "%u", &i3, "%u", &i4);
	
	while(!feof(adt1))
	{
		n = n+1;
		selon_n(n, adt1, adt2, i);		
		//selon_n(n, adt1, adt2, i1, i2, i3, i4);
		//fread(&i, sizeof(struct evaluation_s), 1, adt2);
		//fscanf(adt, "%u", &i1, "%u", &i2 , "%u", &i3, "%u", &i4);
	}
	fclose(adt);
	fclose(adt1);
	fclose(adt2);
	
	return n;
}

int interclate(char nom[], char nom1[],char nom2[], int lg)
{
	FILE *adt1, *adt2, *adt;
	int l1, l2, n = 0;
	struct evaluation_s x, y;
		
	adt1 = fopen(nom1,"r");
	adt2 = fopen(nom2,"r");
	adt = fopen(nom,"w");
	
	
	
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
			//selon_n(n, adt3, adt4, x);
			fwrite(&x, sizeof(struct evaluation_s), 1, adt);
			l1++;
			//fscanf(adt1, "%u", &x.utilisateur, "%u", &x.film , "%u", &x.note, "%u", &x.date);
			fread(&x, sizeof(struct evaluation_s), 1, adt1);
			}
			else
			{
				//selon_n(n, adt3, adt4, y.utilisateur, y.film, y.note, y.date);
				//selon_n(n, adt3, adt4, y);
				fwrite(&y, sizeof(struct evaluation_s), 1, adt);
				l2++;
				//fscanf(adt2, "%u", &y.utilisateur, "%u", &y.film , "%u", &y.note, "%u", &y.date);
				fread(&y, sizeof(struct evaluation_s), 1, adt2);
			}
		}
		while(l1< lg && !feof(adt1))
		{
			//selon_n(n, adt3, adt4, x.utilisateur, x.film, x.note, x.date);
			//selon_n(n, adt3, adt4, x);
			fwrite(&x, sizeof(struct evaluation_s), 1, adt);
			l1++;
			//fscanf(adt1, "%u", &x.utilisateur, "%u", &x.film , "%u", &x.note, "%u", &x.date);
			fread(&x, sizeof(struct evaluation_s), 1, adt1);
		}
		while(l2< lg && !feof(adt2))
		{
			//selon_n(n, adt3, adt4, y.utilisateur, y.film, y.note, y.date);
			//selon_n(n, adt3, adt4, y);
			fwrite(&y, sizeof(struct evaluation_s), 1, adt);
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
			//selon_n(n, adt3, adt4, x);
			fwrite(&x, sizeof(struct evaluation_s), 1, adt);
			//fscanf(adt1, "%u", &x.utilisateur, "%u", &x.film , "%u", &x.note, "%u", &x.date);
			fread(&x, sizeof(struct evaluation_s), 1, adt1);
		}
	}
	fclose(adt1);
	fclose(adt2);
	fclose(adt);
		
	return n;		
}
void selon_n(int n, FILE* adt1, FILE* adt2, struct evaluation_s i)
{
	if(n%2)		
		fread(&i, sizeof(struct evaluation_s), 1, adt1);
		//fprintf(adt1, "%u", &i1, "%u", &i2 , "%u", &i3, "%u", &i4);
	else
		fread(&i, sizeof(struct evaluation_s), 1, adt2);
		//fprintf(adt2, "%u", &i1, "%u", &i2 , "%u", &i3, "%u", &i4);

}


int comparer_evaluation(struct evaluation_s e1, struct evaluation_s e2) {
	if (e1.date < e2.date) {
		return 1;
	}
	if (e1.date > e2.date) {
		return (-1);
	}
	/* egalite des dates */
	if (e1.film < e2.film) {
		return 1;
	}
	if (e1.film > e2.film) {
		return (-1);
	}
	/* egalite des dates et des identifiants de film */
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
