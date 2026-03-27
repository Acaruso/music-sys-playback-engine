#pragma once

#include <cmath>
#include <cstdlib>
#include <sstream>
#include <string>
#include <vector>

#include "constants.h"

// get random double between 0.0 and 1.0
inline double getRand() {
    return rand() / (RAND_MAX + 1.0);
}

inline bool getRandBool(float f) {
    return (getRand() < f);
}

template <typename T>
inline std::string toHexString(const T& t) {
    std::stringstream ss;
    ss << "0x" << std::hex << t;
    return ss.str();
}

template <typename T>
inline std::wstring toHexStringW(const T& t) {
    std::wstringstream ss;
    ss << "0x" << std::hex << t;
    return ss.str();
}

inline std::vector<float> makeSineBuffer(unsigned size) {
    std::vector<float> buffer(size, 0.0);

    double inc = twoPi / size;
    double cur = 0.0;

    for (unsigned i = 0; i < buffer.size(); i++) {
        buffer[i] = (float)sin(cur);
        cur += inc;
    }

    return buffer;
}

template <typename T>
bool inBounds(std::vector<T>& vec, unsigned i) {
    return i > 0 && i < vec.size();
}

// idx = (idx + 1) % mod
// return `true` if the counter "rolled over" to 0
inline bool modInc(int& idx, int mod) {
    if ((idx + 1) < mod) {
        idx = idx + 1;
        return false;
    } else {
        idx = 0;
        return true;
    }
}
