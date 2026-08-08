cmake_minimum_required(VERSION 3.16)
project(traction-control)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -Werror -O3 -g)
add_compile_definitions(CANLIB_TIMESTAMP)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CDIR ${CMAKE_CURRENT_LIST_DIR})

function(get_git_submodule_info submodule_path hash_var status_var status_value_var)
  execute_process(
    COMMAND git -C ${submodule_path} rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE _hash
    OUTPUT_STRIP_TRAILING_WHITESPACE
  )
  execute_process(
    COMMAND git -C ${submodule_path} diff --quiet --exit-code
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE _diff_result
  )
  if(_diff_result EQUAL 0)
    set(_status "")
    set(_status_value "0")
  else()
    set(_status "-dirty")
    set(_status_value "1")
  endif()
  
  set(${hash_var} ${_hash} PARENT_SCOPE)
  set(${status_var} ${_status} PARENT_SCOPE)
  set(${status_value_var} ${_status_value} PARENT_SCOPE)
endfunction()

# --- CAN ---
get_git_submodule_info("external/libcan-sw" CAN_HASH CAN_STATUS CAN_STATUS_VALUE)
message(STATUS "\"libcan-sw\" version: ${CAN_HASH} (${CAN_STATUS}) (${CAN_STATUS_VALUE})")
add_definitions(-DCAN_SUBMODULE_COMMIT_HASH_TOTAL=\"${CAN_HASH}${CAN_STATUS}\")
add_definitions(-DCAN_SUBMODULE_COMMIT_HASH=\"${CAN_HASH}\")
add_definitions(-DCAN_SUBMODULE_COMMIT_STATUS=\"${CAN_STATUS}\")
add_definitions(-DCAN_SUBMODULE_COMMIT_STATUS_VALUE=\"${CAN_STATUS_VALUE}\")

file(GLOB traction-control-lib-src ${CMAKE_CURRENT_LIST_DIR}/src/*.c)
file(GLOB_RECURSE can-lib-src ${CMAKE_CURRENT_LIST_DIR}/external/can/lib/*.c)

file(GLOB_RECURSE canlib_lib_c ${CDIR}/external/libcan-sw/src/*.c)
add_library(can-lib
    ${canlib_lib_c}
)
set_source_files_properties(
    ${canlib_lib_c}
    PROPERTIES LANGUAGE CXX
)
target_compile_options(can-lib PRIVATE -w)
include_directories(
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/lib

    # exported
    ${CMAKE_CURRENT_LIST_DIR}/exported/lib

    # external
    ${CMAKE_CURRENT_LIST_DIR}/external/soc/external
    ${CMAKE_CURRENT_LIST_DIR}/external/libeagletrt-sw
    ${CMAKE_CURRENT_LIST_DIR}/external/libeagletrt-sw/include
    ${CMAKE_CURRENT_LIST_DIR}/external/libcan-sw
    ${CMAKE_CURRENT_LIST_DIR}/external/libcan-sw/include
    ${CMAKE_CURRENT_LIST_DIR}/external/libcan-sw/include/bms
    ${CMAKE_CURRENT_LIST_DIR}/external/libcan-sw/include/inverters
    ${CMAKE_CURRENT_LIST_DIR}/external/libcan-sw/include/primary
    ${CMAKE_CURRENT_LIST_DIR}/external/libcan-sw/proto
    ${CMAKE_CURRENT_LIST_DIR}/external/libcan-sw/src
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
    traction-control-lib
    STATIC
    ${traction-control-lib-src}
)
target_link_libraries(traction-control-lib can-lib m pthread)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin)

add_executable(traction-control src/main.cpp)
target_link_libraries(traction-control exported traction-control-lib soclib)
