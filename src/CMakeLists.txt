set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)

add_library(matrix_chain_lib INTERFACE)
target_include_directories(matrix_chain_lib INTERFACE ${INCLUDE_DIR})

target_link_libraries(matrix_chain_lib INTERFACE matrix_lib)

add_executable(main_chain main.cpp)
target_link_libraries(main_chain matrix_chain_lib)