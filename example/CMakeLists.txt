cmake_minimum_required(VERSION 3.13)

# give a name to the project
project(example)

# find Ratio
# if build as standalone project, find the lib by yourself ...
# if build transitively 

add_executable(example src/main.cpp)                # file to compile and name of the app
target_link_libraries(example PRIVATE Ratio)      # lib dependency

# compilation flags
target_compile_features(example PRIVATE cxx_std_14) # use at least c++ 14
if (MSVC)
    target_compile_options(example PRIVATE /W3)
else()
    target_compile_options(example PRIVATE -Wall -Wextra -Wpedantic -pedantic-errors)
endif()
