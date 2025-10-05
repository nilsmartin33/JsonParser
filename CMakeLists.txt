cmake_minimum_required(VERSION 3.15)
project(JSONParser VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4 /WX)
else()
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

include_directories(${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/core
        ${PROJECT_SOURCE_DIR}/include/core/composite
        ${PROJECT_SOURCE_DIR}/include/core/primitive
        ${PROJECT_SOURCE_DIR}/include/parser
        ${PROJECT_SOURCE_DIR}/include/visitor
        ${PROJECT_SOURCE_DIR}/include/tokenizer
        ${PROJECT_SOURCE_DIR}/include/tokenizer/reader
        ${PROJECT_SOURCE_DIR}/include/tokenizer/parser
        ${PROJECT_SOURCE_DIR}/include/tokenizer/token)

add_executable(json_tokenizer
        main.cpp
)

option(BUILD_TESTS "Build test suite" OFF)

if(BUILD_TESTS)
    enable_testing()

    add_executable(test_tokenizer
            tests/test_tokenizer.cpp
    )

    add_test(NAME TokenizerTests COMMAND test_tokenizer)
endif()

install(TARGETS json_tokenizer DESTINATION bin)
install(DIRECTORY include/ DESTINATION include)