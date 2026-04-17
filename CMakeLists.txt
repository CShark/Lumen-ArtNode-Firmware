cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

project(lumen_artnode C ASM CXX)
add_compile_options(-fmacro-prefix-map=${CMAKE_SOURCE_DIR}/=)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(hal)
add_subdirectory(lumen-core)
add_subdirectory(boards)