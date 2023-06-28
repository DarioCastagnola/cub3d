# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcastagn <dcastagn@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/28 11:46:42 by dcastagn          #+#    #+#              #
#    Updated: 2023/06/28 12:24:01 by dcastagn         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D

SRC			= $(wildcard gnl/*.c) $(wildcard *.c) $(wildcard errors/*.c)

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
	@make -C libft
ifeq ($(shell uname), Linux)
	@make -C minilibx-linux
	$(CC) $(FLAGS) $(OBJ) -L ./libft -lft -L ./minilibx-linux -lmlx -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

endif
	@printf "\r\033[KCUBE3D  CREATED  SUCCESSUFULLY\n$(RESET)"
	@printf "$(BLUE)-------------------------------------------------------------------------\n$(RESET)"

%.o : %.c
ifeq ($(shell uname),Linux)
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imxl_linux -O3 -c $< -o $@

endif
		

all: $(NAME)

linux: $(OBJ)
	$(CC) -fsanitize=address $(OBJ) $(RDLN_L) -o $(NAME)

clean:
ifeq ($(shell uname), Linux)
	@make -C minilibx-linux clean
	@rm -rf libmlx.dylib
endif
	@make -C libft clean
	@printf "$(RED)\nRemoving Object files...\n$(RESET)"
	@printf "$(BLUE)-------------------------------------------------------------------------\n$(RESET)"
	@$(RM) $(OBJ)
	@printf "$(RED)Object files removed\n$(RESET)"
	
fclean: clean
	@make -C libft fclean
	@printf "$(RED)\nRemoving program executable...\n$(RESET)"
	@printf "$(BLUE)-------------------------------------------------------------------------\n$(RESET)"
	@$(RM) $(NAME)
	@printf "$(RED)CUDE3D REMOVED\n$(RESET)"

	
re: fclean all

test:
	./cub3D ./maps/test.cub

.PHONY: all clean fclean re
