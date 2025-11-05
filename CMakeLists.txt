cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

project(Tenderer VERSION 1.0)
project(Application VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin/)

file(GLOB_RECURSE SRC_FILES Tenderer/src/*.cpp Tenderer/Vendor/src/*.cpp)
file(GLOB_RECURSE SRC_SANDBOX_FILES Sandbox/*.cpp Sandbox/vendor/src/*.cpp)

add_compile_options(-Wall -Wextra -Wpedantic)
add_library(Tenderer STATIC ${SRC_FILES})
target_include_directories(Tenderer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Tenderer/src ${CMAKE_CURRENT_SOURCE_DIR}/Tenderer/Vendor/include)

add_executable(Application ${SRC_SANDBOX_FILES})
target_include_directories(Application PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Tenderer/src ${CMAKE_CURRENT_SOURCE_DIR}/Tenderer/Vendor/include)
target_link_libraries(Application PUBLIC Tenderer)



