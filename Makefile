# ------------- VARIABLES ------------- #
NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
HEADER = include/philo.h
SRC_DIR = src/
SRC = acces_mutex.c action.c clean.c handle.c init.c main.c \
      monitor.c parse.c simulation.c time.c utils.c
OBJ_DIR = OBJ/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

# ------------- COLORS ------------- #
GREEN = \033[0;32m
RED = \033[0;31m
BOLD = \033[1m
END = \033[0m

# --------------- RULES --------------- #
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)
	@echo "$(BOLD)$(GREEN)$(NAME) done$(END)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER) Makefile
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	@echo "$(BOLD)$(RED)clean done$(END)"

fclean: clean
	rm -f $(NAME)
	@echo "$(BOLD)$(RED)fclean done$(END)"

re: fclean all

.PHONY: all clean fclean re