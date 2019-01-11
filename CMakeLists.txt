cmake_minimum_required(VERSION 3.5)
project(P4 CXX)

# require a C++11 compiler for all targets
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(NODE_SOURCE
  Node.hpp Node.txx)

set(TERM_SOURCE
  Term.hpp Term.cpp)

set(POLY_SOURCE
  Polynomial.hpp Polynomial.cpp)

set(LIST_SOURCE
  LinkedList.hpp LinkedList.txx)

set(TEST_SOURCE
  student_tests.cpp)

set(MAIN_SOURCE
 pcalc.cpp)

# create unittests
add_executable(student-tests catch.hpp ${NODE_SOURCE} ${TERM_SOURCE} ${POLY_SOURCE} ${LIST_SOURCE} ${TEST_SOURCE})

# create main
add_executable(pcalc ${NODE_SOURCE} ${TERM_SOURCE} ${POLY_SOURCE} ${LIST_SOURCE} ${MAIN_SOURCE})

# some simple tests
enable_testing()
add_test(student-tests student-tests)

add_custom_target(submission COMMAND
  ${CMAKE_COMMAND} -E tar "cfv" "${CMAKE_CURRENT_BINARY_DIR}/submission.zip" --format=zip
  Term.cpp LinkedList.txx Polynomial.cpp student_tests.cpp pcalc.cpp
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
