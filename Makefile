# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: afesyk <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/16 11:37:29 by afesyk            #+#    #+#              #
#    Updated: 2018/03/16 11:37:31 by afesyk           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
SRCS = main.c parser.c parser2.c print_map.c exit.c map_modificator.c
OBJS = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror 
MLXFLAG = -lmlx -framework OpenGl -framework AppKit
LDIR = libft

GREEN = \033[32;1m
YELLOW = \033[1;33m
RED = \033[1;31m

all: $(NAME)

%.o: %.c
	@gcc $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@make -C $(LDIR)
	@gcc $(MLXFLAG) $(OBJS) -L $(LDIR) -lft -o $(NAME)
	@echo "$(GREEN)Compilation went successfully!"

clean:
	@make clean -C $(LDIR)
	@/bin/rm -f $(OBJS)
	@echo "$(YELLOW)All object-files are gone!"

fclean: clean
	@make fclean -C $(LDIR)
	@/bin/rm -f $(NAME)
	@echo "$(RED)Library and executable are removed!"

re: fclean all
