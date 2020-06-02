/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_skybox_selection_buttons.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 09:40:31 by sipatry           #+#    #+#             */
/*   Updated: 2020/04/30 13:35:18 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		init_skybox_big(int i, t_env *env)
{
	t_button_param	*new;

	if (!(new = new_button_param(env, (-i - 1))))
		return (-1);
	env->editor.skyboxes[i] = new_image_button(ON_RELEASE,
	&save_texture, new, env);
	env->editor.skyboxes[i].img_up = env->mini_skyboxes[i].surface;
	env->editor.skyboxes[i].img_hover = env->mini_skyboxes[i].surface;
	env->editor.skyboxes[i].img_pressed = env->mini_skyboxes[i].surface;
	env->editor.skyboxes[i].img_down = env->mini_skyboxes[i].surface;
	env->editor.skyboxes[i].size_up = new_point(128, 128);
	env->editor.skyboxes[i].size_hover = new_point(128, 128);
	env->editor.skyboxes[i].size_pressed = new_point(128, 128);
	env->editor.skyboxes[i].size_down = new_point(128, 128);
	return (0);
}

int		init_skybox_small(int i, int mod, int mod_e, t_env *env)
{
	t_button_param	*new;

	if (!(new = new_button_param(env, (-i - 1))))
		return (-1);
	env->editor.skyboxes[i] = new_image_button(ON_RELEASE,
	&save_texture, new, env);
	env->editor.skyboxes[i].img_up = env->mini_skyboxes[i].surface;
	env->editor.skyboxes[i].img_hover = env->mini_skyboxes[i].surface;
	env->editor.skyboxes[i].img_pressed = env->mini_skyboxes[i].surface;
	env->editor.skyboxes[i].img_down = env->mini_skyboxes[i].surface;
	env->editor.skyboxes[i].size_up = new_point(64, 64);
	env->editor.skyboxes[i].size_hover = new_point(64, 64);
	env->editor.skyboxes[i].size_pressed = new_point(64, 64);
	env->editor.skyboxes[i].size_down = new_point(64, 64);
	env->editor.skyboxes[i].pos =
	new_point(300 + (66 * (i % mod)) + 7,
	(233 + 20 + (((MAX_WALL_TEXTURE / mod_e)) * 64))
	+ 64 * (i / mod) + 5);
	return (0);
}

int		init_current_skybox_button(int i, int mod, int mod_e, t_env *env)
{
	if (i < MAX_SKYBOX)
	{
		if (init_skybox_small(i, mod, mod_e, env))
			return (-1);
	}
	else if (init_skybox_big(i, env))
		return (-1);
	return (0);
}

int		init_skybox_selection_buttons(t_env *env)
{
	int	i;
	int	mod;
	int	mod_e;

	if (MAX_WALL_TEXTURE > 50)
		mod_e = 15;
	else if (MAX_WALL_TEXTURE > 25)
		mod_e = 10;
	else
		mod_e = 5;
	if (MAX_SKYBOX > 20)
		mod = 10;
	else
		mod = 5;
	i = -1;
	while (++i < MAX_SKYBOX + MAX_SKYBOX)
	{
		if (init_current_skybox_button(i, mod, mod_e, env))
			return (-1);
	}
	return (0);
}
