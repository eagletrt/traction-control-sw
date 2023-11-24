cmake_minimum_required(VERSION 3.16)
project(traction-control)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Werror -O0 -g)
add_compile_definitions(CANLIB_TIMESTAMP)

file(GLOB traction-control-lib-src ${CMAKE_CURRENT_LIST_DIR}/src/*.c)
file(GLOB can-lib-src ${CMAKE_CURRENT_LIST_DIR}/lib/can/**/**/*.c)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/lib

    # exported
    ${CMAKE_CURRENT_LIST_DIR}/exported/lib
    # VelocityEstimation
    ${CMAKE_CURRENT_LIST_DIR}/exported/Velocity_Estimation
)

add_library(
    exported
    STATIC

    ${CMAKE_CURRENT_LIST_DIR}/exported/Slip_Control/SlipV2.c

    ${CMAKE_CURRENT_LIST_DIR}/exported/Traction_Control/Torque.c

    ${CMAKE_CURRENT_LIST_DIR}/exported/Velocity_Estimation/Velocity_Estimation.c
    ${CMAKE_CURRENT_LIST_DIR}/exported/Velocity_Estimation/Velocity_Estimation_data.c
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

add_executable(traction-control src/main.c)
target_link_libraries(traction-control exported traction-control-lib)
