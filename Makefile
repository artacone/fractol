NAME			=	fractol

SRCS_DIR		=	./srcs/

OBJS_DIR		=	./objs/

HEADERS_DIR		=	./includes/

SRCS			=	$(SRCS_DIR)main.c \
					$(SRCS_DIR)fractal.c

HEADERS			=	$(wildcard $(HEADERS_DIR)*.h)

OBJS			=	$(addprefix $(OBJS_DIR), $(notdir $(SRCS:.c=.o)))

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror -O3

LDFLAGS			=	-L$(LIBMLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -framework OpenGL -framework Appkit -O3

RM				=	rm -f

LIBFT_DIR		=	./libft/

LIBFT			=	$(addprefix $(LIBFT_DIR), libft.a)

LIBMLX_DIR		=	./mlx/

LIBMLX			=	$(addprefix $(LIBMLX_DIR), libmlx.a)

all: $(LIBFT) $(LIBMLX) $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) $(LIBFT) $(LIBMLX) | $(OBJS_DIR)
	$(CC) $(CFLAGS) -I$(HEADERS_DIR) -Imlx -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(LIBMLX):
	make -C $(LIBMLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(LIBMLX)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

clean:
		$(RM) -r $(OBJS_DIR)
		make -C $(LIBFT_DIR) clean
		make -C $(LIBMLX_DIR) clean

fclean: clean
		$(RM) $(NAME)
		make -C $(LIBFT_DIR) fclean
		make -C $(LIBMLX_DIR) fclean

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

re: fclean $(OBJS_DIR) all

.PHONY: all clean fclean re
