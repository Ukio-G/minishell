cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 90)
add_executable(minishell main.c start_new_process.c shell_status.c env_utils.c executable.c file_utils.c cd.c basic_shell.h echo.c unset.c pwd.c env.c export.c exit.c cd_utils.c update_env.c find_env.c move_env.c)

include_directories(libft get-next-line)

target_link_libraries(minishell PUBLIC readline ${CMAKE_SOURCE_DIR}/libft.a ${CMAKE_SOURCE_DIR}/get_next_line.a)
