cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 90)

file(GLOB FT_VECTOR_SRCS "ft_vector/*.c")
file(GLOB ENV "env/*.c")
file(GLOB BUILTIN "builtin/*.c")

#add_definitions(-D DEBUG_PRINT)
add_definitions(-D PRINT_PREPROCESSED_INPUT)
add_definitions(-D READLINE_LIBRARY)

add_executable(minishell
        ${FT_VECTOR_SRCS}
        ${ENV}
        ${BUILTIN}
        main.c
        processes/processes.c
        shell_status/shell_status.c
        file_utils/executable.c
        file_utils/file_utils.c
        pipes/pipes.c
        errors_printer/error_printer.c
        preprocessor/preprocessor.c
        redirection/redirection.c
        redirection/heredoc.c
        signal/signal.c
        file_utils/executable_1.c
        preprocessor/preprocessor_1.c
        preprocessor/preprocessor_2.c
        preprocessor/preprocessor_3.c
        preprocessor/preprocessor_4.c
        preprocessor/preprocessor_loops.c
        processes/processes_1.c
        redirection/redirection_1.c
        redirection/redirection_2.c
        main_functions/main_functions.c
        main_functions/main_functions_1.c
        )

include_directories(libft get-next-line . env builtin file_utils rl)

target_link_libraries(minishell PUBLIC
        ${CMAKE_SOURCE_DIR}/libtermcap.a
        ${CMAKE_SOURCE_DIR}/libreadline.a
        ${CMAKE_SOURCE_DIR}/libhistory.a
        ${CMAKE_SOURCE_DIR}/libft.a
        ${CMAKE_SOURCE_DIR}/get_next_line.a)

