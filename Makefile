NAME        = client

CC          = cc
CFLAGS      = -Wall -Wextra -Werror

OBJ_DIR     = objs

SRC         = ft_http_get_to_buffer.c \
              ft_simple_get.c \
              ft_util.c \
              ft_write_callback.c \
			  ft_http_post.c \
              main.c

OBJS        = $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L. -lft -lcurl -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I. -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re