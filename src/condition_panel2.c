/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_panel2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 15:14:33 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/20 17:29:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "events_conditions.h"
#include "draw.h"

int		draw_condition_type_tab(t_env *env)
{
	SDL_Surface	*img;

	if (env->editor.event_panel.target_tab.anim_state == HOVER)
		img = env->ui_textures[ACTION_ICON_HOVER].surface;
	else if (env->editor.event_panel.target_tab.state == DOWN
		|| env->editor.event_panel.target_tab.anim_state == PRESSED)
		img = env->ui_textures[ACTION_ICON_DOWN].surface;
	else
		img = env->ui_textures[ACTION_ICON].surface;
	if (draw_button(env, env->editor.event_panel.target_tab, NULL))
		return (-1);
	apply_surface(img, new_point(env->editor.event_panel.pos.y
	+ env->editor.event_panel.top_size + (50 - img->h / 2),
	env->editor.event_panel.pos.x + (50 - img->h / 2)),
	new_point(img->w, img->h), env);
	return (0);
}

int		draw_condition_target_tab(t_env *env)
{
	SDL_Surface	*img;

	if (env->editor.event_panel.action_tab.anim_state == HOVER)
		img = env->ui_textures[TARGET_ICON_HOVER].surface;
	else if (env->editor.event_panel.action_tab.state == DOWN
		|| env->editor.event_panel.action_tab.anim_state == PRESSED)
		img = env->ui_textures[TARGET_ICON_DOWN].surface;
	else
		img = env->ui_textures[TARGET_ICON].surface;
	if (draw_button(env, env->editor.event_panel.action_tab, NULL))
		return (-1);
	apply_surface(img, new_point(env->editor.event_panel.pos.y
	+ env->editor.event_panel.top_size + 100 + (50 - img->h / 2),
	env->editor.event_panel.pos.x + (50 - img->h / 2)),
	new_point(img->w, img->h), env);
	return (0);
}

int		draw_condition_condition_panel2(t_env *env)
{
	if (env->editor.condition_panel.condition.target_type == INT)
		ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d",
		env->editor.condition_panel.int_value);
	else if (env->editor.condition_panel.condition.target_type == DOUBLE)
		ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
		get_decimal_len(env->editor.condition_panel.double_value),
		env->editor.condition_panel.double_value);
	else if (env->editor.condition_panel.condition.target_type == UINT32)
		ft_snprintf(env->snprintf, SNPRINTF_SIZE, "0x%X",
		env->editor.condition_panel.uint32_value);
	if (draw_button(env, env->editor.condition_panel.value, env->snprintf))
		return (-1);
	return (0);
}

int		draw_condition_condition_panel(t_env *env)
{
	if (draw_button(env, env->editor.condition_panel.equals, "="))
		return (-1);
	if (draw_button(env, env->editor.condition_panel.different, "!="))
		return (-1);
	if (draw_button(env, env->editor.condition_panel.less, "<"))
		return (-1);
	if (draw_button(env, env->editor.condition_panel.greater, ">"))
		return (-1);
	if (draw_button(env, env->editor.condition_panel.less_or_equals, "<="))
		return (-1);
	if (draw_button(env, env->editor.condition_panel.greater_or_equals, ">="))
		return (-1);
	if (draw_button(env, env->editor.condition_panel.event_ended, "end"))
		return (-1);
	if (draw_button(env, env->editor.condition_panel.event_ended_start,
		"end(start)"))
		return (-1);
	if (draw_condition_condition_panel2(env))
		return (-1);
	return (0);
}
