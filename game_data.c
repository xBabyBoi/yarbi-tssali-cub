/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 11:51:22 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/01 12:00:18 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_position(t_game *game, s_cub_info *info)
{
	game->player.px = (info->player->x + 0.5f) * tile_size;
	game->player.py = (info->player->y + 0.5f) * tile_size;
}

static void	set_player_direction_and_plane(t_game *game, s_cub_info *info,
		double plane_len)
{
	if (info->player->f == 'N')
		set_dir_plane_n(game, plane_len);
	else if (info->player->f == 'S')
		set_dir_plane_s(game, plane_len);
	else if (info->player->f == 'E')
		set_dir_plane_e(game, plane_len);
	else if (info->player->f == 'W')
		set_dir_plane_w(game, plane_len);
}

static void	set_arena_and_size(t_game *game, s_cub_info *info)
{
	int	i;

	i = 0;
	game->arena = info->map;
	while (info->map[i])
		i++;
	game->arena_size = i;
}

void	transfer_parsed_data_to_game(t_game *game, s_cub_info *info)
{
	const double	pi = 3.14159265358979323846;
	double			plane_len;

	plane_len = tan((FOV * (pi / 180.0)) / 2.0);
	set_arena_and_size(game, info);
	set_player_position(game, info);
	set_player_direction_and_plane(game, info, plane_len);
}
