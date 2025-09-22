project(client_app)

add_executable(music_language_client_app 
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_include_directories(music_language_client_app PRIVATE
    #${rtaudio_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib
)

target_link_libraries(music_language_client_app PRIVATE
    music_language
    #rtaudio
    #"-framework CoreAudio"
    #"-framework CoreFoundation"
    #"-framework AudioUnit"
)