cmake_minimum_required(VERSION 3.16)
project(traction-control)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Werror -O3 -g)
add_compile_definitions(CANLIB_TIMESTAMP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB traction-control-lib-src ${CMAKE_CURRENT_LIST_DIR}/src/*.c)
file(GLOB_RECURSE can-lib-src ${CMAKE_CURRENT_LIST_DIR}/external/can/lib/*.c)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/lib

    # exported
    ${CMAKE_CURRENT_LIST_DIR}/exported/lib

    # external
    ${CMAKE_CURRENT_LIST_DIR}/external/soc/external
)

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/external/soc)

add_library(
    exported
    STATIC

    ${CMAKE_CURRENT_LIST_DIR}/exported/Regen/Regen.c
    ${CMAKE_CURRENT_LIST_DIR}/exported/Slip_Control/SLIP.c
    ${CMAKE_CURRENT_LIST_DIR}/exported/Traction_Control/TV.c
)

add_library(
    can-lib
    STATIC
    ${can-lib-src}
)
target_compile_definitions(can-lib PUBLIC CANLIB_TIMESTAMP)
target_compile_options(can-lib PRIVATE -w)

add_library(
    traction-control-lib
    STATIC
    ${traction-control-lib-src}
)
target_link_libraries(traction-control-lib can-lib m pthread)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

add_executable(traction-control src/main.cpp)
target_link_libraries(traction-control exported traction-control-lib soclib)
