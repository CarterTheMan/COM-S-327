#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gensnd.h"
#include "process.h"
#include "iosnd.h"

/**
 * Mixed functions together and their values based on the w[] which specifies each sounds level of mix
 *
 * @param s
 * @param w
 * @param c
 * @return returned
 */
sound * mix(sound *s[], float w[], int c) {
    int longestSound = s[0]->length;
    int sRate = s[0]->rate;     //might need to be changed

    //finds the length of the longest sound
    for (int i = 0; i < c; i++) {
        if (s[i]->length > longestSound) {
            longestSound = s[i]->length;
            sRate = s[i]->rate;     //might need to be changed
        }
    }

    //creates the sample to be returned
    sound * returned = malloc(sizeof(sound));                     //Creates and allocates memory for a sound struct
    returned->samples = malloc(sizeof(float) * longestSound);      //Allocates memory for the samples pointer
    returned->length = longestSound;
    returned->rate = sRate;              //used to be "returned->rate = sample_rate;

    //For the whole samples array
    for (int i = 0; i < longestSound; i++) {
        float sample = 0;

        //For each sound sample to find altered size
        for (int j = 0; j < c; j++) {
            if (i < s[j]->length) {     //if it is still within samples
                sample = sample + s[j]->samples[i] * w[j];
            } else {                    //if its past the number of samples
                sample = sample + 0;
            }
        }

        returned->samples[i] = sample;

    }

    return returned;
}

/**
 * Takes two sounds and multiplies them together for the returned sound
 *
 * @param s1
 * @param s2
 * @return returned
 */
sound * modulate(sound *s1, sound *s2) {
    if (s1->length != s2->length) {
        return NULL;
    } else {
        //creates the sample to be returned
        sound * returned = malloc(sizeof(sound));                     //Creates and allocates memory for a sound struct
        returned->samples = malloc(sizeof(float) * s1->length);      //Allocates memory for the samples pointer
        returned->length = s1->length;
        returned->rate = s1->rate;          //may need to be changed

        for (int i = 0; i < returned->length; i++) {
            returned->samples[i] = s1->samples[i] * s2->samples[i];
        }

        return returned;
    }

}

/**
 * Takes a sound and multiplies each sample by previous samples based on the fir
 *
 * @param s
 * @param fir
 * @param c
 * @return returned
 */
sound * filter(sound *s, float fir[], int c) {
    //creates the sample to be returned
    sound * returned = (struct sound_t *)malloc(sizeof(struct sound_t));
    returned->samples = malloc(sizeof(float) * s->length);        //Allocates memory for the samples pointer
    returned->length = s->length;
    returned->rate = s->rate;

    for (int i = 0; i < returned->length; i++) {
        float sample = 0;

        for (int j = 0; j < c; j++) {
            if (i-j < 0) {
                //nothing here since it multiplies the sample by 0 if i-j<0
            } else {
                sample = sample + (s->samples[i-j] * fir[j]);
            }
        }

        returned->samples[i] = sample;
    }

    return returned;
}

/**
 * Takes a sound, makes a fir array based on the delay and attenuation and then uses filter
 * to make the sound that is to be returned. Should only work on 0 - .1
 *
 * @param s
 * @param delay
 * @param attenuation
 * @return returned
 */
sound* reverb(sound *s, float delay, float attenuation) {
    //To check for sane values. Figure out how to throw an error below
    if (s == NULL) {
        fprintf(stderr, "The sound is null\n");
        return NULL;
    } else if (delay <= 0 || delay >= 0.1) {
        fprintf(stderr, "The delay %f is out of bounds\n", delay);
        return NULL;
    } else if (attenuation <= 0 || attenuation >= 1) {
        fprintf(stderr, "The attenuation %f is out of bounds\n", attenuation);
        return NULL;
    }

    int length = (int)(delay * s->rate) + 1;
    float fir[length];
    for (int i = 0; i < length; i++) {
        fir[i] = 0;
    }
    fir[0] = 1;
    fir[length-1] = attenuation;

    //Makes the sound struct that is to be returned
    sound * returned = malloc(sizeof(sound));                     //Creates and allocates memory for a sound struct
    returned->samples = malloc(sizeof(float) * s->length);        //Allocates memory for the samples pointer
    returned->length = s->length;
    returned->rate = s->rate;

    returned = filter(s, fir, length);

    return returned;
}

/**
 * Takes a sound, makes a fir array based on the delay and attenuation and then uses filter
 * to make the sound that is to be returned. Should only work on .1 - 1
 *
 * @param s
 * @param delay
 * @param attenuation
 * @return returned
 */
sound* echo(sound *s, float delay, float attenuation) {
    if (s == NULL) {
        fprintf(stderr, "The sound is null\n");
        return NULL;
    } else if (delay < .1 || delay > 1) {
        fprintf(stderr, "The delay %f is out of bounds\n", delay);
        return NULL;
    } else if (attenuation <= 0 || attenuation >= 1) {
        fprintf(stderr, "The attenuation %f is out of bounds\n", attenuation);
        return NULL;
    }

    int length = (int)(s->rate * delay) + 1;
    float fir[length];
    for (int i = 0; i < length; i++) {
        fir[i] = 0;
    }
    fir[0] = 1;
    fir[length-1] = attenuation;

    sound * returned = malloc(sizeof(sound));                     //Creates and allocates memory for a sound struct
    returned->samples = malloc(sizeof(float) * s->length);        //Allocates memory for the samples pointer
    returned->length = s->length;
    returned->rate = s->rate;

    returned = filter(s, fir, length);

    return returned;
}

/**
 * Takes in a key value and returns the frequency equivalent
 *
 * @param key
 * @return pow(2,(key - 49)/12) * 440
 */
float keyChange(float key) {
    return pow(2,(key - 49)/12) * 440;
}

/**
 * Takes in a sound and normalizes it
 *
 * @param s
 * @return returned
 */
sound * normalize(sound *s) {
    //Creates the returned sound structure
    sound * returned = (struct sound_t *)malloc(sizeof(struct sound_t));
    returned->samples = malloc(sizeof(float) * s->length);      //Allocates memory for the samples pointer
    returned->length = s->length;
    returned->rate = s->rate;

    float highestX = 0;     //For highest above 0 sample
    float lowestX = 0;      //For highest below 0 sample
    for (int i = 0; i < s->length; i++) {
        if (s->samples[i] > highestX) {
            highestX = s->samples[i];
        }
        if (s->samples[i] < lowestX) {
            lowestX = s->samples[i];
        }
    }

    float temp = 0;         //The const to store which number is greater
    lowestX = lowestX * -1;
    if (highestX > lowestX) {
        temp = highestX;
    } else {
        temp = lowestX;
    }

    float mult = 1/temp;    //What to multiply so that the sound it normalized

    for (int i = 0; i < s->length; i++) {
        returned->samples[i] = s->samples[i] * mult;
    }

    return returned;
}