set(TEST_LIST ${TEST_LIST} test_misc PARENT_SCOPE)

add_executable(test_misc_same agent_same_value_data.cpp)
target_link_libraries(test_misc_same broccoli pthread)

add_executable(test_misc_independent independent_agent.cpp)
target_link_libraries(test_misc_independent broccoli pthread)
