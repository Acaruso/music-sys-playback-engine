#pragma once

#include <cmath>
#include "audio_constants.h"

const float PI = 3.14159265358979323846f;

inline void generateSine(float* output, size_t numSamples, float freq, unsigned long& sampleCounter) {
    for (size_t i = 0; i < numSamples; i++) {
        float phase = 2.0f * PI * freq * sampleCounter / samplesPerSecond;
        output[i] = std::sin(phase) * 0.25f;
        sampleCounter++;
    }
}
