#pragma once

#include <vector>

#include "../shared_data/shared_data.h"
#include "sine_test.h"

class AudioApp {
public:
    AudioApp(SharedData &sharedData)
        : sharedData(sharedData)
    {}

    void fillSampleBuffer(std::vector<float>& sampleBuffer) {
        generateSine(sampleBuffer.data(), sampleBuffer.size(), 440.0f);
    }

private:
    SharedData& sharedData;
};
