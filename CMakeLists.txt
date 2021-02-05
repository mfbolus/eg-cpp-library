cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

# set project name and version (MAJOR.minor.patch)
project(egcpp VERSION 0.1.0 LANGUAGES CXX C)

# Specify C++ standard
# n.b. this has to be before adding targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
message(STATUS "CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}")

include(CheckIncludeFileCXX) # from docs: CHECK_INCLUDE_FILE_CXX(<include> <variable> [<flags>])
include(CheckLibraryExists) # from docs: CHECK_LIBRARY_EXISTS(LIBRARY FUNCTION LOCATION VARIABLE)

# For usage later with clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)


# TODO(mfbolus): armadillo sets CMAKE_CXX_FLAGS as a function of the compiler/compiler version. I'm skipping for now.

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  message(STATUS "*** CMAKE_INSTALL_PREFIX was initalised by cmake to the default value of ${CMAKE_INSTALL_PREFIX} ...")
endif()

# Adhere to GNU filesystem layout conventions
include(GNUInstallDirs)

############ OPTIONS
####################
if(MSVC)
  option(BUILD_SHARED_LIBS "build shared library" OFF)
else()
  option(BUILD_SHARED_LIBS "build shared library" ON)
endif()

option(DETECT_HDF5 "Detect HDF5 and include HDF5 support, if found." OFF)
# set(DETECT_HDF5 true)
# uncomment the above line to enable the detection of the HDF5 library;
# you can also enable HDF5 detection directly on the command line:
# cmake -D DETECT_HDF5=true
set(EGCPP_USE_HDF5 false)

option(BUILD_EXAMPLES "Build the example programs." ON)
# disable:
# cmake -D BUILD_SMOKE_TEST=false .

message(STATUS "CMAKE_SYSTEM_NAME          = ${CMAKE_SYSTEM_NAME}"         )
message(STATUS "CMAKE_CXX_COMPILER_ID      = ${CMAKE_CXX_COMPILER_ID}"     )
message(STATUS "CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "CMAKE_COMPILER_IS_GNUCXX   = ${CMAKE_COMPILER_IS_GNUCXX}"  )
message(STATUS "BUILD_SHARED_LIBS          = ${BUILD_SHARED_LIBS}"         )
message(STATUS "DETECT_HDF5                = ${DETECT_HDF5}"               )
message(STATUS "BUILD_EXAMPLES           = ${BUILD_EXAMPLES}"          )
message(STATUS "")
message(STATUS "*** Looking for external libraries")

############ FIND LIBRARIES
###########################
# For each dependecy, check whether exists and get include directory (list CMAKE_REQUIRED_INCLUDES) and absolute path to library (list PROJECT_REQUIRED_LIBS).
set(PROJECT_REQUIRED_LIBS)

# There may be differences in how you handle this as a function of
if(APPLE)
  message(STATUS "Detected macOS")
  set(CMAKE_MACOSX_RPATH 1)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  message(STATUS "Detected Linux")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake_aux/Modules/")

find_package(PkgConfig)

# ARMADILLO
include(FindArmadillo)
include(DetectHDF5)

# after getting these lists, take out duplicates
list(REMOVE_DUPLICATES PROJECT_REQUIRED_LIBS)
list(REMOVE_DUPLICATES CMAKE_REQUIRED_INCLUDES)

message(STATUS "")
message(STATUS "*** Project will use the following libraries:")
message(STATUS "*** PROJECT_REQUIRED_LIBS = ${PROJECT_REQUIRED_LIBS}")
message(STATUS "")

# With variables/includes configured, configure the template header,
# copy the source, and add include directories to entire project.
message(STATUS "Copying ${PROJECT_SOURCE_DIR}/include/ to ${PROJECT_BINARY_DIR}/include/")
file(COPY ${PROJECT_SOURCE_DIR}/include/eg_cpp_h/ DESTINATION ${PROJECT_BINARY_DIR}/include/eg_cpp_h/)

message(STATUS "Generating ${PROJECT_BINARY_DIR}/include/eg_cpp")
configure_file(${PROJECT_SOURCE_DIR}/include/eg_cpp.in ${PROJECT_BINARY_DIR}/include/eg_cpp)

# c.f. target_include_directories()
include_directories(${PROJECT_BINARY_DIR}/include/ ${CMAKE_REQUIRED_INCLUDES})

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

# add targets
# library itself
add_library(${CMAKE_PROJECT_NAME} SHARED)
target_link_libraries(${CMAKE_PROJECT_NAME} ${PROJECT_REQUIRED_LIBS})
target_include_directories(${CMAKE_PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include> $<INSTALL_INTERFACE:include>)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES VERSION ${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}.${CMAKE_PROJECT_VERSION_PATCH} SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})
add_subdirectory(src) #add source files...

# examples
if(BUILD_EXAMPLES)
  add_subdirectory(examples)
endif()

################################################################################
# INSTALL CONFIGURATION
message(STATUS ""                                                      )
message(STATUS "CMAKE_INSTALL_PREFIX     = ${CMAKE_INSTALL_PREFIX}"    )
message(STATUS "CMAKE_INSTALL_LIBDIR     = ${CMAKE_INSTALL_LIBDIR}"    )
message(STATUS "CMAKE_INSTALL_INCLUDEDIR = ${CMAKE_INSTALL_INCLUDEDIR}")
message(STATUS "CMAKE_INSTALL_DATADIR    = ${CMAKE_INSTALL_DATADIR}"   )
message(STATUS "CMAKE_INSTALL_BINDIR     = ${CMAKE_INSTALL_BINDIR}"    )


# Note that the trailing / character in "include/" is critical
install(DIRECTORY ${PROJECT_BINARY_DIR}/include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
PATTERN ".svn" EXCLUDE
PATTERN "*.cmake" EXCLUDE
PATTERN "*~" EXCLUDE
PATTERN "*orig" EXCLUDE
)

install(TARGETS ${CMAKE_PROJECT_NAME} EXPORT EgCppDepends
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE ${CMAKE_PROJECT_NAME})

## LOCAL FILES
# Create {Project}Config.cmake file for the use from the build tree
set(LOCAL_INCLUDE_DIRS "${PROJECT_BINARY_DIR}/include")
set(LOCAL_LIB_DIR      "${PROJECT_BINARY_DIR}")
set(LOCAL_CMAKE_DIR    "${PROJECT_BINARY_DIR}")


message(STATUS "Generating '${PROJECT_BINARY_DIR}/EgCppConfig.cmake'")
# copy/change config and configVersion file (modify only the @xyz@ variables)
configure_file(${PROJECT_SOURCE_DIR}/cmake_aux/InstallFiles/EgCppConfig.cmake.in
  "${PROJECT_BINARY_DIR}/EgCppConfig.cmake" @ONLY)

message(STATUS "Generating '${PROJECT_BINARY_DIR}/EgCppConfigVersion.cmake'")
configure_file(${PROJECT_SOURCE_DIR}/cmake_aux/InstallFiles/EgCppConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/EgCppConfigVersion.cmake" @ONLY)

# Install the export set for use with the install-tree
install(EXPORT EgCppDepends DESTINATION
  "${CMAKE_INSTALL_DATADIR}/EgCpp/CMake"
  COMPONENT dev)

## GLOBAL INSTALL FILES
# Create EgCppConfig.cmake file for the use from the install tree
# and install it
set(EGCPP_INCLUDE_DIRS "${CMAKE_INSTALL_FULL_INCLUDEDIR}")
set(EGCPP_LIB_DIR      "${CMAKE_INSTALL_FULL_LIBDIR}")
set(EGCPP_CMAKE_DIR    "${CMAKE_INSTALL_FULL_DATADIR}/EgCpp/CMake")

# copy/change config and configVersion file (modify only the @xyz@ variables)
message(STATUS "Generating '${PROJECT_BINARY_DIR}/InstallFiles/EgCppConfig.cmake'")
configure_file(${PROJECT_SOURCE_DIR}/cmake_aux/InstallFiles/EgCppConfig.cmake.in
  "${PROJECT_BINARY_DIR}/InstallFiles/EgCppConfig.cmake" @ONLY)

message(STATUS "Generating '${PROJECT_BINARY_DIR}/InstallFiles/EgCppConfigVersion.cmake'")
configure_file(${PROJECT_SOURCE_DIR}/cmake_aux/InstallFiles/EgCppConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/InstallFiles/EgCppConfigVersion.cmake" @ONLY)

# Install files to be found by cmake users with find_package()
install(FILES
  "${PROJECT_BINARY_DIR}/InstallFiles/EgCppConfig.cmake"
  "${PROJECT_BINARY_DIR}/InstallFiles/EgCppConfigVersion.cmake"
  DESTINATION "${EGCPP_CMAKE_DIR}" COMPONENT dev)


# pkgconfig related
message(STATUS "Copying ${PROJECT_SOURCE_DIR}/misc/ to ${PROJECT_BINARY_DIR}/misc/")
file(COPY ${PROJECT_SOURCE_DIR}/misc/ DESTINATION ${PROJECT_BINARY_DIR}/misc/)

message(STATUS "Generating '${PROJECT_BINARY_DIR}/misc/${CMAKE_PROJECT_NAME}.pc'")
configure_file(${PROJECT_BINARY_DIR}/misc/${CMAKE_PROJECT_NAME}.pc.in "${PROJECT_BINARY_DIR}/misc/${CMAKE_PROJECT_NAME}.pc" @ONLY)

install(FILES "${PROJECT_BINARY_DIR}/misc/${CMAKE_PROJECT_NAME}.pc" DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)


# # smoke test
# if(BUILD_SMOKE_TEST)
#   message(STATUS "*** configuring smoke_test")
#   enable_testing()
#   add_subdirectory(tests1)
# endif()
