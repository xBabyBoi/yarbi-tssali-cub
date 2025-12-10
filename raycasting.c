/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 13:05:49 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/10 16:46:36 by outourmi         ###   ########.fr       */
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

	pos_x = game->player.px / TILE_SIZE;
	pos_y = game->player.py / TILE_SIZE;
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - pos_x + (1 - ray->step_x) / 2.0)
			/ ray->raydir_x;
	else
		ray->perp_wall_dist = (ray->map_y - pos_y + (1 - ray->step_y) / 2.0)
			/ ray->raydir_y;
	if (ray->perp_wall_dist < 1e-6)
		ray->perp_wall_dist = 1e-6;
	if (ray->side == 0)
		ray->wall_x = pos_y + ray->perp_wall_dist * ray->raydir_y;
	else
		ray->wall_x = pos_x + ray->perp_wall_dist * ray->raydir_x;
	ray->wall_x -= floor(ray->wall_x);
}
