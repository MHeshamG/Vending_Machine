cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(vending-machine)

# Executable srcs
set(EXE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/VendingMachine.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Product.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/states/VendingMachineState.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/states/IdleState.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/states/HasMoneyState.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/states/ProductSelectedState.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/states/LockState.cpp"
   )

add_executable(vending-machine-exe ${EXE_SOURCES})

target_compile_features(vending-machine-exe
    PRIVATE
        cxx_std_17
)

target_include_directories(vending-machine-exe PUBLIC 
                           "${CMAKE_CURRENT_SOURCE_DIR}/src" 
                           "${CMAKE_CURRENT_SOURCE_DIR}/src/states"
                          )