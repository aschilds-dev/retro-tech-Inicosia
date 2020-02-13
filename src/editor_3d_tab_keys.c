/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_3d_tab_keys.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:14:45 by sipatry           #+#    #+#             */
/*   Updated: 2020/02/13 15:50:51 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		general_tab_keys(t_env *env)
{
	if (env->editor.events_tab.state == DOWN)
	{
		if (button_keys(&env->editor.next_events, env)
		|| button_keys(&env->editor.previous_events, env))
			return (-1);
		if (are_event_selection_buttons_visible(env))
		{
			if (button_keys(&env->editor.next_event, env)
			|| button_keys(&env->editor.previous_event, env))
				return (-1);
		}
		if (are_launch_condition_selection_buttons_visible(env))
		{
			if (button_keys(&env->editor.next_launch_condition, env)
			|| button_keys(&env->editor.previous_launch_condition, env))
				return (-1);
		}
		if (are_exec_condition_selection_buttons_visible(env))
		{
			if (button_keys(&env->editor.next_exec_condition, env)
			|| button_keys(&env->editor.previous_exec_condition, env))
				return (-1);
		}
	}
	return (0);
}

int		general_keys(t_env *env)
{
	if (button_keys(&env->editor.save, env))
		return (-1);
	if (button_keys(&env->editor.sprite_tab, env))
		return (-1);
	else if (button_keys(&env->editor.general_tab, env))
		return (-1);
	else if (button_keys(&env->editor.sector_tab, env))
		return (-1);
	if (button_keys(&env->editor.change_mode, env))
		return (-1);
	if (button_keys(&env->editor.launch_game, env))
		return (-1);
	if (button_keys(&env->editor.texture_background, env))
		return (-1);
	if (button_keys(&env->editor.events_tab, env))
		return (-1);
	return (0);
}

int		selection_button_keys(t_env *env)
{
	if (env->selected_ceiling != -1 && ceiling_buttons(env))
		return (-1);
	if (env->selected_floor != -1 && floor_buttons(env))
		return (-1);
	if (env->editor.selected_wall != -1 && wall_buttons(env))
		return (-1);
	if (env->selected_enemy != -1 && enemy_buttons(env))
		return (-1);
	if (env->selected_object != -1 && object_buttons(env))
		return (-1);
	if ((env->selected_floor_sprite != -1 || env->selected_ceiling_sprite != -1
	|| env->selected_wall_sprite_sprite != -1) && env->editor.sprite_tab.state == DOWN)
	{
		if (button_keys(&env->editor.next_sprite, env)
		|| button_keys(&env->editor.previous_sprite, env)
		|| button_keys(&env->editor.current_sprite_selection, env))
			return (-1);
	}
	if (env->selected_floor_sprite != -1 && floor_sprite_buttons(env))
		return (-1);
	if (env->selected_ceiling_sprite != -1 && ceiling_sprite_buttons(env))
		return (-1);
	if (env->selected_wall_sprite_sprite != -1 && wall_sprite_buttons(env))
		return (-1);
	return (0);
}

int		editor_3d_tab_keys(t_env *env)
{
	if (general_keys(env))
		return (-1);
	if (general_tab_keys(env))
		return (-1);
	if (selection_button_keys(env))
		return (-1);
	if (selection_tab_button_keys(env))
		return (-1);
	if (env->editor.creating_event)
	{
		if (event_panel_keys(env))
			return (-1);
	}
	return (0);
}