cmake_minimum_required(VERSION 3.10)
project(AppTimerProject C)

# Sources
set(SRCS
    main.c
    appTimer/appTimer.c
)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/appTimer
)

# Compiler flags
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

# --- Native Linux Builds ---
add_executable(main_linux ${SRCS})
set_target_properties(main_linux PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release
)

add_executable(main_debug ${SRCS})
set_target_properties(main_debug PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug
)
target_compile_options(main_debug PRIVATE -g -O0)

# --- Raspberry Pi Builds (Cross Compilation) ---
# To build for Raspberry Pi, invoke cmake with:
#   cmake -DCMAKE_TOOLCHAIN_FILE=toolchains/raspberrypi.cmake ..
#
# Example toolchain file (toolchains/raspberrypi.cmake):
#   set(CMAKE_SYSTEM_NAME Linux)
#   set(CMAKE_SYSTEM_PROCESSOR arm)
#   set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc)

add_executable(main_rpi ${SRCS})
set_target_properties(main_rpi PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/release
)

add_executable(main_rpi_debug ${SRCS})
set_target_properties(main_rpi_debug PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug
)
target_compile_options(main_rpi_debug PRIVATE -g -O0)

# --- Custom Targets ---
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E rm -rf ${CMAKE_BINARY_DIR}/release ${CMAKE_BINARY_DIR}/debug
    COMMENT "Cleaning all build artifacts"
)

add_custom_target(gdb
    COMMAND gdb ${CMAKE_BINARY_DIR}/debug/main_debug
    DEPENDS main_debug
    COMMENT "Run debug build inside gdb"
)
