set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(INCLUDE_DIR1 ${CMAKE_SOURCE_DIR}/Matrix/include)

add_library(matrix_chain_lib INTERFACE)
target_include_directories(matrix_chain_lib INTERFACE ${INCLUDE_DIR})
target_include_directories(matrix_chain_lib INTERFACE ${INCLUDE_DIR1})

add_executable(main_chain main.cpp)
target_link_libraries(main_chain matrix_chain_lib)