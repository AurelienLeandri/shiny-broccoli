set(BROCCOLI_SOURCES ${BROCCOLI_SOURCES}
        # Add context .cpp files here
        ${CMAKE_CURRENT_SOURCE_DIR}/thread_pool.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/thread_pool_agent.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/thread_pool_lock_free.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/thread_pool_agent_lock_free.cpp
        PARENT_SCOPE
        )
