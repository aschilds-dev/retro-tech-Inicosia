/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_action_panel_bottom.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 16:07:39 by lnicosia          #+#    #+#             */
/*   Updated: 2020/04/29 16:07:40 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "draw.h"

int		draw_number_of_uses(t_env *env)
{
	t_point			text_size;

	if (draw_button(env, env->editor.event_panel.action_panel.max_uses,
	env->snprintf))
		return (-1);
	if (TTF_SizeText(env->sdl.fonts.lato20, "Number of uses", &text_size.x,
	&text_size.y))
		return (0);
	if (print_text(new_point(env->editor.event_panel.action_panel.max_uses.pos.y
	- text_size.y - 5, env->editor.event_panel.action_panel.max_uses.pos.x +
	env->editor.event_panel.action_panel.max_uses.size_up.x / 2 -
	text_size.x / 2), new_printable_text("Number of uses",
	env->sdl.fonts.lato20, 0x333333FF, 0), env))
		return (0);
	return (0);
}

int		draw_action_panel_bottom(t_env *env)
{
	t_point			text_size;

	if (TTF_SizeText(env->sdl.fonts.lato20, "Delay (ms)", &text_size.x,
	&text_size.y))
		return (0);
	if (print_text(new_point(env->editor.event_panel.action_panel.delay.pos.y
	- text_size.y - 5, env->editor.event_panel.action_panel.delay.pos.x +
	env->editor.event_panel.action_panel.delay.size_up.x / 2 - text_size.x / 2),
	new_printable_text("Delay (ms)", env->sdl.fonts.lato20, 0x333333FF, 0),
	env))
		return (0);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d",
	env->editor.event_panel.action_panel.delay_value);
	if (draw_button(env, env->editor.event_panel.action_panel.delay,
		env->snprintf))
		return (-1);
	if (env->editor.event_panel.event.max_uses)
		ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d",
		env->editor.event_panel.event.max_uses);
	else
		ft_snprintf(env->snprintf, SNPRINTF_SIZE, "Inf.");
	return (draw_number_of_uses(env));
}
