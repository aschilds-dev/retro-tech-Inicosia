/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_env_floor_buttons.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:37:36 by sipatry           #+#    #+#             */
/*   Updated: 2020/02/19 11:30:23 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	init_floor_sprite_env(t_env *env)
{
	env->editor.hud.sp_floor_sprite.t_pos_x.env = env;
	env->editor.hud.sp_floor_sprite.t_pos_x.pos = new_point(0, 0);
	env->editor.hud.sp_floor_sprite.t_pos_x.type = DOUBLE;
	env->editor.hud.sp_floor_sprite.t_pos_y.env = env;
	env->editor.hud.sp_floor_sprite.t_pos_y.pos = new_point(0, 0);
	env->editor.hud.sp_floor_sprite.t_pos_y.type = DOUBLE;
	env->editor.hud.sp_floor_sprite.t_scale_x.env = env;
	env->editor.hud.sp_floor_sprite.t_scale_x.pos = new_point(0, 0);
	env->editor.hud.sp_floor_sprite.t_scale_x.type = DOUBLE;
	env->editor.hud.sp_floor_sprite.t_scale_y.env = env;
	env->editor.hud.sp_floor_sprite.t_scale_y.pos = new_point(0, 0);
	env->editor.hud.sp_floor_sprite.t_scale_y.type = DOUBLE;
}

void	init_floor_sector_env(t_env *env)
{
	env->editor.hud.s_floor.t_brightness.env = env;
	env->editor.hud.s_floor.t_brightness.pos = new_point(0, 0);
	env->editor.hud.s_floor.t_brightness.type = INT;
	env->editor.hud.s_floor.t_color.env = env;
	env->editor.hud.s_floor.t_color.pos = new_point(0, 0);
	env->editor.hud.s_floor.t_color.type = UINT32;
	env->editor.hud.s_floor.t_intensity.env = env;
	env->editor.hud.s_floor.t_intensity.pos = new_point(0, 0);
	env->editor.hud.s_floor.t_intensity.type = INT;
	env->editor.hud.s_floor.t_gravity.env = env;
	env->editor.hud.s_floor.t_gravity.pos = new_point(0, 0);
	env->editor.hud.s_floor.t_gravity.type = DOUBLE;
}

void	init_floor_general_env(t_env *env)
{
	env->editor.hud.g_floor.t_height.env = env;
	env->editor.hud.g_floor.t_height.pos = new_point(0, 0);
	env->editor.hud.g_floor.t_height.type = DOUBLE;
	env->editor.hud.g_floor.t_slope.env = env;
	env->editor.hud.g_floor.t_slope.pos = new_point(0, 0);
	env->editor.hud.g_floor.t_slope.type = DOUBLE;
	env->editor.hud.g_floor.t_texture_scale_x.env = env;
	env->editor.hud.g_floor.t_texture_scale_x.pos = new_point(0, 0);
	env->editor.hud.g_floor.t_texture_scale_x.type = DOUBLE;
	env->editor.hud.g_floor.t_texture_scale_y.env = env;
	env->editor.hud.g_floor.t_texture_scale_y.pos = new_point(0, 0);
	env->editor.hud.g_floor.t_texture_scale_y.type = DOUBLE;
	env->editor.hud.g_floor.t_texture_align_x.env = env;
	env->editor.hud.g_floor.t_texture_align_x.pos = new_point(0, 0);
	env->editor.hud.g_floor.t_texture_align_x.type = DOUBLE;
	env->editor.hud.g_floor.t_texture_align_y.env = env;
	env->editor.hud.g_floor.t_texture_align_y.pos = new_point(0, 0);
	env->editor.hud.g_floor.t_texture_align_y.type = DOUBLE;
	env->editor.hud.g_floor.t_add_sprite.env = env;
	env->editor.hud.g_floor.t_add_sprite.pos = new_point(0, 0);
	env->editor.hud.g_floor.t_add_sprite.type = DOUBLE;
}
