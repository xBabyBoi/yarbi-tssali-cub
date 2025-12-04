# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/16 21:45:03 by yel-qori          #+#    #+#              #
#    Updated: 2025/12/04 18:35:05 by outourmi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror -I./minilibx-linux
LDFLAGS = -L./minilibx-linux -lmlx -lX11 -lXext -lm
SRC = main.c\
	draw.c\
	get_next_line/get_next_line_utils.c\
	get_next_line/get_next_line.c\
	keys_handler.c\
	movements.c\
	camera.c\
	raycasting.c\
	map_parsing1.c\
	map_parsing2.c\
	map_validation1.c\
	map_validation2.c\
	map_info1.c\
	map_info2.c\
	utils/utils1.c\
	utils/utils2.c\
	utils/ft_strtrim.c\
	utils/ft_itoa.c\
	init_rays.c\
	drawing.c\
	closing.c\
	rays_utils.c\
	player_movements.c\
	game_data.c\
	set_direction.c
	
OBJS = ${SRC:.c=.o}

all: ${NAME}

${NAME} : ${OBJS}
	${CC} ${OBJS} ${LDFLAGS} -o ${NAME}



clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re