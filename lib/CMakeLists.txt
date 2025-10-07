project(musiclib)

set(SOURCE_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/audioengine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/midimanager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/soundsource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sinewave.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/trianglewave.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/squarewave.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sawwave.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/envelope.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/noise.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utility.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sampleplayer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/clock.cpp
)

add_library(music_language STATIC ${SOURCE_FILES})

target_include_directories(music_language PRIVATE
    ${rtaudio_SOURCE_DIR}
    ${xoshiro_SOURCE_DIR}
    ${rtmidi_SOURCE_DIR}
    ${audiofile_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(music_language PRIVATE
    rtmidi
    rtaudio
    "-framework CoreAudio"
    "-framework CoreFoundation"
    "-framework AudioUnit"
)
