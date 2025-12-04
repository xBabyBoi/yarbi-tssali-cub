/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 08:58:21 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/01 11:52:56 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_textures(t_game *game, s_cub_info *info)
{
	game->textures[0].img = mlx_xpm_file_to_image(game->mlx, info->north,
			&game->textures[0].width, &game->textures[0].height);
	if (!game->textures[0].img)
		return (printf("Error: Failed to load North texture: %s\n",
				info->north), 1);
	game->textures[0].addr = mlx_get_data_addr(game->textures[0].img,
			&game->textures[0].bpp, &game->textures[0].line_len,
			&game->textures[0].endian);
	game->textures[1].img = mlx_xpm_file_to_image(game->mlx, info->south,
			&game->textures[1].width, &game->textures[1].height);
	if (!game->textures[1].img)
		return (printf("Error: Failed to load South texture: %s\n",
				info->south), 1);
	game->textures[1].addr = mlx_get_data_addr(game->textures[1].img,
			&game->textures[1].bpp, &game->textures[1].line_len,
			&game->textures[1].endian);
	game->textures[2].img = mlx_xpm_file_to_image(game->mlx, info->west,
			&game->textures[2].width, &game->textures[2].height);
	if (!game->textures[2].img)
		return (printf("Error: Failed to load West texture: %s\n", info->west),
			1);
	game->textures[2].addr = mlx_get_data_addr(game->textures[2].img,
			&game->textures[2].bpp, &game->textures[2].line_len,
			&game->textures[2].endian);
	game->textures[3].img = mlx_xpm_file_to_image(game->mlx, info->east,
			&game->textures[3].width, &game->textures[3].height);
	if (!game->textures[3].img)
		return (printf("Error: Failed to load East texture: %s\n", info->east),
			1);
	game->textures[3].addr = mlx_get_data_addr(game->textures[3].img,
			&game->textures[3].bpp, &game->textures[3].line_len,
			&game->textures[3].endian);
	printf("Textures loaded successfully!\n");
	printf("  North: %dx%d\n", game->textures[0].width,
		game->textures[0].height);
	printf("  South: %dx%d\n", game->textures[1].width,
		game->textures[1].height);
	printf("  West: %dx%d\n", game->textures[2].width,
		game->textures[2].height);
	printf("  East: %dx%d\n", game->textures[3].width,
		game->textures[3].height);
	return (0);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	game->frame.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->frame.addr = mlx_get_data_addr(game->frame.img, &game->frame.bpp,
			&game->frame.line_len, &game->frame.endian);
	game->arena = NULL;
	game->arena_size = 0;
	game->player.speed = 0.3;
	game->keys.w = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.left = 0;
	game->keys.right = 0;
}

// void	transfer_parsed_data_to_game(t_game *game, s_cub_info *info)
// {
// 	int				i;
// 	double			plane_len;
// 	const double	pi = 3.14159265358979323846;

// 	plane_len = tan((FOV * (pi / 180.0)) / 2.0);
// 	game->arena = info->map;
// 	i = 0;
// 	while (info->map[i])
// 		i++;
// 	game->arena_size = i;
// 	game->player.px = (info->player->x + 0.5f) * tile_size;
// 	game->player.py = (info->player->y + 0.5f) * tile_size;
// 	if (info->player->f == 'N')
// 	{
// 		game->player.dirX = 0;
// 		game->player.dirY = -1;
// 		game->camera.planeX = plane_len;
// 		game->camera.planeY = 0;
// 	}
// 	else if (info->player->f == 'S')
// 	{
// 		game->player.dirX = 0;
// 		game->player.dirY = 1;
// 		game->camera.planeX = -plane_len;
// 		game->camera.planeY = 0;
// 	}
// 	else if (info->player->f == 'E')
// 	{
// 		game->player.dirX = 1;
// 		game->player.dirY = 0;
// 		game->camera.planeX = 0;
// 		game->camera.planeY = plane_len;
// 	}
// 	else if (info->player->f == 'W')
// 	{
// 		game->player.dirX = -1;
// 		game->player.dirY = 0;
// 		game->camera.planeX = 0;
// 		game->camera.planeY = -plane_len;
// 	}
// }

int	main(int ac, char **av)
{
	t_game		game;
	s_cub_info	*info;
	char		*line;
	int			i;
	int			line_count;
	int			fd;

	if (ac != 2)
		return (printf("Usage: %s <map.cub>\n", av[0]), 1);
	if (format_check(av[1], ".cub") == 1)
		return (printf("Error: Invalid file format (expected .cub)\n"), 1);
	info = malloc(sizeof(s_cub_info));
	if (!info)
		return (printf("Error: Memory allocation failed\n"), 1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (printf("Error: Cannot open file %s\n", av[1]), 1);
	line_count = count_lines(fd);
	close(fd);
	fd = open(av[1], O_RDONLY);
	info->map = malloc(sizeof(char *) * (line_count + 1));
	if (!info->map)
		return (printf("Error: Memory allocation failed\n"), 1);
	i = 0;
	line = get_next_line(fd);
	while (line)
	{
		info->map[i++] = line;
		line = get_next_line(fd);
	}
	info->map[i] = NULL;
	close(fd);
	if (map_info(info) != 0)
		return (printf("Error: Failed to parse map info\n"), 1);
	if (map_parsing(info) != 0)
		return (printf("Error: Failed to parse map\n"), 1);
	if (!validate_map_closure(info))
		return (printf("Error: Map validation failed\n"), 1);
	printf("Map parsed successfully!\n");
	printf("Textures:\n");
	printf("  North: %s\n", info->north);
	printf("  South: %s\n", info->south);
	printf("  East: %s\n", info->east);
	printf("  West: %s\n", info->west);
	printf("Floor color: %s\n", info->floor_color);
	printf("Ceiling color: %s\n", info->ceiling_color);
	printf("Player at: (%d, %d) facing %c\n", info->player->x, info->player->y,
		info->player->f);
	init_game(&game);
	if (load_textures(&game, info) != 0)
		return (1);
	transfer_parsed_data_to_game(&game, info);
	draw_map(game.arena, game.arena_size, &game);
	mlx_hook(game.win, 2, 1L << 0, key_handler, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release_handler, &game);
	mlx_hook(game.win, 17, 1L << 17, close_handler, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
