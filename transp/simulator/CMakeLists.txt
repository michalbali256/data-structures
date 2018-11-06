cmake_minimum_required(VERSION 3.10)

project(simulator)

add_executable(simulator
    simulator.cpp
)

if(MSVC)
  target_compile_options(transp PRIVATE /W4 )
else(MSVC)
  target_compile_options(transp PRIVATE -Wall -Wextra -pedantic)
endif(MSVC)
