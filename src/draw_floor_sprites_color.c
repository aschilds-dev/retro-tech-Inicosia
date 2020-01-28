/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_sprites_color.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 18:49:31 by lnicosia          #+#    #+#             */
/*   Updated: 2020/01/28 10:31:26 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "render.h"

void	draw_floor_sprites_color(t_sector sector, t_render render, t_env *env)
{
	int			j;
	int			i;
	int			end;
	double		alpha;
	double		divider;
	double		z;
	double		y;
	double		x;
	double		sprite_x;
	double		sprite_y;
	t_sprite	sprite;
	Uint32*		sprite_pixels;
	Uint32*		pixels;
	int			coord;

	i = ft_max(0, (int)render.current_floor);
	end = env->ymax[render.x];
	pixels = env->sdl.texture_pixels;
	while (i <= end)
	{
		coord = render.x + env->w * i;
		alpha = (i - render.max_floor) / render.floor_height;
		divider = 1 / (render.camera->near_z + alpha * render.zrange);
		z = render.z_near_z * divider;
		if (z >= env->zbuffer[coord])
		{
			i++;
			continue;
		}
		y = (render.texel_y_near_z + alpha * render.texel_y_camera_range)
			* divider;
		x = (render.texel_x_near_z + alpha * render.texel_x_camera_range)
			* divider;
		j = 0;
		while (j < sector.floor_sprites.nb_sprites)
		{
			sprite = env->object_sprites[sector.floor_sprites.sprite[j]];
			sprite_pixels = (Uint32*)env->sprite_textures[sprite.texture].str;
			/*sprite_x = (x - sector.floor_sprites.pos[j].x)
				* (sprite.size[0].x) / sector.floor_sprites.scale[j].x;
			sprite_y = (y - sector.floor_sprites.pos[j].y)
				* (sprite.size[0].y) / sector.floor_sprites.scale[j].y;*/
			sprite_x = (x - sector.floor_sprites.pos[j].x)
				* sector.floor_sprites_scale[j].x + sprite.start[0].x;
			sprite_y = (y - sector.floor_sprites.pos[j].y)
				* sector.floor_sprites_scale[j].y + sprite.start[0].y;
			if (sprite_x >= sprite.start[0].x && sprite_x < sprite.end[0].x
					&& sprite_y >= sprite.start[0].y && sprite_y < sprite.end[0].y
					&& sprite_pixels[(int)sprite_x
					+ env->sprite_textures[sprite.texture].surface->w
					* (int)sprite_y] != 0xFFC10099)
			{
				if (env->editor.select && render.x == env->h_w && i == env->h_h)
				{
					reset_selection(env);
					env->selected_floor = sector.num;
					env->selected_floor_sprite = j;
					env->editor.sprite_tab.state = DOWN;
					env->editor.sprite_tab.anim_state = PRESSED;
				}
				pixels[coord] = apply_light_color(sprite_pixels[(int)sprite_x
				+ env->sprite_textures[sprite.texture].surface->w
				* (int)sprite_y], sector.light_color, sector.intensity);
				if (!env->editor.select && env->selected_floor == sector.num
					&& env->selected_floor_sprite == j)
					pixels[coord] = blend_alpha(pixels[coord], 0x1abc9c, 128);
				env->zbuffer[coord] = z;
				break;
			}
			j++;
		}
		i++;
	}
}
