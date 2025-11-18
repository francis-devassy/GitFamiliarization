# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I. -IappTimer

# Debug flags
DEBUG_FLAGS = -g -O0

# Cross compiler for Raspberry Pi
CC_RPI = arm-linux-gnueabihf-gcc

# Targets
LINUX_TARGET = release/main_linux
RPI_TARGET   = release/main_rpi
DEBUG_TARGET = debug/main_debug
DEBUG_RPI    = debug/main_rpi_debug

# Sources
SRCS = main.c appTimer/appTimer.c

# Objects
RELEASE_OBJS = $(SRCS:%.c=release/%.o)
DEBUG_OBJS   = $(SRCS:%.c=debug/%.o)

# Default goal
.DEFAULT_GOAL := all

# Build all targets
all: linux rpi debug debug_rpi

# Native Linux build
linux: $(LINUX_TARGET)

$(LINUX_TARGET): $(RELEASE_OBJS) | release_dir
	$(CC) $(CFLAGS) -o $@ $(RELEASE_OBJS)

# Raspberry Pi release build
rpi: $(RPI_TARGET)

$(RPI_TARGET): $(SRCS) | release_dir
	$(CC_RPI) $(CFLAGS) $^ -o $@

# Debug build (Linux)
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(DEBUG_OBJS) | debug_dir
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -o $@ $(DEBUG_OBJS)

# Debug build (Raspberry Pi)
debug_rpi: $(DEBUG_RPI)

$(DEBUG_RPI): $(SRCS) | debug_dir
	$(CC_RPI) $(CFLAGS) $(DEBUG_FLAGS) $^ -o $@

# Compile each .c file into .o (release)
release/%.o: %.c customTypes.h appTimer/appTimer.h | release_dir
	$(CC) $(CFLAGS) -c $< -o $@

# Compile each .c file into .o (debug)
debug/%.o: %.c customTypes.h appTimer/appTimer.h | debug_dir
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -c $< -o $@

# Ensure directories exist
release_dir:
	mkdir -p release/appTimer

debug_dir:
	mkdir -p debug/appTimer

# Run debug build inside gdb (Linux)
gdb: $(DEBUG_TARGET)
	gdb $(DEBUG_TARGET)

# Clean build artifacts
clean:
	rm -rf release debug
