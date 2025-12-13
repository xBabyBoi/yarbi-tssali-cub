/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 08:58:21 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/13 19:27:41 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_text(t_game *game, int i)
{
	game->textures[i].img = NULL;
	game->textures[i].addr = NULL;
	game->textures[i].bpp = 0;
	game->textures[i].line_len = 0;
	game->textures[i].endian = 0;
	game->textures[i].width = 0;
	game->textures[i].height = 0;
}

void	init_game(t_game *game)
{
	int	i;

	i = 0;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "CUB3D");
	game->frame.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->frame.addr = mlx_get_data_addr(game->frame.img, &game->frame.bpp,
			&game->frame.line_len, &game->frame.endian);
	while (i < 4)
	{
		init_text(game, i);
		i++;
	}
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

int	load_map_from_file(const char *path, t_cub_info *info)
{
	int		fd;
	int		line_count;
	int		i;
	char	*line;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (printf("Error: Cannot open file %s\n", path), 1);
	line_count = count_lines(fd);
	close(fd);
	fd = open(path, O_RDONLY);
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
	return (0);
}

static int	parse_and_validate(t_cub_info *info)
{
	if (map_info(info) != 0)
		return (printf("Error: Failed to parse map info\n"), 1);
	if (map_parsing(info) != 0)
		return (printf("Error: Failed to parse map\n"), 1);
	if (!validate_map_closure(info))
		return (printf("Error: Map validation failed\n"), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_game		game;
	t_cub_info	*info;

	if (ac != 2 || format_check(av[1], ".cub") == 1)
		return (printf("Error"));
	info = calloc(1, sizeof(t_cub_info));
	if (!info)
		return (printf("Error: Memory allocation failed\n"), 1);
	if (load_map_from_file(av[1], info) != 0)
		return (free_initial_info(info));
	if (parse_and_validate(info) != 0)
		return (free_info(info));
	init_game(&game);
	game.info = info;
	if (load_textures(&game, info) != 0)
		return (cleanup_game(&game));
	transfer_parsed_data_to_game(&game, info);
	draw_map(game.arena, game.arena_size, &game);
	mlx_hook(game.win, 2, 1L << 0, key_handler, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release_handler, &game);
	mlx_hook(game.win, 17, 1L << 17, close_handler, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
