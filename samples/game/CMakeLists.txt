set(${SAMPLES_LIST} sample_game PARENT_SCOPE)
set(SAMPLE_GAME_SOURCES ${SAMPLE_GAME_SOURCES}
        main.cpp
        resources-manager.cpp resources-manager.hpp
        game.cpp game.hpp
        constants.hpp)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
find_package(SFML)

add_subdirectory(agent)
add_subdirectory(environment)
add_subdirectory(graphics)

add_executable(sample_game_mt_lock_free ${SAMPLE_GAME_SOURCES})
target_link_libraries(sample_game_mt_lock_free broccoli sfml-graphics sfml-window sfml-system -pthread)
