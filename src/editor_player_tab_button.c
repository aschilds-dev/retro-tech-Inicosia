/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_player_tab_button.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:23:43 by sipatry           #+#    #+#             */
/*   Updated: 2020/02/03 18:03:40 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	init_player_sprite_buttons(t_env *env)
{
	(void)env;
}

void	init_player_sector_buttons(t_env *env)
{
	env->editor.hud.s_player.brightness = new_hud_button(ON_RELEASE, &change_var,
	&env->editor.hud.s_player.t_brightness, env);
	env->editor.hud.s_player.brightness.pos = new_point(250, 520);
	env->editor.hud.s_player.t_brightness.pos = new_point(250, 520);
	env->editor.hud.s_player.color = new_hud_button(ON_RELEASE, &change_var,
	&env->editor.hud.s_player.t_color, env);
	env->editor.hud.s_player.color.pos = new_point(250, 560);
	env->editor.hud.s_player.t_color.pos = new_point(250, 560);
	env->editor.hud.s_player.intensity = new_hud_button(ON_RELEASE, &change_var,
	&env->editor.hud.s_player.t_intensity, env);
	env->editor.hud.s_player.intensity.pos = new_point(250, 600);
	env->editor.hud.s_player.t_intensity.pos = new_point(250, 600);
	env->editor.hud.s_player.gravity = new_hud_button(ON_RELEASE, &change_var,
	&env->editor.hud.s_player.t_gravity, env);
	env->editor.hud.s_player.gravity.pos = new_point(250, 640);
	env->editor.hud.s_player.t_gravity.pos = new_point(250, 640);
}

void	init_player_general_buttons(t_env *env)
{
	env->editor.hud.g_player.pos_x = new_hud_pos_button(ON_RELEASE, &change_var,
	&env->editor.hud.g_player.t_pos_x, env);
	env->editor.hud.g_player.pos_x.pos = new_point(170, 520);
	env->editor.hud.g_player.t_pos_x.pos = new_point(170, 520);
	env->editor.hud.g_player.pos_y = new_hud_pos_button(ON_RELEASE, &change_var,
	&env->editor.hud.g_player.t_pos_y, env);
	env->editor.hud.g_player.pos_y.pos = new_point(250, 520);
	env->editor.hud.g_player.t_pos_y.pos = new_point(250, 520);
	env->editor.hud.g_player.pos_z = new_hud_pos_button(ON_RELEASE, &change_var,
	&env->editor.hud.g_player.t_pos_z, env);
	env->editor.hud.g_player.pos_z.pos = new_point(330, 520);
	env->editor.hud.g_player.t_pos_z.pos = new_point(330, 520);
	env->editor.hud.g_player.health = new_hud_button(ON_RELEASE, &change_var,
	&env->editor.hud.g_player.t_health, env);
	env->editor.hud.g_player.health.pos = new_point(250, 560);
	env->editor.hud.g_player.t_health.pos = new_point(250, 560);
	env->editor.hud.g_player.armor = new_hud_button(ON_RELEASE, &change_var,
	&env->editor.hud.g_player.t_armor, env);
	env->editor.hud.g_player.armor.pos = new_point(250, 600);
	env->editor.hud.g_player.t_armor.pos = new_point(250, 600);
	env->editor.hud.g_player.speed = new_hud_button(ON_RELEASE, &change_var,
	&env->editor.hud.g_player.t_speed, env);
	env->editor.hud.g_player.speed.pos = new_point(250, 640);
	env->editor.hud.g_player.t_speed.pos = new_point(250, 640);
}