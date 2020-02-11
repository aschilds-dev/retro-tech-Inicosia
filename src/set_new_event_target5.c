/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_new_event_target4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 13:44:55 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/11 15:39:30 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "events_parser.h"

int		select_player_target2(t_env *env, t_event_panel *panel,
t_target_panel *target_panel)
{
	if (target_panel->targets[4].state == DOWN)
	{
		panel->event.target = &env->player.armor;
		panel->event.target_index = PLAYER_ARMOR;
		panel->event.type = INT;
	}
	else if (target_panel->targets[5].state == DOWN)
	{
		panel->event.target = &env->player.speed;
		panel->event.target_index = PLAYER_SPEED;
	}
	else if (target_panel->targets[6].state == DOWN)
	{
		panel->event.target = &env->player.invincible;
		panel->event.target_index = PLAYER_INVINCIBLE;
		panel->event.type = INT;
	}
	else if (target_panel->targets[7].state == DOWN)
	{
		panel->event.target = &env->player.infinite_ammo;
		panel->event.target_index = PLAYER_INFINITE_AMMO;
		panel->event.type = INT;
	}
	set_target_panel_buttons_state(env);
	return (0);
}

int		select_player_target(t_env *env, t_event_panel *panel,
t_target_panel *target_panel)
{
	if (target_panel->targets[0].state == DOWN)
	{
		panel->event.target = &env->player.pos.x;
		panel->event.target_index = PLAYER_X;
	}
	else if (target_panel->targets[1].state == DOWN)
	{
		panel->event.target = &env->player.pos.y;
		panel->event.target_index = PLAYER_Y;
	}
	else if (target_panel->targets[2].state == DOWN)
	{
		panel->event.target = &env->player.pos.z;
		panel->event.target_index = PLAYER_Z;
	}
	else if (target_panel->targets[3].state == DOWN)
	{
		panel->event.target = &env->player.health;
		panel->event.target_index = PLAYER_HP;
		panel->event.type = INT;
	}
	return (select_player_target2(env, panel, target_panel));
}

int		select_object_target2(t_env *env, t_event_panel *panel,
t_target_panel *target_panel, int object)
{
	if (target_panel->targets[3].state == DOWN)
	{
		panel->event.target = &env->objects[object].pos.z;
		panel->event.target_index = OBJECT_Z;
	}
	else if (target_panel->targets[4].state == DOWN)
	{
		panel->event.target = &env->objects[object].scale;
		panel->event.target_index = OBJECT_SCALE;
	}
	else if (target_panel->targets[5].state == DOWN)
	{
		panel->event.target = &env->objects[object].damage;
		panel->event.target_index = OBJECT_DAMAGE;
	}
	else if (target_panel->targets[6].state == DOWN)
	{
		panel->event.target = &env->objects[object].health;
		panel->event.target_index = OBJECT_HP;
	}
	panel->event.update_param.object = object;
	panel->event.check_param.object = object;
	set_target_panel_buttons_state(env);
	return (0);
}

int		select_object_target(t_env *env, t_event_panel *panel,
t_target_panel *target_panel)
{
	int		object;

	object = env->selected_enemy;
	if (target_panel->targets[0].state == DOWN)
	{
		panel->event.target = &env->objects[object].sprite;
		panel->event.target_index = OBJECT_SPRITE;
		panel->event.type = INT;
	}
	else if (target_panel->targets[1].state == DOWN)
	{
		panel->event.target = &env->objects[object].pos.x;
		panel->event.target_index = OBJECT_X;
	}
	else if (target_panel->targets[2].state == DOWN)
	{
		panel->event.target = &env->objects[object].pos.y;
		panel->event.target_index = OBJECT_Y;
	}
	return (select_object_target2(env, panel, target_panel, object));
}
