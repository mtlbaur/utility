cmake_minimum_required(VERSION 3.25.1)

set(CMAKE_C_COMPILER_WORKS true)
set(CMAKE_CXX_COMPILER_WORKS true)
set(CMAKE_C_COMPILER "clang.exe")
set(CMAKE_CXX_COMPILER "clang++.exe")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(utility)

set(root_source "${PROJECT_SOURCE_DIR}/source/")
set(root_tests "${PROJECT_SOURCE_DIR}/tests/")
set(root_examples "${PROJECT_SOURCE_DIR}/examples/")

message(${root_source})
message(${root_tests})
message(${root_examples})

include_directories(${root_source})

add_executable(check_runtime_test "${root_tests}check_runtime_test.cpp")
add_executable(print "${root_tests}print.cpp")
add_executable(test_vt "${root_tests}test_vt.cpp")
add_executable(trie "${root_tests}trie.cpp")

add_executable(rng "${root_source}rng.cpp" "${root_examples}rng.cpp")
add_executable(fibonacci_sequence "${root_examples}fibonacci_sequence.cpp")
add_executable(power_set "${root_examples}power_set.cpp")
add_executable(n-queens "${root_examples}n-queens.cpp")
add_executable(word_search "${root_examples}word_search.cpp")

# this is supposed to prevent vscode from cutting off error messages in its problems window
add_compile_options("-fmessage-length=0")