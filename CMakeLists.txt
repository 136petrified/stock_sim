cmake_minimum_required(VERSION 3.30.0)
# set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
project(pone)

set(CMAKE_HOME_DIRECTORY $ENV{USERPROFILE})
set(CMAKE_CURRENT_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set($ENV{HOME} CMAKE_HOME_DIRECTORY)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_SOURCE_DIR $ENV{USERPROFILE}/pone)

set(CFLAGS "-g -Wall -Wfatal-errors -Werror -pedantic -Iheaders/src")
set(CMAKE_C_FLAGS ${CFLAGS})

# set(CMAKE_C_COMPILER ${PROJECT_SOURCE_DIR}/compile/gcc.exe)
# set(CMAKE_CXX_COMPILER {PROJECT_SOURCE_DIR}/compile/g++.exe)

enable_testing()

# add_subdirectory(${PROJECT_SOURCE_DIR}/googletest)


set(ALL_SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/stk_sim.h
    ${PROJECT_SOURCE_DIR}/src/stk_sim.c
    ${PROJECT_SOURCE_DIR}/src/stk_sim_stkht.h
    ${PROJECT_SOURCE_DIR}/src/stk_sim_stkht.c
    ${PROJECT_SOURCE_DIR}/src/stk_sim_psht.h
    ${PROJECT_SOURCE_DIR}/src/stk_sim_psht.c
)

set(ALL_UNITY_FILES
    ${PROJECT_SOURCE_DIR}/unity/unity.c
    ${PROJECT_SOURCE_DIR}/unity/unity.h
    ${PROJECT_SOURCE_DIR}/unity/unity_internals.h
)

add_executable(stk_sim_tests
${ALL_SRC_FILES}
${ALL_UNITY_FILES}
${PROJECT_SOURCE_DIR}/test/unity_main.c
)

target_include_directories(
    stk_sim_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include_directories(
    ${PROJECT_SOURCE_DIR}/unity
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(stk_sim_tests
)