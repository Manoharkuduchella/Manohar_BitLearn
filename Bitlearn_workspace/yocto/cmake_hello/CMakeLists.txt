cmake_minimum_required(VERSION 3.22)

project(cmake_recipe)

add_executable(hello hello.c)

install (TARGETS hello DESTINATION bin)
