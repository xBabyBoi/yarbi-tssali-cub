/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:17:23 by outourmi          #+#    #+#             */
/*   Updated: 2025/12/12 19:26:44 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map_array(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	free_info(t_cub_info *info)
{
	if (!info)
		return (2);
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
	return (1);
}

int	cleanup_game(t_game *game)
{
	if (!game)
		return (2);
	free_texture_images(game);
	if (game->frame.img)
		mlx_destroy_image(game->mlx, game->frame.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->info)
		free_info(game->info);
	if (game->mlx)
		free(game->mlx);
	return (1);
}

int	free_initial_info(t_cub_info *info)
{
	if (!info)
		return (2);
	if (info->map)
		free_map_array(info->map);
	if (info->player)
		free(info->player);
	free(info);
	return (1);
}
