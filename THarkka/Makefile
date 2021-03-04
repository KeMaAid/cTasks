# Makefile for the whole program
#Tekijä Konsta Keski-Mattinen
#Opiskelijanumero: 0568752
#Päivämäärä 21-03-04

ohjelma.exe: paaohjelma.o ali1.o ali2.o
	gcc -o ohjelma.exe -g paaohjelma.o ali1.o ali2.o -Wall -std=c99

paaohjelma.o: paaohjelma.c ali1.h ali2.h
	gcc -c -g paaohjelma.c -Wall -std=c99

ali1.o: ali1.c ali1.h ali2.h
	gcc -c -g ali1.c ali1.h ali2.h -Wall -std=c99 

ali2.o: ali2.c ali2.h ali1.h
	gcc -c -g ali2.c ali2.h ali1.h -Wall -std=c99




