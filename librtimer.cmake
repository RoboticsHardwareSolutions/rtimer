if (MSVC OR MSYS OR MINGW)
    add_definitions(-DRTIMER_FOR_WINDOWS)
endif ()

if (APPLE)
    add_definitions(-DRTIMER_FOR_APPLE)
endif ()

if (UNIX AND NOT APPLE)
    add_definitions(-DRTIMER_FOR_UNIX)
endif ()

set(RTIMER_DIRECTORIES  rtimer )
set(RTIMER_EXECUTABLE_FILES  rtimer/rtimer.c)




