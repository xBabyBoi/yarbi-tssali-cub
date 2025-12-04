/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 10:25:03 by yel-qori          #+#    #+#             */
/*   Updated: 2025/11/20 00:41:58 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_camera(t_game *game, double angle)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->player.dirX;
	old_planex = game->camera.planeX;
	game->player.dirX = game->player.dirX * cos(angle) - game->player.dirY
		* sin(angle);
	game->player.dirY = old_dirx * sin(angle) + game->player.dirY * cos(angle);
	game->camera.planeX = game->camera.planeX * cos(angle) - game->camera.planeY
		* sin(angle);
	game->camera.planeY = old_planex * sin(angle) + game->camera.planeY
		* cos(angle);
}
