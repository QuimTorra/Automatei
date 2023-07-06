cmake_minimum_required(VERSION 3.12)
project(AutomateiEngine)

# Set the C++ standard to use
set(CMAKE_CXX_STANDARD 14)

# Find the SDL2 library
find_package(SDL2 REQUIRED)

# Add the include directories for SDL2
include_directories(${SDL2_INCLUDE_DIRS})

# Name of the program
set(PROG_NAME automateiEngine)

# Add the source files of your program
set(SOURCES main.cpp)

# Add all header files in the src directory
file(GLOB HEADERS "src/*.h")

# Add all implementation files in the src directory
file(GLOB IMPLEMENTATIONS "src/*.cpp")

# Create the executable
add_executable(${PROG_NAME} ${SOURCES} ${HEADERS} ${IMPLEMENTATIONS})

# Link against the SDL2 library
target_link_libraries(${PROG_NAME} ${SDL2_LIBRARIES})