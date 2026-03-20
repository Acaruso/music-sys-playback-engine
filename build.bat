@echo off
setlocal

set VS_PATH=C:\Program Files\Microsoft Visual Studio\2022\Community
set PRESET=x64-debug
set BUILD_DIR=out\build\%PRESET%
set EXE=%BUILD_DIR%\music-sys-playback-engine\music_sys_playback_engine.exe

if "%1"=="init" goto init
if "%1"=="build" goto build
if "%1"=="run" goto run
if "%1"=="clean" goto clean
goto usage

:init
call "%VS_PATH%\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul
cmake --preset %PRESET%
goto end

:build
call "%VS_PATH%\VC\Auxiliary\Build\vcvarsall.bat" x64 >nul
if not exist "%BUILD_DIR%" cmake --preset %PRESET%
cmake --build %BUILD_DIR%
goto end

:run
if not exist "%EXE%" (
    echo Error: %EXE% not found. Run "build.bat build" first.
    exit /b 1
)
"%EXE%"
goto end

:clean
if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
echo Cleaned %BUILD_DIR%
goto end

:usage
echo Usage: build.bat [command]
echo.
echo Commands:
echo   init    Configure the CMake project
echo   build   Build the project
echo   run     Run the executable
echo   clean   Remove build artifacts
goto end

:end
endlocal
