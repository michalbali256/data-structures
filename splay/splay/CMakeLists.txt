cmake_minimum_required(VERSION 3.10)

project(splay)

add_executable(splay
    main.cpp
    tree.cpp
)

if(MSVC)
  target_compile_options(splay PRIVATE /W4 /WX)
else(MSVC)
  target_compile_options(splay PRIVATE -Wall -Wextra -pedantic)
endif(MSVC)
