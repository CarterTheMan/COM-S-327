#include "SoundSamples.h"
#include "wave.h"
#include "soundio.h"
#include <iostream>
#include <string>
using namespace std;

int main() {

    int type;
    cin >> type;

    float samplerate;
    cin >> samplerate;

    float frequency;
    cin >> frequency;

    float duration;
    cin >> duration;

    string filename;
    cin >> filename;

    /**
     * For each type of wave, it creates that wave with the name of the Wave created being the type of wave it is,
     * i.e. Sinewaves are named Sine, and then it generates the a SoundSample based on the wave selected with
     * the input of frequency, samplerate and duration. Then it prints all the samples in that wave to an output
     * file whose name was specified by the input. If the type the user inputs doesn't match a type of wave then
     * it prints out that the waves type is  out of bounds and returns 1;
     */
    if (type == 1) {
        Wave *w = new SineWave("Sine");
        SoundSamples *wPtr = w->generateSamples(frequency,samplerate,duration);
        SoundIO::OutputSound(wPtr, filename);
    } else if (type == 2) {
        Wave *w = new SquareWave("Square");
        SoundSamples *wPtr = w->generateSamples(frequency,samplerate,duration);
        SoundIO::OutputSound(wPtr, filename);
    } else if (type == 3) {
        Wave *w = new TriangleWave("Triangle");
        SoundSamples *wPtr = w->generateSamples(frequency,samplerate,duration);
        SoundIO::OutputSound(wPtr, filename);
    } else if (type == 4) {
        Wave *w = new SawtoothWave("Sawtooth");
        SoundSamples *wPtr = w->generateSamples(frequency,samplerate,duration);
        SoundIO::OutputSound(wPtr, filename);
    } else {
        cout << "The type (" << type  << ") is out of bounds" << endl;
        return 1;
    }

    return 0;
}