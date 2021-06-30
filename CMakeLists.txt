cmake_minimum_required(VERSION 3.20)
project(minishell C)

set(CMAKE_C_STANDARD 90)
add_executable(minishell main.c)


target_link_libraries(minishell PUBLIC readline)
