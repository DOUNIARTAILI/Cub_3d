# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaqbour <mmaqbour@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/29 21:01:57 by drtaili           #+#    #+#              #
#    Updated: 2023/09/05 18:43:32 by mmaqbour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = draw.c main.c init.c dda.c map.c move_shape.c minimap.c
OBJS = $(SRC:.c=.o)
NAME = cube3d

CC = cc

RM = rm -rf

FLAGS = -Wall -Wextra -Werror

FLAGS_mlx = -lm -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

cube3d : $(OBJS)
	$(CC) $(FLAGS) $(FLAGS_mlx) $(OBJS) -o $(NAME)

%.o : %.c cube3d.h
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) 

re: fclean $(NAME) 

.PHONY = all clean fclean re
