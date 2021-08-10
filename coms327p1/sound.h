#ifndef SOUND_H
#define SOUND_H

typedef struct sound_t sound;

typedef struct sound_t {
    float *samples;          //An array of samples of sound
    int length;             //Number of samples in the array
    float rate;             //Sample rate for the sound
} sound;

#endif