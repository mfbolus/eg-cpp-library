cmake_minimum_required(VERSION 3.19)

# set project name
project(eg-cpp VERSION 0.1.0 LANGUAGES CXX)
include(CheckIncludeFileCXX)
include(CheckLibraryExists)

# Specify C++ standard
# n.b. this has to be before adding targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
message(STATUS "CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}")

# For each dependecy, check whether exists and get include directory and absolute path.
set(PROJECT_LIBS)

# ARMADILLO
# TODO(mfbolus): Create a FindArma in cmake_aux dir
# find
find_library(ARMA_LIB armadillo REQUIRED)
list(APPEND PROJECT_LIBS ${ARMA_LIB})
set(ARMA_INCLUDES_DIR /opt/local/include)
list(APPEND CMAKE_REQUIRED_INCLUDES ${ARMA_INCLUDES_DIR})

# With variables/includes configured, configure the template header,
# copy the source, and add include directories to entire project.
message(STATUS "Copying ${PROJECT_SOURCE_DIR}/include/ to ${PROJECT_BINARY_DIR}/include/")
file(COPY ${PROJECT_SOURCE_DIR}/include/eg_cpp_h/ DESTINATION ${PROJECT_BINARY_DIR}/include/eg_cpp_h/)

message(STATUS "Generating ${PROJECT_BINARY_DIR}/include/eg_cpp")
configure_file(${PROJECT_SOURCE_DIR}/include/eg_cpp.in ${PROJECT_BINARY_DIR}/include/eg_cpp)

# c.f. target_include_directories()
include_directories(${PROJECT_BINARY_DIR}/include/ ${CMAKE_REQUIRED_INCLUDES})

# Finished configuring: print status
message(STATUS "CMAKE_CXX_FLAGS           = ${CMAKE_CXX_FLAGS}"          )
message(STATUS "CMAKE_SHARED_LINKER_FLAGS = ${CMAKE_SHARED_LINKER_FLAGS}")
message(STATUS "CMAKE_REQUIRED_INCLUDES   = ${CMAKE_REQUIRED_INCLUDES}"  )

# add targets
# library itself
add_subdirectory(src)

# examples
add_subdirectory(examples)

# ################################################################################
# # INSTALL CONFIGURATION
# message(STATUS ""                                                      )
# message(STATUS "CMAKE_INSTALL_PREFIX     = ${CMAKE_INSTALL_PREFIX}"    )
# message(STATUS "CMAKE_INSTALL_LIBDIR     = ${CMAKE_INSTALL_LIBDIR}"    )
# message(STATUS "CMAKE_INSTALL_INCLUDEDIR = ${CMAKE_INSTALL_INCLUDEDIR}")
# message(STATUS "CMAKE_INSTALL_DATADIR    = ${CMAKE_INSTALL_DATADIR}"   )
# message(STATUS "CMAKE_INSTALL_BINDIR     = ${CMAKE_INSTALL_BINDIR}"    )

# # Note that the trailing / character in "include/" is critical
# install(DIRECTORY ${PROJECT_BINARY_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
# PATTERN ".svn" EXCLUDE
# PATTERN "*.cmake" EXCLUDE
# PATTERN "*~" EXCLUDE
# PATTERN "*orig" EXCLUDE
# )

# install(TARGETS armadillo EXPORT ArmadilloLibraryDepends
#   ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#   RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# # Export the package for use from the build-tree
# # (this registers the build-tree with a global CMake-registry)
# export(PACKAGE egcpp)
