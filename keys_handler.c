/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:47:41 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/09 17:55:55 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_handler(int keysym, t_game *game)
{
	if (keysym == XK_ESCAPE)
		close_handler(game);
	else if (keysym == XK_W_LOW || keysym == XK_W_UPPER)
		game->keys.w = 1;
	else if (keysym == XK_S_LOW || keysym == XK_S_UPPER)
		game->keys.s = 1;
	else if (keysym == XK_A_LOW || keysym == XK_A_UPPER)
		game->keys.a = 1;
	else if (keysym == XK_D_LOW || keysym == XK_D_UPPER)
		game->keys.d = 1;
	else if (keysym == XK_LEFT)
		game->keys.left = 1;
	else if (keysym == XK_RIGHT)
		game->keys.right = 1;
	return (0);
}

int	key_release_handler(int keysym, t_game *game)
{
	if (keysym == XK_W_LOW || keysym == XK_W_UPPER)
		game->keys.w = 0;
	else if (keysym == XK_S_LOW || keysym == XK_S_UPPER)
		game->keys.s = 0;
	else if (keysym == XK_A_LOW || keysym == XK_A_UPPER)
		game->keys.a = 0;
	else if (keysym == XK_D_LOW || keysym == XK_D_UPPER)
		game->keys.d = 0;
	else if (keysym == XK_LEFT)
		game->keys.left = 0;
	else if (keysym == XK_RIGHT)
		game->keys.right = 0;
	return (0);
}

static void	handle_player_movement(t_game *game, int *moved)
{
	if (game->keys.w)
	{
		calculate_next_position(game, &game->player, XK_W_LOW);
		*moved = 1;
	}
	if (game->keys.s)
	{
		calculate_next_position(game, &game->player, XK_S_LOW);
		*moved = 1;
	}
	if (game->keys.a)
	{
		calculate_next_position(game, &game->player, XK_A_LOW);
		*moved = 1;
	}
	if (game->keys.d)
	{
		calculate_next_position(game, &game->player, XK_D_LOW);
		*moved = 1;
	}
}

static void	handle_camera_rotation(t_game *game, int *moved)
{
	if (game->keys.left)
	{
		rotate_camera(game, -0.01);
		*moved = 1;
	}
	if (game->keys.right)
	{
		rotate_camera(game, 0.01);
		*moved = 1;
	}
}

int	game_loop(t_game *game)
{
	int	moved;

	moved = 0;
	handle_player_movement(game, &moved);
	handle_camera_rotation(game, &moved);
	if (moved)
		draw_map(game->arena, game->arena_size, game);
	return (0);
}
