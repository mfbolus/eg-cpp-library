# e.g., add executable
add_executable(example_program_1 example_program_1.cpp)
target_link_libraries(example_program_1 PUBLIC ${CMAKE_PROJECT_NAME} ${PROJECT_LIBS})
