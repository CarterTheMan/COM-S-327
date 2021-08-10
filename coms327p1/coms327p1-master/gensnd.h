#ifndef GENSND_H
#define GENSND_H
#include "sound.h"

sound * gensine(float hertz, float sample_rate, float duration);
sound * genDTMF(char key, float sample_rate, float duration);
sound * genSilence(float sample_rate, float duration);

sound * genSquare(float hertz, float sample_rate, float duration);
sound * genTriangle(float hertz, float sample_rate, float duration);
sound * genSawtooth(float hertz, float sample_rate, float duration);

#endif