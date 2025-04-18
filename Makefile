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
SRC = main.c \
	  data_obj.c \
	  param_obj.c \
	  errors.c \
	  handlers.c \
	  hooks.c \
	  draw.c \
	  draw_utils.c \
	  str_utils.c \
	  num_utils.c \

OBJ = ${SRC:.c=.o}

# Default rule (make)
all: $(NAME)

# Linking
# $(OBJ) -fsanitize=address -g
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
