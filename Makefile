NAME = pipex

SRC_DIR = ./src
BONUS_DIR = ./bonus
INC_DIR = ./inc
LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

SRC_FILES =	$(SRC_DIR)/main.c \
			$(SRC_DIR)/parse_check_input.c \
			$(SRC_DIR)/utils.c \
			$(SRC_DIR)/execute_commands.c \

BONUS_SRC_FILES = $(BONUS_DIR)/main_bonus.c \
				  $(BONUS_DIR)/parse_check_input_bonus.c \
				  $(BONUS_DIR)/utils_bonus.c \
				  $(BONUS_DIR)/free_bonus.c \
				  $(BONUS_DIR)/execute_commands_bonus.c \

OBJ_FILES = $(SRC_FILES:.c=.o)
BONUS_OBJ_FILES = $(BONUS_SRC_FILES:.c=.o)

REMOVE = rm -f
CC = clang
CFLAGS = -Wall -Werror -Wextra -Wno-unused-result -I$(INC_DIR) -I$(BONUS_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	@echo "Pipex:	Compiling"
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT) -o $(NAME)
	@echo "Pipex:	Compiled"

$(LIBFT):
	@echo "Libft:	Compiling"
	@make -s all -C $(LIBFT_DIR)

bonus: $(LIBFT) $(BONUS_OBJ_FILES)
	@echo "Pipex Bonus:	Compiling"
	@$(CC) $(CFLAGS) $(BONUS_OBJ_FILES) $(LIBFT) -o $(NAME)
	@echo "Pipex Bonus:	Compiled"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -s clean -C $(LIBFT_DIR)
	@$(REMOVE) $(OBJ_FILES) $(BONUS_OBJ_FILES)
	@echo "Pipex:	Object Files Removed"

fclean:
	@make -s fclean -C $(LIBFT_DIR)
	@$(REMOVE) $(OBJ_FILES) $(BONUS_OBJ_FILES)
	@echo "Pipex:	Object Files Removed"
	@$(REMOVE) $(NAME)
	@echo "Pipex:	Executable Removed"

re:	fclean all

.PHONY: all clean fclean re bonus
