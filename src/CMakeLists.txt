add_subdirectory(agent)
add_subdirectory(context)
add_subdirectory(scheduler)
add_subdirectory(utils)

add_library(
        broccoli SHARED ${BROCCOLI_SOURCES}
        )
