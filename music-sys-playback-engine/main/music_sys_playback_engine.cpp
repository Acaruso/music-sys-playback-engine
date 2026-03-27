#include "wave_reader.h"
#include "audio_main.h"
#include "shared_data/shared_data.h"

#include <thread>
#include <chrono>
#include <windows.h>

void loadSamples(SharedData& sharedData);

int main() {
	SharedData sharedData;
	loadSamples(sharedData);

	std::thread audioThread(audioMain, std::ref(sharedData));
	audioThread.detach();

	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void loadSamples(SharedData& sharedData) {
    WaveReader waveReader;

    waveReader.openWaveFileAndFillFloatVec(
        L"samples\\606HH_01_TapeSat_16_bit.wav",
        &sharedData.samples["hihat"]);

    waveReader.openWaveFileAndFillFloatVec(
        L"samples\\606SDmod_03_TapeSat_16_bit.wav",
        &sharedData.samples["snare"]
    );
}
