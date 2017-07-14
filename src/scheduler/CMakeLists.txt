set(BROCCOLI_SOURCES ${BROCCOLI_SOURCES}
        # Add context .cpp files here
        ${CMAKE_CURRENT_SOURCE_DIR}/data-manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/action.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/action-result.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/data-update.cpp
        PARENT_SCOPE
        )
