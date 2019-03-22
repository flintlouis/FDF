# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fhignett <fhignett@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/01/24 12:18:10 by rkuijper       #+#    #+#                 #
#    Updated: 2019/03/22 18:55:24 by fhignett      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = fdf
INCL = -Ilibft -Iminilibx_macos
LIB = -Lminilibx_macos -lmlx -Llibft -lft
FILESC = angles.c draw_line.c errors.c get_map.c gradient.c init_cam.c \
key_conf_xtra.c key_conf.c main.c
FILESO = $(FILESC:.c=.o)

all: $(NAME)

$(NAME):
	@echo "Compiling..."
	@make -C libft
	@gcc -Wall -Werror -Wextra -o $(NAME) $(FILESC) $(LIB) $(INCL) -framework OpenGL -framework AppKit
	@echo "Done!"

clean:
	@echo "Removing object files..."
	@rm -f $(FILESO)
	@make -C libft clean
fclean: clean
	@echo "Removing binaries..."
	@rm -f $(NAME)
	@make -C libft fclean

re: fclean all
