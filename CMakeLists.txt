cmake_minimum_required(VERSION 3.10)

project(SynAnalyzer VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(Config.h.in Config.h)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

add_subdirectory(external/googletest)

find_package(FLEX REQUIRED)

FLEX_TARGET(FlexTokenizer ${SRC_DIR}/lexer.l ${CMAKE_BINARY_DIR}/lexer.cpp)

set(SOURCES
${SRC_DIR}/main.cpp
${SRC_DIR}/Analyzer.cpp
${SRC_DIR}/Visualize.cpp
${FLEX_FlexTokenizer_OUTPUTS}
)

add_executable(SynAnalyzer ${SOURCES})
add_executable(Tests test/test_main.cpp test/test_SynAnalyzer.cpp)

target_include_directories(SynAnalyzer PUBLIC
                          ${INCLUDE_DIR}
                          "${PROJECT_BINARY_DIR}"
                          )

target_link_libraries(Tests gtest gtest_main)
target_include_directories(Tests PUBLIC include)

enable_testing()
add_test(NAME Tests COMMAND Tests)