/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid_vertices.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 11:52:27 by lnicosia          #+#    #+#             */
/*   Updated: 2019/07/25 15:47:00 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	draw_grid_vertices(t_env *env)
{
	t_list		*tmp;
	t_vertex	*vertex;
	t_point		center;
	double		scale;
	Uint32		color;

	tmp = env->edit.vertices;
	while (tmp)
	{
		vertex = (t_vertex*)tmp->content;
		center = new_point(env->edit.center.x + vertex->x * env->edit.scale,
				env->edit.center.y + vertex->y * env->edit.scale);
		if (env->sdl.mx > center.x - env->edit.scale / 5.0
				&& env->sdl.mx < center.x + env->edit.scale / 5.0
				&& env->sdl.my > center.y - env->edit.scale / 5.0
				&& env->sdl.my < center.y + env->edit.scale / 5.0)
		{
			scale = env->edit.scale / 3.5;
			color = 0xFF00FF00;
		}
		else
		{
			scale = env->edit.scale / 5.0;
			color = 0xFFFF0000;
		}
		if (center.x - scale >= 0 && center.x + scale < env->w
				&& center.y - scale >= 0 && center.y + scale < env->h)
			draw_circle(new_circle(color,
						color,
						center,
						scale), env);
		tmp = tmp->next;
	}
}
