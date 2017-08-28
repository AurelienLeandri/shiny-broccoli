set(SAMPLE_GAME_SOURCES ${SAMPLE_GAME_SOURCES}
        # Add context .cpp files here
        ${CMAKE_CURRENT_SOURCE_DIR}/board.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/board.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/board-element.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/board-element.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/grid-tile.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/grid-tile.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tree.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tree.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ore.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ore.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ressource.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ressource.hpp
        PARENT_SCOPE)