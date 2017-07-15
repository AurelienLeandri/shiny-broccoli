add_subdirectory(agent)
add_subdirectory(context)
add_subdirectory(scheduler)

add_library(
        broccoli SHARED ${BROCCOLI_SOURCES}
        scheduler/scheduler.cpp scheduler/scheduler.hpp context/context.cpp context/context.hpp)
