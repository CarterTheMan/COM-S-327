#ifndef MULTISOUND_H
#define MULTISOUND_H
#include "wave.h"

typedef struct multisound_m msound;

typedef struct multisound_m {
    char * name;                //The name of this multisound
    wave ** waves;              //An array of pointers to the waves used under this sound
    float * fir;                //Values of this sound to be mixed
    int size;                   //Size of this multisound
};

#endif

