add_library(stack INTERFACE)
target_include_directories(stack INTERFACE include)

add_executable(stack_tests tests/tests.cpp)
target_link_libraries(stack_tests stack gtest gtest_main)