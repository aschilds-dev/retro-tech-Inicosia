/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:07:41 by lnicosia          #+#    #+#             */
/*   Updated: 2020/01/31 11:57:02 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int			editor_keys(t_env *env)
{
	double time;
	int	i;

	i = 0;
	time = SDL_GetTicks();
	if (env->inputs.backspace && !env->confirmation_box.state)
	{
		del_last_vertex(env);
		env->inputs.backspace = 0;
	}
	if (env->inputs.del)
		if (delete_action(env))
			return (-1);
	player_selection(env);
	enemy_selection(env);
	objects_selection(env);
	vertices_selection(env);
	if (env->confirmation_box.state)
		confirmation_box_keys(&env->confirmation_box, env);
	if (env->inputs.right_click)
	{
		env->editor.center.x += env->sdl.mouse_x;
		env->editor.center.y += env->sdl.mouse_y;
	}

	/*
	**	Moving the map with arrows
	*/
	
	if (env->inputs.left && !env->editor.tab && !env->inputs.ctrl)
		env->editor.center.x -= 3;
	if (env->inputs.right && !env->editor.tab && !env->inputs.ctrl)
		env->editor.center.x += 3;
	if (env->inputs.forward && !env->editor.tab && !env->inputs.ctrl)
		env->editor.center.y -= 3;
	if (env->inputs.backward && !env->editor.tab && !env->inputs.ctrl)
		env->editor.center.y += 3;
	if (env->inputs.s && env->inputs.ctrl && !valid_map(env))
	{
		new_input_box(&env->input_box, new_point(env->h_w, env->h_h),
		STRING, &env->save_file);
		env->input_box.accept_inputs = 0;
		env->inputs.s = 0;
		env->inputs.ctrl = 0;
	}

	/*
	**	control of the selection the stats in 2D mode editor iwh include:
	**	floor | ceiling | brightness control on arrows or keybord usual binding (w-a-s-d)
	**	control of the sector status with +/-
	*/

	button_keys(&env->editor.add_enemy, env);
	button_keys(&env->editor.add_object, env);
	button_keys(&env->editor.save, env);
	button_keys(&env->editor.general_tab, env);
	button_keys(&env->editor.sprite_tab, env);
	button_keys(&env->editor.sector_tab, env);
	button_keys(&env->editor.change_mode, env);
	button_keys(&env->editor.launch_game, env);
	button_keys(&env->editor.texture_background, env);
	button_keys(&env->editor.enemy_background, env);
	if (env->editor.selected_sector != -1)
		sector_buttons(env);
	if (env->editor.selected_player != -1)
		player_buttons(env);
	if (env->selected_enemy != -1)
		enemy_buttons(env);
	if (is_events_tab_visible(env))
	{
		button_keys(&env->editor.events_tab, env);
		if (env->editor.events_tab.state == DOWN)
		{
			button_keys(&env->editor.next_events, env);
			button_keys(&env->editor.previous_events, env);
		}
		if (are_event_selection_buttons_visible(env))
		{
			button_keys(&env->editor.next_event, env);
			button_keys(&env->editor.previous_event, env);
		}
		if (are_launch_condition_selection_buttons_visible(env))
		{
			button_keys(&env->editor.next_launch_condition, env);
			button_keys(&env->editor.previous_launch_condition, env);
		}
		if (are_exec_condition_selection_buttons_visible(env))
		{
			button_keys(&env->editor.next_exec_condition, env);
			button_keys(&env->editor.previous_exec_condition, env);
		}
	}
	if (env->editor.draw_selection_tab)
	{
		while (i < MAX_WALL_TEXTURE)
		{
			button_keys(&env->editor.textures[i], env);
			i++;
		}
	}
	if (env->editor.draw_enemy_tab)
	{
		while (i < MAX_ENEMIES)
		{
			button_keys(&env->editor.enemy_tab[i], env);
			i++;
		}
	}
	if ((env->inputs.plus || env->inputs.minus) && !env->editor.in_game && env->editor.selected_sector != -1)
	{
		if (!env->time.tick4)
			env->time.tick4 = SDL_GetTicks();
		time = SDL_GetTicks();
	}
	return (0);
}
