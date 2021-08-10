#ifndef PROCESS_H
#define PROCESS_H
#include "sound.h"

sound * mix(sound *s[], float w[], int c);
sound * modulate(sound *s1, sound *s2);
sound * filter(sound *s, float fir[], int c);
sound* reverb(sound *s, float delay, float attenuation);
sound* echo(sound *s, float delay, float attenuation);

//My own method
float keyChange(float key);
sound * normalize(sound *s);

#endif