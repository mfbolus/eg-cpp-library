# e.g., add shared library (default is static)
add_library(egcpp SHARED lds_sys.cpp)
target_link_libraries(egcpp PUBLIC ${PROJECT_LIBS})
set_target_properties(egcpp PROPERTIES VERSION ${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}.${CMAKE_PROJECT_VERSION_PATCH} SOVERSION ${CMAKE_PROJECT_VERSION_MAJOR})
