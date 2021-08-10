#include "SoundSamples.h"
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

/**
 * This is a constructor for SoundSamples with no parameters
 */
SoundSamples::SoundSamples() {
    length = 0;
    sampleRate = 8000;
}

/**
 * This is a constructor for SoundSamples that takes a pointer to a float array and makes that the samples,
 * and then assigns the length and samples rate based on the two other parameters
 * @param ptr
 * @param len
 * @param sampleR
 */
SoundSamples::SoundSamples(float * ptr, int len, float sampleR) {
    length = len;
    sampleRate = sampleR;
    samples = new float[length];
    for (int i = 0; i < length; i++) {
        samples[i] = ptr[i];
    }
}

/**
 * This is a constructor for SoundSamples that takes a in a length and sample rate
 * and assigns each respectively
 *
 * @param len
 * @param sampleR
 */
SoundSamples::SoundSamples(int len, float sampleR) {
    length = len;
    sampleRate = sampleR;
    samples = new float[length];

    for (int i = 0; i < len; i++) {
        samples[i] = 0;
    }
}

/**
 * This is a method for SoundSamples that returns the sample rate of the SoundSamples
 *
 * @return sampleRate
 */
float SoundSamples::getSampleRate() const {
    return sampleRate;
}

/**
 * This is a copy constructor for SoundSamples. It provides a deep copy
 *
 * @param origClass
 */
SoundSamples::SoundSamples(const SoundSamples& origClass) {
    sampleRate = origClass.sampleRate;
    length = origClass.length;
    samples = new float[length];
    for (int i = 0; i < length; i++) {
        samples[i] = origClass.samples[i];
    }
}

/**
 * This is an operator= method for SoundSamples. It creates a deep copy based
 * on the SoundSamples it is set equal to
 *
 * @param rhs
 * @return *this
 */
const SoundSamples& SoundSamples::operator=(const SoundSamples& rhs) {
    if (this != &rhs) {
        sampleRate  = rhs.sampleRate;
        length = rhs.length;
        for (int i = 0; i < length; i++) {
            samples[i] = rhs.samples[i];
        }
    }

    return *this;
}

/**
 * This is a get method for SoundSamples that returns the length of the SoundSamples
 *
 * @return length
 */
int SoundSamples::getLength() const {
    return length;
}

/**
 * This is an overloaded operator[] for SoundSamples. It gets an index point of the sample in SoundSamples
 * that is to be changed and returns a reference float to that sample
 *
 * @param index
 * @return this->samples[index]
 */
float& SoundSamples::operator[] (int index) {
    return this->samples[index];
}

/**
 * This is an overloaded operator+ for the SoundSamples class. It appends one sample one another so it adds
 * one samples to the end of another samples. This way the returned SoundSamples has a length equal to both
 * the lengths of the SoundSamples that are used
 *
 * @param rhs
 * @return temp
 */
SoundSamples SoundSamples::operator+ (SoundSamples& rhs) {
    float forSound[length + rhs.length];
    for (int i = 0; i < length; i++) {
        forSound[i] = samples[i];
    }
    for (int i = 0; i < rhs.length; i++) {
        forSound[length + i] = rhs.samples[i];
    }

    SoundSamples temp = SoundSamples(forSound, length + rhs.length, sampleRate);

    return temp;
}

/**
 * This is a method for SoundSamples that prints out all of the samples in this to standard out
 */
void SoundSamples::returnSamples() const {
    for (int i = 0; i < length; i++) {
        cout << i << ":" << samples[i] << endl;
    }
}

/**
 * This is a method for SoundSamples that returns a sample from SoundSamples based on an index point
 * that is given in the parameters
 *
 * @param index
 * @return samples[index]
 */
float SoundSamples::returnSample(int index) const {
    return samples[index];
}

/**
 * This is a function that acts as a reverb for SoundSamples
 *
 * @param delay
 * @param attenuation
 */
void SoundSamples::reverb2(float delay, float attenuation) {
    //The following if statements are for handling errors. The length is changed to a negative number since that would
    //never happen normally and the negative number depends on the error. The main finds the changed length and
    //prints the error that occurs depending on the length.
    if (delay < 0) {
        length = -1;
        return;
    }
    if (attenuation < 0) {
        length = -2;
        return;
    }

    //This makes space for the new samples array and calculates the delay of this reverb
    float * y = new float[length];
    int sDelay = (int)round(delay * sampleRate);

    //Sets the new samples all to 0
    for (int i = 0; i < length; i++) {
        y[i] = 0;
    }

    //Uses the equation we were given to set the new samples to another number
    for (int i = 0; i < length; i++) {
        if (i - sDelay < 0) {
            y[i] = samples[i];
        } else {
            y[i] = samples[i] + (y[i - sDelay] * attenuation);
        }
    }

    //Sets the original samples equal to the new samples
    for (int i = 0; i < length; i++) {
        samples[i] = y[i];
    }
}

void SoundSamples::adsr(float atime, float alevel, float dtime, float slevel, float rtime) {
    //The following if statements are for handling errors. The length is changed to a negative number since that would
    //never happen normally and the negative number depends on the error. The main finds the changed length and
    //prints the error that occurs depending on the length.
    if ((atime + dtime + rtime) * sampleRate > length) {
        length = -1;
        return;
    }
    if (atime < 0) {
        length = -2;
        return;
    }
    if (dtime < 0) {
        length = -3;
        return;
    }
    if (rtime < 0) {
        length = -4;
        return;
    }

    //Length of the different times in number of samples
    int lenA = (int) round(sampleRate * atime);
    int lenD = (int) round(sampleRate * dtime);
    int lenR = (int) round(sampleRate * rtime);
    float midtime = (length / sampleRate) - atime - dtime - rtime;
    int lenS = (int) round(sampleRate * midtime);

    //For alevel samples
    for (int i = 0; i < lenA; i++) {
        samples[i] = samples[i] * ((alevel / lenA) * i);
    }

    //For dlevel samples
    for (int i = 0; i < lenD; i++) {
        samples[i + lenA] = samples[i + lenA] * ((-(alevel-slevel) / (lenD)) * i + alevel);
    }

    //For mid samples
    for (int i = 0; i < lenS; i++) {
        samples[lenA + lenD + i] = samples[i + lenA + lenD] * slevel;
    }

    //For rsamples
    for (int i = 0; i < lenR; i++) {
        samples[length - i - 1] = samples[length - i - 1] * ((slevel/lenR) * i);
    }

}




















