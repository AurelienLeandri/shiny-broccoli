set(TEST_LIST ${TEST_LIST} test_misc PARENT_SCOPE)

add_executable(test_misc main.cpp)
target_link_libraries(test_misc broccoli pthread)
