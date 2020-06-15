cmake_minimum_required(VERSION 3.17)
project(flags)

set(CMAKE_CXX_STANDARD 20)

add_library(flags src/option_spec.cpp src/validations.cpp src/errors.cpp)
target_include_directories(flags PUBLIC include)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    if (MSVC)
        # warning level 4 and all warnings as errors
        target_compile_options(flags PRIVATE /W4 /WX)
    else ()
        # lots of warnings and all warnings as errors
        target_compile_options(flags PRIVATE -Wall -Wextra -pedantic -Werror)
    endif ()

    if (BUILD_TESTING)
        add_subdirectory(tests)
    endif ()
endif ()

export(TARGETS flags NAMESPACE flags:: FILE ${PROJECT_BINARY_DIR}/flags.cmake)