cmake_minimum_required(VERSION 3.16)

# Project name and language
project(oddBox
    VERSION 1.0
    LANGUAGES C
)

# Use modern C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(COMMON_SRC
    ${PROJECT_SOURCE_DIR}/oddBox.c
    ${PROJECT_SOURCE_DIR}/data_generator/data_generator.c
    ${PROJECT_SOURCE_DIR}/file_writer/file_writer.c
)

# Create executable
add_executable(oddBox
    ${COMMON_SRC}
)

# Include directories
target_include_directories(oddBox
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/data_generator
        ${PROJECT_SOURCE_DIR}/file_writer
)

# Compiler warnings
if (MSVC)
    target_compile_options(oddBox PRIVATE /W4)
else()
    target_compile_options(oddBox PRIVATE -Wall -Wextra -Wpedantic)
endif()

