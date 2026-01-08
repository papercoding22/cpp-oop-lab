cmake_minimum_required(VERSION 3.15)
project(CPP_OOP_Lab VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler warnings
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Output directories - each concept goes to its own subdirectory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/concepts)

# Auto-discover all concept directories
file(GLOB CONCEPT_DIRS "concepts/*")
foreach(CONCEPT_DIR ${CONCEPT_DIRS})
    if(IS_DIRECTORY ${CONCEPT_DIR} AND EXISTS ${CONCEPT_DIR}/CMakeLists.txt)
        get_filename_component(CONCEPT_NAME ${CONCEPT_DIR} NAME)
        message(STATUS "Found concept: ${CONCEPT_NAME}")
        add_subdirectory(${CONCEPT_DIR})
    endif()
endforeach()

# Print helpful message
message(STATUS "")
message(STATUS "C++ OOP Lab - Build Configuration Complete")
message(STATUS "To build a specific concept: make <concept_name>_demo")
message(STATUS "To build all concepts: make")
message(STATUS "")
