cmake_minimum_required(VERSION 3.20)
project(mindseye_ledger_core LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(mindseye_ledger_core
  src/sha256.cpp
  src/merkle.cpp
  src/block.cpp
  src/ledger.cpp
  src/storage_file.cpp
  src/storage_memory.cpp
)

target_include_directories(mindseye_ledger_core
  PUBLIC
    include
)

if (MSVC)
  target_compile_options(mindseye_ledger_core PRIVATE /W4)
else()
  target_compile_options(mindseye_ledger_core PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_executable(example_append examples/example_append.cpp)
target_link_libraries(example_append PRIVATE mindseye_ledger_core)

add_executable(example_verify examples/example_verify.cpp)
target_link_libraries(example_verify PRIVATE mindseye_ledger_core)
