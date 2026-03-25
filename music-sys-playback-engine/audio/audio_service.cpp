#include "audio_service.h"

#include <cstdlib>
#include <vector>

#include "audio_util.h"
#include "sine_test.h"

AudioService::AudioService(AudioApp& audioApp, WasapiClient& wasapiClient)
    : audioApp(audioApp), wasapiClient(wasapiClient)
{
    bufferSizeBytes = wasapiClient.getBufferSizeBytes();
    sampleBuffer.init(bufferSizeBytes);

    bufferSizeFrames = wasapiClient.getBufferSizeFrames();
}

void AudioService::run() {
    sampleBuffer.zero();

    wasapiClient.writeBuffer(sampleBuffer.buffer, bufferSizeFrames);

    wasapiClient.startPlaying();

    bool quit = false;

    unsigned numPaddingFrames = 0;
    unsigned numFramesToWrite = 0;

    // main loop:
    while (!quit) {
        WaitForSingleObject(wasapiClient.hEvent, INFINITE);

        numPaddingFrames = wasapiClient.getCurrentPadding();
        numFramesToWrite = bufferSizeFrames - numPaddingFrames;

        fillSampleBuffer(numFramesToWrite);

        wasapiClient.writeBuffer(sampleBuffer.buffer, numFramesToWrite);
    }

    wasapiClient.stopPlaying();
}

void AudioService::fillSampleBuffer(size_t numFramesToWrite) {
    unsigned numChannels = 2;

    std::vector<float> floatSamps(numFramesToWrite);
    generateSine(floatSamps.data(), numFramesToWrite, 440.0f);

    for (size_t i = 0; i < numFramesToWrite; i++) {
        unsigned samp = scaleSignal(floatSamps[i]);
        sampleBuffer.buffer[i * numChannels]     = samp;  // L
        sampleBuffer.buffer[i * numChannels + 1] = samp;  // R
        ++sampleCounter;
    }
}
