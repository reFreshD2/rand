cmake_minimum_required(VERSION 3.17)
project(rand)

set(CMAKE_CXX_STANDARD 17)

add_executable(rand rand.cpp Source.cpp config.h experiments.h num_threads.cpp num_threads.h run_experiments.cpp rand.h)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -fopenmp -pthread")