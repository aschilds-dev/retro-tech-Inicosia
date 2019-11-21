/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 13:52:01 by lnicosia          #+#    #+#             */
/*   Updated: 2019/11/21 14:17:26 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "render.h"

/*
**	Draw a vertical vline on the screen at vline.x
*/

void	draw_vline_floor(t_sector sector, t_vline vline,
t_render render, t_env *env)
{
	int		i;
	int		j;
	Uint32	*pixels;
	Uint32	*texture_pixels;
	Uint32	*sprite_pixels;
	double	*zbuffer;
	int		coord;
	double	y;
	double	x;
	double	text_y;
	double	text_x;
	double	sprite_y;
	double	sprite_x;
	double	z;
	double	alpha;
	double	divider;
	size_t	map_lvl;
	t_sprite	sprite;

	pixels = env->sdl.texture_pixels;
	zbuffer = env->zbuffer;
	map_lvl = env->wall_textures[sector.floor_texture].nb_maps - 1;
	if (!env->options.show_minimap)
	{
		render.texture_w = env->wall_textures[sector.floor_texture].maps[map_lvl]->w;
		render.texture_h = env->wall_textures[sector.floor_texture].maps[map_lvl]->h;
	}
	i = vline.start;
	while (i <= vline.end)
	{
		coord = vline.x + env->w * i;
		// Peut etre opti
		alpha = (i - render.max_floor) / (render.camera->feet_y[render.sector] - render.max_floor);
		divider = 1 / (render.camera->near_z + alpha * render.zrange);
		z = render.z_near_z * divider;
		if (env->options.show_minimap)
			map_lvl = get_current_floor_map(sector.floor_texture, z, &render, env);
		texture_pixels = (Uint32*)env->wall_textures[sector.floor_texture].
		maps[map_lvl]->pixels;
		if (z >= zbuffer[coord])
		{
			i++;
			continue;
		}
		if (env->editor.select && vline.x == env->h_w && i == env->h_h)
		{
			reset_selection(env);
			env->selected_floor = render.sector;
		}
		y = (render.texel_y_near_z + alpha * render.texel_y_camera_range)
			* divider;
		x = (render.texel_x_near_z + alpha * render.texel_x_camera_range)
			* divider;
		text_y = y * sector.floor_scale[map_lvl].y + sector.floor_align.y;
		text_x = x * sector.floor_scale[map_lvl].x + sector.floor_align.x;
		text_y = render.texture_h - text_y;
		text_x = render.texture_w - text_x;
		if (text_y >= render.texture_h || text_y < 0)
			text_y = ft_abs((int)text_y % render.texture_h);
		if (text_x >= render.texture_w || text_x < 0)
			text_x = ft_abs((int)text_x % render.texture_w);
		if (text_x >= 0 && text_x < render.texture_w && text_y >= 0 && text_y < render.texture_h)
		{
			if (!env->options.lighting && !env->playing)
				pixels[coord] = texture_pixels[(int)text_x + render.texture_w * (int)text_y];
			else
				pixels[coord] = apply_light(texture_pixels[(int)text_x + render.texture_w * (int)text_y], sector.light_color, sector.brightness);
			if (env->editor.in_game && !env->editor.select && env->selected_floor == render.sector)
				pixels[coord] = blend_alpha(pixels[coord], 0xFF00FF00, 128);
			zbuffer[coord] = z;
			if (env->options.zbuffer || env->options.contouring)
				if (i == (int)(render.max_floor) || i == vline.end)
					pixels[vline.x + env->w * i] = 0xFFFF0000;
		}
		j = 0;
		while (j < sector.nb_floor_sprites)
		{
			sprite = env->wall_sprites[sector.floor_sprites.sprite[j]];
			sprite_pixels = (Uint32*)env->textures[sprite.texture].str;
			sprite_x = (x - sector.floor_sprites.pos[j].x)
			* (sprite.size[0].x) / sector.floor_sprites.scale[j].x;
			sprite_y = (y - sector.floor_sprites.pos[j].y)
			 * (sprite.size[0].y) / sector.floor_sprites.scale[j].y;
			if (sprite_x >= sprite.start[0].x && sprite_x < sprite.end[0].x
				&& sprite_y >= sprite.start[0].y && sprite_y < sprite.end[0].y
				&& sprite_pixels[(int)sprite_x
				+ env->textures[sprite.texture].surface->w
				* (int)sprite_y] != 0xFFC10099)
			{
					pixels[coord] = apply_light(sprite_pixels[(int)sprite_x + env->textures[sprite.texture].surface->w * (int)sprite_y], sector.light_color, sector.brightness);
					//break;
			}
			j++;
		}
		i++;
	}
}

/*
**	Draw a vertical vline on the screen at vline.x
*/

void	draw_vline_floor_color(t_vline vline, t_render render, t_env *env)
{
	int		coord;
	Uint32	*pixels;

	(void)render;
	pixels = env->sdl.texture_pixels;
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

void	draw_floor(t_sector sector, t_render render, t_env *env)
{
	t_vline	vline;

	vline.x = render.x;
	vline.start = ft_max(0, (int)(render.current_floor));
	vline.end = env->ymax[vline.x];
	draw_vline_floor(sector, vline, render, env);
}
