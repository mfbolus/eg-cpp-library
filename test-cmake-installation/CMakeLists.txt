cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

# set project name and version (MAJOR.minor.patch)
# for project name, use lowercase
project(test VERSION 0.1.0 LANGUAGES CXX C)
# some name variants I will be using:
set(CMAKE_PROJECT_NAME_CAP TEST)#all caps
set(CMAKE_PROJECT_NAME_CAMEL Test)#CamelCase

# Specify C++ standard
# n.b. this has to be before adding targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
message(STATUS "CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}")

include(CheckIncludeFileCXX) # from docs: CHECK_INCLUDE_FILE_CXX(<include> <variable> [<flags>])
include(CheckLibraryExists) # from docs: CHECK_LIBRARY_EXISTS(LIBRARY FUNCTION LOCATION VARIABLE)

# Let user know where things getting installed since they did not specify
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  message(STATUS "*** CMAKE_INSTALL_PREFIX was initalised by cmake to the default value of ${CMAKE_INSTALL_PREFIX} ...")
endif()

# Adhere to GNU filesystem layout conventions
include(GNUInstallDirs)

############ OPTIONS
####################
# For usage later with clangd
option(CMAKE_EXPORT_COMPILE_COMMANDS "Whether to export compile commands to json file." ON)

message(STATUS "CMAKE_SYSTEM_NAME          = ${CMAKE_SYSTEM_NAME}"         )
message(STATUS "CMAKE_CXX_COMPILER_ID      = ${CMAKE_CXX_COMPILER_ID}"     )
message(STATUS "CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "CMAKE_COMPILER_IS_GNUCXX   = ${CMAKE_COMPILER_IS_GNUCXX}"  )
message(STATUS "")
message(STATUS "*** Looking for external libraries")

############ FIND LIBRARIES
###########################
# For each dependecy, check whether exists and get include directory (list CMAKE_REQUIRED_INCLUDES) and absolute path to library (list PROJECT_REQUIRED_LIBS).
set(PROJECT_REQUIRED_LIBS)

# There may be differences in how you handle this as a function of OS
if(APPLE)
  message(STATUS "Detected macOS")
  # set(CMAKE_MACOSX_RPATH 1)
  set(CMAKE_INSTALL_RPATH "@executable_path/../lib")
elseif(UNIX)
  message(STATUS "Detected Unix")
  set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
  # from armadillo re linux:
  # "necessary when linking with Intel MKL on Linux systems"
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-as-needed")
endif()

# should return egcpp
find_package(EgCpp REQUIRED)

# Set optimization level
# (have to check if a compiler that supports)
if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
else()
  if(DEFINED CMAKE_CXX_COMPILER_ID)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    elseif(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    endif()
  endif()
endif()

# Finished configuring: print status
message(STATUS "CMAKE_CXX_FLAGS           = ${CMAKE_CXX_FLAGS}"          )
message(STATUS "CMAKE_SHARED_LINKER_FLAGS = ${CMAKE_SHARED_LINKER_FLAGS}")
message(STATUS "CMAKE_REQUIRED_INCLUDES   = ${CMAKE_REQUIRED_INCLUDES}"  )

####### Add targets
###################
# e.g., add executable
add_executable(test src/main.cpp)
target_link_libraries(test PUBLIC egcpp)
