/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:28:16 by lnicosia          #+#    #+#             */
/*   Updated: 2020/04/28 17:09:31 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_point	get_button_current_size(t_button b)
{
	t_point	size;

	size = new_point(0, 0);
	if (b.anim_state == HOVER)
		size = b.size_hover;
	else if (b.anim_state == PRESSED)
		size = b.size_pressed;
	else if (b.state == UP)
		size = b.size_up;
	else if (b.state == DOWN)
		size = b.size_down;
	return (size);
}

int		is_mouse_on_button(t_button b, t_point mouse)
{
	t_point	size;

	size = get_button_current_size(b);
	if (mouse.x < b.pos.x || mouse.x > b.pos.x + size.x
		|| mouse.y < b.pos.y || mouse.y > b.pos.y + size.y)
		return (0);
	return (1);
}

int		button_keyup(t_button *b, t_env *env)
{
	if (!is_mouse_on_button(*b, new_point(env->sdl.mx, env->sdl.my))
		|| b->anim_state != PRESSED)
	{
		b->anim_state = REST;
		return (0);
	}
	b->anim_state = REST;
	if (!b->release_action)
		b->state = b->state == UP ? DOWN : UP;
	if (b->state == DOWN)
	{
		if (b->down_action && b->down_action(b->param))
			return (-1);
	}
	if (b->state == UP)
	{
		if (b->release_action && b->release_action(b->release_param))
			return (-1);
	}
	return (0);
}

int		button_keys(t_button *b, t_env *env)
{
	if (!is_mouse_on_button(*b, new_point(env->sdl.mx, env->sdl.my)))
	{
		if (b->anim_state == HOVER)
			b->anim_state = REST;
		return (0);
	}
	if (env->inputs.left_click)
	{
		b->anim_state = PRESSED;
		if (b->press_action && b->press_action(b->param))
			return (-1);
	}
	else if (b->state == UP)
		b->anim_state = HOVER;
	return (0);
}
