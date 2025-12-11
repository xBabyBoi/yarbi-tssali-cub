/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 17:12:17 by outourmi          #+#    #+#             */
/*   Updated: 2025/12/10 17:18:19 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	rotate_camera(t_game *game, double angle)
{
	double	old_dirx;
	double	old_planex;

	old_dirx = game->player.dir_x;
	old_planex = game->camera.plane_x;
	game->player.dir_x = game->player.dir_x * cos(angle) - game->player.dir_y
		* sin(angle);
	game->player.dir_y = old_dirx * sin(angle) + game->player.dir_y
		* cos(angle);
	game->camera.plane_x = game->camera.plane_x * cos(angle)
		- game->camera.plane_y * sin(angle);
	game->camera.plane_y = old_planex * sin(angle) + game->camera.plane_y
		* cos(angle);
}

int	get_map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	get_line_length(char *line)
{
	int	len;

	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

int	close_handler(t_game *game)
{
	printf("Closing game...\n");
	cleanup_game(game);
	exit(0);
}

static void	free_texture_images(t_game *game)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image(game->mlx, game->textures[i].img);
		i++;
	}
}

void	free_map_array(char **map)
{
	int i;

	if (!map)
		return;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_info(t_cub_info *info)
{
	if (!info)
		return;
	if (info->map)
		free_map_array(info->map);
	if (info->north)
		free(info->north);
	if (info->south)
		free(info->south);
	if (info->east)
		free(info->east);
	if (info->west)
		free(info->west);
	if (info->floor_color)
		free(info->floor_color);
	if (info->ceiling_color)
		free(info->ceiling_color);
	if (info->player)
		free(info->player);
	free(info);
}

void	cleanup_game(t_game *game)
{
	if (!game)
		return;
	/* Destroy MLX images (textures and frame). MLX internal leaks are suppressed separately */
	free_texture_images(game);
	if (game->frame.img)
		mlx_destroy_image(game->mlx, game->frame.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	/* Free parsed info and arena memory */
	if (game->info)
		free_info(game->info);
}


void	free_initial_info(t_cub_info *info)
{
	/* Free info when parsing hasn't transformed/aliased pointers yet */
	if (!info)
		return;
	if (info->map)
		free_map_array(info->map);
	if (info->player)
		free(info->player);
	free(info);
}
