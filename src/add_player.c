/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:58:46 by sipatry           #+#    #+#             */
/*   Updated: 2019/08/21 12:34:10 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	draw_grid_player(t_env *env)
{
	t_circle	circle;
	double		scale;

	circle.color = 0xFFFF0000;
	circle.line_color = 0xFFFF0000;
	scale = 0;
	if (env->editor.selected_player == 1)
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
				&& env->sdl.my < circle.center.y + env->editor.scale / 2
				&& env->editor.selected_object == -1 && env->editor.selected_vertex == -1)
		{
			circle.radius = env->editor.scale;
			if (env->inputs.left_click)
				env->editor.selected_player = 1;
		}
		else
			circle.radius = env->editor.scale / 2;
	}
	draw_circle(circle, env);
}

void	add_player(t_env *env)
{
	env->player.pos.x = (env->sdl.mx - env->editor.center.x) / env->editor.scale;
	env->player.pos.y = (env->sdl.my - env->editor.center.y) / env->editor.scale;
	env->player.pos.z = 0;
	env->player.angle = 0;
	env->player.angle_z = 0;
	env->player.eyesight = 6;
	env->player.speed = 0.5;
	env->player.angle_cos = cos(env->player.angle);
	env->player.angle_cos = sin(env->player.angle);
	env->player.perp_cos = cos(env->player.angle - M_PI / 2);
	env->player.perp_sin = sin(env->player.angle - M_PI / 2);
	env->player.sector = get_sector_no_z(env,
			env->player.pos);
	if (env->player.sector != -1)
		update_player_z(env);
}
