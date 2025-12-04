/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:47:41 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/01 11:41:42 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_handler(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		close_handler(game);
	else if (keysym == XK_w || keysym == XK_W)
		game->keys.w = 1;
	else if (keysym == XK_s || keysym == XK_S)
		game->keys.s = 1;
	else if (keysym == XK_a || keysym == XK_A)
		game->keys.a = 1;
	else if (keysym == XK_d || keysym == XK_D)
		game->keys.d = 1;
	else if (keysym == XK_Left)
		game->keys.left = 1;
	else if (keysym == XK_Right)
		game->keys.right = 1;
	return (0);
}

int	key_release_handler(int keysym, t_game *game)
{
	if (keysym == XK_w || keysym == XK_W)
		game->keys.w = 0;
	else if (keysym == XK_s || keysym == XK_S)
		game->keys.s = 0;
	else if (keysym == XK_a || keysym == XK_A)
		game->keys.a = 0;
	else if (keysym == XK_d || keysym == XK_D)
		game->keys.d = 0;
	else if (keysym == XK_Left)
		game->keys.left = 0;
	else if (keysym == XK_Right)
		game->keys.right = 0;
	return (0);
}

static void	handle_player_movement(t_game *game, int *moved)
{
	if (game->keys.w)
	{
		calculate_next_position(game, &game->player, XK_w);
		*moved = 1;
	}
	if (game->keys.s)
	{
		calculate_next_position(game, &game->player, XK_s);
		*moved = 1;
	}
	if (game->keys.a)
	{
		calculate_next_position(game, &game->player, XK_a);
		*moved = 1;
	}
	if (game->keys.d)
	{
		calculate_next_position(game, &game->player, XK_d);
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
