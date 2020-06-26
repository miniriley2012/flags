cmake_minimum_required(VERSION 3.17)
project(options)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} src/option_spec.cpp src/validations.cpp src/errors.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include)

if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    if (MSVC)
        # warning level 4 and all warnings as errors
        target_compile_options(${PROJECT_NAME} PRIVATE /W4 /WX)
    else ()
        # lots of warnings and all warnings as errors
        target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif ()

    if (BUILD_TESTING)
        add_subdirectory(tests)
    endif ()
endif ()

export(TARGETS ${PROJECT_NAME} NAMESPACE ${PROJECT_NAME}:: FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.cmake)