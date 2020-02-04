/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_floor_tab_button.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:32:50 by sipatry           #+#    #+#             */
/*   Updated: 2020/02/04 09:21:25 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	init_floor_sprite_buttons(t_env *env)
{
	env->editor.hud.sp_floor_sprite.pos_x = new_hud_pos_button(ON_RELEASE,
	&change_var, &env->editor.hud.sp_floor_sprite.t_pos_x, env);
	env->editor.hud.sp_floor_sprite.pos_x.pos = new_point(250, 560);
	env->editor.hud.sp_floor_sprite.t_pos_x.pos = new_point(250, 560);
	env->editor.hud.sp_floor_sprite.pos_y = new_hud_pos_button(ON_RELEASE,
	&change_var, &env->editor.hud.sp_floor_sprite.t_pos_y, env);
	env->editor.hud.sp_floor_sprite.pos_y.pos = new_point(300, 560);
	env->editor.hud.sp_floor_sprite.t_pos_y.pos = new_point(300, 560);
	env->editor.hud.sp_floor_sprite.scale_x = new_hud_pos_button(ON_RELEASE,
	&change_floor_sprite_scale,
	&env->editor.hud.sp_floor_sprite.t_scale_x, env);
	env->editor.hud.sp_floor_sprite.scale_x.pos = new_point(250, 600);
	env->editor.hud.sp_floor_sprite.t_scale_x.pos = new_point(300, 600);
	env->editor.hud.sp_floor_sprite.scale_y = new_hud_pos_button(ON_RELEASE,
	&change_floor_sprite_scale,
	&env->editor.hud.sp_floor_sprite.t_scale_y, env);
	env->editor.hud.sp_floor_sprite.scale_y.pos = new_point(300, 600);
	env->editor.hud.sp_floor_sprite.t_scale_y.pos = new_point(300, 600);
}

void	init_floor_sector_buttons(t_env *env)
{
	env->editor.hud.s_floor.brightness = new_hud_button(ON_RELEASE,
	&change_brightness_or_intensity,
	&env->editor.hud.s_floor.t_brightness, env);
	env->editor.hud.s_floor.brightness.pos = new_point(250, 520);
	env->editor.hud.s_floor.t_brightness.pos = new_point(250, 520);
	env->editor.hud.s_floor.color = new_hud_button(ON_RELEASE,
	&change_color, &env->editor.hud.s_floor.t_color, env);
	env->editor.hud.s_floor.color.pos = new_point(250, 560);
	env->editor.hud.s_floor.t_color.pos = new_point(250, 560);
	env->editor.hud.s_floor.intensity = new_hud_button(ON_RELEASE,
	&change_brightness_or_intensity,
	&env->editor.hud.s_floor.t_intensity, env);
	env->editor.hud.s_floor.intensity.pos = new_point(250, 600);
	env->editor.hud.s_floor.t_intensity.pos = new_point(250, 600);
	env->editor.hud.s_floor.gravity = new_hud_button(ON_RELEASE,
	&change_gravity, &env->editor.hud.s_floor.t_gravity, env);
	env->editor.hud.s_floor.gravity.pos = new_point(250, 640);
	env->editor.hud.s_floor.t_gravity.pos = new_point(250, 640);
}

void	init_floor_general_buttons(t_env *env)
{
	env->editor.hud.g_floor.height = new_hud_button(ON_RELEASE,
	&change_floor_height, &env->editor.hud.g_floor.t_height, env);
	env->editor.hud.g_floor.height.pos = new_point(250, 520);
	env->editor.hud.g_floor.t_height.pos = new_point(250, 520);
	env->editor.hud.g_floor.slope = new_hud_button(ON_RELEASE,
	&change_floor_slope, &env->editor.hud.g_floor.t_slope, env);
	env->editor.hud.g_floor.slope.pos = new_point(250, 560);
	env->editor.hud.g_floor.t_slope.pos = new_point(250, 560);
	env->editor.hud.g_floor.texture_scale_x = new_hud_button(ON_RELEASE,
	&change_floor_texture_scale,
	&env->editor.hud.g_floor.t_texture_scale_x, env);
	env->editor.hud.g_floor.texture_scale_x.pos = new_point(250, 640);
	env->editor.hud.g_floor.t_texture_scale_x.pos = new_point(250, 640);
	env->editor.hud.g_floor.texture_scale_y = new_hud_button(ON_RELEASE,
	&change_floor_texture_scale,
	&env->editor.hud.g_floor.t_texture_scale_y, env);
	env->editor.hud.g_floor.texture_scale_y.pos = new_point(250, 680);
	env->editor.hud.g_floor.t_texture_scale_y.pos = new_point(250, 680);
	env->editor.hud.g_floor.texture_align_x = new_hud_button(ON_RELEASE,
	&change_floor_texture_align,
	&env->editor.hud.g_floor.t_texture_align_x, env);
	env->editor.hud.g_floor.texture_align_x.pos = new_point(250, 720);
	env->editor.hud.g_floor.t_texture_align_x.pos = new_point(250, 720);
	env->editor.hud.g_floor.texture_align_y = new_hud_button(ON_RELEASE,
	&change_floor_texture_align,
	&env->editor.hud.g_floor.t_texture_align_y, env);
	env->editor.hud.g_floor.texture_align_y.pos = new_point(250, 760);
	env->editor.hud.g_floor.t_texture_align_y.pos = new_point(250, 760);
}
