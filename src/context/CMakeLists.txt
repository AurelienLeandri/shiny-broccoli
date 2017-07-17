set(BROCCOLI_SOURCES ${BROCCOLI_SOURCES}
        # Add context .cpp files here
        ${CMAKE_CURRENT_SOURCE_DIR}/environment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/environment.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/context.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/context.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/grid-element.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/grid-element.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/grid.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/grid.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/grid-point.hpp
        PARENT_SCOPE)