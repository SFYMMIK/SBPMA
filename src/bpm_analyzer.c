#include "include/bpm_analyzer.h"
#include "include/audio_processing.h"
#include <math.h>

double round_bpm(double bpm) {
    double rounded_bpm;
    double decimal_part = bpm - floor(bpm);

    if (decimal_part > 0.5) {
        rounded_bpm = ceil(bpm);
    } else if (decimal_part < 0.5) {
        rounded_bpm = floor(bpm);
    } else {
        rounded_bpm = floor(bpm) + 0.5;
    }
    return rounded_bpm;
}

double calculate_bpm(const char *file_path) {
    AudioData *audio = load_audio_file(file_path);
    if (!audio) {
        return -1;  // Error loading file
    }

    double bpm = analyze_bpm(audio);
    free_audio_data(audio);

    return round_bpm(bpm);
}
