#include "SoundSamples.h"
#include "wave.h"
#include "soundio.h"
#include <iostream>
#include <string>
#include <math.h>
#include <limits>

using namespace std;

int main() {

    //Sets the sample rate for the program and creates the initial sound sample that will store all the sound samples
    //made through every note
    float sampleRate = 8000;
    SoundSamples initial = SoundSamples(0, sampleRate);

    int type;
    cout << "Type: " << endl;
    cin >> type;

    float delay;
    cout << "Delay: " << endl;
    cin >> delay;

    float attenuation;
    cout << "Attenuation: " << endl;
    cin >> attenuation;

    float atime;
    cout << "atime: " << endl;
    cin >> atime;

    float alevel;
    cout << "alevel: " << endl;
    cin >> alevel;

    float dtime;
    cout << "dtime: " << endl;
    cin >> dtime;

    float slevel;
    cout << "slevel: " << endl;
    cin >> slevel;

    float rtime;
    cout << "rtime: " << endl;
    cin >> rtime;

    string filename;
    cout << "filename: " << endl;
    cin >> filename;

    int key = 0;
    cout << "key(s): " << endl;
    cin >> key;

    int iteration = 0;

    while (true) {
        //Break for if key is less than 0
        if (key < 0) break;

        //Gets the keys number and converts to the correct frequency
        float key2 = pow(2,(float)(key - 49.00)/12.00) * 440.00;

        /**
         * This goes through every wave type. If creates the wave, and then the sound for that wave using key2,
         * sampleRate and 1 for a duration. Then it puts the sound through adsr and reverb2 based on the input
         * the user previously input. Then it creates a temporary sound that is the new sound appended onto the
         * initial sound. Then it sets the initial sound equal to the temporary one.
         */
        if (type == 1) {
            //Makes a sine wave and puts it through adsr
            Wave *w = new SineWave("Sine");
            SoundSamples *wPtr = w->generateSamples(key2,sampleRate,1);
            wPtr->adsr(atime, alevel, dtime, slevel, rtime);

            //This is for handling errors that could happen in adsr. It finds the negative length (since that would
            //never happen normally) and depending on the number it throws the error.
            if (wPtr->getLength() == -1) {
                cerr << "atime, dtime and rtime added together are longer than the length of the total sample time" << endl;
                return 1;
            }
            if (wPtr->getLength() == -2) {
                cerr << "atime (" << atime << ") must be positive." << endl;
                return 1;
            }
            if (wPtr->getLength() == -3) {
                cerr << "dtime (" << dtime << ") must be positive." << endl;
                return 1;
            }
            if (wPtr->getLength() == -4) {
                cerr << "rtime (" << rtime << ") must be positive." << endl;
                return 1;
            }

            //Puts the sine sound through reverb2
            wPtr->reverb2(delay, attenuation);

            //This is for handling errors that could happen in reverb2. It finds the negative length (since that would
            //never happen normally) and depending on the number it throws the error.
            if (wPtr->getLength() == -1) {
                cerr << "The delay is " << delay << ". It needs to be greater than or equal to 0." << endl;
                return 1;
            }
            if (wPtr->getLength() == -2) {
                cerr << "The attenuation is " << attenuation << ". It needs to be greater than or equal to 0." << endl;
                return 1;
            }

            //Creates a sound sample equal to the initial wave plus the one just made and sets the initial equal to
            //the one that was just made
            SoundSamples temp = initial + *(wPtr);
            initial = temp;
        } else if (type == 2) {
            //Makes a square wave and puts it through adsr
            Wave *w = new SquareWave("Square");
            SoundSamples *wPtr = w->generateSamples(key2,sampleRate,1);
            wPtr->adsr(atime, alevel, dtime, slevel, rtime);

            //This is for handling errors that could happen in adsr. It finds the negative length (since that would
            //never happen normally) and depending on the number it throws the error.
            if (wPtr->getLength() == -1) {
                cerr << "atime, dtime and rtime added together are longer than the length of the total sample time" << endl;
                return 1;
            }
            if (wPtr->getLength() == -2) {
                cerr << "atime (" << atime << ") must be positive." << endl;
                return 1;
            }
            if (wPtr->getLength() == -3) {
                cerr << "dtime (" << dtime << ") must be positive." << endl;
                return 1;
            }
            if (wPtr->getLength() == -4) {
                cerr << "rtime (" << rtime << ") must be positive." << endl;
                return 1;
            }

            //Puts the square sound through reverb2
            wPtr->reverb2(delay, attenuation);

            //This is for handling errors that could happen in reverb2. It finds the negative length (since that would
            //never happen normally) and depending on the number it throws the error.
            if (wPtr->getLength() == -1) {
                cerr << "The delay is " << delay << ". It needs to be greater than or equal to 0." << endl;
                return 1;
            }
            if (wPtr->getLength() == -2) {
                cerr << "The attenuation is " << attenuation << ". It needs to be greater than or equal to 0." << endl;
                return 1;
            }

            //Creates a sound sample equal to the initial wave plus the one just made and sets the initial equal to
            //the one that was just made
            SoundSamples temp = initial + *(wPtr);
            initial = temp;
        } else if (type == 3) {
            //Makes a triangle wave and puts it through adsr
            Wave *w = new TriangleWave("Triangle");
            SoundSamples *wPtr = w->generateSamples(key2,sampleRate,1);
            wPtr->adsr(atime, alevel, dtime, slevel, rtime);

            //This is for handling errors that could happen in adsr. It finds the negative length (since that would
            //never happen normally) and depending on the number it throws the error.
            if (wPtr->getLength() == -1) {
                cerr << "atime, dtime and rtime added together are longer than the length of the total sample time" << endl;
                return 1;
            }
            if (wPtr->getLength() == -2) {
                cerr << "atime (" << atime << ") must be positive." << endl;
                return 1;
            }
            if (wPtr->getLength() == -3) {
                cerr << "dtime (" << dtime << ") must be positive." << endl;
                return 1;
            }
            if (wPtr->getLength() == -4) {
                cerr << "rtime (" << rtime << ") must be positive." << endl;
                return 1;
            }

            //Puts the triangle sound through reverb2
            wPtr->reverb2(delay, attenuation);

            //This is for handling errors that could happen in reverb2. It finds the negative length (since that would
            //never happen normally) and depending on the number it throws the error.
            if (wPtr->getLength() == -1) {
                cerr << "The delay is " << delay << ". It needs to be greater than or equal to 0." << endl;
                return 1;
            }
            if (wPtr->getLength() == -2) {
                cerr << "The attenuation is " << attenuation << ". It needs to be greater than or equal to 0." << endl;
                return 1;
            }

            //Creates a sound sample equal to the initial wave plus the one just made and sets the initial equal to
            //the one that was just made
            SoundSamples temp = initial + *(wPtr);
            initial = temp;
        } else if (type == 4) {
            //Makes a sawtooth wave and puts it through adsr
            Wave *w = new SawtoothWave("Sawtooth");
            SoundSamples *wPtr = w->generateSamples(key2,sampleRate,1);
            wPtr->adsr(atime, alevel, dtime, slevel, rtime);

            //This is for handling errors that could happen in adsr. It finds the negative length (since that would
            //never happen normally) and depending on the number it throws the error.
            if (wPtr->getLength() == -1) {
                cerr << "atime, dtime and rtime added together are longer than the length of the total sample time" << endl;
                return 1;
            }
            if (wPtr->getLength() == -2) {
                cerr << "atime (" << atime << ") must be positive." << endl;
                return 1;
            }
            if (wPtr->getLength() == -3) {
                cerr << "dtime (" << dtime << ") must be positive." << endl;
                return 1;
            }
            if (wPtr->getLength() == -4) {
                cerr << "rtime (" << rtime << ") must be positive." << endl;
                return 1;
            }

            //Puts the sawtooth sound through reverb2
            wPtr->reverb2(delay, attenuation);

            //This is for handling errors that could happen in reverb2. It finds the negative length (since that would
            //never happen normally) and depending on the number it throws the error.
            if (wPtr->getLength() == -1) {
                cerr << "The delay is " << delay << ". It needs to be greater than or equal to 0." << endl;
                return 1;
            }
            if (wPtr->getLength() == -2) {
                cerr << "The attenuation is " << attenuation << ". It needs to be greater than or equal to 0." << endl;
                return 1;
            }

            //Creates a sound sample equal to the initial wave plus the one just made and sets the initial equal to
            //the one that was just made
            SoundSamples temp = initial + *(wPtr);
            initial = temp;
        } else {
            //This handles the error for if the wave type is invalid
            cerr << "The type (" << type  << ") is out of bounds" << endl;
            return 1;
        }

        //Created blank noise of the silence that is .25 seconds long and adds it to initial
        SoundSamples silence = SoundSamples(sampleRate * .25, sampleRate);
        SoundSamples temp = initial + silence;
        initial = temp;

        //Clears the buffer and then takes in the next key
        //Then it adds one to the iteration and checks if key is negative to break the while loop
        cin.ignore();
        cin >> key;
        iteration = iteration + 1;
        if (key < 0) break;
    }

    /**
     * If loop to handle the the number of iterations. If there are no iterations it prints to an empty file,
     * else if there was at least one interation it prints the initial sound sample to the specified output file
     */
    if (iteration == 0) {
        SoundSamples * empty = new SoundSamples();
        SoundIO::OutputSound(empty, filename);
    } else {
        SoundIO::OutputSound(&initial, filename);
    }

    return 0;
}