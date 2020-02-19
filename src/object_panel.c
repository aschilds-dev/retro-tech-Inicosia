/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:09:54 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/17 16:22:31 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "events_parser.h"

int		set_object_panel_buttons_state(t_target_panel *panel, int index)
{
	if (index == OBJECT_SPRITE)
		panel->targets[0].state = DOWN;
	else if (index == OBJECT_X)
		panel->targets[1].state = DOWN;
	else if (index == OBJECT_Y)
		panel->targets[2].state = DOWN;
	else if (index == OBJECT_Z)
		panel->targets[3].state = DOWN;
	else if (index == OBJECT_SCALE)
		panel->targets[4].state = DOWN;
	else if (index == OBJECT_DAMAGE)
		panel->targets[5].state = DOWN;
	else if (index == OBJECT_HP)
		panel->targets[6].state = DOWN;
	return (0);
}

int		select_object(void *param)
{
	t_env			*env;
	t_target_panel	*panel;
	int				i;

	env = (t_env*)param;
	if (env->editor.creating_condition)
		panel = &env->editor.condition_panel.target_panel;
	else
		panel = &env->editor.event_panel.target_panel;
	panel->object_type = 1;
	i = 0;
	while (i < 8)
	{
		panel->targets[i].state = UP;
		panel->targets[i].anim_state = REST;
		i++;
	}
	if (env->editor.creating_condition)
	{
		if (env->editor.condition_panel.condition.target)
			set_object_panel_buttons_state(panel,
			env->editor.condition_panel.condition.target_index);
	}
	else
	{
		if (env->editor.event_panel.event.target)
			set_object_panel_buttons_state(panel,
			env->editor.event_panel.event.target_index);
	}
	return (0);
}

int		draw_object_panel(t_env *env, t_target_panel *panel)
{
	draw_button(env, panel->targets[0], "Sprite");
	draw_button(env, panel->targets[1], "X");
	draw_button(env, panel->targets[2], "Y");
	draw_button(env, panel->targets[3], "Z");
	draw_button(env, panel->targets[4], "Scale");
	draw_button(env, panel->targets[5], "Damage");
	draw_button(env, panel->targets[6], "Health");
	return (0);
}
