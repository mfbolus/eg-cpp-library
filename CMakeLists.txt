cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

# set project name and version (MAJOR.minor.patch)
# for project name, use lowercase. this will be the name of build library (libegcpp.so)
project(egcpp VERSION 0.1.0 LANGUAGES CXX C)
# some name variants I will be using:
set(CMAKE_PROJECT_NAME_CAP EGCPP)#all caps
set(CMAKE_PROJECT_NAME_CAMEL EgCpp)#CamelCase

# TODO(mfbolus): Update on per-project basis
set(PROJECT_URL https://github.com/USER/REPOSITORY)

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

option(DETECT_HDF5 "Detect HDF5 and include HDF5 support, if found." OFF)
# you can enable HDF5 detection directly on the command line:
# cmake -D DETECT_HDF5=true
set(PROJECT_USE_HDF5 false)

option(BUILD_EXAMPLES "Build the example programs." ON)
# disable:
# cmake -D BUILD_EXAMPLES=false

message(STATUS "CMAKE_SYSTEM_NAME          = ${CMAKE_SYSTEM_NAME}"         )
message(STATUS "CMAKE_CXX_COMPILER_ID      = ${CMAKE_CXX_COMPILER_ID}"     )
message(STATUS "CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "CMAKE_COMPILER_IS_GNUCXX   = ${CMAKE_COMPILER_IS_GNUCXX}"  )
message(STATUS "DETECT_HDF5                = ${DETECT_HDF5}"               )
message(STATUS "BUILD_EXAMPLES             = ${BUILD_EXAMPLES}"          )
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

# add project cmake modules to module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

# pkg-config may be be used later
# this allows `find_package` function to use pkg-config files rather than just cmake
find_package(PkgConfig)

# ARMADILLO
include(FindArmadillo)

# HDF5
include(DetectHDF5)

# after getting these lists, take out duplicates
list(REMOVE_DUPLICATES PROJECT_REQUIRED_LIBS)
list(REMOVE_DUPLICATES CMAKE_REQUIRED_INCLUDES)

message(STATUS "")
message(STATUS "*** Project will use the following libraries:")
message(STATUS "*** PROJECT_REQUIRED_LIBS = ${PROJECT_REQUIRED_LIBS}")
message(STATUS "")

# With variables/includes set, configure the template header,
# copy the headers, and add include directories to entire project.
# TODO(mfbolus): update this section
message(STATUS "Copying ${PROJECT_SOURCE_DIR}/include/ to ${PROJECT_BINARY_DIR}/include/")
file(COPY ${PROJECT_SOURCE_DIR}/include/eg_cpp_h/ DESTINATION ${PROJECT_BINARY_DIR}/include/eg_cpp_h/)
message(STATUS "Generating ${PROJECT_BINARY_DIR}/include/eg_cpp")
configure_file(${PROJECT_SOURCE_DIR}/include/eg_cpp.in ${PROJECT_BINARY_DIR}/include/eg_cpp)

# # cf target_include_directories()
# include_directories(${PROJECT_BINARY_DIR}/include/ ${CMAKE_REQUIRED_INCLUDES})

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
# library itself
add_library(${CMAKE_PROJECT_NAME} SHARED)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC ${PROJECT_REQUIRED_LIBS})
# state that anybody linking to us needs to include the current source dir
# to find header, while we do not?
target_include_directories(${CMAKE_PROJECT_NAME} INTERFACE $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include> $<INSTALL_INTERFACE:include>)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES VERSION ${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}.${CMAKE_PROJECT_VERSION_PATCH} SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})
add_subdirectory(src) #add source files...

# n.b.: For header-only library consider using INTERFACE mode. From docs:
# A primary use-case for INTERFACE libraries is header-only libraries.
# ```
# add_library(Eigen INTERFACE
#   src/eigen.h
#   src/vector.h
#   src/matrix.h
#   )
# target_include_directories(Eigen INTERFACE
#   $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
#   $<INSTALL_INTERFACE:include/Eigen>
# )
# add_executable(exe1 exe1.cpp)
# target_link_libraries(exe1 Eigen)
# ```

# build examples?
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

install(
  TARGETS ${CMAKE_PROJECT_NAME}
  EXPORT ${CMAKE_PROJECT_NAME_CAMEL}#-> file <export-name>.cmake by default
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

# Export the package for use from outside the build-tree
export(PACKAGE ${CMAKE_PROJECT_NAME})

# get `configure_package_config_file`, `write_basic_package_version_file` functions:
include(CMakePackageConfigHelpers)

# Create {Project}Config.cmake file
message(STATUS "Generating '${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME_CAMEL}Config.cmake'")
configure_package_config_file(
  ${CMAKE_CURRENT_SOURCE_DIR}/cmake/InstallFiles/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/InstallFiles/${CMAKE_PROJECT_NAME_CAMEL}Config.cmake"
  INSTALL_DESTINATION "${CMAKE_INSTALL_DATADIR}/${CMAKE_PROJECT_NAME_CAMEL}/CMake"
  )

# generate the version file for the config file
message(STATUS "Generating '${PROJECT_BINARY_DIR}/${CMAKE_PROJECT_NAME_CAMEL}ConfigVersion.cmake'")
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/InstallFiles/${CMAKE_PROJECT_NAME_CAMEL}ConfigVersion.cmake"
  VERSION "${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}.${CMAKE_PROJECT_VERSION_PATCH}"
  COMPATIBILITY AnyNewerVersion
)

# Install the export set for use with the install-tree
install(EXPORT ${CMAKE_PROJECT_NAME_CAMEL}
  DESTINATION "${CMAKE_INSTALL_DATADIR}/${CMAKE_PROJECT_NAME_CAMEL}/CMake")
  # COMPONENT dev)

# Install files to be found by cmake users with find_package()
install(FILES
  "${PROJECT_BINARY_DIR}/InstallFiles/${CMAKE_PROJECT_NAME_CAMEL}Config.cmake"
  "${PROJECT_BINARY_DIR}/InstallFiles/${CMAKE_PROJECT_NAME_CAMEL}ConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_DATADIR}/${CMAKE_PROJECT_NAME_CAMEL}/CMake")
   # COMPONENT dev)

# pkgconfig related
message(STATUS "Generating '${PROJECT_BINARY_DIR}/misc/${CMAKE_PROJECT_NAME}.pc'")
configure_file(${PROJECT_SOURCE_DIR}/misc/config.pc.in "${PROJECT_BINARY_DIR}/misc/${CMAKE_PROJECT_NAME}.pc" @ONLY)
install(FILES "${PROJECT_BINARY_DIR}/misc/${CMAKE_PROJECT_NAME}.pc" DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)

# TODO(mfbolus): TESTING! see cmake/Help/guide/tutorial/Complete/CMakesLists.txt
