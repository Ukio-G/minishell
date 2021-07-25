LIBFT = libft
LIBFT_DIR = libft
LIBFT_STATIC_LIB = libft.a

GET_NEXT_LINE = get_next_line
GET_NEXT_LINE_DIR = get-next-line
GET_NEXT_LINE_STATIC_LIB = get_next_line.a

$(LIBFT):
	cd $(LIBFT) && make bonus && cp $(LIBFT_STATIC_LIB) ..

$(GET_NEXT_LINE):
	cd $(GET_NEXT_LINE_DIR) && make $(GET_NEXT_LINE_STATIC_LIB) && cp $(GET_NEXT_LINE_STATIC_LIB) ..

.PHONY: $(LIBFT) $(GET_NEXT_LINE)

