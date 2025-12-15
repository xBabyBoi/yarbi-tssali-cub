/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:56:43 by outourmi          #+#    #+#             */
/*   Updated: 2025/12/13 19:04:05 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	validate_map_closure(t_cub_info *info)
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

void	replace_enclosed_spaces(char **map, char **copy, int h)
{
	int	i;
	int	j;

	i = 0;
	while (i < h)
	{
		j = 0;
		while (copy[i][j] && copy[i][j] != '\n')
		{
			if (copy[i][j] == 'V')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	is_inside_space(char **map, int y, int x)
{
	int	line_len;
	int	has_wall_left;
	int	has_wall_right;
	int	j;

	line_len = get_line_length(map[y]);
	has_wall_left = 0;
	has_wall_right = 0;
	j = 0;
	while (j < x)
	{
		if (map[y][j] == '1' || map[y][j] == '0' || map[y][j] == 'N'
			|| map[y][j] == 'S' || map[y][j] == 'E' || map[y][j] == 'W')
			has_wall_left = 1;
		j++;
	}
	j = x + 1;
	while (j < line_len && map[y][j] != '\n')
	{
		if (map[y][j] == '1' || map[y][j] == '0' || map[y][j] == 'N'
			|| map[y][j] == 'S' || map[y][j] == 'E' || map[y][j] == 'W')
			has_wall_right = 1;
		j++;
	}
	return (has_wall_left && has_wall_right);
}

void	process_inside_spaces(char **map, int h, int w)
{
	int		i;
	int		j;

	h = get_map_height(map);
	w = get_map_width(map);
	    (void)w;
	i = 0;
	while (i < h)
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			if (map[i][j] == ' ' && is_inside_space(map, i, j))
				map[i][j] = '1';
			j++;
		}
		i++;
	}
}
