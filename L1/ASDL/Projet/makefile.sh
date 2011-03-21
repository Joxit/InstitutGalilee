gcc -c projet_asdl.c -o projet_asdl.o -Wall
gcc -c main.c -o main.o -Wall

gcc projet_asdl.o main.o -o projet -Wall
