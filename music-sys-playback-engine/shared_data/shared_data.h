#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class SharedData {
public:
    std::unordered_map<std::string, std::vector<float>> samples;
};
