cmake_minimum_required(VERSION 3.9)
project(rtimer
        VERSION 0.3.0
        LANGUAGES C
        DESCRIPTION
        "simple C lib for using timer functions in your project")

add_library(rtimer rtimer.c rtimer.h rtimer_def.h)


add_executable(${PROJECT_NAME}_test
        tests/test.c
        rtimer.c)


if (arm-none-eabi-gcc)
    if (NOT NO_STATIC_ANALYSIS)
        # clang-tidy (separate config files per directory)
        find_program(clang_tidy NAMES clang-tidy)
        if (NOT clang_tidy)
            message(FATAL_ERROR "Could not locate clang-tidy")
        endif ()
        message(STATUS "Using clang-tidy: ${clang_tidy}")
        set(CMAKE_C_CLANG_TIDY ${clang_tidy})
        set(CMAKE_CXX_CLANG_TIDY ${clang_tidy})
    endif ()
endif ()

#target_include_directories(${PROJECT_NAME}_test PRIVATE c)
#include(tests/runit/compiler_flags.cmake) # uncomment it for test

# for tests for lib

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

# for tests

if (MSVC OR MSYS OR MINGW)
    target_compile_definitions(${PROJECT_NAME}_test PUBLIC -DRTIMER_FOR_WINDOWS)
    target_link_libraries(${PROJECT_NAME} PRIVATE runit )
endif ()

if (APPLE)
    target_compile_definitions(${PROJECT_NAME}_test PUBLIC -DRTIMER_FOR_APPLE)
    target_link_libraries(${PROJECT_NAME}_test runit )
endif ()

if (UNIX AND NOT APPLE)
    target_compile_definitions(${PROJECT_NAME}_test PUBLIC -DRTIMER_FOR_UNIX)
    target_link_libraries(${PROJECT_NAME}_test PRIVATE rt runit)
endif ()

set(FILES_FOR_FORMATTING
        rtimer.c
        rtimer_def.h
        rtimer.h
        )

# clang-format
find_program(clang_format NAMES clang-format)
if (NOT clang_format)
    message(STATUS "Could not locate clang-format")
else ()
    file(GLOB format_files ${FILES_FOR_FORMATTING})
    message(STATUS "Using clang-format: ${clang_format}; files: ${format_files}")
    add_custom_target(format_rtimer COMMAND ${clang_format} -i -fallback-style=none -style=file --verbose ${format_files})
endif ()


enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
