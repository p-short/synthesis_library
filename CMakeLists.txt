cmake_minimum_required(VERSION 3.19)
project(builder)
set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
  xoshiro
  GIT_REPOSITORY https://github.com/Reputeless/Xoshiro-cpp.git
  GIT_TAG v1.1
)

FetchContent_MakeAvailable(xoshiro)

# RtMidi
FetchContent_Declare(
  rtmidi
  GIT_REPOSITORY https://github.com/thestk/rtmidi.git
  GIT_TAG 6.0.0
)

set(RTMIDI_TARGETNAME_UNINSTALL "rtmidi_uninstall" CACHE STRING "Name of 'uninstall' build target" FORCE)
set(RTMIDI_BUILD_TESTING OFF CACHE INTERNAL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "" FORCE)

FetchContent_MakeAvailable(rtmidi)

# RtAudio
FetchContent_Declare(
  rtaudio
  GIT_REPOSITORY https://github.com/thestk/rtaudio.git
  GIT_TAG 6.0.1
)

set(RTAUDIO_BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(RTAUDIO_BUILD_EXAMPLES OFF CACHE INTERNAL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "" FORCE)

FetchContent_MakeAvailable(rtaudio)

FetchContent_Declare(
  audiofile
  GIT_REPOSITORY https://github.com/adamstark/AudioFile.git
  GIT_TAG 1.1.3
)

set(BUILD_TESTS OFF CACHE INTERNAL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "" FORCE)

FetchContent_MakeAvailable(audiofile)

add_subdirectory(lib)
add_subdirectory(client_app)