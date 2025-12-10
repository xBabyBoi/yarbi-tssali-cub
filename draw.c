/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:47:42 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/09 18:10:26 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map(char **arena, int arena_size, t_game *game)
{
	(void)arena;
	(void)arena_size;
	mlx_clear_window(game->mlx, game->win);
	raycast_3d(game);
}

void	put_pixel_to_frame(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->frame.addr + (y * game->frame.line_len + x * (game->frame.bpp
				/ 8));
	*(unsigned int *)dst = color;
}

int	select_texture_index(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->raydir_x < 0)
			return (2);
		else
			return (3);
	}
	else
	{
		if (ray->raydir_y < 0)
			return (0);
		else
			return (1);
	}
}
