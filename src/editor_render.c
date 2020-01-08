/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_render.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 16:07:41 by lnicosia          #+#    #+#             */
/*   Updated: 2020/01/08 11:48:30 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		editor_render(t_env *env)
{
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
	minimap(env);
	if (!env->input_box.state)
		view(env);
	env->editor.select = 0;
	return (0);
}
