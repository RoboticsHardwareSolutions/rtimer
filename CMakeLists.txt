cmake_minimum_required(VERSION 3.9)
project(rtimer
        VERSION 0.3.0
        LANGUAGES C
        DESCRIPTION
        "simple C lib for using timer functions in your project")

add_library(${PROJECT_NAME} rtimer.c)

target_include_directories(
        ${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)


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


# Test runner executable testing the static library
if (NOT ${CMAKE_SYSTEM_NAME} MATCHES Generic)
    add_executable(${PROJECT_NAME}_test
            tests/test.c
            rtimer.c)

    if (MSVC OR MSYS OR MINGW)
        target_compile_definitions(${PROJECT_NAME}_test PUBLIC -DRTIMER_FOR_WINDOWS)
        target_link_libraries(${PROJECT_NAME}_test PRIVATE runit)
    endif ()

    if (APPLE)
        target_compile_definitions(${PROJECT_NAME}_test PUBLIC -DRTIMER_FOR_APPLE)
        target_link_libraries(${PROJECT_NAME}_test runit)
    endif ()

    if (UNIX AND NOT APPLE)
        target_compile_definitions(${PROJECT_NAME}_test PUBLIC -DRTIMER_FOR_UNIX)
        target_link_libraries(${PROJECT_NAME}_test PRIVATE rt runit)
    endif ()

    enable_testing()
    add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)
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
