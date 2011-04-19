# _______________________________
# Projet A.S.D.L pour la R.A.T.P
# _______________________________

#all: projet
projet: aide.o menu.o main.o actions.o infos.o
	gcc aide.o actions.o infos.o menu.o main.o -o projet -Wall -lm

#_______________________________

aide.o: aide.c
	gcc -c aide.c -o aide.o -Wall

actions.o: actions.c
	gcc -c actions.c -o actions.o -Wall

infos.o: infos.c
	gcc -c infos.c -o infos.o -Wall -lm

	 
#menu.c: projet_asdl.h
menu.o: main.c
	gcc -c menu.c -o menu.o -Wall

#main.c: projet_asdl.h
main.o: main.c
	gcc -c main.c -o main.o -Wall

	
	
# nettoyage
clean: 
	rm *.o
