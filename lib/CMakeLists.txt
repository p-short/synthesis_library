project(musiclib)

set(SOURCE_FILES 
    ${CMAKE_CURRENT_SOURCE_DIR}/soundsource.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/triangle.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/square.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/saw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/envelope.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/noise.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/utility.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sampleplayer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/clock.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/fx.cpp
)

if (BUILD_SCULPT_WITH_RTAUDIO)
    list(APPEND SOURCE_FILES 
        ${CMAKE_CURRENT_SOURCE_DIR}/audioengine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/midimanager.cpp
    )
endif()

add_library(music_language STATIC ${SOURCE_FILES})

target_include_directories(music_language PRIVATE
    ${xoshiro_SOURCE_DIR}
    ${audiofile_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)

if (BUILD_SCULPT_WITH_RTAUDIO)
    target_include_directories(music_language PRIVATE
        ${rtaudio_SOURCE_DIR}
        ${rtmidi_SOURCE_DIR}
    )   
endif()

if (BUILD_SCULPT_WITH_RTAUDIO)
    target_link_libraries(music_language PRIVATE
        rtmidi
        rtaudio
        "-framework CoreAudio"
        "-framework CoreFoundation"
        "-framework AudioUnit"
    )
endif()
