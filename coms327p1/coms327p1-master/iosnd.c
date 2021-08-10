#include <stdio.h>
#include "gensnd.h"
#include "sound.h"
#include "iosnd.h"

/**
 * Prints out a sound to a specified file
 *
 * @param s
 * @param f
 * @return 0 if success and 1 if fails
 */
int outputSound(sound *s, FILE *f) {
    if (f == NULL) {    //If the file is NULL it prints an error and returns 1
        fprintf(stderr, "There was an error with the file\n");
        return 1;
    }
    if (s == NULL) {    //If the sound pointer is NULL it prints an error and returns 1
        fprintf(stderr, "There was an error with the sound\n");
        return 1;
    }

    //Prints each sample onto the file
    for (int i = 0; i < s->length; i++) {
        fprintf(f, "%f\n", s->samples[i]);
    }
    return 0;
}
