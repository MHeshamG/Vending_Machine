cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(vending-machine)

# Executable srcs
set(EXE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
    )

add_executable(vending-machine-exe ${EXE_SOURCES})

target_compile_features(vending-machine-exe
    PRIVATE
        cxx_std_17
)