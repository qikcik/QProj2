cmake_minimum_required(VERSION 3.26)
project(QProj LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof -fno-strict-aliasing")

include("${CMAKE_CURRENT_LIST_DIR}/utils/modules_def.cmake")

add_subdirectory("core/memory")
add_subdirectory("core/struct")
add_subdirectory("core/json")
add_subdirectory("core/qstruct_serialize")


add_subdirectory("application/todoApp")


