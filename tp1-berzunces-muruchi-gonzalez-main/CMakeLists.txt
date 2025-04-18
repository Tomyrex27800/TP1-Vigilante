cmake_minimum_required(VERSION 3.14)
project(tp1)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  tp_tests
  tests/tests.cpp
  utils/utils.cpp
  launch/launch.cpp
  generation/generation.cpp
)
target_link_libraries(
  tp_tests
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tp_tests)

# Main executable
add_executable(
  main
  main.cpp
  utils/utils.cpp
  launch/launch.cpp
)

# Include the directory containing the header files
target_include_directories(
  main PRIVATE ${CMAKE_SOURCE_DIR}
)

# Generation executable
add_executable(
  generate
  generation/generate.cpp
  generation/generation.cpp
  utils/utils.cpp
)

# Include the directory containing the header files
target_include_directories(
  generate PRIVATE ${CMAKE_SOURCE_DIR}
)

