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
include(FetchContent)

# add_subdirectory(${PROJECT_SOURCE_DIR}/googletest)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

set(GTEST_LIBRARY ${PROJECT_SOURCE_DIR}/build/_deps/googletest-src)
set(GTEST_INCLUDE_DIR ${GTEST_LIBRARY}/googletest/include)
set(GTEST_MAIN_LIBRARY ${GTEST_LIBRARY}/googletest/lib/libgtest_main.a)

find_package(GTest REQUIRED)

set(ALL_SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/stk_sim.h
    ${PROJECT_SOURCE_DIR}/src/stk_sim.c
    ${PROJECT_SOURCE_DIR}/src/stk_sim_stkht.h
    ${PROJECT_SOURCE_DIR}/src/stk_sim_stkht.c
    ${PROJECT_SOURCE_DIR}/src/stk_sim_psht.h
    ${PROJECT_SOURCE_DIR}/src/stk_sim_psht.c
)

add_executable(stk_sim_tests
${ALL_SRC_FILES}
${PROJECT_SOURCE_DIR}/test/stk_sim_test.c
${PROJECT_SOURCE_DIR}/test/gtestmain.c
)

target_include_directories(
    stk_sim_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src
)

include_directories(
    ${GTEST_ROOT}/googletest/include
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(stk_sim_tests
                      GTest::gtest_main
)

gtest_discover_tests(stk_sim_tests
)
