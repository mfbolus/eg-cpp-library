# see: https://crascit.com/2016/01/31/enhanced-source-file-handling-with-target_sources/
# e.g., add shared library (default is static)
set(LIB_SOURCES ${LIB_SOURCES})
file(READ sourcelist.txt LIB_SOURCES)
message(STATUS "LIB_SOURCES           = ${LIB_SOURCES}")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${LIB_SOURCES})

