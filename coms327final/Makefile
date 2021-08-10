all: candy

candy: main.o candy.o
	g++ main.o candy.o -o candy

main.o: main.cpp
	g++ -c main.cpp

candy.o: candy.cpp
	g++ -c candy.cpp

clean:
	rm *.o candy
