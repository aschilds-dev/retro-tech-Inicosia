/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_env_wall_buttons.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:46:44 by sipatry           #+#    #+#             */
/*   Updated: 2020/02/25 10:18:52 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	init_wall_sprite_sector_env(t_env *env)
{
	env->editor.hud.s_wall_sprite.t_brightness.env = env;
	env->editor.hud.s_wall_sprite.t_brightness.pos = new_point(0, 0);
	env->editor.hud.s_wall_sprite.t_brightness.type = INT;
	env->editor.hud.s_wall_sprite.t_color.env = env;
	env->editor.hud.s_wall_sprite.t_color.pos = new_point(0, 0);
	env->editor.hud.s_wall_sprite.t_color.type = UINT32;
	env->editor.hud.s_wall_sprite.t_intensity.env = env;
	env->editor.hud.s_wall_sprite.t_intensity.pos = new_point(0, 0);
	env->editor.hud.s_wall_sprite.t_intensity.type = INT;
	env->editor.hud.s_wall_sprite.t_gravity.env = env;
	env->editor.hud.s_wall_sprite.t_gravity.pos = new_point(0, 0);
	env->editor.hud.s_wall_sprite.t_gravity.type = DOUBLE;
}

void	init_wall_sprite_env(t_env *env)
{
	env->editor.hud.sp_wall_sprite.t_pos_x.env = env;
	env->editor.hud.sp_wall_sprite.t_pos_x.pos = new_point(0, 0);
	env->editor.hud.sp_wall_sprite.t_pos_x.type = DOUBLE;
	env->editor.hud.sp_wall_sprite.t_pos_y.env = env;
	env->editor.hud.sp_wall_sprite.t_pos_y.pos = new_point(0, 0);
	env->editor.hud.sp_wall_sprite.t_pos_y.type = DOUBLE;
	env->editor.hud.sp_wall_sprite.t_scale_x.env = env;
	env->editor.hud.sp_wall_sprite.t_scale_x.pos = new_point(0, 0);
	env->editor.hud.sp_wall_sprite.t_scale_x.type = DOUBLE;
	env->editor.hud.sp_wall_sprite.t_scale_y.env = env;
	env->editor.hud.sp_wall_sprite.t_scale_y.pos = new_point(0, 0);
	env->editor.hud.sp_wall_sprite.t_scale_y.type = DOUBLE;
	env->editor.hud.sp_wall_sprite.t_add_sprite.env = env;
	env->editor.hud.sp_wall_sprite.t_add_sprite.pos = new_point(0, 0);
	env->editor.hud.sp_wall_sprite.t_add_sprite.type = DOUBLE;
}

void	init_wall_sector_env(t_env *env)
{
	env->editor.hud.s_wall.t_brightness.env = env;
	env->editor.hud.s_wall.t_brightness.pos = new_point(0, 0);
	env->editor.hud.s_wall.t_brightness.type = INT;
	env->editor.hud.s_wall.t_color.env = env;
	env->editor.hud.s_wall.t_color.pos = new_point(0, 0);
	env->editor.hud.s_wall.t_color.type = UINT32;
	env->editor.hud.s_wall.t_intensity.env = env;
	env->editor.hud.s_wall.t_intensity.pos = new_point(0, 0);
	env->editor.hud.s_wall.t_intensity.type = INT;
	env->editor.hud.s_wall.t_gravity.env = env;
	env->editor.hud.s_wall.t_gravity.pos = new_point(0, 0);
	env->editor.hud.s_wall.t_gravity.type = DOUBLE;
}

void	init_wall_general_env(t_env *env)
{
	env->editor.hud.g_wall.t_texture_scale_x.env = env;
	env->editor.hud.g_wall.t_texture_scale_x.pos = new_point(0, 0);
	env->editor.hud.g_wall.t_texture_scale_x.type = DOUBLE;
	env->editor.hud.g_wall.t_texture_scale_y.env = env;
	env->editor.hud.g_wall.t_texture_scale_y.pos = new_point(0, 0);
	env->editor.hud.g_wall.t_texture_scale_y.type = DOUBLE;
	env->editor.hud.g_wall.t_texture_align_x.env = env;
	env->editor.hud.g_wall.t_texture_align_x.pos = new_point(0, 0);
	env->editor.hud.g_wall.t_texture_align_x.type = DOUBLE;
	env->editor.hud.g_wall.t_texture_align_y.env = env;
	env->editor.hud.g_wall.t_texture_align_y.pos = new_point(0, 0);
	env->editor.hud.g_wall.t_texture_align_y.type = DOUBLE;
	env->editor.hud.g_wall.t_portal.env = env;
	env->editor.hud.g_wall.t_portal.pos = new_point(0, 0);
	env->editor.hud.g_wall.t_portal.type = INT;
	env->editor.hud.g_wall.t_add_sprite.env = env;
	env->editor.hud.g_wall.t_add_sprite.pos = new_point(0, 0);
	env->editor.hud.g_wall.t_add_sprite.type = INT;
}
