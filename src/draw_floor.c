/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 13:52:01 by lnicosia          #+#    #+#             */
/*   Updated: 2019/09/17 17:16:33 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "render.h"
#include "render2.h"

/*
**	Draw a vertical vline on the screen at vline.x
*/

void	draw_vline_floor2(t_sector sector, t_vline vline, t_render2 render, t_env *env)
{
	int		i;
	double	y;
	double	x;
	Uint32	*pixels;
	Uint32	*texture_pixels;
	double	*zbuffer;
	int		coord;
	int		texture_w;
	int		texture_h;
	double	z;
	double	yalpha;

	pixels = env->sdl.texture_pixels;
	zbuffer = env->depth_array;
	texture_w = env->textures[sector.floor_texture].surface->w;
	texture_h = env->textures[sector.floor_texture].surface->h;
	texture_pixels = env->textures[sector.floor_texture].str;
	i = vline.start;
	while (i <= vline.end)
	{
		coord = vline.x + env->w * i;
		yalpha = (i - render.max_floor) / (sector.feet_y - render.max_floor);
		z = 1 / ((1 - yalpha) / render.z + yalpha / env->camera.near_z);
		if (z >= zbuffer[coord])
		{
			i++;
			continue;
		}
		if (env->editor.select && vline.x == env->h_w && i == env->h_h)
		{
			env->selected_wall1 = -1;
			env->selected_wall2 = -1;
			env->selected_floor = render.sector;
			env->selected_ceiling = -1;
			env->selected_object = -1;
			env->selected_enemy = -1;
			env->editor.selected_wall = -1;
		}
		y = ((1 - yalpha) * render.texel.y / render.z + yalpha * env->player.camera_y / env->camera.near_z) / ((1 - yalpha) / render.z + yalpha / env->camera.near_z);
		x = ((1 - yalpha) * render.texel.x / render.z + yalpha * env->player.camera_x / env->camera.near_z) / ((1 - yalpha) / render.z + yalpha / env->camera.near_z);
		y *= sector.floor_scale.y;
		x *= sector.floor_scale.x;
		y = texture_h - y;
		x = texture_w - x;
		if (y >= texture_h || y < 0)
			y = ft_abs((int)y % texture_h);
		if (x >= texture_w || x < 0)
			x = ft_abs((int)x % texture_w);
		if (x >= 0 && x < texture_w && y >= 0 && y < texture_h)
		{
			if (!env->options.lighting)
				pixels[coord] = texture_pixels[(int)x + texture_w * (int)y];
			else
				pixels[coord] = apply_light(texture_pixels[(int)x + texture_w * (int)y], sector.light_color, sector.brightness);
			if (env->editor.in_game && !env->editor.select && env->selected_floor == render.sector)
				pixels[coord] = blend_alpha(pixels[coord], 0xFF00FF00, 128);
			zbuffer[coord] = z;
			if (env->options.zbuffer || env->options.contouring)
				if (i == (int)(render.max_floor) || i == vline.end)
					pixels[vline.x + env->w * i] = 0xFFFF0000;
		}
		i++;
	}
}

/*
**	Draw a vertical vline on the screen at vline.x
*/

void	draw_vline_floor_color2(t_vline vline, t_render2 render, t_env *env)
{
	int		coord;
	Uint32	*pixels;
	double	*zbuffer;

	(void)render;
	pixels = env->sdl.texture_pixels;
	zbuffer = env->depth_array;
	while (vline.start <= vline.end)
	{
		coord = vline.x + env->w * vline.start;
		if (env->editor.select && vline.x == env->h_w && vline.start == env->h_h)
		{
			env->selected_wall1 = -1;
			env->selected_wall2 = -1;
			env->selected_floor = render.sector;
			env->selected_ceiling = -1;
			env->selected_object = -1;
			env->selected_enemy = -1;
			env->editor.selected_wall = -1;
		}
		if (env->editor.in_game && !env->editor.select && env->selected_floor == render.sector)
			pixels[coord] = blend_alpha(0xFF3F3D61, 0xFF00FF00, 128);
		else
			pixels[coord] = 0xFF3D3D61;
		vline.start++;
	}
}

void	draw_floor2(t_sector sector, t_render2 render, t_env *env)
{
	t_vline	vline;

	vline.x = render.x;
	vline.start = ft_max(0, (int)(render.current_floor));
	vline.end = env->ymax[vline.x];
	draw_vline_floor2(sector, vline, render, env);
}
