/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_conditions_tab2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 09:15:55 by marvin            #+#    #+#             */
/*   Updated: 2020/05/15 22:44:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "events_conditions.h"
#include "draw.h"

int	print_event_link_condition(t_condition *condition, t_event_panel *panel,
t_env *env)
{
	t_point			text_size;

	env->print_link_target_data[condition->target_trigger.type](env,
	condition, new_point(panel->pos.x + 100,
	panel->pos.y + panel->top_size + panel->content_panel_size.y / 4), 20);
	if (TTF_SizeText(env->sdl.fonts.lato_bold20, env->snprintf, &text_size.x,
		&text_size.y))
		return (-1);
	if (print_text(new_point(panel->pos.y + panel->top_size + 17 +
		panel->content_panel_size.y / 6, panel->pos.x + 100 +
		panel->content_panel_size.x / 2 - text_size.x / 2),
		new_printable_text(env->snprintf,
		env->sdl.fonts.lato_bold20, 0x333333FF, 0), env))
		return (-1);
	return (0);
}

int	draw_condition(t_env *env, t_condition *condition)
{
	t_point			text_size;
	t_event_panel	*panel;

	panel = &env->editor.event_panel;
	if (condition->type < EVENT_ENDED)
	{
		env->print_condition_target_data[condition->target_index](env,
		condition, new_point(panel->pos.x + 100,
		panel->pos.y + panel->top_size + panel->content_panel_size.y / 4), 20);
		if (TTF_SizeText(env->sdl.fonts.lato_bold20,
			env->snprintf, &text_size.x, &text_size.y))
			return (-1);
		if (print_text(new_point(panel->pos.y + panel->top_size + 17 +
			panel->content_panel_size.y / 6, panel->pos.x + 100 +
			panel->content_panel_size.x / 2 - text_size.x / 2),
			new_printable_text(env->snprintf,
			env->sdl.fonts.lato_bold20, 0x333333FF, 0), env))
			return (-1);
	}
	else
	{
		if (print_event_link_condition(condition, panel, env))
			return (-1);
	}
	return (0);
}
