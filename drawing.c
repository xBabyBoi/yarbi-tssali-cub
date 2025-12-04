/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-qori <yel-qori@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:00:32 by yel-qori          #+#    #+#             */
/*   Updated: 2025/11/21 18:03:24 by yel-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel_to_frame(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = game->frame.addr + (y * game->frame.line_len + x * (game->frame.bpp
				/ 8));
	*(unsigned int *)dst = color;
}

void	draw_wall_stripe(t_game *game, int x, t_ray *ray)
{
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		y;
	int		tex_num;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;
	t_img	*texture;

	line_height = (int)(HEIGHT / ray->perpWallDist);
	draw_start = -line_height / 2 + HEIGHT / 2;
	draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;
	if (ray->side == 0)
	{
		if (ray->rayDirX < 0)
			tex_num = 2;
		else
			tex_num = 3;
	}
	else
	{
		if (ray->rayDirY < 0)
			tex_num = 0;
		else
			tex_num = 1;
	}
	texture = &game->textures[tex_num];
	tex_x = (int)(ray->wallX * (double)texture->width);
	if ((ray->side == 0 && ray->rayDirX > 0) || (ray->side == 1
			&& ray->rayDirY < 0))
		tex_x = texture->width - tex_x - 1;
	step = (double)texture->height / line_height;
	tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
	y = 0;
	while (y < draw_start)
	{
		put_pixel_to_frame(game, x, y, 0x87CEEB);
		++y;
	}
	y = draw_start;
	while (y <= draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = *(int *)(texture->addr + (tex_y * texture->line_len + tex_x
					* (texture->bpp / 8)));
		put_pixel_to_frame(game, x, y, color);
		++y;
	}
	y = draw_end + 1;
	while (y < HEIGHT)
	{
		put_pixel_to_frame(game, x, y, 0x228B22);
		++y;
	}
}
