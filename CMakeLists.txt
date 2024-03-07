cmake_minimum_required(VERSION 3.19)
project(tinySTL)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O2 -Wall -Wextra -Wno-sign-compare \
    -Wno-unused-but-set-variable -Wno-array-bounds \
    -fexec-charset=GBK -finput-charset=UTF-8")

add_executable(tinySTL main.cpp)

message(${PROJECT_SOURCE_DIR})
add_subdirectory(MyTinySTL)
add_subdirectory(Test)
target_link_libraries(tinySTL PRIVATE test)
target_link_libraries(tinySTL PRIVATE algorithm)
target_link_libraries(tinySTL PRIVATE allocator)
target_link_libraries(tinySTL PRIVATE seq_container ass_container)
target_link_libraries(tinySTL PRIVATE function)
target_link_libraries(tinySTL PRIVATE iterator)
target_link_libraries(tinySTL PRIVATE adapter)
target_link_libraries(tinySTL PRIVATE utils)
