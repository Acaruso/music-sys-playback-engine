#pragma once

#include "sample_buffer.h"
#include "wasapi_client.h"

class AudioService {
public:
    AudioService(WasapiClient& wasapiClient);
    void run();

private:
    WasapiClient& wasapiClient;
    SampleBuffer sampleBuffer;

    unsigned bufferSizeBytes{0};
    unsigned bufferSizeFrames{0};

    unsigned long sampleCounter{0};

    double avgTime = 0.0;
    unsigned avgCount = 0;

    void fillSampleBuffer(size_t numSamplesToWrite);
};
