all: libft.a libgnl.a minishell

.PHONY: all
CFLAGS = -Wextra -Wall -Werror
INCLUDE = -I. -Irl -Ift_vector -Ilibft -Iget-next-line -Ierrors_printer -Ibuiltin -Ienv -Ifile_utils -Imain_functions -Ipipes -Ipreprocessor -Iprocesses -Iredirection -Ishell_status -Isignal

# Create list of .obj files, based on .c files
OBJS_DIR = objs
SRC = main.c \
	builtin/cd.c \
	builtin/cd_utils.c \
	builtin/echo.c \
	builtin/env.c \
	builtin/exit.c \
	builtin/export.c \
	builtin/pwd.c \
	builtin/unset.c \
	env/env_utils.c \
	env/find_env.c \
	env/move_env.c \
	env/update_env.c \
	errors_printer/error_printer.c \
	file_utlis/executable.c \
	file_utlis/executable_1.c \
	file_utlis/file_utlis.c \
	ft_vector/ft_vector.c \
	ft_vector/ft_vector_2.c \
	ft_vector/ft_vector_3.c \
	ft_vector/ft_vector_4.c \
	main_functions/main_functions.c \
	main_functions/main_functions_1.c \
	pipes/pipes.c \
	preprocessor/preprocessor.c \
	preprocessor/preprocessor_1.c \
	preprocessor/preprocessor_2.c \
	preprocessor/preprocessor_3.c \
	preprocessor/preprocessor_4.c \
	preprocessor/preprocessor_loops.c \
	processes/processes.c \
	processes/processes_1.c \
	redirection/heredoc.c \
	redirection/redirection.c \
	redirection/redirection_1.c \
	redirection/redirection_2.c \
	shell_status/shell_status.c \
	signal/signal.c

HEADERS = builtin/basic_shell.h \
	env/env_utils.h \
	errors_printer/errors_printer.h \
	file_utils/executable_file_error.h \
	file_utils/file_utils.h \
	file_utils/permission.h \
	ft_vector/ft_vector.h \
	main_functions/main_functions.h \
	pipes/pipes.h \
	preprocessor/preprocessor.h \
	processes/processes.h \
	redirection/redirection.h \
	shell_status/shell_status.h \
	signal/signal.h \
	rl/ansi_stdlib.h \
	rl/chardefs.h \
	rl/colors.h \
	rl/config.h \
	rl/file \
	rl/histlib.h \
	rl/history.h \
	rl/keymaps.h \
	rl/parse-colors.h \
	rl/posixdir.h \
	rl/posixjmp.h \
	rl/posixselect.h \
	rl/posixstat.h \
	rl/readline.h \
	rl/rlconf.h \
	rl/rldefs.h \
	rl/rlmbutil.h \
	rl/rlprivate.h \
	rl/rlshell.h \
	rl/rlstdc.h \
	rl/rltty.h \
	rl/rltypedefs.h \
	rl/rlwinsize.h \
	rl/tcap.h \
	rl/tilde.h \
	rl/xmalloc.h \
	command.h

$(addprefix $(OBJS_DIR)/,%o): $(addprefix builtin/, $(notdir %c)) $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(addprefix $(OBJS_DIR)/,%o): $(addprefix env/, $(notdir %c)) $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(addprefix $(OBJS_DIR)/,%o): $(addprefix errors_printer/, $(notdir %c)) $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(addprefix $(OBJS_DIR)/,%o): $(addprefix file_utils/, $(notdir %c)) $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(addprefix $(OBJS_DIR)/,%o): $(addprefix ft_vector/, $(notdir %c)) $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(addprefix $(OBJS_DIR)/,%o): $(addprefix main_functions/, $(notdir %c)) $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(addprefix $(OBJS_DIR)/,%o): $(addprefix pipes/, $(notdir %c)) $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(addprefix $(OBJS_DIR)/,%o): $(addprefix preprocessor/, $(notdir %c)) $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(addprefix $(OBJS_DIR)/,%o): $(addprefix processes/, $(notdir %c)) $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(addprefix $(OBJS_DIR)/,%o): $(addprefix redirection/, $(notdir %c)) $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(addprefix $(OBJS_DIR)/,%o): $(addprefix shell_status/, $(notdir %c)) $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(addprefix $(OBJS_DIR)/,%o): $(addprefix signal/, $(notdir %c)) $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(addprefix $(OBJS_DIR)/,%o): %c $(HEADERS)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

BASIC_OBJS = $(addprefix $(OBJS_DIR)/, $(patsubst %c, %o, $(notdir $(SRC))))

LIBFT_SRCS = libft/ft_memset.c \
	libft/ft_bzero.c \
	libft/ft_memcpy.c \
	libft/ft_memccpy.c \
	libft/ft_memmove.c \
	libft/ft_memchr.c \
	libft/ft_memcmp.c \
	libft/ft_strlen.c \
	libft/ft_strlcpy.c \
	libft/ft_strlcat.c \
	libft/ft_strchr.c \
	libft/ft_strrchr.c \
	libft/ft_strnstr.c \
	libft/ft_strncmp.c \
	libft/ft_atoi.c \
	libft/ft_isalpha.c \
	libft/ft_isdigit.c \
	libft/ft_isalnum.c \
	libft/ft_isascii.c \
	libft/ft_isprint.c \
	libft/ft_toupper.c \
	libft/ft_tolower.c \
	libft/ft_calloc.c \
	libft/ft_strdup.c \
	libft/ft_substr.c \
	libft/ft_strtrim.c \
	libft/ft_strjoin.c \
	libft/ft_split.c \
	libft/ft_split_count.c \
	libft/ft_split_free.c \
	libft/ft_itoa.c \
	libft/ft_strmapi.c \
	libft/ft_putchar_fd.c \
	libft/ft_putstr_fd.c \
	libft/ft_putendl_fd.c \
	libft/ft_putnbr_fd.c \
	libft/ft_swap.c \
	libft/ft_wcount.c \
	libft/ft_strrev.c \
	libft/ft_strnlen.c \
	libft/ft_pow.c \
	libft/ft_min.c \
	libft/ft_max.c \
	libft/ft_isspace.c \
	libft/ft_isinset.c \
	libft/ft_digits_count.c \
	libft/ft_dec_to_hex.c \
	libft/ft_tolower_str.c \
	libft/ft_abs.c \
	libft/ft_dword_to_hex.c \
	libft/ft_atof.c \
	libft/ft_strpbrk.c \
	libft/ft_strndup.c \
	libft/ft_strchr2.c \
	libft/ft_strpbrk2.c \
	libft/ft_slice_cpy.c \
	libft/ft_ternary.c

libft.a: $(LIBFT_SRCS) libft/libft.h
	make -C libft
	cp libft/libft.a .

LIBGNL_SRCS =	get-next-line/get_next_line.c \
				get-next-line/get_next_line.h \
				get-next-line/get_next_line_utils.c

# Compile GNL
libgnl.a: $(LIBGNL_SRCS)
	make -C get-next-line/
	cp get-next-line/get_next_line.a ./libgnl.a

minishell: $(BASIC_OBJS) libft.a libgnl.a
	gcc $(CFLAGS) -o $@ $^ -lhistory -lreadline -ltermcap -L.

clean:
	cd libft && make clean
	cd get-next-line && make clean
	rm -rf objs

fclean: clean
	cd libft && make fclean
	cd get-next-line && make fclean
	rm -f libgnl.a libft.a minishell

re: fclean all clean libft.a libgnl.a