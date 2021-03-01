# Makefile
ohjelma.exe: paaohjelma.o ali1.o ali2.o
	gcc -o ohjelma.exe paaohjelma.o ali1.o ali2.o -Wall -std=c99

paaohjelma.o: paaohjelma.c ali1.h ali2.h
	gcc -c paaohjelma.c -Wall -std=c99

ali1.o: ali1.c ali1.h ali2.h
	gcc -c ali1.c ali1.h ali2.h -Wall -std=c99 

ali2.o: ali2.c ali2.h
	gcc -c ali2.c -Wall -std=c99 -o ali2.o




