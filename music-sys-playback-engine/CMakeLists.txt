file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "main/*.cpp" "main/*.h"
    "audio/*.cpp" "audio/*.h"
)

add_executable(music_sys_playback_engine ${SOURCES})

target_include_directories(music_sys_playback_engine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/main
    ${CMAKE_CURRENT_SOURCE_DIR}/third_party
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET music_sys_playback_engine PROPERTY CXX_STANDARD 20)
endif()
