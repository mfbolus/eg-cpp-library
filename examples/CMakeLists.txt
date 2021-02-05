# e.g., add executable
add_executable(example1 example1.cpp)
target_link_libraries(example1 PUBLIC egcpp ${PROJECT_LIBS})
