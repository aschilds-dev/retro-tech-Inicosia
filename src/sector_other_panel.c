/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_other_panel.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 13:09:54 by lnicosia          #+#    #+#             */
/*   Updated: 2020/03/03 13:49:24 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "events_parser.h"

int		set_sector_other_panel_buttons_state(t_target_panel *panel, int index)
{
	int		down;

	down = 0;
	if (index == SECTOR_BRIGHTNESS)
		down = 0;
	else if (index == SECTOR_LIGHT_COLOR)
		down = 1;
	else if (index == SECTOR_INTENSITY)
		down = 2;
	else if (index == SECTOR_GRAVITY)
		down = 3;
	panel->targets[down].state = DOWN;
	panel->selected_button = down;
	return (0);
}

int		select_sector_other(void *param)
{
	t_env			*env;
	t_target_panel	*panel;
	int				i;

	env = (t_env*)param;
	if (env->editor.creating_condition)
		panel = &env->editor.condition_panel.target_panel;
	else
		panel = &env->editor.event_panel.target_panel;
	panel->sector_other_type = 1;
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
			set_sector_other_panel_buttons_state(panel,
			env->editor.condition_panel.condition.target_index);
	}
	else
	{
		if (env->editor.event_panel.event.target)
			set_sector_other_panel_buttons_state(panel,
			env->editor.event_panel.event.target_index);
	}
	return (0);
}

int		draw_sector_other_panel(t_env *env, t_target_panel *panel)
{
	draw_button(env, panel->targets[0], "Light brightness");
	draw_button(env, panel->targets[1], "Light color");
	draw_button(env, panel->targets[2], "Color intensity");
	draw_button(env, panel->targets[3], "Gravity");
	return (0);
}
