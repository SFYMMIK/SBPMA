#ifndef AUDIO_PROCESSING_H
#define AUDIO_PROCESSING_H

#include <stdint.h>

typedef struct {
    int sample_rate;
    int channels;
    int samples_count;
    double *samples;
} AudioData;

AudioData *load_audio_file(const char *file_path);
void free_audio_data(AudioData *audio);
double analyze_bpm(AudioData *audio);

#endif // AUDIO_PROCESSING_H
