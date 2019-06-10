ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so
CC = gcc
CFLAGS = -Wall -Wextra -Werror
FUNC = malloc free realloc
SRC = $(addprefix src/, $(addsuffix .c, $(FUNC) main)) includes/malloc.h
OBJ = $(addprefix build/, $(addsuffix .o, $(FUNC)))
RED = \033[1;31m
GREEN = \033[1;92m
BLUE = \033[34;1m
YELLOW = \033[0;33m
HEADER = -I includes/ -I libft/includes/
LDLIBS = -lft
LDFLAGS = -L libft/ -shared

all: $(NAME)

$(NAME): $(OBJ) lib
	@ar -rc lib/$(NAME) $(OBJ)
	@ranlib lib/$(NAME)
	@ln -s lib/$(NAME) lib/libft_malloc.so

./build/%.o: ./src/%.c
	@echo "     $(YELLOW) → Compiling $<"
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADER)
	@echo "     $(GREEN)   OK"

lib:
	@make -C libft

test: $(NAME)
	@make -C test

norm:
	@norminette $(SRC)

clean:
	@/bin/rm -f $(OBJ)
	@echo "  $(YELLOW)OBJ files have been deleted."

fclean:
	@/bin/rm -f $(OBJ) lib/$(NAME) lib/libft_malloc.so
	@echo "  $(YELLOW)$(NAME) and OBJ files have been deleted."

re: fclean $(NAME)

.PHONY = all clean fclean re norm lib
