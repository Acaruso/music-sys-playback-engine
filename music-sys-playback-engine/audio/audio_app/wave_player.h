#pragma once

#include <iostream>
#include <vector>

class WavePlayer {
    std::vector<float>& wave;
    float curSamp;
    int idx;
    bool playing;

    const int DIRECTION_FORWARD = 0;
    const int DIRECTION_BACK = 1;
    int direction;

public:
    WavePlayer(std::vector<float>& wave)
        : wave(wave),
        curSamp(0.0f),
        idx(0),
        playing(false),
        direction(DIRECTION_FORWARD)
    {
        std::cout << "WavePlayer "
            << "wave.size()=" << wave.size() << std::endl;
    }

    void trigger() {
        idx = 0;
        playing = true;
    }

    float get() {
        if (playing == false) {
            return 0.0f;
        }

        curSamp = wave[idx];

        direction == DIRECTION_FORWARD ? ++idx : --idx;

        if (idx >= wave.size() || idx < 0) {
            idx = 0;
            playing = false;
        }

        return curSamp;
    }
};
