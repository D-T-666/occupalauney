cmake_minimum_required(VERSION 3.15)
project(occupalauney)

# Dependencies
find_package(raylib 4.0.0 QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

set(CMAKE_CXX_STANDARD 17) # Requires C11 standard
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

file( GLOB_RECURSE LIB_SOURCES src/*.cpp )
add_executable(occupalauney ${LIB_SOURCES})

include_directories(occupalauney include)

target_link_libraries(occupalauney raylib)

# Checks if OSX and links appropriate frameworks (only required on MacOS)
if (APPLE)
    target_link_libraries(occupalauney "-framework IOKit")
    target_link_libraries(occupalauney "-framework Cocoa")
    target_link_libraries(occupalauney "-framework OpenGL")
elseif (LINUX)
    target_link_libraries(occupalauney glfw)
endif()

# file(COPY assets/tri-textures.png DESTINATION bin/assets)