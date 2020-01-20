/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_button_keyup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 13:46:07 by sipatry           #+#    #+#             */
/*   Updated: 2020/01/17 14:46:40 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	wall_buttons_up(t_env *env)
{
	if (env->editor.sector_tab.state == DOWN)
	{
		button_keyup(&env->editor.hud.s_wall.brightness, env);
		button_keyup(&env->editor.hud.s_wall.color, env);
		button_keyup(&env->editor.hud.s_wall.intensity, env);
	}
	if (env->editor.general_tab.state == DOWN)
	{
		button_keyup(&env->editor.hud.g_wall.texture, env);
		button_keyup(&env->editor.hud.g_wall.texture_scale_x, env);
		button_keyup(&env->editor.hud.g_wall.texture_scale_y, env);
		button_keyup(&env->editor.hud.g_wall.texture_align_x, env);
		button_keyup(&env->editor.hud.g_wall.texture_align_y, env);
	}
}

void	floor_buttons_up(t_env *env)
{
	button_keyup(&env->editor.hud.s_floor.brightness, env);
	button_keyup(&env->editor.hud.s_floor.color, env);
	button_keyup(&env->editor.hud.s_floor.intensity, env);
	button_keyup(&env->editor.hud.g_floor.height, env);
	button_keyup(&env->editor.hud.g_floor.slope, env);
	button_keyup(&env->editor.hud.g_floor.texture, env);
	button_keyup(&env->editor.hud.g_floor.texture_scale_x, env);
	button_keyup(&env->editor.hud.g_floor.texture_scale_y, env);
	button_keyup(&env->editor.hud.g_floor.texture_align_x, env);
	button_keyup(&env->editor.hud.g_floor.texture_align_y, env);
}

void	ceiling_buttons_up(t_env *env)
{
	button_keyup(&env->editor.hud.s_ceilling.brightness, env);
	button_keyup(&env->editor.hud.s_ceilling.color, env);
	button_keyup(&env->editor.hud.s_ceilling.intensity, env);
	button_keyup(&env->editor.hud.g_ceilling.height, env);
	button_keyup(&env->editor.hud.g_ceilling.slope, env);
	button_keyup(&env->editor.hud.g_ceilling.texture, env);
	button_keyup(&env->editor.hud.g_ceilling.texture_scale_x, env);
	button_keyup(&env->editor.hud.g_ceilling.texture_scale_y, env);
	button_keyup(&env->editor.hud.g_ceilling.texture_align_x, env);
	button_keyup(&env->editor.hud.g_ceilling.texture_align_y, env);
}