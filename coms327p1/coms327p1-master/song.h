#ifndef SONG_H
#define SONG_H
#include "multisound.h"

typedef struct song_s song;

typedef struct song_s {
    msound * m;             //Pointer to the multisound used by this song
    float key;              //The key of the song (hertz)
    float time;             //When this note is played
    float duration;         //How long this note is played
};

#endif
