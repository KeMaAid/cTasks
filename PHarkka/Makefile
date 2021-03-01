ohjelma.exe: paaohjelma.o ali1.o 
	gcc -o ohjelma.exe paaohjelma.o ali1.o

paaohjelma.o: paaohjelma.c ali1.o
	gcc -c paaohjelma.c paaohjelma.c ali1.o -Wall std=c99

ali1.o: ali1.c ali1.h ali2.o
	gcc -c ali1.c ali1.h ali2.o -Wall -std=c99

ali2.o: ali2.c ali2.h
	gcc -c ali2.c ali2.h -Wall -std=c99




