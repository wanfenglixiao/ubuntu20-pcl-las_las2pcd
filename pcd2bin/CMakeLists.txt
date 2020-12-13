cmake_minimum_required(VERSION 3.10)
project(pcd2bin)

set(CMAKE_CXX_STANDARD 17)
find_package(PCL 1.9 REQUIRED)
include_directories(${PCL_INCLUDE_DIRS})
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS})

FIND_PACKAGE( Boost 1.58 COMPONENTS program_options REQUIRED )


add_executable(pcd2bin main.cpp)
target_link_libraries (pcd2bin ${PCL_LIBRARIES} ${Boost_LIBRARIES})
