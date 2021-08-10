#ifndef WAVE_H
#define WAVE_H

typedef struct wave_w wave;

typedef struct wave_w {
    char * name;                //Name of the wave
    char * type;                //Type of the wave (sine, square, triangle, sawtooth)
    float delay;                //Delay on the reverb
    float attenuation;          //Attenuation on the reverb
};

#endif