set(${SAMPLES_LIST} sample_game PARENT_SCOPE)
set(SAMPLE_GAME_SOURCES ${SAMPLE_GAME_SOURCES}
        main.cpp
        resources-manager.cpp resources-manager.hpp)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
find_package(SFML)

add_subdirectory(agent)
add_subdirectory(environment)
add_subdirectory(graphics)

add_executable(sample_game ${SAMPLE_GAME_SOURCES})
target_link_libraries(sample_game broccoli sfml-graphics sfml-window sfml-system)
