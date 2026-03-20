#include "music_sys_playback_engine.h"
#include "util.h"
#include "audio/audio_main.h"

#include <thread>
#include <chrono>

int main()
{
	std::thread audioThread(audioMain);
	audioThread.detach();

	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
}
