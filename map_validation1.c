/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:56:43 by outourmi          #+#    #+#             */
/*   Updated: 2025/12/04 18:28:20 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	get_map_width(char **map)
{
	int	i;
	int	max_width;
	int	current_width;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		current_width = get_line_length(map[i]);
		if (current_width > max_width)
			max_width = current_width;
		i++;
	}
	return (max_width);
}

int	flood_fill(char **map, int y, int x, int max_y)
{
	if (y < 0 || x < 0 || y >= max_y)
		return (0);
	if (x >= get_line_length(map[y]) || !map[y][x] || map[y][x] == '\n')
		return (0);
	if (map[y][x] == ' ')
		return (0);
	if (map[y][x] == '1')
		return (1);
	if (map[y][x] == 'V')
		return (1);
	map[y][x] = 'V';
	if (!flood_fill(map, y - 1, x, max_y))
		return (0);
	if (!flood_fill(map, y + 1, x, max_y))
		return (0);
	if (!flood_fill(map, y, x - 1, max_y))
		return (0);
	if (!flood_fill(map, y, x + 1, max_y))
		return (0);
	return (1);
}

int	validate_map_closure(s_cub_info *info)
{
	char	**map_copy;
	int		height;
	int		width;
	int		result;

	if (!info || !info->map || !info->player)
		return (0);
	height = get_map_height(info->map);
	width = get_map_width(info->map);
	if (height == 0 || width == 0)
		return (0);
	if (!validate_all_spaces_enclosed(info->map, height))
		return (0);
	map_copy = duplicate_map(info->map, height, width);
	if (!map_copy)
		return (0);
	result = flood_fill(map_copy, info->player->y, info->player->x, height);
	free_map_copy(map_copy);
	if (!result)
		return (0);
	return (1);
}
