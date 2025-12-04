/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:44:01 by outourmi          #+#    #+#             */
/*   Updated: 2025/11/21 18:35:33 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_line(s_cub_info *info, char *line, t_texture_count *cnt)
{
	int	j;

	j = 0;
	while (line[j] == ' ' || line[j] == '\t')
		j++;
	if (ft_strncmp(&line[j], "NO", 2) == 0 && ++cnt->no)
		info->north = line;
	else if (ft_strncmp(&line[j], "SO", 2) == 0 && ++cnt->so)
		info->south = line;
	else if (ft_strncmp(&line[j], "WE", 2) == 0 && ++cnt->we)
		info->west = line;
	else if (ft_strncmp(&line[j], "EA", 2) == 0 && ++cnt->ea)
		info->east = line;
	else if (ft_strncmp(&line[j], "F", 1) == 0 && ++cnt->f)
		info->floor_color = line;
	else if (ft_strncmp(&line[j], "C", 1) == 0 && ++cnt->c)
		info->ceiling_color = line;
}

int	map_info(s_cub_info *info)
{
	t_texture_count	cnt;
	int				i;

	cnt.no = 0;
	cnt.so = 0;
	cnt.ea = 0;
	cnt.we = 0;
	cnt.f = 0;
	cnt.c = 0;
	i = 0;
	while (info->map[i])
	{
		process_line(info, info->map[i], &cnt);
		i++;
	}
	if (cnt.no != 1 || cnt.so != 1 || cnt.we != 1
		|| cnt.ea != 1 || cnt.f != 1 || cnt.c != 1)
		exit(printf("Texture identifier error\n"));
	parse_info(info);
	return (0);
}
