/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:44:01 by outourmi          #+#    #+#             */
/*   Updated: 2025/12/12 17:51:19 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*rgb_to_hex(char *r, char *g, char *b)
{
	char	*color;
	int		value_r;
	int		value_g;
	int		value_b;

	value_r = ft_atoi(r);
	value_g = ft_atoi(g);
	value_b = ft_atoi(b);
	if ((value_r < 0 || value_r > 255) || (value_g < 0 || value_g > 255)
		|| (value_b < 0 || value_b > 255))
		exit(printf("invalid color"));
	color = malloc(9);
	if (!color)
		return (NULL);
	color[0] = '0';
	color[1] = 'x';
	color[2] = "0123456789ABCDEF"[value_r / 16];
	color[3] = "0123456789ABCDEF"[value_r % 16];
	color[4] = "0123456789ABCDEF"[value_g / 16];
	color[5] = "0123456789ABCDEF"[value_g % 16];
	color[6] = "0123456789ABCDEF"[value_b / 16];
	color[7] = "0123456789ABCDEF"[value_b % 16];
	color[8] = '\0';
	return (color);
}

static void	process_color_char(char *str, t_parse_color *p)
{
	if ((str[p->i] < 48 || str[p->i] > 57) && str[p->i] != ','
		&& str[p->i] != ' ' && str[p->i] != '\t')
		exit(printf("error\n"));
	if (str[p->i] == ',')
	{
		p->color[p->comp][p->j] = '\0';
		if (str[p->i + 1] >= 48 && str[p->i + 1] <= 57)
			p->x++;
		p->comp++;
		p->j = 0;
	}
	else
	{
		p->color[p->comp][p->j] = str[p->i];
		p->j++;
	}
}

char	*parse_color2(char *str1, t_parse_color p)
{
	if (p.x != 3)
	{
		free(p.color[0]);
		free(p.color[1]);
		free(p.color[2]);
		free(p.color);
		exit(printf("error"));
	}
	p.color[p.comp][p.j] = '\0';
	str1 = rgb_to_hex(p.color[0], p.color[1], p.color[2]);
	free(p.color[0]);
	free(p.color[1]);
	free(p.color[2]);
	free(p.color);
	return (str1);
}

char	*parse_color(char *str)
{
	t_parse_color	p;
	char			*str1;

	p.color = malloc(3 * sizeof(char *));
	if (!p.color)
		return (NULL);
	p.color[0] = malloc(4);
	p.color[1] = malloc(4);
	p.color[2] = malloc(4);
	p.i = 0;
	p.j = 0;
	p.x = 1;
	p.comp = 0;
	while (str[p.i] && p.comp < 3)
	{
		process_color_char(str, &p);
		p.i++;
	}
	str1 = parse_color2(str, p);
	return (str1);
}

void	parse_info(t_cub_info *info)
{
	char	*tmp_floor;
	char	*tmp_ceiling;

	info->north = ft_strtrim(info->north, " \nNOSOWEAFC");
	info->south = ft_strtrim(info->south, " \nNOSOWEAFC");
	info->west = ft_strtrim(info->west, " \nNOSOWEAFC");
	info->east = ft_strtrim(info->east, " \nNOSOWEAFC");
	tmp_floor = ft_strtrim(info->floor_color, " \nNOSOWEAFC");
	tmp_ceiling = ft_strtrim(info->ceiling_color, " \nNOSOWEAFC");
	info->floor_color = parse_color(tmp_floor);
	info->ceiling_color = parse_color(tmp_ceiling);
	if (tmp_floor)
		free(tmp_floor);
	if (tmp_ceiling)
		free(tmp_ceiling);
	if (format_check(info->north, ".xpm") == 1 || format_check(info->south,
			".xpm") == 1 || format_check(info->west, ".xpm") == 1
		|| format_check(info->east, ".xpm") == 1)
		exit(printf("Invalid texture format\n"));
}
