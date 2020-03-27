/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_panel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 11:12:43 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/18 22:02:58 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "events_conditions.h"

void	draw_condition_target_panel(t_env *env)
{
	if (env->editor.condition_panel.condition.type < EVENT_ENDED)
		draw_condition_targets_panel(env);
	else if (env->editor.condition_panel.condition.type == EVENT_ENDED
		|| env->editor.condition_panel.condition.type == EVENT_ENDED_START)
		draw_condition_event_panel(env);
}

void	draw_condition_panel_tab_content(t_env *env)
{
	if (env->editor.event_panel.target_tab.state == DOWN)
		draw_condition_condition_panel(env);
	else if (env->editor.event_panel.action_tab.state == DOWN)
		draw_condition_target_panel(env);
}

int		draw_condition_panel2(t_env *env)
{
	apply_surface(env->ui_textures[CONDITION_ICON].surface,
	new_point(env->editor.event_panel.pos.y +
	(env->editor.event_panel.top_size / 2 -
	env->ui_textures[CONDITION_ICON].surface->h / 2),
	env->editor.event_panel.pos.x +
	(env->editor.event_panel.top_size / 2 -
	env->ui_textures[CONDITION_ICON].surface->h / 2)),
	new_point(env->ui_textures[CONDITION_ICON].surface->w,
	env->ui_textures[CONDITION_ICON].surface->h), env);
	draw_button(env, env->editor.event_panel.ok, "OK");
	draw_button(env, env->editor.event_panel.cancel, "X");
	draw_condition_type_tab(env);
	draw_condition_target_tab(env);
	draw_condition_panel_tab_content(env);
	return (0);
}

int		draw_condition_panel(t_env *env)
{
	t_point		text_size;

	draw_rectangle(env, new_rectangle(0xc8ccd0, 0xc8ccd0, 1, 0),
	new_point(env->editor.event_panel.pos.x, env->editor.event_panel.pos.y),
	new_point(env->editor.event_panel.size.x,
	env->editor.event_panel.size.y - 100));
	draw_rectangle(env, new_rectangle(0xFFf1f2f3, 0xFFf1f2f3, 1, 0),
	env->editor.event_panel.pos, new_point(env->editor.event_panel.size.x - 200,
	env->editor.event_panel.top_size - 2));
	draw_rectangle(env, new_rectangle(0xe3e4e8, 0xe3e4e8 + 100, 1, 0),
	new_point(env->editor.event_panel.pos.x + 100,
	env->editor.event_panel.pos.y + env->editor.event_panel.top_size),
	new_point(env->editor.event_panel.size.x - 100,
	env->editor.event_panel.size.y - env->editor.event_panel.top_size - 100));
	TTF_SizeText(env->sdl.fonts.lato_black30, "Condition", &text_size.x,
	&text_size.y);
	print_text(new_point(env->editor.event_panel.pos.y + 20,
	env->editor.event_panel.pos.x + 75), new_printable_text("Condition",
	env->sdl.fonts.lato_black30, 0x333333FF, 0), env);
	return (draw_condition_panel2(env));
}
