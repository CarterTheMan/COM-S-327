#include "wave.h"
#include "SoundSamples.h"
#include "soundio.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/**
 * This method, for the SoundIO class, is used for outputing the samples of the SoundSamples to
 * the file that is specified
 *
 * @param samples
 * @param filename
 */
void SoundIO::OutputSound(SoundSamples *samples, string filename) {
    ofstream outputFile;
    outputFile.open(filename);
    cout.precision(6);
    if (samples->getLength() > 0) {
        for (int i = 0; i < samples->getLength() - 1; i++) {
            outputFile << samples->returnSample(i) << std::fixed << "\n";
        }
        outputFile << samples->returnSample(samples->getLength() - 1);
    }
    outputFile.close();
}