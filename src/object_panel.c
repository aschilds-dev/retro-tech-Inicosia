/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_panel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:09:54 by lnicosia          #+#    #+#             */
/*   Updated: 2020/03/11 13:25:42 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "events_parser.h"
#include "draw.h"

int		set_object_panel_buttons_state(t_target_panel *panel, int index)
{
	int		down;

	down = -1;
	if (index == OBJECT_SPRITE)
		down = 0;
	else if (index == OBJECT_X)
		down = 1;
	else if (index == OBJECT_Y)
		down = 2;
	else if (index == OBJECT_Z)
		down = 3;
	else if (index == OBJECT_SCALE)
		down = 4;
	else if (index == OBJECT_DAMAGE)
		down = 5;
	else if (index == OBJECT_HP)
		down = 6;
	if (down != -1)
	{
		panel->targets[down].state = DOWN;
		panel->selected_button = down;
	}
	return (0);
}

void	select_object2(t_target_panel *panel, t_env *env)
{
	if (env->editor.event_panel.event.target)
		set_object_panel_buttons_state(panel,
		env->editor.event_panel.event.target_index);
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
	i = -1;
	while (++i < 8)
	{
		panel->targets[i].state = UP;
		panel->targets[i].anim_state = REST;
	}
	if (env->editor.creating_condition)
	{
		if (env->editor.condition_panel.condition.target)
			set_object_panel_buttons_state(panel,
			env->editor.condition_panel.condition.target_index);
	}
	else
		select_object2(panel, env);
	return (0);
}

int		draw_object_panel(t_env *env, t_target_panel *panel)
{
	if (draw_button(env, panel->targets[0], "Sprite"))
		return (-1);
	if (draw_button(env, panel->targets[1], "X"))
		return (-1);
	if (draw_button(env, panel->targets[2], "Y"))
		return (-1);
	if (draw_button(env, panel->targets[3], "Z"))
		return (-1);
	if (draw_button(env, panel->targets[4], "Scale"))
		return (-1);
	if (draw_button(env, panel->targets[5], "Damage"))
		return (-1);
	if (draw_button(env, panel->targets[6], "Health"))
		return (-1);
	return (0);
}
