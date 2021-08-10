all: main_a main_b

main_a: main.o SoundSamples.o wave.o soundio.o
	g++ main.o SoundSamples.o wave.o soundio.o -o main_a -lm

main_b: TestMain.o SoundSamples.o wave.o soundio.o
	g++ TestMain.o SoundSamples.o wave.o soundio.o -o main_b -lm

main.o: main.cpp
	g++ -c main.cpp

TestMain.o: TestMain.cpp
	g++ -c TestMain.cpp

SoundSamples.o: SoundSamples.cpp
	g++ -c SoundSamples.cpp

wave.o: wave.cpp
	g++ -c wave.cpp

soundio.o: soundio.cpp
	g++ -c soundio.cpp

clean:
	rm *.o main_a main_b