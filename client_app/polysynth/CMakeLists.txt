project(polysynth)

add_executable(polysynth ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

target_include_directories(polysynth PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../../lib
)

target_link_libraries(polysynth PRIVATE music_language)