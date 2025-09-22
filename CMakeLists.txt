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

FetchContent_Declare(
  rtaudio
  GIT_REPOSITORY https://github.com/thestk/rtaudio.git
  GIT_TAG 6.0.1
  CMAKE_ARGS
  -DRTAUDIO_API_CORE=ON
  -DRTAUDIO_BUILD_TESTS=OFF
  -DRTAUDIO_BUILD_EXAMPLES=OFF
)

# build rtaudio as a static lib
set(BUILD_SHARED_LIBS OFF) 
FetchContent_MakeAvailable(rtaudio)

add_subdirectory(lib)
add_subdirectory(client_app)