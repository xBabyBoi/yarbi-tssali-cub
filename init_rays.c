/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:21:00 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/10 16:46:00 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_step_y(t_game *game, t_ray *ray)
{
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player.py / TILE_SIZE - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player.py / TILE_SIZE)
			* ray->delta_dist_y;
	}
}

void	init_rays(t_game *game, t_ray *ray, int x)
{
	init_ray_dir_and_map(game, ray, x);
	init_delta_dist(ray);
	init_step_x(game, ray);
	init_step_y(game, ray);
}

void	check_hit_wall(t_game *game, t_ray *ray)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map_x < 0 || ray->map_y < 0)
			break ;
		if (ray->map_y >= game->arena_size || !game->arena[ray->map_y])
			break ;
		if (game->arena[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}
}
