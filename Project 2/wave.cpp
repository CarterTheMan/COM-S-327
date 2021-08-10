#include "wave.h"
#include "SoundSamples.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/**
 * A constructor for the Wave class that sets the name of the Wave
 *
 * @param n
 */
Wave::Wave(string n) {
    name = n;
}

/**
 * A method that takes input of frequency, samplerate and duration to make a SoundSamples.
 * This method sets the frequency and samplerate in all derived classes and then uses
 * the generateFunction class to make the samples of the returned SoundSamples
 *
 * @param frequency
 * @param samplerate
 * @param duration
 * @return returned
 */
SoundSamples * Wave::generateSamples(float frequency, float samplerate, float duration) {
    int length = (int)round(samplerate * duration);
    setFrequency(frequency);
    setSampleRate(samplerate);

    float forSound[length];
    for (int i = 0; i < length; i++) {
        forSound[i] = generateFunction(i);
    }

    SoundSamples * returned = new SoundSamples(forSound, length, samplerate);

    return returned;
}

//All methods for the SineWave

/**
 * Returns a samples of a sine wave from a specific point in time
 *
 * @param time
 * @return sin((2 * M_PI / sampleRate * frequency) * time)
 */
float SineWave::generateFunction(float time) {
    return sin((2 * M_PI / sampleRate * frequency) * time);
}

/**
 * Sets the frequency of the sine wave
 *
 * @param freq
 */
void SineWave::setFrequency(float freq) {
    frequency = freq;
}

/**
 * Sets the sampleRate of the sine wave
 *
 * @param sr
 */
void SineWave::setSampleRate(float sr) {
    sampleRate = sr;
}

//All methods for the square wave

/**
 * Returns a samples of a square wave from a specific point in time
 *
 * @param time
 * @return 0, 1, or -1
 */
float SquareWave::generateFunction(float time) {
    float temp = sin((2 * M_PI / sampleRate * frequency) * time);

    //The following if statement is for super small numbers that should be 0 but aren't due to
    //PI not being exact
    if (temp >= 0.000001) {
        return 1;
    } else if (temp <= -0.000001) {
        return -1;
    } else {
        return 0;
    }
}

/**
 * Sets the frequency of the square wave
 *
 * @param freq
 */
void SquareWave::setFrequency(float freq) {
    frequency = freq;
}

/**
 * Sets the sampleRate of a square wave
 *
 * @param sr
 */
void SquareWave::setSampleRate(float sr) {
    sampleRate = sr;
}

//All methods for the triangle wave

/**
 * Returns a samples of a triangle wave from a specific point in time
 *
 * @param time
 * @return (2 / M_PI) * asin(sin(2 * M_PI * time / (sampleRate / frequency)))
 */
float TriangleWave::generateFunction(float time) {
    return (2 / M_PI) * asin(sin(2 * M_PI * time / (sampleRate / frequency)));
}

/**
 * Sets the frequency of a triangle wave
 *
 * @param freq
 */
void TriangleWave::setFrequency(float freq) {
    frequency = freq;
}

/**
 * Sets the sampleRate of a triangle wave
 *
 * @param sr
 */
void TriangleWave::setSampleRate(float sr) {
    sampleRate = sr;
}

//Methods for a sawtooth wave

/**
 * Returns a samples of a sawtooth wave from a specific point in time
 *
 * @param time
 * @return (-2 / M_PI) * atan(cos(time * M_PI / (sampleRate / frequency)) / sin(time * M_PI / (sampleRate / frequency)))
 */
float SawtoothWave::generateFunction(float time) {
    return (-2 / M_PI) * atan(cos(time * M_PI / (sampleRate / frequency)) / sin(time * M_PI / (sampleRate / frequency)));
}

/**
 * Sets the frequency of a sawtooth wave
 *
 * @param freq
 */
void SawtoothWave::setFrequency(float freq) {
    frequency = freq;
}

/**
 * Sets the sampleRate of a sawtooth wave
 *
 * @param sr
 */
void SawtoothWave::setSampleRate(float sr) {
    sampleRate = sr;
}