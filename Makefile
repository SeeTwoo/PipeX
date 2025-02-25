CC = cc
CFLAGS = -Wall -Wextra -Werror -Ilibft/src
DFLAGS = -Wall -Wextra -Werror -Ilibft/src -g

LIB_DIR = libft
LIB_NAME = $(LIB_DIR)/libft.a

SRC_DIR = src
SRC_FILES = cleaners.c \
			main.c \
			parsing.c \
			pipex.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

SRC_BNS_DIR = src_bns
SRC_BNS_FILES = 
SRC_BNS = $(addprefix $(SRC_BNS_DIR)/, $(SRC_BNS_FILES))


OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

OBJ_BNS_DIR = obj_bns
OBJ_BNS = $(SRC_BNS:$(SRC_BNS_DIR)%.c=$(OBJ_BNS_DIR)%.o)

NAME = pipex

NAME_BNS = pipex_bonus

all: $(LIB_NAME) $(NAME)

bonus: $(LIB_NAME) $(NAME_BNS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_NAME):
	$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJ) $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $^

$(NAME_BNS): $(OBJ_BNS) $(LIB_NAME)
	$(CC) $(CFLAGS) -o $@ $^

debug: fclean
	$(MAKE) -C $(LIB_DIR) debug
	$(MAKE) CFLAGS="$(DFLAGS)" all

debug_bonus: fclean
	$(MAKE) -C $(LIB_DIR) debug
	$(MAKE) CFLAGS="$(DFLAGS)" bonus

clean:
	$(MAKE) -C $(LIB_DIR) clean
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJ_BNS_DIR)

fclean: clean
	$(MAKE) -C $(LIB_DIR) fclean
	rm -f $(NAME)
	rm -f $(NAME_BNS)

re: fclean all

.PHONY: all debug bonus debug_bonus clean fclean re
