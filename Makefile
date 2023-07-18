# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lde-mich <lde-mich@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/06 15:20:41 by lde-mich          #+#    #+#              #
#    Updated: 2023/07/18 09:38:18 by lde-mich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 11:46:42 by dcastagn          #+#    #+#              #
#    Updated: 2023/06/30 12:36:59 by dcastagn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3d

SRC		= $(wildcard gnl/*.c) $(wildcard parser/*.c) $(wildcard init/*.c) $(wildcard player/*.c) $(wildcard raycasting/*.c) $(wildcard visuals/*.c) $(wildcard maps/*.c) $(wildcard *.c)

OBJ		= $(SRC:%.c=%.o)

CC		= gcc
FLAGS	= -Wall -Wextra -Werror
RM		= rm -f

RED		= \033[0;31m
GREEN	= \033[0;32m
YELLOW	= \033[1;33m
BLUE	= \033[1;34m
RESET	= \033[0;0m

$(NAME): $(OBJ)
	@make -C libft > /dev/null
	@make -C minilibx-linux > /dev/null 2>&1
	@$(CC) $(FLAGS) $(OBJ) -L ./libft -lft -L ./minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)
	@printf "$(GREEN)cub3d initialized\n$(RESET)"
	@printf "$(BLUE)-------------------------------------------------------------------------\n$(RESET)"

%.o : %.c
	@$(CC) -Wall -Wextra -Werror -I/usr/include -Imxl_linux -c $< -o $@

all: $(NAME)

linux: $(OBJ)
	$(CC) -fsanitize=address $(OBJ) $(RDLN_L) -o $(NAME)

clean:
	@make -C minilibx-linux clean > /dev/null
	@rm -rf libmlx.dylib > /dev/null
	@make -C libft clean > /dev/null
	@printf "$(RED)\nRemoving Object files...\n$(RESET)"
	@printf "$(BLUE)-------------------------------------------------------------------------\n$(RESET)"
	@$(RM) $(OBJ)
	@printf "$(RED)Object files removed\n$(RESET)"
	
fclean: clean
	@make -C libft fclean > /dev/null
	@printf "$(RED)\nRemoving program executable...\n$(RESET)"
	@printf "$(BLUE)-------------------------------------------------------------------------\n$(RESET)"
	@$(RM) $(NAME)
	@printf "$(RED)Cub3d removed\n$(RESET)"

	
re: fclean all

test:
	./cub3D ./maps/test.cub

.PHONY: all clean fclean re