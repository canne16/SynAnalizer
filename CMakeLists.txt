cmake_minimum_required(VERSION 3.10)

project(SynAnalizer VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(Config.h.in Config.h)

set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")


find_package(FLEX REQUIRED)

FLEX_TARGET(FlexTokenizer ${SRC_DIR}/lexer.l ${CMAKE_BINARY_DIR}/lexer.cpp)

set(SOURCES
    ${SRC_DIR}/main.cpp
    ${FLEX_FlexTokenizer_OUTPUTS}
)

add_executable(SynAnalizer ${SOURCES})

target_include_directories(SynAnalizer PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

