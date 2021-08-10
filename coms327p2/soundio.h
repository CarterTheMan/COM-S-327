#ifndef SOUNDIOH
#define SOUNDIOH
#include "SoundSamples.h"
#include <string>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <fstream>
using namespace std;

class SoundIO {
    public:
        static void OutputSound(SoundSamples *samples, string filename);

};

#endif