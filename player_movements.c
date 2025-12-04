/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:35:20 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/01 11:37:40 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_direction(t_game *game, int keysym, double *dx, double *dy)
{
	if (keysym == XK_w || keysym == XK_W)
	{
		*dx = game->player.dirX;
		*dy = game->player.dirY;
	}
	else if (keysym == XK_s || keysym == XK_S)
	{
		*dx = -game->player.dirX;
		*dy = -game->player.dirY;
	}
	else if (keysym == XK_a || keysym == XK_A)
	{
		*dx = -game->camera.planeX;
		*dy = -game->camera.planeY;
	}
	else if (keysym == XK_d || keysym == XK_D)
	{
		*dx = game->camera.planeX;
		*dy = game->camera.planeY;
	}
}

void	normalize_vector(double *dx, double *dy)
{
	double	mag;

	mag = sqrt((*dx) * (*dx) + (*dy) * (*dy));
	if (mag > 0.000001)
	{
		*dx /= mag;
		*dy /= mag;
	}
}

void	try_move(t_game *game, t_player *player, double dx, double dy)
{
	double	try_px;
	double	try_py;

	try_px = player->px + dx * player->speed;
	try_py = player->py + dy * player->speed;
	if (can_move_to(game, try_px, player->py))
		player->px = try_px;
	if (can_move_to(game, player->px, try_py))
		player->py = try_py;
}
