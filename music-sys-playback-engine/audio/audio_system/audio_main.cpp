#include "audio_main.h"

#include <comdef.h>
#include <iostream>
#include <xmmintrin.h>

#include "audio_app.h"
#include "audio_service.h"
#include "wasapi_client.h"

int audioMain(SharedData& sharedData) {
    // set flush-to-zero and denormals-are-zero mode (SSE2)
    // see Agner Fog optimization manual example 7.5
    // https://www.agner.org/optimize/optimizing_cpp.pdf
    _mm_setcsr(_mm_getcsr() | 0x8040);

    // initialize COM:
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

    try {
        AudioApp audioApp{sharedData};
        WasapiClient wasapiClient;
        AudioService audioService{audioApp, wasapiClient};
        audioService.run();
    } catch(std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}
