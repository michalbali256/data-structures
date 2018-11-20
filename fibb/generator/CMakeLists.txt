cmake_minimum_required(VERSION 3.9)

project(generator)

add_executable(generator
    fibgen.c
)

if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
  target_compile_options(fibbonacci PRIVATE /W4 )
  endif()
else(MSVC)
  target_compile_options(generator PRIVATE -Wall -Wextra -pedantic)
endif(MSVC)
