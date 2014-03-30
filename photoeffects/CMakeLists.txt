CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

set(PROJECT_NAME photoeffects)
PROJECT(${PROJECT_NAME})

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# FIXME: make it work (Kirill Kornyakov)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/")

set( PHOTOEFFECTS_LIBRARY ${PROJECT_NAME} )
set( PHOTOEFFECTS_TESTS "${PROJECT_NAME}_test" )

find_package(OpenCV REQUIRED)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/3rdparty")

set(LIBRARY_DEPS ${OpenCV_LIBS})

# BUILD
add_subdirectory(3rdparty)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(samples)

# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME} =====================================")
message( STATUS "")
message( STATUS "   Configuration:           ${CMAKE_BUILD_TYPE}")
message( STATUS "   OpenCV build path:       ${OpenCV_DIR}")
