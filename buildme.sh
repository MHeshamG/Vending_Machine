#!/bin/bash

source scripts/styling.sh

BUILD_DIR="build"

# Check if the build directory exists
if [ ! -d "$BUILD_DIR" ]; then
    # If the build directory doesn't exist, create it
    mkdir "$BUILD_DIR"
    green_log "Build directory '$BUILD_DIR' created successfully."
fi

# Change directory to the build directory
cd "$BUILD_DIR" || exit

# Run CMake to generate build files using Ninja
yellow_log "[Step 1] Running CMake to generate build files using Ninja..."
if cmake .. -GNinja -DCMAKE_TOOLCHAIN_FILE="conan_toolchain.cmake" -DCMAKE_BUILD_TYPE=Release; then
    green_log "CMake configuration completed successfully."
else
    red_log_and_exit "CMake configuration failed."
fi

# Run Ninja to start the build process
yellow_log "[Step 2] Running Ninja to build the project..."
if ninja; then
    green_log "Build process completed successfully."
else
    red_log_and_exit "Build process failed."
fi
