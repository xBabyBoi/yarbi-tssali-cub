/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 11:21:00 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/01 11:45:18 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_step_y(t_game *game, t_ray *ray)
{
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->player.py / tile_size - ray->mapY)
			* ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - game->player.py / tile_size)
			* ray->deltaDistY;
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
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (ray->mapX < 0 || ray->mapY < 0)
			break ;
		if (ray->mapY >= game->arena_size || !game->arena[ray->mapY])
			break ;
		if (game->arena[ray->mapY][ray->mapX] == '1')
			hit = 1;
	}
}
