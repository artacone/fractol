NAME		= libft.a

SRC_DIR		= ./srcs/

OBJ_DIR		= ./objs/

HEADER_DIR	= ./includes/

SRCS		= $(wildcard ${SRC_DIR}*.c)

HEADERS		= $(wildcard ${HEADER_DIR}*.h)

OBJS		= $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror -O3

RM			= rm -f


.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(HEADER_DIR) -c $< -o $@

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

re: fclean  $(OBJ_DIR) all
