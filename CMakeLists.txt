project(traction-control)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic -Werror)

file(GLOB traction-control-lib-src ${CMAKE_CURRENT_LIST_DIR}/src/*.c)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/lib

    # exported
    ${CMAKE_CURRENT_LIST_DIR}/exported/lib
    # VelocityEstimation
    ${CMAKE_CURRENT_LIST_DIR}/exported/Velocity_Estimation_ert_rtw
)

add_library(
    exported
    SHARED

    ${CMAKE_CURRENT_LIST_DIR}/exported/Velocity_Estimation_ert_rtw/Velocity_Estimation.c
    ${CMAKE_CURRENT_LIST_DIR}/exported/Velocity_Estimation_ert_rtw/Velocity_Estimation_data.c
)

add_library(
    traction-control-lib
    SHARED
    ${traction-control-lib-src}
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

add_executable(traction-control src/main.c)
target_link_libraries(traction-control exported traction-control-lib)