cmake_minimum_required(VERSION 3.9)

project(fibb)

add_executable(fibb
    main.cpp
	node_list.cpp
	fibb.cpp
)

if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
  target_compile_options(fibb PRIVATE /W4 )
  endif()
else(MSVC)
  target_compile_options(fibb PRIVATE -Wall -Wextra -pedantic)
endif(MSVC)
