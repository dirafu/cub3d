P_NAME=cub3D
CFLAGS=-Wall -Wextra -Werror -fsanitize=address -g
HEADER=cub3d.h
P_SRC=main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
draw_routines.c game_loop.c key_ops.c vector_ops.c movement.c rendering.c rendering2.c \
rendering3.c rendering4.c rendering5.c cleanup.c cleanup2.c init.c init2.c mouse.c get_time.c \
test_mock_map_structure_prep.c read_resources.c read_resources2.c read_resources3.c \
      verif/main_verif.c \
      verif/map_check.c \
      verif/pre_map_content_check.c \
      verif/pre_map_structure_check.c \
      verif/row_checker.c \
      verif/utils_map_check.c \
      verif/utils.c
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
