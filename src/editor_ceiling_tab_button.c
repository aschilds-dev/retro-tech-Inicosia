/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_ceiling_tab_button.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:32:50 by sipatry           #+#    #+#             */
/*   Updated: 2020/01/17 15:23:43 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	init_ceilling_sprite_buttons(t_env *env)
{
	(void)env;
}

void	init_ceilling_sector_buttons(t_env *env)
{
	env->editor.hud.s_ceilling.brightness = new_hud_button(WHEN_DOWN, &change_var,
	&env->editor.hud.s_ceilling.t_brightness, env);
	env->editor.hud.s_ceilling.brightness.pos = new_point(250, 520);
	env->editor.hud.s_ceilling.t_brightness.pos = new_point(250, 520);
	env->editor.hud.s_ceilling.color = new_hud_button(WHEN_DOWN, &change_var,
	&env->editor.hud.s_ceilling.t_color, env);
	env->editor.hud.s_ceilling.color.pos = new_point(250, 560);
	env->editor.hud.s_ceilling.t_color.pos = new_point(250, 560);
	env->editor.hud.s_ceilling.intensity = new_hud_button(WHEN_DOWN, &change_var,
	&env->editor.hud.s_ceilling.t_intensity, env);
	env->editor.hud.s_ceilling.intensity.pos = new_point(250, 600);
	env->editor.hud.s_ceilling.t_intensity.pos = new_point(250, 600);
	env->editor.hud.s_ceilling.gravity = new_hud_button(WHEN_DOWN, &change_var,
	&env->editor.hud.s_ceilling.t_gravity, env);
	env->editor.hud.s_ceilling.gravity.pos = new_point(250, 640);
	env->editor.hud.s_ceilling.t_gravity.pos = new_point(250, 640);
	//env->editor.hud.s_ceilling.gravity.str = ;
}

void	init_ceilling_general_buttons(t_env *env)
{
	env->editor.hud.g_ceilling.height = new_hud_button(WHEN_DOWN, &change_var,
	&env->editor.hud.g_ceilling.t_height, env);
	env->editor.hud.g_ceilling.height.pos = new_point(250, 520);
	env->editor.hud.g_ceilling.t_height.pos = new_point(250, 520);
	env->editor.hud.g_ceilling.slope = new_hud_button(WHEN_DOWN, &change_var,
	&env->editor.hud.g_ceilling.t_slope, env);
	env->editor.hud.g_ceilling.slope.pos = new_point(250, 560);
	env->editor.hud.g_ceilling.t_slope.pos = new_point(250, 560);
	env->editor.hud.g_ceilling.texture = new_hud_button(WHEN_DOWN, &change_var,
	&env->editor.hud.g_ceilling.t_texture, env);
	env->editor.hud.g_ceilling.texture.pos = new_point(250, 600);
	env->editor.hud.g_ceilling.t_texture.pos = new_point(250, 600);
	env->editor.hud.g_ceilling.texture_scale_x = new_hud_button(WHEN_DOWN, &change_var,
	&env->editor.hud.g_ceilling.t_texture_scale_x, env);
	env->editor.hud.g_ceilling.texture_scale_x.pos = new_point(250, 640);
	env->editor.hud.g_ceilling.t_texture_scale_x.pos = new_point(250, 640);
	env->editor.hud.g_ceilling.texture_scale_y = new_hud_button(WHEN_DOWN, &change_var,
	&env->editor.hud.g_ceilling.t_texture_scale_y, env);
	env->editor.hud.g_ceilling.texture_scale_y.pos = new_point(250, 680);
	env->editor.hud.g_ceilling.t_texture_scale_y.pos = new_point(250, 680);
	env->editor.hud.g_ceilling.texture_align_x = new_hud_button(WHEN_DOWN, &change_var,
	&env->editor.hud.g_ceilling.t_texture_align_x, env);
	env->editor.hud.g_ceilling.texture_align_x.pos = new_point(250, 720);
	env->editor.hud.g_ceilling.t_texture_align_x.pos = new_point(250, 720);
	env->editor.hud.g_ceilling.texture_align_y = new_hud_button(WHEN_DOWN, &change_var,
	&env->editor.hud.g_ceilling.t_texture_align_y, env);
	env->editor.hud.g_ceilling.texture_align_y.pos = new_point(250, 760);
	env->editor.hud.g_ceilling.t_texture_align_y.pos = new_point(250, 760);
}