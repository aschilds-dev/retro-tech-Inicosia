/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_button_keyup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 10:59:14 by sipatry           #+#    #+#             */
/*   Updated: 2020/02/04 11:30:35 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	enemy_buttons_up(t_env *env)
{
	if (button_keyup(&env->editor.current_enemy_selection, env))
		return (-1);
	if (button_keyup(&env->editor.enemy_background, env))
		return (-1);
	if (env->editor.sector_tab.state == DOWN)
	{
		if (button_keyup(&env->editor.hud.s_enemy.brightness, env))
			return (-1);
		if (button_keyup(&env->editor.hud.s_enemy.color, env))
			return (-1);
		if (button_keyup(&env->editor.hud.s_enemy.intensity, env))
			return (-1);
		if (button_keyup(&env->editor.hud.s_enemy.gravity, env))
			return (-1);
	}
	if (env->editor.general_tab.state == DOWN)
	{
		if (button_keyup(&env->editor.hud.g_enemy.health, env))
			return (-1);
		if (button_keyup(&env->editor.hud.g_enemy.speed, env))
			return (-1);
		if (button_keyup(&env->editor.hud.g_enemy.scale, env))
			return (-1);
		if (button_keyup(&env->editor.hud.g_enemy.damage, env))
			return (-1);
	}
	return (0);
}

int	player_buttons_up(t_env *env)
{
	if (env->editor.sector_tab.state == DOWN)
	{
		if (button_keyup(&env->editor.hud.s_player.brightness, env))
			return (-1);
		if (button_keyup(&env->editor.hud.s_player.color, env))
			return (-1);
		if (button_keyup(&env->editor.hud.s_player.intensity, env))
			return (-1);
		if (button_keyup(&env->editor.hud.s_player.gravity, env))
			return (-1);
	}
	if (env->editor.general_tab.state == DOWN)
	{
		if (button_keyup(&env->editor.hud.g_player.health, env))
			return (-1);
		if (button_keyup(&env->editor.hud.g_player.armor, env))
			return (-1);
		if (button_keyup(&env->editor.hud.g_player.speed, env))
			return (-1);
	}
	return (0);
}

int	sector_buttons_up(t_env *env)
{
	if (env->editor.general_tab.state == DOWN)
	{
		if (button_keyup(&env->editor.hud.g_sector.brightness, env))
			return (-1);
		if (button_keyup(&env->editor.hud.g_sector.color, env))
			return (-1);
		if (button_keyup(&env->editor.hud.g_sector.intensity, env))
			return (-1);
		if (button_keyup(&env->editor.hud.g_sector.floor, env))
			return (-1);
		if (button_keyup(&env->editor.hud.g_sector.ceiling, env))
			return (-1);
		if (button_keyup(&env->editor.hud.g_sector.floor_slope, env))
			return (-1);
		if (button_keyup(&env->editor.hud.g_sector.ceiling_slope, env))
			return (-1);
		if (button_keyup(&env->editor.hud.g_sector.gravity, env))
			return (-1);
	}
	return (0);
}
