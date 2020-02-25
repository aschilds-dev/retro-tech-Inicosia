/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_player_tabs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 12:23:23 by sipatry           #+#    #+#             */
/*   Updated: 2020/02/25 14:34:19 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		printf_player_sprite_tab(t_env *env)
{
	(void)env;
	return (0);
}

int		print_player_sector_tab(t_env *env)
{
	print_text(new_point(480, 60), new_printable_text("Player:",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	print_text(new_point(520, 60), new_printable_text("Brightness:",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d",
	env->sectors[env->player.sector].brightness);
	env->editor.hud.s_player.t_brightness.target =
	&env->sectors[env->player.sector].brightness;
	draw_button(env, env->editor.hud.s_player.brightness, env->snprintf);
	print_text(new_point(560, 60), new_printable_text("Light_color:",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "0x%X",
	env->sectors[env->player.sector].light_color);
	env->editor.hud.s_player.t_color.target =
	&env->sectors[env->player.sector].light_color;
	draw_button(env, env->editor.hud.s_player.color, env->snprintf);
	print_text(new_point(600, 60), new_printable_text("Intensity:",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d",
	env->sectors[env->player.sector].intensity);
	env->editor.hud.s_player.t_intensity.target =
	&env->sectors[env->player.sector].intensity;
	draw_button(env, env->editor.hud.s_player.intensity, env->snprintf);
	print_text(new_point(640, 60), new_printable_text("Gravity:",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	get_decimal_len(env->sectors[env->player.sector].gravity),
	env->sectors[env->player.sector].gravity);
	env->editor.hud.s_player.t_gravity.target =
	&env->sectors[env->player.sector].gravity;
	draw_button(env, env->editor.hud.s_player.gravity, env->snprintf);
	return (0);
}

int		print_player_general_tab(t_env *env)
{
	print_text(new_point(520, 60), new_printable_text("Pos: ",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	ft_min(1, get_decimal_len(env->player.starting_pos.x)), env->player.starting_pos.x);
	env->editor.hud.g_player.t_pos_x.target = &env->player.starting_pos.x;
	draw_button(env, env->editor.hud.g_player.pos_x, env->snprintf);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	ft_min(1, get_decimal_len(env->player.starting_pos.y)),
	env->player.starting_pos.y);
	env->editor.hud.g_player.t_pos_y.target = &env->player.pos.y;
	draw_button(env, env->editor.hud.g_player.pos_y, env->snprintf);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	ft_min(1, get_decimal_len(env->player.starting_pos.z)),
	env->player.starting_pos.z);
	env->editor.hud.g_player.t_pos_z.target = &env->player.starting_pos.z;
	draw_button(env, env->editor.hud.g_player.pos_z, env->snprintf);
	print_text(new_point(560, 60), new_printable_text("Health: ",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d", env->player.health);
	env->editor.hud.g_player.t_health.target = &env->player.health;
	draw_button(env, env->editor.hud.g_player.health, env->snprintf);
	print_text(new_point(600, 60), new_printable_text("Armor: ",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d", env->player.armor);
	env->editor.hud.g_player.t_armor.target = &env->player.armor;
	draw_button(env, env->editor.hud.g_player.armor, env->snprintf);
	print_text(new_point(640, 60), new_printable_text("Speed: ",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	get_decimal_len(env->player.speed), env->player.speed);
	env->editor.hud.g_player.t_speed.target = &env->player.speed;
	draw_button(env, env->editor.hud.g_player.speed, env->snprintf);
	return (0);
}
