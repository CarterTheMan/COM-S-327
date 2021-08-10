# -*- MakeFile -*-

#target: dependencies
#	action

all: playsong

playsong: playsong.o gensnd.o iosnd.o process.o
	gcc playsong.o gensnd.o iosnd.o process.o -o playsong -lm

playsong.o: playsong.c
	gcc -c playsong.c

gensnd.o: gensnd.c
	gcc -c gensnd.c

iosnd.o: iosnd.c
	gcc -c iosnd.c

process.o: process.c
	gcc -c process.c

clean:
	rm *.o playsong