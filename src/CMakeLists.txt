add_library(matrix_chain_lib INTERFACE)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_include_directories(matrix_chain_lib INTERFACE ${INCLUDE_DIR})
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../Matrix/include)
target_include_directories(matrix_chain_lib INTERFACE ${INCLUDE_DIR})

add_executable(main_chain main.cpp)
target_link_libraries(main_chain matrix_chain_lib)