/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:04:12 by lnicosia          #+#    #+#             */
/*   Updated: 2019/06/24 19:10:29 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "render.h"

void		draw_object(t_object object, t_env *env, t_render *render)
{
	t_render_object	orender;
	int				x;
	int				xstart;
	int				xend;
	int				y;
	int				ystart;
	int				yend;
	int				textx;
	int				texty;
	int				index;
	double			xalpha;
	double			yalpha;
	int				anglediff;
	t_texture		texture;

	(void)render;
	get_translated_object_pos(&orender, object, env);
	get_rotated_object_pos(&orender, env);
	project_object(&orender, object, env);
	if (orender.rotated_pos.z <= 0)
		return ;
	if (!object.oriented)
	{
		index = 0;
	}
	else
	{
		anglediff = (int)(object.angle - env->player.angle * CONVERT_DEGREES) % 360;
		//ft_printf("object = %f\n", object.angle);
		//ft_printf("player = %f\n", env->player.angle * CONVERT_DEGREES);
		//ft_printf("%d\n", anglediff);
		if (anglediff >= -22.5 && anglediff < 22.5)
			index = 0;
		else if (anglediff >= 22.5 && anglediff < 77.5)
			index = 7;
		else if (anglediff >= 77.5 && anglediff < 122.5)
			index = 6;
		else if (anglediff >= 122.5 && anglediff < 167.5)
			index = 5;
		else if (anglediff >= 167.5 && anglediff < 212.5)
			index = 4;
		else if (anglediff >= 212.5 && anglediff < 257.5)
			index = 3;
		else if (anglediff >= 257.7 && anglediff < 302.5)
			index = 2;
		else
			index = 1;
	}
	texture = env->textures[object.sprite];
	xstart = orender.screen_pos.x - object.size[index].x / 2.0 / (orender.dist / object.scale);
	ystart = orender.screen_pos.y - object.size[index].y / (orender.dist / object.scale);
	xend = orender.screen_pos.x + object.size[index].x / 2.0 / (orender.dist / object.scale);
	yend = (orender.screen_pos.y);
	x = xstart;
	while (x <= xend)
	{
		xalpha = (x - xstart) / (double)(xend - xstart);
		if (object.reversed[index])
			xalpha = 1.0 - xalpha;
		textx = (1.0 - xalpha) * object.start[index].x + xalpha * object.end[index].x;
		y = ystart;
		while (y <= yend)
		{
			yalpha = (y - ystart) / (double)(yend - ystart);
			texty = (1.0 - yalpha) * object.start[index].y + yalpha * object.end[index].y;
			if (x >= 0 && x < env->w && y >= 0 && y < env->h
					&& texture.str[textx + texty * texture.surface->w] != 0xFFC10099)
			{
				if (!env->options.lighting)
					env->sdl.texture_pixels[x + y * env->w] = texture.str[textx + texty * texture.surface->w];
				else
					env->sdl.texture_pixels[x + y * env->w] = apply_light(texture.str[textx + texty * texture.surface->w], render->light);
			}
			y++;
		}
		x++;
	}
}

void		draw_sprites(t_env *env, t_render *render)
{
	int	i;

	i = 0;
	while (i < env->nb_objects)
	{
		if (env->objects[i].sector == render->sector && !env->objects[i].drawn)
		{
			draw_object(env->objects[i], env, render);
			env->objects[i].drawn = 1;
		}
		i++;
	}
}
