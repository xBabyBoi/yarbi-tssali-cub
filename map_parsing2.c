/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:44:08 by outourmi          #+#    #+#             */
/*   Updated: 2025/11/21 18:23:29 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**extract_map2(char **lines, int start, int count)
{
	char	**map;
	int		k;
	int		j;

	map = malloc((count + 1) * sizeof(char *));
	if (!map)
		return (NULL);
	k = 0;
	j = start;
	while (lines[j])
	{
		if (!is_empty_line(lines[j]))
		{
			map[k++] = lines[j];
		}
		j++;
	}
	map[k] = NULL;
	return (map);
}

char	**extract_map(char **lines, int *map_start_idx)
{
	int		i;
	int		j;
	int		count;

	i = 0;
	while (lines[i] && (is_identifier_line(lines[i])
			|| is_empty_line(lines[i])))
		i++;
	if (map_start_idx)
		*map_start_idx = i;
	count = 0;
	j = i;
	while (lines[j])
	{
		if (!is_empty_line(lines[j]))
			count++;
		j++;
	}
	return (extract_map2(lines, i, count));
}

int	scan_for_player(char **map, s_cub_info *info)
{
	int		i;
	int		count;
	char	c;
	int		j;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && map[i][j] != '\n')
		{
			c = map[i][j];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				count++;
				info->player->f = c;
				info->player->y = i;
				info->player->x = j;
			}
			j++;
		}
		i++;
	}
	return (count);
}

void	check_player(char **map, s_cub_info *info)
{
	int	count;

	if (!info->player)
	{
		info->player = malloc(sizeof(*info->player));
		if (!info->player)
			exit(printf("malloc failed\n"));
	}
	info->player->x = -1;
	info->player->y = -1;
	info->player->f = 0;
	count = scan_for_player(map, info);
	if (count != 1)
		exit(printf("invalid map\n"));
}
