/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox_draw_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 10:06:35 by lnicosia          #+#    #+#             */
/*   Updated: 2020/01/07 13:50:19 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "render.h"
#include "render.h"

/*
**	Draw a vertical vline on the screen at vline.x
*/

void	draw_skybox_wall(t_vline vline, t_skybox_data wall_data, t_render render, t_env *env)
{
	int			i;
	double		yalpha;
	double		y;
	double		x;
	Uint32		*pixels;
	Uint32		*texture_pixels;
	double		*zbuffer;
	t_texture	texture;
	int			texture_w;
	int			texture_h;
	int			start_coord;
	int			end_coord;
	int			coord;
	double		z;
	double		alpha;
	double		divider;

	if (wall_data.mode == CEILING)
		texture = env->skyboxes[abs(env->sectors[render.sector].ceiling_texture) - 1].textures[render.texture];
	else if (wall_data.mode == FLOOR)
		texture = env->skyboxes[abs(env->sectors[render.sector].floor_texture) - 1].textures[render.texture];
	else
		texture = env->skyboxes[abs(env->sectors[render.sector].textures[wall_data.i]) - 1].textures[render.texture];
	pixels = env->sdl.texture_pixels;
	texture_pixels = texture.str;
	zbuffer = env->zbuffer;
	texture_w = texture.surface->w;
	texture_h = texture.surface->h;
	x = render.alpha * render.texture_w * render.z;
	if (x != x)
		return ;
	while (x >= texture_w)
		x -= texture_w;
	while (x < 0)
		x += texture_w;
	x = ft_fclamp(x, 0, texture_w);
	i = vline.start;
	while (i <= vline.end)
	{
		coord = vline.x + env->w * i;
		if (wall_data.mode == CEILING)
		{
			alpha = (wall_data.max_ceiling - i) / render.ceiling_height;
			divider = 1 / (render.camera->near_z + alpha * render.zrange);
			z = render.z_near_z * divider;
		}
		else if (wall_data.mode == FLOOR)
		{
			alpha = (i - wall_data.max_floor) / render.floor_height;
			divider = 1 / (render.camera->near_z + alpha * render.zrange);
			z = render.z_near_z * divider;
		}
		else
			z = wall_data.z;
		if (z >= zbuffer[coord])
		{
			i++;
			continue;
		}
		if (vline.x == env->h_w && i == env->h_h)
		{
			if (env->playing)
			{
				env->hovered_wall_sprite_wall = -1;
				env->hovered_wall_sprite_sprite = -1;
				env->hovered_wall_sprite_sector = -1;
			}
			if (env->editor.select)
			{
				reset_selection(env);
				if (wall_data.mode == CEILING)
					env->selected_ceiling = render.sector;
				else if (wall_data.mode == FLOOR)
					env->selected_floor = render.sector;
				else
				{
					if (env->editor.in_game)
					{
						env->editor.selected_sector = render.sector;
						env->editor.selected_wall = wall_data.i;
					}
					env->selected_wall1 = env->sectors[render.sector].vertices[wall_data.i];
					env->selected_wall2 = env->sectors[render.sector].vertices[wall_data.i + 1];
				}
			}
		}
		yalpha = (i - render.max_ceiling) / render.line_height;
		y = yalpha * render.texture_h;
		while (y >= texture_h)
			y -= texture_h;
		while (y < 0)
			y += texture_h;
		pixels[coord] = texture_pixels[(int)x + texture_w * (int)y];
		if (env->editor.in_game && render.selected && !env->editor.select
			&& (wall_data.mode != CEILING || env->selected_ceiling_sprite == -1)
			&& (wall_data.mode != FLOOR || env->selected_floor_sprite == -1))
			pixels[coord] = blend_alpha(pixels[coord], 0x1ABC9C, 128);
		zbuffer[coord] = z;
		i++;
	}
	if (env->options.zbuffer || env->options.contouring)
	{
		if (vline.start == (int)render.max_ceiling)
		{
			start_coord = vline.x + env->w * vline.start;
			pixels[start_coord] = 0xFFFF0000;
		}
		if (vline.end == (int)render.max_floor)
		{
			end_coord = vline.x + env->w * vline.end;
			pixels[end_coord] = 0xFFFF0000;
		}
	}
}

/*
**	Draw a vertical vline on the screen at vline.x
*/

void	draw_skybox_ceiling(t_vline vline, t_skybox_data wall_data, t_render render, t_env *env)
{
	int		i;
	double	y;
	double	x;
	double	alpha;
	Uint32	*pixels;
	Uint32	*texture_pixels;
	double	*zbuffer;
	int		coord;
	int		texture_w;
	int		texture_h;
	double	z;
	double	salpha;
	double	divider;

	pixels = env->sdl.texture_pixels;
	zbuffer = env->zbuffer;
	if (wall_data.mode == CEILING)
	{
		texture_w = env->skyboxes[abs(env->sectors[render.sector].ceiling_texture) - 1].textures[1].surface->w;
		texture_h = env->skyboxes[abs(env->sectors[render.sector].ceiling_texture) - 1].textures[1].surface->h;
		texture_pixels = env->skyboxes[abs(env->sectors[render.sector].ceiling_texture) - 1].textures[1].str;
	}
	else if (wall_data.mode == FLOOR)
	{
		texture_w = env->skyboxes[abs(env->sectors[render.sector].floor_texture) - 1].textures[1].surface->w;
		texture_h = env->skyboxes[abs(env->sectors[render.sector].floor_texture) - 1].textures[1].surface->h;
		texture_pixels = env->skyboxes[abs(env->sectors[render.sector].floor_texture) - 1].textures[1].str;
	}
	else
	{
		texture_w = env->skyboxes[abs(env->sectors[render.sector].textures[wall_data.i]) - 1].textures[1].surface->w;
		texture_h = env->skyboxes[abs(env->sectors[render.sector].textures[wall_data.i]) - 1].textures[1].surface->h;
		texture_pixels = env->skyboxes[abs(env->sectors[render.sector].textures[wall_data.i]) - 1].textures[1].str;
	}
	i = vline.start;
	while (i <= vline.end)
	{
		coord = vline.x + env->w * i;
		alpha = render.ceiling_start / (double)(i - render.ceiling_horizon);
		if (wall_data.mode == CEILING)
		{
			salpha = (wall_data.max_ceiling - i) / render.ceiling_height;
			divider = 1 / (render.camera->near_z + salpha * render.zrange);
			z = render.z_near_z * divider;
		}
		else if (wall_data.mode == FLOOR)
		{
			salpha = (i - wall_data.max_floor) / render.floor_height;
			divider = 1 / (render.camera->near_z + salpha * render.zrange);
			z = render.z_near_z * divider;
		}
		else
			z = wall_data.z;
		if (z >= zbuffer[coord])
		{
			i++;
			continue;
		}
		if (vline.x == env->h_w && i == env->h_h)
		{
			if (env->playing)
			{
				env->hovered_wall_sprite_wall = -1;
				env->hovered_wall_sprite_sprite = -1;
				env->hovered_wall_sprite_sector = -1;
			}
			if (env->editor.select)
			{
				reset_selection(env);
				if (wall_data.mode == CEILING)
					env->selected_ceiling = render.sector;
				else if (wall_data.mode == FLOOR)
					env->selected_floor = render.sector;
				else
				{
					if (env->editor.in_game)
					{
						env->editor.selected_sector = render.sector;
						env->editor.selected_wall = wall_data.i;
					}
					env->selected_wall1 = env->sectors[render.sector].vertices[wall_data.i];
					env->selected_wall2 = env->sectors[render.sector].vertices[wall_data.i + 1];
				}
			}
		}
		y = alpha * render.texel.y + (1.0 - alpha) * 5;
		x = alpha * render.texel.x + (1.0 - alpha) * 5;
		if (wall_data.mode == CEILING)
		{
			y *= env->skyboxes[abs(env->sectors[render.sector].ceiling_texture) - 1].textures[1].surface->h / 10;
			x *= env->skyboxes[abs(env->sectors[render.sector].ceiling_texture) - 1].textures[1].surface->w / 10;
		}
		else if (wall_data.mode == FLOOR)
		{
			y *= env->skyboxes[abs(env->sectors[render.sector].floor_texture) - 1].textures[1].surface->h / 10;
			x *= env->skyboxes[abs(env->sectors[render.sector].floor_texture) - 1].textures[1].surface->w / 10;
		}
		else
		{
			y *= env->skyboxes[abs(env->sectors[render.sector].textures[wall_data.i]) - 1].textures[1].surface->h / 10;
			x *= env->skyboxes[abs(env->sectors[render.sector].textures[wall_data.i]) - 1].textures[1].surface->w / 10;
		}
		if (y >= texture_h || y < 0)
			y = ft_abs((int)y % texture_h);
		if (x >= texture_w || x < 0)
			x = ft_abs((int)x % texture_w);
		x = texture_w - x;
		if (x >= 0 && x < texture_w && y >= 0 && y < texture_h)
		{
			pixels[coord] = texture_pixels[(int)x + texture_w * (int)y];
			if (env->editor.in_game && render.selected && !env->editor.select
				&& (wall_data.mode != CEILING || env->selected_ceiling_sprite == -1)
				&& (wall_data.mode != FLOOR || env->selected_floor_sprite == -1))
				pixels[coord] = blend_alpha(pixels[coord], 0x1ABC9C, 128);
			zbuffer[coord] = z;
		}
		i++;
	}
	if (env->options.zbuffer || env->options.contouring)
	{
		if (vline.start >= 0 && vline.start < env->h - 1)
			pixels[vline.x + env->w * vline.start] = 0xFFFF0000;
		if (vline.end == (int)render.max_ceiling - 1
				&& vline.end >= 0 && vline.end < env->h)
			pixels[vline.x + env->w * vline.end] = 0xFFFF0000;
	}
}

/*
**	Draw a vertical vline on the screen at vline.x
*/

void	draw_skybox_floor(t_vline vline, t_skybox_data wall_data, t_render render, t_env *env)
{
	int		i;
	double	y;
	double	x;
	double	alpha;
	Uint32	*pixels;
	Uint32	*texture_pixels;
	double	*zbuffer;
	int		coord;
	int		texture_w;
	int		texture_h;
	double	z;
	double	salpha;
	double	divider;

	pixels = env->sdl.texture_pixels;
	zbuffer = env->zbuffer;
	texture_h = 0;
	texture_w = 0;
	texture_pixels = env->skyboxes[abs(env->sectors[render.sector].ceiling_texture) - 1].textures[0].str;
	if (wall_data.mode == CEILING)
	{
		texture_w = env->skyboxes[abs(env->sectors[render.sector].ceiling_texture) - 1].textures[0].surface->w;
		texture_h = env->skyboxes[abs(env->sectors[render.sector].ceiling_texture) - 1].textures[0].surface->h;
		texture_pixels = env->skyboxes[abs(env->sectors[render.sector].ceiling_texture) - 1].textures[0].str;
	}
	else if (wall_data.mode == FLOOR)
	{
		texture_w = env->skyboxes[abs(env->sectors[render.sector].floor_texture) - 1].textures[0].surface->w;
		texture_h = env->skyboxes[abs(env->sectors[render.sector].floor_texture) - 1].textures[0].surface->h;
		texture_pixels = env->skyboxes[abs(env->sectors[render.sector].floor_texture) - 1].textures[0].str;
	}
	else
	{
		texture_w = env->skyboxes[abs(env->sectors[render.sector].textures[wall_data.i]) - 1].textures[0].surface->w;
		texture_h = env->skyboxes[abs(env->sectors[render.sector].textures[wall_data.i]) - 1].textures[0].surface->h;
		texture_pixels = env->skyboxes[abs(env->sectors[render.sector].textures[wall_data.i]) - 1].textures[0].str;
	}
	i = vline.start;
	while (i <= vline.end)
	{
		coord = vline.x + env->w * i;
		alpha = render.floor_start / (double)(i - render.floor_horizon);
		if (wall_data.mode == CEILING)
		{
			salpha = (wall_data.max_ceiling - i) / render.ceiling_height;
			divider = 1 / (render.camera->near_z + salpha * render.zrange);
			z = render.z_near_z * divider;
		}
		else if (wall_data.mode == FLOOR)
		{
			salpha = (i - wall_data.max_floor) / render.floor_height;
			divider = 1 / (render.camera->near_z + salpha * render.zrange);
			z = render.z_near_z * divider;
		}
		else
			z = wall_data.z;
		if (z >= zbuffer[coord])
		{
			i++;
			continue;
		}
		if (vline.x == env->h_w && i == env->h_h)
		{
			if (env->playing)
			{
				env->hovered_wall_sprite_wall = -1;
				env->hovered_wall_sprite_sprite = -1;
				env->hovered_wall_sprite_sector = -1;
			}
			if (env->editor.select)
			{
				reset_selection(env);
				if (wall_data.mode == CEILING)
					env->selected_ceiling = render.sector;
				else if (wall_data.mode == FLOOR)
					env->selected_floor = render.sector;
				else
				{
					if (env->editor.in_game)
					{
						env->editor.selected_sector = render.sector;
						env->editor.selected_wall = wall_data.i;
					}
					env->selected_wall1 = env->sectors[render.sector].vertices[wall_data.i];
					env->selected_wall2 = env->sectors[render.sector].vertices[wall_data.i + 1];
				}
			}
		}
		y = alpha * render.texel.y + (1.0 - alpha) * 5;
		x = alpha * render.texel.x + (1.0 - alpha) * 5;
		if (wall_data.mode == CEILING)
		{
			y *= env->skyboxes[abs(env->sectors[render.sector].ceiling_texture) - 1].textures[0].surface->h / 10;
			x *= env->skyboxes[abs(env->sectors[render.sector].ceiling_texture) - 1].textures[0].surface->w / 10;
		}
		else if (wall_data.mode == FLOOR)
		{
			y *= env->skyboxes[abs(env->sectors[render.sector].floor_texture) - 1].textures[0].surface->h / 10;
			x *= env->skyboxes[abs(env->sectors[render.sector].floor_texture) - 1].textures[0].surface->w / 10;
		}
		else if (wall_data.mode == WALL || wall_data.mode == UPPER_WALL
			|| wall_data.mode == BOTTOM_WALL)
		{
			y *= env->skyboxes[abs(env->sectors[render.sector].textures[wall_data.i]) - 1].textures[0].surface->h / 10;
			x *= env->skyboxes[abs(env->sectors[render.sector].textures[wall_data.i]) - 1].textures[0].surface->w / 10;
		}
		if (y >= texture_h || y < 0)
			y = ft_abs((int)y % texture_h);
		if (x >= texture_w || x < 0)
			x = ft_abs((int)x % texture_w);
		y = texture_h - y;
		x = texture_w - x;
		if (x >= 0 && x < texture_w && y >= 0 && y < texture_h)
		{
			pixels[coord] = texture_pixels[(int)x + texture_w * (int)y];
			if (env->editor.in_game && render.selected && !env->editor.select
				&& (wall_data.mode != CEILING || env->selected_ceiling_sprite == -1)
				&& (wall_data.mode != FLOOR || env->selected_floor_sprite == -1))
				pixels[coord] = blend_alpha(pixels[coord], 0x1ABC9C, 128);
			zbuffer[coord] = z;
		}
		i++;
	}
	if (env->options.zbuffer || env->options.contouring)
	{
		if (vline.start == (int)render.max_floor + 1
				&& vline.start >= 0 && vline.start < env->h)
			pixels[vline.x + env->w * vline.start] = 0xFFFF0000;
		if (vline.end < env->h - 1 && vline.end >= 0)
			pixels[vline.x + env->w * vline.end] = 0xFFFF0000;
	}
}
