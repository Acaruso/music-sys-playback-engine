#include "audio_service.h"

#include <cstdlib>
#include <vector>

#include "audio_util.h"
#include "sine_test.h"

AudioService::AudioService(WasapiClient& wasapiClient)
    : wasapiClient(wasapiClient)
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
    unsigned numSamplesToWrite = 0;

    // main loop:
    while (!quit) {
        WaitForSingleObject(wasapiClient.hEvent, INFINITE);

        numPaddingFrames = wasapiClient.getCurrentPadding();

        // recall that each elt of buffer stores 1 sample.
        // a frame is 2 samples -> 1 for each channel.
        // so numSamplesToWrite = numFramesToWrite * 2.

        numFramesToWrite = bufferSizeFrames - numPaddingFrames;

        numSamplesToWrite = numFramesToWrite * 2;

        fillSampleBuffer(numSamplesToWrite);

        wasapiClient.writeBuffer(sampleBuffer.buffer, numFramesToWrite);
    }

    wasapiClient.stopPlaying();
}

void AudioService::fillSampleBuffer(size_t numSamplesToWrite) {
    unsigned numChannels = 2;
    unsigned numFrames = numSamplesToWrite / numChannels;

    std::vector<float> floatSamps(numFrames);
    generateSine(floatSamps.data(), numFrames, 440.0f, sampleCounter);

    for (size_t i = 0; i < numFrames; i++) {
        unsigned samp = scaleSignal(floatSamps[i]);
        sampleBuffer.buffer[i * numChannels]     = samp;  // L
        sampleBuffer.buffer[i * numChannels + 1] = samp;  // R
    }
}
