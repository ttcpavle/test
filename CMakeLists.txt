cmake_minimum_required(VERSION 3.11)  # For FetchContent - version 3.11+ required

# vcpkg
if(DEFINED ENV{VCPKG_ROOT})
    message(STATUS "VCPKG found")
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
    if(DEFINED ENV{VCPKG_DEFAULT_TRIPLET})
        set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}")
    else()
        set(VCPKG_TARGET_TRIPLET "x64-windows")
    endif()
endif()

project(MyRaylibProject)
find_package(raylib QUIET) # QUIET or REQUIRED

# if raylib is not found via find_package() and host is UNIX
if(NOT raylib_FOUND AND UNIX)
    find_path(raylib_INCLUDE_DIRS raylib.h
        HINTS /usr/local/include /usr/include
    )
    
    find_library(raylib_LIBRARIES
        NAMES raylib libraylib
        HINTS /usr/local/lib /usr/lib
    )
    
    if(raylib_INCLUDE_DIRS AND raylib_LIBRARIES)
        set(raylib_FOUND TRUE)
    endif()
endif()

# if raylib is not found, fetch from github
set(RAYLIB_VERSION 5.5)
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_MakeAvailable(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_GAMES OFF CACHE BOOL "" FORCE) # don't build the supplied example games
  endif()
endif()

file(GLOB PROJECT_SOURCES "src/*.cpp")
file(GLOB PROJECT_INCLUDE "src/*.h")

# Declaring our executable
add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_INCLUDE})
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()