# e.g., add executable
add_executable(example_program_1 example_program_1.cpp)
target_link_libraries(example_program_1 PUBLIC ${CMAKE_PROJECT_NAME} ${PROJECT_LIBS})
target_include_directories(example_program_1 INTERFACE $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include> $<INSTALL_INTERFACE:include>)
