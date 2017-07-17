add_subdirectory(agent)
add_subdirectory(context)
add_subdirectory(scheduler)

add_library(
        broccoli SHARED ${BROCCOLI_SOURCES}
        )
