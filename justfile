set windows-shell := ["powershell.exe", "-NoLogo", "-Command"]

preset := "x64-debug"
build_dir := "out/build/" + preset
exe := build_dir + "/music-sys-playback-engine/music_sys_playback_engine.exe"

init:
    cmake --preset {{preset}}

build:
    cmake --build {{build_dir}}

run: build
    ./{{exe}}

clean:
    rm -rf {{build_dir}}
