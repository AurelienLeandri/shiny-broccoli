set(BROCCOLI_SOURCES ${BROCCOLI_SOURCES}
        # Add context .cpp files here
        ${CMAKE_CURRENT_SOURCE_DIR}/environment.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/environment.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/context.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/context.hpp
        PARENT_SCOPE)