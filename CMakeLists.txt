set (CMAKE_CXX_STANDARD 11)
cmake_minimum_required (VERSION 2.6)
project (TheWitnessSolver)
add_executable(solver main.cpp node.cpp puzzle.cpp puzzle_solver.cpp grid_puzzle_factory.cpp puzzle_printer.cpp)