cmake_minimum_required(VERSION 3.14)

project(SynAnalyzer VERSION 1.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(Config.h.in Config.h)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

find_package(FLEX REQUIRED)
FLEX_TARGET(FlexTokenizer ${SRC_DIR}/lexer.l ${CMAKE_BINARY_DIR}/lexer.cpp)

set(SOURCES
${SRC_DIR}/main.cpp
${SRC_DIR}/Analyzer.cpp
${SRC_DIR}/Visualize.cpp
${FLEX_FlexTokenizer_OUTPUTS}
)

add_executable(SynAnalyzer ${SOURCES})

target_include_directories(SynAnalyzer PUBLIC
                          ${INCLUDE_DIR}
                          "${PROJECT_BINARY_DIR}"
                          )


# Fetch Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.16.0  # Specific version 1.16.0
)
FetchContent_MakeAvailable(googletest)

add_executable(runTests 
                        tests/test_main.cpp
                        tests/test_SynAnalyzer.cpp
                        ${SRC_DIR}/Analyzer.cpp
                        ${SRC_DIR}/Visualize.cpp
                        ${FLEX_FlexTokenizer_OUTPUTS}
              )

target_compile_definitions(runTests PRIVATE TESTING)


target_include_directories(runTests PUBLIC
                          ${INCLUDE_DIR}
                          "${PROJECT_BINARY_DIR}"
                          )

target_link_libraries(runTests gtest gtest_main pthread)


enable_testing()
add_test(NAME BasicTest COMMAND runTests)