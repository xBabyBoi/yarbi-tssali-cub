/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:05:49 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/01 11:33:40 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast_3d(t_game *game)
{
	int		x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		init_rays(game, &ray, x);
		check_hit_wall(game, &ray);
		calculate_wall_distance(game, &ray);
		draw_wall_stripe(game, x, &ray);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}

void	calculate_wall_distance(t_game *game, t_ray *ray)
{
	double	pos_x;
	double	pos_y;

	pos_x = game->player.px / tile_size;
	pos_y = game->player.py / tile_size;
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - pos_x + (1 - ray->stepX) / 2.0)
			/ ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - pos_y + (1 - ray->stepY) / 2.0)
			/ ray->rayDirY;
	if (ray->perpWallDist < 1e-6)
		ray->perpWallDist = 1e-6;
	if (ray->side == 0)
		ray->wallX = pos_y + ray->perpWallDist * ray->rayDirY;
	else
		ray->wallX = pos_x + ray->perpWallDist * ray->rayDirX;
	ray->wallX -= floor(ray->wallX);
}
