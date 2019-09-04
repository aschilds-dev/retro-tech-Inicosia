/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:40:49 by lnicosia          #+#    #+#             */
/*   Updated: 2019/09/04 10:47:41 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	draw_grid_player(t_env *env)
{
	t_circle	circle;
	double		scale;
	t_v3		v[3];

	circle.color = 0xFFFF0000;
	circle.line_color = 0xFFFF0000;
	scale = 0;
	if (env->editor.dragged_player == 1)
	{
		circle.center.x = env->sdl.mx;
		circle.center.y = env->sdl.my;
		circle.radius = env->editor.scale;
	}
	else
	{
		circle.center.x = (env->player.pos.x * env->editor.scale) + env->editor.center.x;
		circle.center.y = (env->player.pos.y * env->editor.scale) + env->editor.center.y;
		if (env->sdl.mx > circle.center.x - env->editor.scale / 2
				&& env->sdl.mx < circle.center.x + env->editor.scale / 2
				&& env->sdl.my > circle.center.y - env->editor.scale / 2
				&& env->sdl.my < circle.center.y + env->editor.scale / 2)
		{
			circle.radius = env->editor.scale;
			if (env->inputs.left_click
					&& !env->confirmation_box.state
					&& env->editor.start_vertex == -1
					&& env->editor.dragged_player == -1
					&& env->editor.dragged_object == -1
					&& env->editor.dragged_vertex == -1)
			{
				env->editor.dragged_player = 1;
				env->editor.selected_player = 1;
				env->editor.selected_object = -1;
				env->editor.selected_vertex = -1;
				env->editor.selected_sector = -1;
			}
		}
		else
			circle.radius = env->editor.scale / 2;
	}
	if (env->editor.selected_player == 1)
		circle.line_color = 0xFF00FF00;
	draw_circle(circle, env);
	v[0] = new_v3(circle.center.x + env->player.perp_cos * circle.radius / 2,
			circle.center.y + env->player.perp_sin * circle.radius / 2,
			0);
	v[2] = new_v3(circle.center.x - env->player.perp_cos * circle.radius / 2,
			circle.center.y - env->player.perp_sin * circle.radius / 2,
			0);
	v[1] = new_v3(circle.center.x + env->player.angle_cos * circle.radius * 2,
			circle.center.y + env->player.angle_sin * circle.radius * 2,
			0);
	fill_triangle(v, 0xFFFF0000, env);
	/*if (env->editor.selected_player == 1)
	{
		circle.radius *= 0.75;
		circle.color = 0xFF00FF00;
		draw_circle(circle, env);
	}*/
}
