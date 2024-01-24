cmake_minimum_required(VERSION 3.17 FATAL_ERROR)

project(vending-machine)

# Find the GTest package
find_package(GTest REQUIRED)


# Sources
set(SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/CommandLineVendingMachineView.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/VendingMachinePresenter.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/VendingMachine.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/Product.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/states/VendingMachineState.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/states/IdleState.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/states/HasMoneyState.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/states/ProductSelectedState.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/states/LockState.cpp"
)


# Executable sources
set(EXE_SOURCES
    "${SOURCES}"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
)

add_executable(vending-machine-exe ${EXE_SOURCES})

target_compile_features(vending-machine-exe PRIVATE cxx_std_17)

target_include_directories(vending-machine-exe PUBLIC 
                           "${CMAKE_CURRENT_SOURCE_DIR}/src" 
                           "${CMAKE_CURRENT_SOURCE_DIR}/src/states"
)

# Test sources
set(TEST_SOURCES
    "${SOURCES}"
    "${CMAKE_CURRENT_SOURCE_DIR}/test/VendingMachineTest.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test/ProductTest.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test/IdleStateTest.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test/HasMoneyStateTest.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test/ProductSelectedStateTest.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test/LockStateTest.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test/VendingMachineIntegrationTest.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/test/main.cpp"
)

# Add the test executable
add_executable(vending-machine-tests ${TEST_SOURCES})

target_compile_features(vending-machine-tests PRIVATE cxx_std_17)

target_include_directories(vending-machine-tests PUBLIC 
                           "${CMAKE_CURRENT_SOURCE_DIR}/src"
                           "${CMAKE_CURRENT_SOURCE_DIR}/src/states"
                           "${CMAKE_CURRENT_SOURCE_DIR}/test"
)

# Link test executable against gtest and your project's source code
target_link_libraries(vending-machine-tests GTest::gtest_main GTest::gtest GTest::gmock GTest::gmock_main)