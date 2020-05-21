/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_enemy_tabs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:55:46 by sipatry           #+#    #+#             */
/*   Updated: 2020/05/18 12:28:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "draw.h"

int		print_enemy_general_tab4(t_env *env)
{
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d",
	env->enemies[env->selected_enemy].damage);
	env->editor.hud.g_enemy.t_damage.target =
	&env->enemies[env->selected_enemy].damage;
	if (draw_button(env, env->editor.hud.g_enemy.damage, env->snprintf))
		return (-1);
	if (print_text(new_point(800, 60), new_printable_text("Angle",
		env->sdl.fonts.lato20, 0x333333FF, 30), env))
		return (-1);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	get_decimal_len(env->enemies[env->selected_enemy].angle),
	env->enemies[env->selected_enemy].angle);
	env->editor.hud.g_enemy.t_angle.target =
	&env->enemies[env->selected_enemy].angle;
	if (draw_button(env, env->editor.hud.g_enemy.angle, env->snprintf))
		return (-1);
	return (0);
}

int		print_enemy_general_tab3(t_env *env)
{
	if (draw_button(env, env->editor.hud.g_enemy.health, env->snprintf))
		return (-1);
	if (print_text(new_point(680, 60), new_printable_text("Speed",
		env->sdl.fonts.lato20, 0x333333FF, 30), env))
		return (-1);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d",
	env->enemies[env->selected_enemy].speed);
	env->editor.hud.g_enemy.t_speed.target =
	&env->enemies[env->selected_enemy].speed;
	if (draw_button(env, env->editor.hud.g_enemy.speed, env->snprintf))
		return (-1);
	if (print_text(new_point(720, 60), new_printable_text("Scale",
		env->sdl.fonts.lato20, 0x333333FF, 30), env))
		return (-1);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	get_decimal_len(env->enemies[env->selected_enemy].scale),
	env->enemies[env->selected_enemy].scale);
	env->editor.hud.g_enemy.t_scale.target =
	&env->enemies[env->selected_enemy].scale;
	if (draw_button(env, env->editor.hud.g_enemy.scale, env->snprintf))
		return (-1);
	if (print_text(new_point(760, 60), new_printable_text("Damage",
		env->sdl.fonts.lato20, 0x333333FF, 30), env))
		return (-1);
	return (print_enemy_general_tab4(env));
}

int		print_enemy_general_tab2(t_env *env)
{
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	ft_min(1, get_decimal_len(env->enemies[env->selected_enemy].pos.y)),
	env->enemies[env->selected_enemy].pos.y);
	env->editor.hud.g_enemy.t_pos_y.target =
	&env->enemies[env->selected_enemy].pos.y;
	if (draw_button(env, env->editor.hud.g_enemy.pos_y, env->snprintf))
		return (-1);
	if (print_text(new_point(600, 60), new_printable_text("Z",
		env->sdl.fonts.lato20, 0x333333FF, 30), env))
		return (-1);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	ft_min(1, get_decimal_len(env->enemies[env->selected_enemy].pos.z)),
	env->enemies[env->selected_enemy].pos.z);
	env->editor.hud.g_enemy.t_pos_z.target =
	&env->enemies[env->selected_enemy].pos.z;
	if (draw_button(env, env->editor.hud.g_enemy.pos_z, env->snprintf))
		return (-1);
	if (print_text(new_point(640, 60), new_printable_text("Health",
		env->sdl.fonts.lato20, 0x333333FF, 30), env))
		return (-1);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d",
	env->enemies[env->selected_enemy].map_hp);
	env->editor.hud.g_enemy.t_health.target =
	&env->enemies[env->selected_enemy].map_hp;
	return (print_enemy_general_tab3(env));
}

int		print_enemy_general_tab(t_env *env)
{
	t_point		size;

	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "Enemy %d",
	env->selected_enemy);
	if (TTF_SizeText(env->sdl.fonts.lato_black30,
		env->snprintf, &size.x, &size.y))
		return (-1);
	if (print_text(new_point(465, 200 - size.x / 2),
		new_printable_text(env->snprintf,
		env->sdl.fonts.lato_black30, 0x333333FF, 30), env))
		return (-1);
	if (print_text(new_point(520, 60), new_printable_text("X",
		env->sdl.fonts.lato20, 0x333333FF, 30), env))
		return (-1);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	ft_min(1, get_decimal_len(env->enemies[env->selected_enemy].pos.x)),
	env->enemies[env->selected_enemy].pos.x);
	env->editor.hud.g_enemy.t_pos_x.target =
	&env->enemies[env->selected_enemy].pos.x;
	if (draw_button(env, env->editor.hud.g_enemy.pos_x, env->snprintf))
		return (-1);
	if (print_text(new_point(560, 60), new_printable_text("Y",
		env->sdl.fonts.lato20, 0x333333FF, 30), env))
		return (-1);
	return (print_enemy_general_tab2(env));
}
