add_executable(benchs benchs.cpp)

target_link_libraries(benchs benchmark::benchmark)
target_link_libraries(benchs matrix_chain_lib)