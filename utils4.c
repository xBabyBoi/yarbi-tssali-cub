/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 17:17:23 by outourmi          #+#    #+#             */
/*   Updated: 2025/12/15 20:58:14 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	hex_to_int(char *hex)
{
	unsigned int	result;
	int				i;
	char			c;

	result = 0;
	i = 0;
	if (hex[0] == '0' && (hex[1] == 'x' || hex[1] == 'X'))
		i = 2;
	while (hex[i] != '\0')
	{
		c = hex[i];
		result = result << 4;
		if (c >= '0' && c <= '9')
			result = result + (c - '0');
		if (c >= 'a' && c <= 'f')
			result = result + (c - 'a' + 10);
		if (c >= 'A' && c <= 'F')
			result = result + (c - 'A' + 10);
		i++;
	}
	return (result);
}

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
