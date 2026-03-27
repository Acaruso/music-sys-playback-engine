file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "main/*.cpp" "main/*.h"
    "audio/*.cpp" "audio/*.h"
    "shared_data/*.cpp" "shared_data/*.h"
)

add_executable(music_sys_playback_engine ${SOURCES})

target_include_directories(music_sys_playback_engine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/audio/audio_system
    ${CMAKE_CURRENT_SOURCE_DIR}/audio/audio_app
    ${CMAKE_CURRENT_SOURCE_DIR}/main
    ${CMAKE_CURRENT_SOURCE_DIR}/shared_data
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party
)

target_compile_definitions(music_sys_playback_engine PRIVATE UNICODE _UNICODE)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET music_sys_playback_engine PROPERTY CXX_STANDARD 20)
endif()
