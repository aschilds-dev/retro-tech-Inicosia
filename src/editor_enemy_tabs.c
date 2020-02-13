/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_enemy_tabs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:55:46 by sipatry           #+#    #+#             */
/*   Updated: 2020/02/13 11:19:58 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		printf_enemy_sprite_tab(t_env *env)
{
	(void)env;
	return (0);
}

int		print_enemy_sector_tab(t_env *env)
{
	print_text(new_point(480, 60), new_printable_text("Enemy:",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	print_text(new_point(520, 60), new_printable_text("Brightness:",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d",
	env->sectors[env->enemies[env->selected_enemy].sector].brightness);
	env->editor.hud.s_enemy.t_brightness.target =
	&env->sectors[env->enemies[env->selected_enemy].sector].brightness;
	draw_button(env, env->editor.hud.s_enemy.brightness, env->snprintf);
	print_text(new_point(560, 60), new_printable_text("Light_color:", 
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "0x%X",
	env->sectors[env->enemies[env->selected_enemy].sector].light_color);
	env->editor.hud.s_enemy.t_color.target =
	&env->sectors[env->enemies[env->selected_enemy].sector].light_color;
	draw_button(env, env->editor.hud.s_enemy.color, env->snprintf);
	print_text(new_point(600, 60), new_printable_text("Intensity:",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d",
	env->sectors[env->enemies[env->selected_enemy].sector].intensity);
	env->editor.hud.s_enemy.t_intensity.target =
	&env->sectors[env->enemies[env->selected_enemy].sector].intensity;
	draw_button(env, env->editor.hud.s_enemy.intensity, env->snprintf);
	print_text(new_point(640, 60), new_printable_text("Gravity:",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	get_decimal_len(env->sectors[env->enemies[env->selected_enemy].sector].
	gravity), env->sectors[env->enemies[env->selected_enemy].sector].gravity);
	env->editor.hud.s_enemy.t_gravity.target =
	&env->sectors[env->enemies[env->selected_enemy].sector].gravity;
	draw_button(env, env->editor.hud.s_enemy.gravity, env->snprintf);
	return (0);
}

int		print_enemy_general_tab(t_env *env)
{
	print_text(new_point(520, 60), new_printable_text("Pos: ",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	ft_min(1, get_decimal_len(env->enemies[env->selected_enemy].pos.x)),
	env->enemies[env->selected_enemy].pos.x);
	env->editor.hud.g_enemy.t_pos_x.target =
	&env->enemies[env->selected_enemy].pos.x;
	draw_button(env, env->editor.hud.g_enemy.pos_x, env->snprintf);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	ft_min(1, get_decimal_len(env->enemies[env->selected_enemy].pos.y)),
	env->enemies[env->selected_enemy].pos.y);
	env->editor.hud.g_enemy.t_pos_y.target =
	&env->enemies[env->selected_enemy].pos.y;
	draw_button(env, env->editor.hud.g_enemy.pos_y, env->snprintf);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	ft_min(1, get_decimal_len(env->enemies[env->selected_enemy].pos.z)),
	env->enemies[env->selected_enemy].pos.z);
	env->editor.hud.g_enemy.t_pos_z.target =
	&env->enemies[env->selected_enemy].pos.z;
	draw_button(env, env->editor.hud.g_enemy.pos_z, env->snprintf);
	print_text(new_point(560, 60), new_printable_text("Health: ",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d",
	get_decimal_len(env->enemies[env->selected_enemy].health),
	env->enemies[env->selected_enemy].health);
	env->editor.hud.g_enemy.t_health.target =
	&env->enemies[env->selected_enemy].health;
	draw_button(env, env->editor.hud.g_enemy.health, env->snprintf);
	print_text(new_point(600, 60), new_printable_text("Speed: ",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	get_decimal_len(env->enemies[env->selected_enemy].speed),
	env->enemies[env->selected_enemy].speed);
	env->editor.hud.g_enemy.t_speed.target =
	&env->enemies[env->selected_enemy].speed;
	draw_button(env, env->editor.hud.g_enemy.speed, env->snprintf);
	print_text(new_point(640, 60), new_printable_text("Scale: ",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	get_decimal_len(env->enemies[env->selected_enemy].scale),
	env->enemies[env->selected_enemy].scale);
	env->editor.hud.g_enemy.t_scale.target =
	&env->enemies[env->selected_enemy].scale;
	draw_button(env, env->editor.hud.g_enemy.scale, env->snprintf);
	print_text(new_point(680, 60), new_printable_text("Damage: ",
	env->sdl.fonts.lato20, 0x00000000, 30), env);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d",
	env->enemies[env->selected_enemy].damage,
	env->enemies[env->selected_enemy].damage);
	env->editor.hud.g_enemy.t_damage.target =
	&env->enemies[env->selected_enemy].damage;
	draw_button(env, env->editor.hud.g_enemy.damage, env->snprintf);
	return (0);
}
