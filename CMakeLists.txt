cmake_minimum_required(VERSION 3.13)

# give a name to the project
project(ratioProject)

# add ratio
message(STATUS "ratio cmake part ..." )
add_subdirectory(ratio INTERFACE)
include_directories(${CMAKE_SOURCE_DIR}/ratio/include) # important : other projects call by this cmake will know this include directory

# add example
message(STATUS "example cmake part ..." )
add_subdirectory(example)

# add UnitTest
find_package(GTest OPTIONAL_COMPONENTS)
if(GTEST_FOUND)
	message(STATUS "UnitTest cmake part ..." )
	add_subdirectory(UnitTest)
elseif()
	message(WARNING "google test not found, skipping UnitTest ..." )
endif()