cmake_minimum_required(VERSION 3.24)
project(rtimer
        VERSION 0.3.0
        LANGUAGES C
        DESCRIPTION
        "simple C lib for using timer functions in your project")

add_library(${PROJECT_NAME} rtimer.c rtimer.h rtimer_def.h)
target_include_directories(
        ${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)


if (MSVC OR MSYS OR MINGW)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DRTIMER_FOR_WINDOWS)
endif ()

if (APPLE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DRTIMER_FOR_APPLE)
endif ()

if (UNIX AND NOT APPLE)
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DRTIMER_FOR_UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE rt)
endif ()

#################### TEST SECTION #######################
if (NOT ${CMAKE_SYSTEM_NAME} MATCHES Generic)
    add_executable(${PROJECT_NAME}_test test/test.c)
    if (NOT TARGET runit)
        include(FetchContent)
        FetchContent_Declare(
                runit
                GIT_REPOSITORY https://github.com/RoboticsHardwareSolutions/runit.git
                GIT_TAG main
        )
        FetchContent_MakeAvailable(runit)
    endif ()

    target_link_libraries(${PROJECT_NAME}_test rtimer runit)
    enable_testing()
    add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
endif ()



#################### FORMAT SECTION #######################
include(FetchContent)
FetchContent_Declare(
        rlibhelper
        GIT_REPOSITORY https://github.com/RoboticsHardwareSolutions/rlibhelper.git
        GIT_TAG main
)
FetchContent_MakeAvailable(rlibhelper)

set(FILES_FOR_FORMATTING
        rtimer.c
        rtimer_def.h
        rtimer.h
        test/test.c
)
if (EXISTS "${rlibhelper_SOURCE_DIR}/format.cmake")
    include(${rlibhelper_SOURCE_DIR}/format.cmake)
else ()
    message(WARNING "format.cmake file not found")
endif ()
format_files(${PROJECT_NAME} SOURCES ${FILES_FOR_FORMATTING})

