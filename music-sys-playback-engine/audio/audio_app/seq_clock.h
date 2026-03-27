#pragma once

#include <iostream>

#include "util.h"

// clock has 96 PPQ resolution
// 96 PPQ == 96 pulses per quarter note
// assert: each pulse is a 384th note
// because: 96 * 4 = 384

// 384th notes    to        x
// -----------------------------------
// 384            to        1 measure
// 192            to        1/2   note
// 96             to        1/4   note
// 48             to        1/8   note
// 32             to        1/8   note triplets (quarter note / 3)
// 24             to        1/16  note
// 16             to        1/16  note triplets (8th note / 3)
// 12             to        1/32  note
// 6              to        1/64  note
// 3              to        1/128 note
class SeqClock {
public:
    // length of measure in pulses
    const int measureSize = 384;

    int samplesPerPulse;

    // counters:
    int sampleInPulse = 0;
    bool sampleInPulseRollover = false;
    int pulseInMeasure = 0;
    bool pulseInMeasureRollover = false;
    int measureInSong = 0;
    bool measureInSongRollover = false;

    SeqClock(int samplesPerPulse)
        : samplesPerPulse(samplesPerPulse)
    {}

    void reset() {
        sampleInPulse = 0;
        sampleInPulseRollover = false;
        pulseInMeasure = 0;
        pulseInMeasureRollover = false;
        measureInSong = 0;
        measureInSongRollover = false;
    }

    bool isPulse() {
        return (sampleInPulse == 0);
    }

    void get() {
        sampleInPulseRollover = modInc(sampleInPulse, samplesPerPulse);
        if (sampleInPulseRollover) {
            measureInSongRollover = modInc(pulseInMeasure, measureSize);
            if (measureInSongRollover) {
                ++measureInSong;
            }
        }
    }
};
