cmake_minimum_required(VERSION 3.10)

project(transp)

add_executable(transp
    main.cpp
)

add_executable(transp_test test.cpp)

if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
else(MSVC)
  target_compile_options(transp PRIVATE -Wall -Wextra -pedantic)
endif(MSVC)
