#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "iosnd.h"
#include "gensnd.h"
#include "process.h"
#include "wave.h"
#include "multisound.h"
#include "song.h"

int main(int argc, char *argv[]) {

    FILE * f;
    f = fopen(argv[1], "r");
    char ln[255];

    //Array of waves (bits under the wave part of the file)
    wave *w[100];
    int wLength = 0;
    //Array of multisounds  (bits under the sound part of the file)
    msound *m[100];
    int mLength = 0;
    //Array of songs (bits under the song part of the file)
    song *s[100];
    int sLength = 0;

    //Gets the sample rate for the file
    fgets(ln, 255, f);
    fgets(ln, 255, f);
    int sampleRate = atoi(ln);

    //While loop for reading through the file
    //Looks for "WAVE", "SOUND" and "SONG"
    while(!feof(f)) {
        char line[255];
        fscanf(f, "%s", line);

        if (strcmp(line, "WAVE") == 0) {
            //Makes the wave structure
            wave * new = malloc(sizeof(struct wave_w));
            new->name = malloc(sizeof(char) * 255);
            new->type = malloc(sizeof(char) * 8);

            //Scans the line and gives the waves all the values based on those lines
            fscanf(f, "%s", new->name);
            fscanf(f, "%s", new->type);
            fscanf(f, "%f %f", &new->delay, &new->attenuation);

            //Adds the wave to the array and increases the length of the array by one
            w[wLength] = new;
            wLength++;
        } else if (strcmp(line, "SOUND") == 0) {
            //Makes the msound structure
            msound * added = malloc(sizeof(struct multisound_m));
            added->name = malloc(sizeof(char) * 255);
            added->waves = (struct wave_w **)malloc(sizeof(struct wave_w *));    //malloc memory for the double pointer wave
            added->waves[0] = (struct wave_w *) malloc(sizeof(struct wave_w));   //malloc memory for the first wave
            added->fir = malloc(sizeof(float));
            added->size = 0;

            //Scans the line and gives the msound it's name
            fscanf(f, "%s", added->name);

            //Scans the next line and stores the name of the wave and gives the msound its first fir value
            char waveName[255];
            fscanf(f, "%s %f", waveName, added->fir);

            //Removes the '\n' from waveName and searches through the array of waves for a matching name
            //Then has a pointer for that wave point to the matching wave. Increases the size by one
            strtok(waveName, "\n");
            for (int i = 0; i < wLength; i++) {
                if (strcmp(w[i]->name, waveName) == 0) {
                    added->waves[added->size] = w[i];
                    added->size = added->size + 1;
                }
            }

            //Gets the next line and stores it's info in the oneLine char array
            char oneline[259];
            fgets(oneline, sizeof(oneline), f);
            fgets(oneline, sizeof(oneline), f);

            while(strcmp(oneline, "\n") != 0) {
                //Reallocates memory for the wave double pointer and allocates memory for the new wave to be added
                added->waves = (struct wave_w **)realloc(added->waves, sizeof(struct wave_w *) * (added->size + 1));
                added->waves[added->size] = (struct wave_w *) malloc(sizeof(struct wave_w));
                added->fir = realloc(added->fir, sizeof(float) * (added->size + 1));

                //Stores the line as a char array, scans that char array for the values and assigns the to the msound
                char names[255];
                char value[4];
                strtok(oneline, "\n");
                sscanf(oneline, "%s %s", names, value);
                float tempFloat = atof(value);
                added->fir[added->size] = tempFloat;

                //Again, finds a wave with a matching name and assigns that wave to this msound
                for (int i = 0; i < wLength; i++) {
                    if (strcmp(w[i]->name, names) == 0) {
                        added->waves[added->size] = w[i];
                    }
                }
                added->size = added->size + 1;

                //Moves onto the next line
                fgets(oneline, sizeof(oneline), f);
            }

            //Assigns this msound to the array of msound and increase the size of the array by one
            m[mLength] = added;
            mLength++;
        } else if (strcmp(line, "SONG") == 0) {
            //Gets the next line
            char oneline[266];
            fgets(oneline, sizeof(oneline), f);
            fgets(oneline, sizeof(oneline), f);

            //While loop for making the song struct
            //Repeats through until the line second to last line of the file
            while (!feof(f)) {
                if (strcmp(oneline, "\n") != 0) {
                    //Makes the song structure and allocates memory for it
                    song * added = malloc(sizeof(struct song_s));
                    added->m = (struct multisound_m *)malloc(sizeof(struct multisound_m));

                    //Creates char arrays and assigns them the matching values
                    char name[255];
                    char key[10];
                    char tim[10];
                    char dur[10];
                    sscanf(oneline, "%s %s %s %s", name, key, tim, dur);

                    //Finds an msound with the same name and points towards that msound
                    for (int i = 0; i < mLength; i++) {
                        if (strcmp(m[i]->name, name) == 0) {
                            added->m = m[i];
                        }
                    }

                    //Gives the song its key, time and duration
                    added->key = keyChange(atof(key));
                    added->time = atof(tim);
                    added->duration = atof(dur);

                    //Moves onto next line
                    fgets(oneline, sizeof(oneline), f);

                    //Adds this to the song array and increases the song array length by one
                    s[sLength] = added;
                    sLength++;
                } else {
                    //Moves onto next line
                    fgets(oneline, sizeof(oneline), f);
                }

            }

            //Makes the last song structure since the while loop goes through the second to last line
            song * added = malloc(sizeof(struct song_s));
            added->m = (struct multisound_m *)malloc(sizeof(struct multisound_m));

            //Creates char arrays and assigns them the matching values
            char name[255];
            char key[10];
            char tim[10];
            char dur[10];
            sscanf(oneline, "%s %s %s %s", name, key, tim, dur);

            //Finds an msound with the same name and points towards that msound
            for (int i = 0; i < mLength; i++) {
                if (strcmp(m[i]->name, name) == 0) {
                    added->m = m[i];
                }
            }

            //Finds an msound with the same name and points towards that msound
            added->key = keyChange(atof(key));
            added->time = atof(tim);
            added->duration = atof(dur);

            //Moves onto next line
            fgets(oneline, sizeof(oneline), f);

            //Adds this to the song array and increases the song array length by one
            s[sLength] = added;
            sLength++;
        }

    }

    //Finds the length of all the sounds
    float longest = 0;
    for (int i = 0; i < sLength; i++) {
        if (s[i]->time + s[i]->duration > longest) {
            longest = s[i]->time + s[i]->duration;
        }
    }

    //Creates the final sound that all song structures will add to
    sound * all = (struct sound_t *)malloc(sizeof(struct sound_t));
    all->samples = malloc(sizeof(float) * longest * sampleRate);
    all->length = longest * sampleRate;
    all->rate = sampleRate;

    //Sets all values of samples to 0
    for (int i = 0; i < all->length; i++) {
        all->samples[i] = 0;
    }

    //For all songs
    for (int i = 0; i < sLength; i++) {
        //Makes an array with a pointer of all the sounds
        sound *sounds[s[i]->m->size];

        //Goes through all waves in a sound and adds them to the sounds array
        for (int j = 0; j < s[i]->m->size; j++) {
            if (strcmp(s[i]->m->waves[j]->type, "sine") == 0) {              //If the wave is a sine wave
                sound * temp = gensine(s[i]->key, sampleRate, s[i]->duration);
                temp = reverb(temp, s[i]->m->waves[j]->delay, s[i]->m->waves[j]->attenuation);
                if (temp == NULL) {
                    return 1;
                }
                sounds[j] = temp;
            } else if (strcmp(s[i]->m->waves[j]->type, "square") == 0) {     //If the wave is a square wave
                sound * temp = genSquare(s[i]->key, sampleRate, s[i]->duration);
                temp = reverb(temp, s[i]->m->waves[j]->delay, s[i]->m->waves[j]->attenuation);
                if (temp == NULL) {
                    return 1;
                }
                sounds[j] = temp;
            } else if (strcmp(s[i]->m->waves[j]->type, "triangle") == 0) {   //If the wave is a triangle wave
                sound * temp = genTriangle(s[i]->key, sampleRate, s[i]->duration);
                temp = reverb(temp, s[i]->m->waves[j]->delay, s[i]->m->waves[j]->attenuation);
                if (temp == NULL) {
                    return 1;
                }
                sounds[j] = temp;
            } else if (strcmp(s[i]->m->waves[j]->type, "saw") == 0) {        //If the wave is a saw wave
                sound * temp = genSawtooth(s[i]->key, sampleRate, s[i]->duration);
                temp = reverb(temp, s[i]->m->waves[j]->delay, s[i]->m->waves[j]->attenuation);
                if (temp == NULL) {
                    return 1;
                }
                sounds[j] = temp;
            }

        }

        //Makes a float array
        float array[s[i]->m->size];
        for (int j = 0; j < s[i]->m->size; j++) {
            array[j] = s[i]->m->fir[j];
        }

        //The final sound created for a song
        sound * temp2 = mix(sounds, array, s[i]->m->size);

        //normalize the temp2 sound
        temp2 = normalize(temp2);

        //Adds the temp2 sample directly to the all sample
        int tempInt = round(s[i]->time * sampleRate);
        for (int j = 0; j < temp2->length; j++) {
            all->samples[j + tempInt] = all->samples[j + tempInt] + temp2->samples[j];
        }

    }

    FILE *e = fopen(argv[2], "w");
    if (outputSound(all, e) == 1) {          //Prints the sound, if an error occurs then it ends the main
        return 1;                            //Returns one to end the main
    }

    return 0;

}
