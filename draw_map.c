/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 10:47:42 by yel-qori          #+#    #+#             */
/*   Updated: 2025/11/21 18:14:19 by yel-qori         ###   ########.fr       */
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
