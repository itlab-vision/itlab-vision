CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

set(PROJECT_NAME photoeffects)
project(${PROJECT_NAME})

option(WITH_TBB "Include Intel TBB support" OFF)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE})

set(PHOTOEFFECTS_LIBRARY ${PROJECT_NAME})
set(PHOTOEFFECTS_TESTS "${PROJECT_NAME}_test")

find_package(OpenCV REQUIRED)

set(PHOTOEFFECTS_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${PHOTOEFFECTS_INCLUDE}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/3rdparty")

set(LIBRARY_DEPS ${OpenCV_LIBS})
if (WITH_TBB)
  include(cmake/DetectTBB.cmake)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_TBB")
endif()

# BUILD
add_subdirectory(3rdparty)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(samples)

# REPORT
message( STATUS "")
message( STATUS "General configuration for ${PROJECT_NAME} =====================================")
message( STATUS "")
message( STATUS "   Configuration:       ${CMAKE_BUILD_TYPE}")
message( STATUS "   OpenCV build path:   ${OpenCV_DIR}")
