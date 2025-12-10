/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 14:01:46 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/09 17:57:34 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	row_len_no_nl(const char *s)
{
	int	i;

	i = 0;
	while (s && s[i] && s[i] != '\n')
		i++;
	return (i);
}

int	can_move_to(t_game *game, float px, float py)
{
	int		grid_x;
	int		grid_y;
	int		row_w;
	char	cell;

	grid_x = (int)(px / TILE_SIZE);
	grid_y = (int)(py / TILE_SIZE);
	if (grid_y < 0 || grid_y >= game->arena_size)
		return (0);
	row_w = row_len_no_nl(game->arena[grid_y]);
	if (grid_x < 0 || grid_x >= row_w)
		return (0);
	cell = game->arena[grid_y][grid_x];
	if (cell == '1' || cell == ' ')
		return (0);
	return (1);
}

void	calculate_next_position(t_game *game, t_player *player, int keysym)
{
	double	dx;
	double	dy;

	dx = 0.0;
	dy = 0.0;
	get_direction(game, keysym, &dx, &dy);
	normalize_vector(&dx, &dy);
	try_move(game, player, dx, dy);
}
