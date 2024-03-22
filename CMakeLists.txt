cmake_minimum_required(VERSION 3.16)

project(stack_cpp LANGUAGES CXX)

add_subdirectory(stack)

add_executable(main main.cpp)
target_link_libraries(main stack)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()