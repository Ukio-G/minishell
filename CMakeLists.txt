cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 90)
add_executable(minishell main.c start_new_process.c shell_status.c env.c executable.c file_utils.c)

include_directories(libft get-next-line)

target_link_libraries(minishell PUBLIC readline ${CMAKE_SOURCE_DIR}/libft.a ${CMAKE_SOURCE_DIR}/get_next_line.a)



add_executable(pipe_example pipe_example.c start_new_process.c)
add_executable(octal_shift test_octal_shift.c)

add_executable(test_file_permissions test_file_permissions.c  start_new_process.c shell_status.c env.c executable.c file_utils.c)
target_link_libraries(test_file_permissions PUBLIC ${CMAKE_SOURCE_DIR}/libft.a)
