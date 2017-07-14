set(${SAMPLES_LIST} sample_game PARENT_SCOPE)

add_executable(sample_game main.cpp)
target_link_libraries(sample_game broccoli)
