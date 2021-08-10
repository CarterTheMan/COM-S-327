#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "gensnd.h"

/**
 * This method take input of hertz (frequency), sample_rate and a duration to create and output
 * a pointer to a sound struct
 *
 * @param hertz
 * @param sample_rate
 * @param duration
 * @return returned
 */
sound * gensine(float hertz, float sample_rate, float duration) {
    int totalSamples = sample_rate * duration;

    //sound * returned = malloc(sizeof(sound));                     //Creates and allocates memory for a sound struct
    sound * returned = (struct sound_t *)malloc(sizeof(struct sound_t));
    returned->samples = malloc(sizeof(float) * totalSamples);      //Allocates memory for the sample pointer
    returned->length = totalSamples;
    returned->rate = hertz;

    float radians = 0;
    float increase = 2 * M_PI / sample_rate * hertz;     //A constant to be added for each iteration
    for (int i = 0; i < totalSamples; i++) {
        float num = sin(radians);
        returned->samples[i] = num;
        radians += increase;                             //Adds the constant for each iteration
    }

    return returned;
}

/**
 * This method takes a key, sample_rate and duration to create two sound pointers and then average them to generate
 * one sound pointer. This one final sound pointer is the one that is returned
 *
 * @param key
 * @param sample_rate
 * @param duration
 * @return returned
 */
sound * genDTMF(char key, float sample_rate, float duration) {
    int frequency1, frequency2;

    //This if/else statement determines the frequency of the two sounds
    if (key == '1') {
        frequency1 = 1209;
        frequency2 = 697;
    } else if (key == '2') {
        frequency1 = 1336;
        frequency2 = 697;
    } else if (key == '3') {
        frequency1 = 1477;
        frequency2 = 697;
    } else if (key == '4') {
        frequency1 = 1209;
        frequency2 = 770;
    } else if (key == '5') {
        frequency1 = 1336;
        frequency2 = 770;
    } else if (key == '6') {
        frequency1 = 1477;
        frequency2 = 770;
    } else if (key == '7') {
        frequency1 = 1209;
        frequency2 = 852;
    } else if (key == '8') {
        frequency1 = 1336;
        frequency2 = 852;
    } else if (key == '9') {
        frequency1 = 1477;
        frequency2 = 852;
    } else if (key == '*') {
        frequency1 = 1209;
        frequency2 = 941;
    } else if (key == '0') {
        frequency1 = 1336;
        frequency2 = 941;
    } else if (key == '#') {
        frequency1 = 1477;
        frequency2 = 941;
    } else if (key == 'a' || key == 'A') {
        frequency1 = 1633;
        frequency2 = 697;
    } else if (key == 'b' || key == 'B') {
        frequency1 = 1633;
        frequency2 = 770;
    } else if (key == 'c' || key == 'C') {
        frequency1 = 1633;
        frequency2 = 852;
    } else if (key == 'd' || key == 'D') {
        frequency1 = 1633;
        frequency2 = 941;
    }

    //Makes two sound pointers. One for each frequency
    sound * sound1 = gensine(frequency1, sample_rate, duration);
    sound * sound2 = gensine(frequency2, sample_rate, duration);

    int totalSamples = sample_rate * duration;
    sound * returned = malloc(sizeof(sound));                       //Creates and allocates memory for a sound struct
    returned->samples = malloc(sizeof(float) * totalSamples);        //Allocates memory for the sample pointer
    returned->rate = sample_rate;
    returned->length = totalSamples;

    //Averages the samples from the first two sound pointers to the new sound sample pointer
    for (int i = 0; i < totalSamples; i++) {
        returned->samples[i] = (sound1->samples[i] + sound2->samples[i]) / 2;
    }

    free(sound1->samples);   //Since we allocated memory for the samples we have to free each
    free(sound2->samples);
    free(sound1);           //Since we allocated memory for the sounds we have to free each
    free(sound2);

    return returned;
}

/**
 * This method takes in a sample rate and duration to generates a sound structure pointer
 * with a sample pointer that is filled with silence
 *
 * @param sample_rate
 * @param duration
 * @return returned
 */
sound * genSilence(float sample_rate, float duration) {
    int totalSamples = sample_rate * duration;

    //sound * returned = malloc(sizeof(sound));                     //Creates and allocates memory for a sound struct
    sound * returned = (struct sound_t *)malloc(sizeof(struct sound_t));
    returned->samples = malloc(sizeof(float) * totalSamples);      //Allocates memory for the samples pointer
    returned->length = totalSamples;
    returned->rate = sample_rate;

    //Generates the silence and adds it to the samples pointer
    for (int i = 0; i < totalSamples; i++) {
        returned->samples[i] = sin(0);
    }

    return returned;
}

/**
 * This method makes a square wave. Uses the normal sine wave formula but if a value is greater than 0
 * it becomes one and if the value is less than 0 it becomes -1
 *
 * @param hertz
 * @param sample_rate
 * @param duration
 * @return returned
 */
sound * genSquare(float hertz, float sample_rate, float duration) {
    int totalSamples = sample_rate * duration;

    //sound * returned = malloc(sizeof(sound));                     //Creates and allocates memory for a sound struct
    sound * returned = (struct sound_t *)malloc(sizeof(struct sound_t));
    returned->samples = malloc(sizeof(float) * totalSamples);      //Allocates memory for the samples pointer
    returned->length = totalSamples;
    returned->rate = sample_rate;

    for (int i = 0; i < totalSamples; i++) {
        float sample = sin(2 * M_PI * hertz / sample_rate * i);
        if (sample > 0) {
            returned->samples[i] = 1;
        } else if (sample < 0) {
            returned->samples[i] = -1;
        } else {
            returned->samples[i] = 0;
        }
    }

    return returned;
}

/**
 * Generates a wave the looks like a triangle
 *
 * @param hertz
 * @param sample_rate
 * @param duration
 * @return returned
 */
sound * genTriangle(float hertz, float sample_rate, float duration) {
    int totalSamples = sample_rate * duration;

    //Creates and allocates memory for a sound struct
    sound * returned = (struct sound_t *)malloc(sizeof(struct sound_t));
    returned->samples = malloc(sizeof(float) * totalSamples);      //Allocates memory for the samples pointer
    returned->length = totalSamples;
    returned->rate = sample_rate;

    for (int i = 0; i < totalSamples; i++) {
        float lenOfTri = 1 / hertz;                                     //Length of each triangle
        float half = lenOfTri / 2;                                     //Length of each half of the triangle
        float dist = (1/sample_rate) * i;

        while (dist > 0) {
            dist = dist - lenOfTri;
        }
        dist = dist + lenOfTri;

        if (dist <= half) {
            float sample = 2 / half * dist -1;          //y = mx+b of the triangle with x = dist for first half
            returned->samples[i] = sample;
        } else {
            float sample = -2 / half * dist + 3;        //y = mx+b of the triangle with x = dist for second half
            returned->samples[i] = sample;
        }

    }

    return returned;
}

/**
 * Generates a wave the looks like a sawtooth
 *
 * @param hertz
 * @param sample_rate
 * @param duration
 * @return returned
 */
sound * genSawtooth(float hertz, float sample_rate, float duration) {
    int totalSamples = sample_rate * duration;

    //sound * returned = malloc(sizeof(sound));                     //Creates and allocates memory for a sound struct
    sound * returned = (struct sound_t *)malloc(sizeof(struct sound_t));
    returned->samples = malloc(sizeof(float) * totalSamples);      //Allocates memory for the samples pointer
    returned->length = totalSamples;
    returned->rate = sample_rate;

    for (int i = 0; i < totalSamples; i++) {
        float lenOfSaw = 1 / hertz;                                     //Length of each saw blade
        float dist = (1/sample_rate) * i;                               //dist to sample

        float temp = fmod(dist, lenOfSaw);

        float sample = 2 / lenOfSaw * temp - 1;
        returned->samples[i] = sample;

    }

    return returned;
}