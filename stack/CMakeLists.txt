file (GLOB_RECURSE SOURCES "src/*.cpp")
add_library(stack SHARED ${SOURCES})

target_include_directories(stack PUBLIC include)