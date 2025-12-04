/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 17:52:27 by outourmi          #+#    #+#             */
/*   Updated: 2025/12/04 20:01:18 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clear_window(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
}

void	free_map_copy(char **map)
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

int	count_lines(int fd)
{
    char	*line;
    int		count;

    count = 0;
    line = get_next_line(fd);
    while (line)
    {
        count++;
        free(line);
        line = get_next_line(fd);
    }
    return (count);
}

int	load_texture_index(t_game *game, const char *path, int idx,
		const char *name)
{
	game->textures[idx].img = mlx_xpm_file_to_image(game->mlx, (char *)path,
			&game->textures[idx].width, &game->textures[idx].height);
	if (!game->textures[idx].img)
		return (printf("Error: Failed to load %s texture: %s\n", name, path),
			1);
	game->textures[idx].addr = mlx_get_data_addr(game->textures[idx].img,
			&game->textures[idx].bpp, &game->textures[idx].line_len,
			&game->textures[idx].endian);
	return (0);
}

int	load_textures(t_game *game, s_cub_info *info)
{
	const char	*paths[4];
	const char	*names[4];
	int			i;

	paths[0] = info->north;
	paths[1] = info->south;
	paths[2] = info->west;
	paths[3] = info->east;
	names[0] = "North";
	names[1] = "South";
	names[2] = "West";
	names[3] = "East";
	i = 0;
	while (i < 4)
	{
		if (load_texture_index(game, paths[i], i, names[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}