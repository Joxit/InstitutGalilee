# _______________________________
# Projet A.S.D.L pour la R.A.T.P
# _______________________________

#all: projet
projet: projet_asdl.o lignes.o menu.o main.o
	gcc projet_asdl.o lignes.o menu.o main.o -o projet -Wall

#_______________________________
# modèle
#projet_asdl.h: 
#projet_asdl.c: projet_asdl.h
projet_asdl.o: projet_asdl.c
	gcc -c projet_asdl.c -o projet_asdl.o -Wall
	 
#lignes.c: projet_asdl.h
lignes.o: lignes.c
	gcc -c lignes.c -o lignes.o -Wall

#menu.c: projet_asdl.h
menu.o: main.c
	gcc -c menu.c -o menu.o -Wall

#main.c: projet_asdl.h
main.o: main.c
	gcc -c main.c -o main.o -Wall

	
	
# nettoyage
clean: 
	rm *.o
