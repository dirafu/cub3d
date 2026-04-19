NAME = verif
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

HEADER = verif.h
SRC = main_verif.c \
      map_check.c \
      pre_map_content_check.c \
      pre_map_structure_check.c \
      row_checker.c \
      utils.c \
      utils_map_check.c \
      ../get_next_line/get_next_line.c \
      ../get_next_line/get_next_line_utils.c
OBJ=$(SRC:.c=.o)

all: $(HEADER) $(SRC) $(NAME)

re: fclean all

$(NAME): $(OBJ)
	@make -C ../libft
	$(CC) $(CFLAGS) -o $@ $(OBJ) -L../libft -lft
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)
	@make -C ../libft clean

fclean: clean
	@make -C ../libft fclean
	rm -f $(NAME)

.PHONY: all fclean re clean
