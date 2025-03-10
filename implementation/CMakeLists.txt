cmake_minimum_required(VERSION 3.10)
project(SmartProcessManager CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the project root directory
set(PROJECT_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Explicitly set include and source directories
set(INCLUDE_DIR "${PROJECT_ROOT_DIR}/include")
set(SRC_DIR "${PROJECT_ROOT_DIR}/src")

# Include directories
include_directories(${INCLUDE_DIR})

add_executable(spm "${SRC_DIR}/main.cpp")

# Compiler-specific flags
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

# Windows-specific libraries
if(WIN32)
    target_link_libraries(spm kernel32)
endif()

# Define build output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
