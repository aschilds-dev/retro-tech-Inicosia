/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 16:07:41 by lnicosia          #+#    #+#             */
/*   Updated: 2019/11/11 13:30:16 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		editor_render(t_env *env)
{
	if (env->inputs.enter)
	{
		env->editor.in_game = 0;
		env->selected_floor = -1;
		env->selected_ceiling = -1;
		env->selected_object = -1;
		env->selected_enemy = -1;
		env->selected_wall1 = -1;
		env->selected_wall2 = -1;
		env->inputs.enter = 0;
		SDL_SetRelativeMouseMode(0);
		return (0);
	}
	if (env->options.animations)
		update_sprites_state(env);
	reset_clipped(env);
	if (!env->input_box.state)
		editor_3d_keys(env);
	animations(env);
	if (draw_walls(&env->player.camera, env))
		return (crash("Failed to draw walls\n", env));
	draw_objects(env->player.camera, env);
	draw_enemies(env->player.camera, env);
	draw_crosshair(env);
	if (env->options.show_fps)
		fps(env);
	game_time(env);
	draw_hud(env);
	minimap(env);
	interactions(env);
	if (!env->input_box.state)
		view(env);
	env->editor.select = 0;
	return (0);
}
