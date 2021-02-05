find_library(ARMA_LIB armadillo REQUIRED)
list(APPEND PROJECT_REQUIRED_LIBS ${ARMA_LIB})
set(ARMA_INCLUDES_DIR /opt/local/include)
list(APPEND CMAKE_REQUIRED_INCLUDES ${ARMA_INCLUDES_DIR})

message(STATUS "ARMA_INCLUDE_DIRS = ${ARMA_INCLUDE_DIRS}")
message(STATUS "ARMA_LIB          = ${ARMA_LIB}")

# For future reference if you cannot find with default paths, e.g. from armadillo looking for OpenBLAS:
#
# find_library(${OpenBLAS_NAME}_LIBRARY
#     NAMES ${OpenBLAS_NAME}
#     PATHS ${CMAKE_SYSTEM_LIBRARY_PATH} /lib64 /lib /usr/lib64 /usr/lib /usr/local/lib64 /usr/local/lib /opt/local/lib64 /opt/local/lib /usr/lib/openblas/ /usr/lib/openblas/lib /usr/local/opt/openblas/lib /opt/local/lib/openblas /opt/local/lib/openblas/lib
#     )
