#ifndef WAVEH
#define WAVEH
#include "SoundSamples.h"
#include <string>
#include <stdio.h>
#include <math.h>
using namespace std;

class Wave {
    public:
        Wave(string n);
        SoundSamples * generateSamples(float frequency, float samplerate, float duration);
        virtual float generateFunction(float time)=0;
        virtual void setFrequency(float freq)=0;
        virtual void setSampleRate(float sr)=0;
    private:
        string name;
};


class SineWave : public Wave {
    public:
        SineWave(string n) : Wave(n) {
        }
        float generateFunction(float time);
        void setFrequency(float freq);
        void setSampleRate(float sr);

    private:
        float frequency = 0;
        float sampleRate = 0;
};


class SquareWave : public Wave {
public:
    SquareWave(string n) : Wave(n) {
    }
    float generateFunction(float time);
    void setFrequency(float freq);
    void setSampleRate(float sr);

    private:
        float frequency = 0;
        float sampleRate = 0;
};

class TriangleWave : public Wave {
public:
    TriangleWave(string n) : Wave(n) {
    }
    float generateFunction(float time);
    void setFrequency(float freq);
    void setSampleRate(float sr);

    private:
        float frequency = 0;
        float sampleRate = 0;
};

class SawtoothWave : public Wave {
public:
    SawtoothWave(string n) : Wave(n) {
    }
    float generateFunction(float time);
    void setFrequency(float freq);
    void setSampleRate(float sr);

    private:
        float frequency = 0;
        float sampleRate = 0;
};

#endif