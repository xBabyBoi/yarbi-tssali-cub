/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: outourmi <outourmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 18:00:32 by yel-qori          #+#    #+#             */
/*   Updated: 2025/12/10 16:46:30 by outourmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	compute_draw_params(t_draw_params *p, t_img *texture, t_ray *ray)
{
	p->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	p->draw_start = -p->line_height / 2 + HEIGHT / 2;
	p->draw_end = p->line_height / 2 + HEIGHT / 2;
	if (p->draw_start < 0)
		p->draw_start = 0;
	if (p->draw_end >= HEIGHT)
		p->draw_end = HEIGHT - 1;
	p->tex_x = (int)(ray->wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->raydir_x > 0) || (ray->side == 1
			&& ray->raydir_y < 0))
		p->tex_x = texture->width - p->tex_x - 1;
	p->step = (double)texture->height / p->line_height;
	p->tex_pos = (p->draw_start - HEIGHT / 2 + p->line_height / 2) * p->step;
}

void	draw_ceiling(t_game *game, int x, int draw_start)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		put_pixel_to_frame(game, x, y, 0x87CEEB);
		++y;
	}
}

void	draw_floor(t_game *game, int x, int start_y)
{
	int	y;

	y = start_y;
	while (y < HEIGHT)
	{
		put_pixel_to_frame(game, x, y, 0x228B22);
		++y;
	}
}

void	draw_wall_pixels(t_game *game, t_img *texture, int x, t_draw_params *p)
{
	int	y;
	int	tex_y;
	int	color;

	y = p->draw_start;
	while (y <= p->draw_end)
	{
		tex_y = (int)p->tex_pos & (texture->height - 1);
		p->tex_pos += p->step;
		color = *(int *)(texture->addr + (tex_y * texture->line_len + p->tex_x
					* (texture->bpp / 8)));
		put_pixel_to_frame(game, x, y, color);
		++y;
	}
}

void	draw_wall_stripe(t_game *game, int x, t_ray *ray)
{
	t_img			*texture;
	t_draw_params	p;
	int				tex_index;

	tex_index = select_texture_index(ray);
	texture = &game->textures[tex_index];
	compute_draw_params(&p, texture, ray);
	draw_ceiling(game, x, p.draw_start);
	draw_wall_pixels(game, texture, x, &p);
	draw_floor(game, x, p.draw_end + 1);
}
