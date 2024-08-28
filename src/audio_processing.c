#include "include/audio_processing.h"
#include <stdio.h>
#include <stdlib.h>
#include <sndfile.h>

AudioData *load_audio_file(const char *file_path) {
    SNDFILE *infile;
    SF_INFO sfinfo;
    AudioData *audio;

    if ((infile = sf_open(file_path, SFM_READ, &sfinfo)) == NULL) {
        printf("Failed to open file %s.\n", file_path);
        return NULL;
    }

    audio = (AudioData *)malloc(sizeof(AudioData));
    audio->sample_rate = sfinfo.samplerate;
    audio->channels = sfinfo.channels;
    audio->samples_count = sfinfo.frames * sfinfo.channels;
    audio->samples = (double *)malloc(audio->samples_count * sizeof(double));

    sf_read_double(infile, audio->samples, audio->samples_count);
    sf_close(infile);

    return audio;
}

void free_audio_data(AudioData *audio) {
    free(audio->samples);
    free(audio);
}

double analyze_bpm(AudioData *audio) {
    // Placeholder for actual BPM analysis logic
    double bpm = 120.0;  // Assume a default BPM
    // Implement FFT and autocorrelation for actual BPM detection

    return bpm;
}
