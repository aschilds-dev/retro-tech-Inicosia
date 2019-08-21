/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 10:24:50 by sipatry           #+#    #+#             */
/*   Updated: 2019/08/21 11:14:58 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"


void	draw_grid_objects(t_env *env)
{
	t_point		center;
	double		scale;
	int			i;
	Uint32		color;

	i = 0;
	if (env->editor.select_object != -1)
	{
		color = 0xFFFFFF00;
		scale = env->editor.scale;
		center.x = env->sdl.mx;
		center.y = env->sdl.my;
		draw_circle(new_circle(color, color, center, scale), env);
	}
	while (i < env->nb_objects)
	{
		center.x = env->objects[i].pos.x  * env->editor.scale + env->editor.center.x;
		center.y = env->objects[i].pos.y  * env->editor.scale + env->editor.center.y;
		if (env->sdl.mx > center.x - env->editor.scale / 2
				&& env->sdl.mx < center.x + env->editor.scale / 2
				&& env->sdl.my > center.y - env->editor.scale / 2
				&& env->sdl.my < center.y + env->editor.scale / 2
				&& env->editor.select_object == -1)
		{
			scale = env->editor.scale;
			color = 0xFF00FF00;
			if (env->inputs.left_click
					&& env->editor.select_player == -1
					&& env->editor.select_vertex == -1)
				env->editor.select_object = i;
		}
		else
		{
			color = 0xFFFFFF00;
			scale = env->editor.scale / 2;
		}
		if (env->editor.select_object != i)
		draw_circle(new_circle(color, color, center, scale), env);
		i++;
	}
}

int	add_object(t_env *env)
{
	t_object	object;

	env->editor.objects = 1;
	object.num = env->nb_objects;
	object.pos.x = round((env->sdl.mx - env->editor.center.x) / env->editor.scale);
	object.pos.y = round((env->sdl.my - env->editor.center.y) / env->editor.scale);
	object.pos.z = 6;
	object.sprite = 1;
	object.scale = 50;
	object.angle = 0;
	object.sector = get_sector_no_z(env, new_v3(object.pos.x, object.pos.y, object.pos.z));
	if (object.sector != -1)
		object.light = env->sectors[object.sector].light;
	else
		object.light = 1;
	if (!(env->objects = (t_object*)ft_realloc(env->objects, sizeof(t_object) * env->nb_objects, sizeof(t_object) * (env->nb_objects + 1))))
		return (ft_printf("Could not realloc objects\n"));
	env->objects[env->nb_objects] = object;
	return (0);
}
