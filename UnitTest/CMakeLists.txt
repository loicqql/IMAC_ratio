cmake_minimum_required(VERSION 3.13)

enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(UnitTests src/sample_test.cpp)
target_link_libraries(UnitTests PUBLIC Ratio GTest::GTest GTest::Main)
target_compile_features(UnitTests PRIVATE cxx_std_14)

gtest_discover_tests(UnitTests)