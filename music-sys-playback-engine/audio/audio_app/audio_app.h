#pragma once

#include <vector>

#include "shared_data.h"
#include "seq.h"
#include "seq_clock.h"

class AudioApp {
private:
    SharedData& sharedData;
    SeqClock seqClock;
    Seq seq;

public:
    AudioApp(SharedData &sharedData)
        : sharedData(sharedData),
        seqClock(500),     // arg: samples per pulse
        seq(seqClock, sharedData)
    {
        seq.set16NotePattern(
            { 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0 }
        );
    }

    void fillSampleBuffer(std::vector<float>& sampleBuffer) {
        float samp = 0.0f;
        for (size_t i = 0; i < sampleBuffer.size(); ++i) {
            samp = seq.get();
            seqClock.get();
            sampleBuffer[i] = samp;
        }
    }
};
