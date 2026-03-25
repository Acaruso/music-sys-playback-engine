#pragma once

#include "../shared_data/shared_data.h"

class AudioApp {
public:
    AudioApp(SharedData &sharedData)
        : sharedData(sharedData)
    {}

private:
    SharedData& sharedData;
};
