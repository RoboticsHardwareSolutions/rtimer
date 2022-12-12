if (MSVC OR MSYS OR MINGW)
    add_definitions(-DRTIMER_FOR_WINDOWS)
endif ()

if (APPLE)
    add_definitions(-DRTIMER_FOR_APPLE)
endif ()

if (UNIX AND NOT APPLE)
    add_definitions(-DRTIMER_FOR_UNIX)
    set(RTIMER_LIBRARIES  rt )
endif ()

set(RTIMER_DIRECTORIES  ${CMAKE_CURRENT_LIST_DIR} )
set(RTIMER_EXECUTABLE_FILES  ${CMAKE_CURRENT_LIST_DIR}/rtimer.c)




