cmake_minimum_required(VERSION 3.17)
project(minishell C)

set(CMAKE_C_STANDARD 90)

file(GLOB FT_VECTOR_SRCS "ft_vector/*.c")
file(GLOB ENV "env/*.c")
file(GLOB BUILTIN "builtin/*.c")
#add_definitions(-D DEBUG_PRINT)
add_definitions(-D PRINT_PREPROCESSED_INPUT)
add_executable(minishell
        ${FT_VECTOR_SRCS}
        ${ENV}
        ${BUILTIN}
        main.c
        processes/processes.c
        shell_status.c
        file_utils/executable.c
        file_utils/file_utils.c
        pipes/pipes.c
        errors_printer/error_printer.c
        signals/signals_handler.c
        preprocessor/preprocessor.c
        test_preprocessor.c
        redirection/redirection.c
        redirection/heredoc.c
        )

include_directories(libft get-next-line . env builtin file_utils)

target_link_libraries(minishell PUBLIC readline ${CMAKE_SOURCE_DIR}/libft.a ${CMAKE_SOURCE_DIR}/get_next_line.a)

