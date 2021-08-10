#ifndef SOUNDSAMPLESH
#define SOUNDSAMPLESH

#include <string>
using namespace std;

class SoundSamples {
    public:
        SoundSamples();
        SoundSamples(float *, int, float);
        SoundSamples(int, float);
        float getSampleRate() const;
        SoundSamples(const SoundSamples& origClass);
        const SoundSamples& operator=(const SoundSamples& rhs);
        int getLength() const;
        float& operator[](int index);
        SoundSamples operator+(SoundSamples& rhs);
        void returnSamples() const;
        float returnSample(int) const;
        void reverb2(float delay, float attenuation);
        void adsr(float atime, float alevel, float dtime, float slevel, float rtime);
    private:
        float sampleRate;
        int length;
        float * samples;
};

#endif