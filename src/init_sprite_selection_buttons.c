/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite_selection_buttons.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 11:41:55 by sipatry           #+#    #+#             */
/*   Updated: 2020/04/30 12:09:07 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		init_array_sprite_buttons2(int i, t_env *env)
{
	t_button_param	*new;

	if (!(new = new_button_param(env, i)))
		return (-1);
	env->editor.current_sprite_selection =
	new_image_button(ON_RELEASE, &open_wall_sprite_selection, new, env);
	env->editor.current_sprite_selection.size_up = new_point(64, 64);
	env->editor.current_sprite_selection.size_down = new_point(64, 64);
	env->editor.current_sprite_selection.size_hover = new_point(64, 64);
	env->editor.current_sprite_selection.size_pressed = new_point(64, 64);
	env->editor.current_sprite_selection.pos = new_point(170, 470);
	env->editor.sprite_background = new_background_button(WHEN_DOWN, &nothing,
	&env->editor.texture_background, env);
	env->editor.sprite_background.pos = new_point(168, 468);
	return (0);
}

int		init_array_sprite_buttons(t_env *env)
{
	int				i;
	int				mod;
	t_button_param	*new;

	if (MAX_OBJECTS > 25)
		mod = 10;
	else
		mod = 5;
	i = 0;
	while (i < MAX_OBJECTS)
	{
		if (!(new = new_button_param(env, i)))
			return (-1);
		env->editor.sprite_selection[i] = new_image_button(ON_RELEASE,
		&save_sprite, new, env);
		env->editor.sprite_selection[i].size_up = new_point(64, 64);
		env->editor.sprite_selection[i].size_down = new_point(64, 64);
		env->editor.sprite_selection[i].size_hover = new_point(64, 64);
		env->editor.sprite_selection[i].size_pressed = new_point(64, 64);
		env->editor.sprite_selection[i].pos =
		new_point(180 + (66 * (i % mod)) + 8, 490 + 8 + (66 * (i / mod)));
		i++;
	}
	return (init_array_sprite_buttons2(i, env));
}
