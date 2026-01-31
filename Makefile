P_NAME=cub3d
CFLAGS=-Wall -Wextra -Werror -fsanitize=address -g
HEADER=cub3d.h
P_SRC=main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
draw_routines.c game_loop.c key_ops.c vector_ops.c
P_OBJ=$(P_SRC:.c=.o)

all: $(HEADER) $(P_SRC) $(P_NAME)

re: fclean all

$(P_NAME): $(P_OBJ) minilibx-linux
	@make -C minilibx-linux
	@make -C libft
	$(CC) $(CFLAGS) -o $@ $(P_OBJ) -L./minilibx-linux -lmlx -lXext -lX11 -lm -L./libft -lft
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(P_OBJ)
	@make -C minilibx-linux clean
	@make -C libft clean

fclean: clean
	@make -C libft fclean
	rm -f $(P_NAME)

.PHONY: all fclean re clean
