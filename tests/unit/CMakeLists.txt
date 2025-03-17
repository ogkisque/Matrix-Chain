set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_executable(chain_tests tests.cpp)
target_include_directories(chain_tests INTERFACE ${INCLUDE_DIR})

target_link_libraries(chain_tests GTest::gtest_main)
target_link_libraries(chain_tests matrix_chain_lib)

target_include_directories(chain_tests PRIVATE ${GMOCK_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})

set(RUN_TESTS ./chain_tests --gtest_color=yes)
add_test(
    NAME chain_tests
    COMMAND ${RUN_TESTS}
)