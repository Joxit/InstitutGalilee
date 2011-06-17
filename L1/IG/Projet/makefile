# _________________
# jeu de puissance4
# _________________

projet: gtk_puissance4.o partie.o dim.o case.o main.o menu.o IA.o
	gcc gtk_puissance4.o menu.o partie.o dim.o case.o IA.o main.o `pkg-config --cflags --libs gtk+-2.0` -o projet.exe
# _________________
# modèle
case.h: 
case.c: case.h
case.o: case.c
	gcc -c case.c -o case.o -Wall --pedantic 

dim.h: 
dim.c: dim.h
dim.o: dim.c
	gcc -c dim.c -o dim.o -Wall --pedantic 

partie.h: case.h dim.h
partie.c: partie.h case.h dim.h
partie.o: partie.c
	gcc -c partie.c -o partie.o -Wall --pedantic 

# _________________
# gtk 

# jeu & exécutable gtk
gtk_puissance4.h: partie.h
gtk_puissance4.c: partie.h gtk_puissance4.h
gtk_puissance4.o: gtk_puissance4.c
	gcc -c gtk_puissance4.c `pkg-config --cflags --libs gtk+-2.0` -o gtk_puissance4.o -Wall --pedantic 
	
menu.c: partie.h gtk_puissance4.h
menu.o: menu.c
	gcc -c menu.c `pkg-config --cflags --libs gtk+-2.0` -o menu.o -Wall --pedantic 

gtk_init.c: partie.h gtk_puissance4.h
main.o: gtk_init.c
	gcc -c gtk_init.c `pkg-config --cflags --libs gtk+-2.0` -o main.o -Wall --pedantic


IA.c: partie.h gtk_puissance4.h
IA.o: IA.c
	gcc -c IA.c `pkg-config --cflags --libs gtk+-2.0` -o IA.o -Wall --pedantic
	
# nettoyage
clean: 
	rm *.o

mrproper: clean
	rm *.exe

