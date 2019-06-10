NAME = test
CC = gcc
CFLAGS = -Wall -Wextra -Werror
FUNC = main
SRC = $(addprefix src/, $(addsuffix .c, $(FUNC)))
OBJ = $(addprefix build/, $(addsuffix .o, $(FUNC)))
RED = \033[1;31m
GREEN = \033[1;92m
BLUE = \033[34;1m
YELLOW = \033[0;33m
HEADER = -I ../includes/ -I ../libft/includes/
LDLIBS = -lft -lmalloc
LDFLAGS = -L ../libft/ -L ../lib/

all: $(NAME)

$(NAME): $(OBJ) lib
	@echo "\033[1;31mCompiling project..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(HEADER) $(LDLIBS) $(LDFLAGS)
	@echo "\033[1;92mSuccess !"

./build/%.o: ./src/%.c
	@echo "     $(YELLOW) → Compiling $<"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADER)
	@echo "     $(GREEN)   OK"

lib :
	@make -C ../libft

clean:
	@/bin/rm -f $(OBJ)
	@echo "  $(YELLOW)OBJ files have been deleted."

fclean:
	@/bin/rm -f $(OBJ) $(NAME)
	@echo "  $(YELLOW)$(NAME) and OBJ files have been deleted."

re: fclean $(NAME)

.PHONY = all clean fclean re norm lib
