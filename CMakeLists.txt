cmake_minimum_required(VERSION 3.19)

# set project name
project(eg-cpp VERSION 0.1.0 LANGUAGES CXX)
include(CheckIncludeFileCXX)
include(CheckLibraryExists)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
message(STATUS "CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}")

# add executable
add_executable(${PROJECT_NAME} src/main.cpp src/lds_sys.cpp)
configure_file(include/eg_cpp_config.cmake include/eg_cpp_config.hpp)

target_include_directories(${PROJECT_NAME}
	PUBLIC "${PROJECT_SOURCE_DIR}/include"
)
target_include_directories(${PROJECT_NAME}
	PUBLIC /opt/local/include
)
