cmake_minimum_required(VERSION 2.8)
project(las2pcd)

find_package(PCL 1.9 REQUIRED)
find_package(libLAS REQUIRED)

include_directories(${PCL_INCLUDE_DIRS})

link_directories(${PCL_LIBRARY_DIRS})

add_definitions(${PCL_DEFINITIONS})

add_executable (las2pcd las2pcd.cpp)
target_link_libraries (las2pcd ${PCL_LIBRARIES} ${libLAS_LIBRARIES})
