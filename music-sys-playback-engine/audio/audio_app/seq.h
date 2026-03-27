#pragma once

#include <algorithm>
#include <iostream>

#include "seq_clock.h"
#include "shared_data.h"
#include "wave_player.h"

struct SeqEvent {
    int pos;
    int value;
};

class Seq {
    SeqClock& seqClock;
    SharedData& sharedData;
    WavePlayer snare;

public:
    int eventsSize = 0;
    std::vector<SeqEvent> events = std::vector<SeqEvent>(
        128,
        SeqEvent{0, 0}
    );

    Seq(
        SeqClock& seqClock,
        SharedData& sharedData
    )
        : seqClock(seqClock),
        sharedData(sharedData),
        snare(sharedData.samples["snare"])
    {}

    Seq(
        SeqClock& seqClock,
        SharedData& sharedData,
        const std::vector<int>& pattern
    )
        : seqClock(seqClock),
        sharedData(sharedData),
        snare(sharedData.samples["snare"])

    {
        set16NotePattern(pattern);
    }

    void set16NotePattern(const std::vector<int>& pattern) {
        for (int i16 = 0; i16 < pattern.size(); ++i16) {
            if (pattern[i16] != 0) {
                set16Note(i16, pattern[i16]);
            }
        }
    }

    void set16Note(int pos, int value) {
        addEvent(pos * 24, value);
    }

    void set32Note(int pos, int value) {
        addEvent(pos * 12, value);
    }

    void set64Note(int pos, int value) {
        addEvent(pos * 6, value);
    }

    static bool SeqEventCompare(
        const SeqEvent& a,
        const SeqEvent& b
    ) {
        return a.pos > b.pos;
    }

    void addEvent(int pos, int value) {
        events[eventsSize] = SeqEvent{pos, value};
        ++eventsSize;
        sort(
            events.begin(),
            events.begin() + eventsSize,
            SeqEventCompare
        );
    }

    int trigger() {
        if (seqClock.isPulse()) {
            for (int i = 0; i < eventsSize; i++) {
                if (events[i].pos == seqClock.pulseInMeasure) {
                    return events[i].value;
                }
            }
        }
        return 0;
    }

    void printEvents() {
        for (int i = 0; i < eventsSize; ++i) {
            std::cout << events[i].pos << " ";
        }
        std::cout << std::endl;
    }

    float get() {
        if (trigger() == 1) {
            snare.trigger();
        }
        return snare.get();
    }
};
