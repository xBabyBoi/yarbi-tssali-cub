/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:57:36 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/09 18:08:42 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_dir_plane_n(t_game *game, double plane_len)
{
	game->player.dir_x = 0;
	game->player.dir_y = -1;
	game->camera.plane_x = plane_len;
	game->camera.plane_y = 0;
}

void	set_dir_plane_s(t_game *game, double plane_len)
{
	game->player.dir_x = 0;
	game->player.dir_y = 1;
	game->camera.plane_x = -plane_len;
	game->camera.plane_y = 0;
}

void	set_dir_plane_e(t_game *game, double plane_len)
{
	game->player.dir_x = 1;
	game->player.dir_y = 0;
	game->camera.plane_x = 0;
	game->camera.plane_y = plane_len;
}

void	set_dir_plane_w(t_game *game, double plane_len)
{
	game->player.dir_x = -1;
	game->player.dir_y = 0;
	game->camera.plane_x = 0;
	game->camera.plane_y = -plane_len;
}
