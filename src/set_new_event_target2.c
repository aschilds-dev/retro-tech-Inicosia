/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_new_event_target2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:07:43 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/12 13:53:39 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "events_parser.h"
#include "events.h"
#include "parser.h"

int		select_enemy_target3(t_env *env, t_event_panel *panel,
t_target_panel *target_panel, int enemy)
{
	if (target_panel->selected_button == 6)
	{
		panel->event.target = &env->enemies[enemy].damage;
		panel->event.target_index = ENEMY_DAMAGE;
		panel->event.type = INT;
	}
	else if (target_panel->selected_button == 7)
	{
		panel->event.target = &env->enemies[enemy].health;
		panel->event.target_index = ENEMY_HP;
		panel->event.type = INT;
	}
	panel->event.update_param.enemy = enemy;
	panel->event.check_param.enemy = enemy;
	return (0);
}

int		select_enemy_target2(t_env *env, t_event_panel *panel,
t_target_panel *target_panel, int enemy)
{
	if (target_panel->selected_button == 3)
	{
		panel->event.target = &env->enemies[enemy].pos.z;
		panel->event.target_index = ENEMY_Z;
	}
	else if (target_panel->selected_button == 4)
	{
		panel->event.target = &env->enemies[enemy].scale;
		panel->event.target_index = ENEMY_SCALE;
	}
	else if (target_panel->selected_button == 5)
	{
		panel->event.target = &env->enemies[enemy].speed;
		panel->event.target_index = ENEMY_SPEED;
	}
	return (select_enemy_target3(env, panel, target_panel, enemy));
}

int		select_enemy_target(t_env *env, t_event_panel *panel,
t_target_panel *target_panel)
{
	int		enemy;

	enemy = env->selected_enemy;
	if (target_panel->selected_button == 0)
	{
		panel->event.target = &env->enemies[enemy].sprite;
		panel->event.target_index = ENEMY_SPRITE;
		panel->event.type = INT;
	}
	else if (target_panel->selected_button == 1)
	{
		panel->event.target = &env->enemies[enemy].pos.x;
		panel->event.target_index = ENEMY_X;
	}
	else if (target_panel->selected_button == 2)
	{
		panel->event.target = &env->enemies[enemy].pos.y;
		panel->event.target_index = ENEMY_Y;
	}
	return (select_enemy_target2(env, panel, target_panel, enemy));
}

int		select_wall_target2(t_env *env, t_event_panel *panel,
t_target_panel *target_panel, int sector)
{
	int		wall;

	wall = env->editor.selected_wall;
	if (target_panel->selected_button == 3)
	{
		panel->event.target = &env->sectors[sector].align[wall].x;
		panel->event.target_index = SECTOR_WALL_ALIGN_Y;
	}
	else if (target_panel->selected_button == 4)
	{
		panel->event.target = &env->sectors[sector].scale[wall].x;
		panel->event.target_index = SECTOR_WALL_SCALE_X;
	}
	else if (target_panel->selected_button == 5)
	{
		panel->event.target = &env->sectors[sector].scale[wall].y;
		panel->event.target_index = SECTOR_WALL_SCALE_Y;
	}
	panel->event.update_param.sector = sector;
	panel->event.check_param.sector = sector;
	panel->event.update_param.wall = wall;
	panel->event.check_param.wall = wall;
	return (0);
}

int		select_wall_target(t_env *env, t_event_panel *panel,
t_target_panel *target_panel)
{
	int		sector;
	int		wall;

	sector = env->editor.selected_sector;
	wall = env->editor.selected_wall;
	if (target_panel->selected_button == 0)
	{
		panel->event.target = &env->sectors[sector].textures[wall];
		panel->event.target_index = SECTOR_WALL_TEXTURE;
		panel->event.type = INT;
	}
	else if (target_panel->selected_button == 1)
	{
		panel->event.target = &env->sectors[sector].portals[wall];
		panel->event.target_index = SECTOR_WALL_PORTAL;
		panel->event.type = INT;
	}
	else if (target_panel->selected_button == 2)
	{
		panel->event.target = &env->sectors[sector].align[wall].x;
		panel->event.target_index = SECTOR_WALL_ALIGN_X;
	}
	return (select_wall_target2(env, panel, target_panel, sector));
}
