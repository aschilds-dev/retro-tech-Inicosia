/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_hud.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:44:44 by sipatry           #+#    #+#             */
/*   Updated: 2020/01/31 18:38:09 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	editor_hud(t_env *env)
{
	if (!env->editor.in_game || (env->editor.in_game &&  env->editor.tab))
	{
		if (env->editor.in_game)
		{
			draw_rectangle(env,
			new_rectangle(0x00000000, 0xFF888888, 1, 5),
			new_point(0 , 0),
			new_point(400, 900));
		}
		draw_rectangle(env,
				new_rectangle(0x00000000, 0xFF888888, 1, 5),
				new_point(0 , 64),
				new_point(400, 270));
		draw_button(env, env->editor.add_enemy);
		draw_button(env, env->editor.add_object);
		draw_button(env, env->editor.texture_background);
		draw_button(env, env->editor.enemy_background);
		draw_button(env, env->editor.current_texture_selection);
		draw_button(env, env->editor.current_enemy_selection);
		draw_button(env, env->editor.change_mode);
		draw_button(env, env->editor.launch_game);
		draw_button(env, env->editor.save);
		draw_rectangle(env,
				new_rectangle(0x00000000, 0x2C3E50, 1, 5),
				new_point(0 , 450),
				new_point(400, 450));
		draw_editor_tabs(env);
		if (env->editor.draw_enemy_tab)
			enemy_tab(env, MAX_ENEMIES);
		if (env->editor.draw_sprite_tab)
			sprite_selection(env, MAX_OBJECTS);
		if (env->editor.draw_selection_tab || env->editor.draw_enemy_tab
		|| env->editor.draw_sprite_tab)
			env->editor.selection_tab = 1;
		else
			env->editor.selection_tab = 0;
	}
}
