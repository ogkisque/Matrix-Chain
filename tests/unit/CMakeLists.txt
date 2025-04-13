add_executable(chain_tests tests.cpp)

target_link_libraries(chain_tests matrix_chain_lib)
target_link_libraries(chain_tests GTest::gtest_main)

target_include_directories(chain_tests PRIVATE ${GMOCK_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS})

set(RUN_TESTS ./chain_tests --gtest_color=yes)
add_test(
    NAME chain_tests
    COMMAND ${RUN_TESTS}
)