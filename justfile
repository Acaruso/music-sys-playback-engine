set windows-shell := ["powershell.exe", "-NoLogo", "-Command"]

preset := "x64-debug"
build_dir := "out/build/" + preset
exe := build_dir + "/music-sys-playback-engine/music_sys_playback_engine.exe"
vcvars := 'C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat'

init:
    cmd /c '"{{vcvars}}" x64 >nul && cmake --preset {{preset}}'

build:
    cmd /c '"{{vcvars}}" x64 >nul && if not exist "{{build_dir}}" (cmake --preset {{preset}}) && cmake --build {{build_dir}}'

run: build
    ./{{exe}}

clean:
    if (Test-Path "{{build_dir}}") { Remove-Item -Recurse -Force "{{build_dir}}" }
