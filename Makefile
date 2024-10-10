NAME = fractol

##Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

##MLX
MLX = mlx
MLX_LNK = -L$(MLX) -lmlx -framework OpenGL -framework AppKit

# Clean command
RM = rm -rf

# Source and Object Files
SRC = main.c
OBJ = ${SRC:.c=.o}

# Default rule (make)
all: $(NAME)

# Linking
$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX_LNK) -o $(NAME)

# Object File Compilation Rule
%.o: %.c
	$(CC) $(CFLAGS) -I$(MLX) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
