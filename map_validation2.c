/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:56:43 by outourmi          #+#    #+#             */
/*   Updated: 2025/11/21 18:09:05 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_neighbor(char **map, int y, int x, int height)
{
	int	line_len;

	if (y < 0 || y >= height)
		return (0);
	if (!map[y] || !map[y][x])
		return (0);
	line_len = get_line_length(map[y]);
	if (x >= line_len)
		return (0);
	if (map[y][x] == ' ')
		return (0);
	return (1);
}

int	check_cell_enclosed(char **map, int y, int x, int height)
{
	if (!is_valid_neighbor(map, y - 1, x, height))
		return (0);
	if (!is_valid_neighbor(map, y + 1, x, height))
		return (0);
	if (!is_valid_neighbor(map, y, x - 1, height))
		return (0);
	if (!is_valid_neighbor(map, y, x + 1, height))
		return (0);
	return (1);
}

int	validate_all_spaces_enclosed(char **map, int height)
{
	int	i;
	int	j;
	int	line_len;

	i = 0;
	while (i < height)
	{
		line_len = get_line_length(map[i]);
		j = 0;
		while (j < line_len)
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'E' || map[i][j] == 'W')
			{
				if (!check_cell_enclosed(map, i, j, height))
				{
					printf("Error: Walkable at [%d][%d] not closed\n", i, j);
					return (0);
				}
			}
			j++;
		}
		i++;
	}
	return (1);
}

char	*duplicate_map_row(char *src, int width)
{
	char	*row;
	int		j;

	row = malloc(sizeof(char) * (width + 1));
	if (!row)
		return (NULL);
	j = 0;
	while (src[j] && src[j] != '\n' && j < width)
	{
		row[j] = src[j];
		j++;
	}
	while (j < width)
		row[j++] = ' ';
	row[j] = '\0';
	return (row);
}

char	**duplicate_map(char **map, int height, int width)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = duplicate_map_row(map[i], width);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}
