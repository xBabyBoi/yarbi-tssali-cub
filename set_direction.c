/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:57:36 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/01 11:58:43 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_dir_plane_n(t_game *game, double plane_len)
{
	game->player.dirX = 0;
	game->player.dirY = -1;
	game->camera.planeX = plane_len;
	game->camera.planeY = 0;
}

void	set_dir_plane_s(t_game *game, double plane_len)
{
	game->player.dirX = 0;
	game->player.dirY = 1;
	game->camera.planeX = -plane_len;
	game->camera.planeY = 0;
}

void	set_dir_plane_e(t_game *game, double plane_len)
{
	game->player.dirX = 1;
	game->player.dirY = 0;
	game->camera.planeX = 0;
	game->camera.planeY = plane_len;
}

void	set_dir_plane_w(t_game *game, double plane_len)
{
	game->player.dirX = -1;
	game->player.dirY = 0;
	game->camera.planeX = 0;
	game->camera.planeY = -plane_len;
}
