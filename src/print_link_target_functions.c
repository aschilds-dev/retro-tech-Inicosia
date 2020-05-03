/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_link_target_functions.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 12:04:01 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/21 17:22:29 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "events_conditions.h"

int		print_global_link_target(t_env *env, t_condition *condition,
t_point pos, int size)
{
	char		*ended;

	(void)size;
	if (condition->type == EVENT_ENDED)
		ended = "ended";
	else
		ended = "ended (start)";
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%s %d %s",
	env->event_links_types[condition->target_trigger.type],
	condition->target_trigger.index, ended);
	return (pos.y);
}

int		print_sector_link_target(t_env *env, t_condition *condition,
t_point pos, int size)
{
	char		*ended;

	(void)size;
	if (condition->type == EVENT_ENDED)
		ended = "ended";
	else
		ended = "ended (start)";
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "Sector %d %s %d %s",
	condition->sector, env->event_links_types[condition->target_trigger.type],
	condition->target_trigger.index, ended);
	return (pos.y);
}

int		print_object_link_target(t_env *env, t_condition *condition,
t_point pos, int size)
{
	char		*ended;

	(void)size;
	if (condition->type == EVENT_ENDED)
		ended = "ended";
	else
		ended = "ended (start)";
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "Object %d %s %d %s",
	condition->object, env->event_links_types[condition->target_trigger.type],
	condition->target_trigger.index, condition->value, ended);
	return (pos.y);
}

int		print_enemy_link_target(t_env *env, t_condition *condition,
t_point pos, int size)
{
	char		*ended;

	(void)size;
	if (condition->type == EVENT_ENDED)
		ended = "ended";
	else
		ended = "ended (start)";
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "Enemy %d %s %d %s",
	condition->enemy, env->event_links_types[condition->target_trigger.type],
	condition->target_trigger.index, condition->value, ended);
	return (pos.y);
}

int		print_wall_sprite_link_target(t_env *env, t_condition *condition,
t_point pos, int size)
{
	char		*ended;

	(void)size;
	if (condition->type == EVENT_ENDED)
		ended = "ended";
	else
		ended = "ended (start)";
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "Sector %d wall %d sprite %d"
	" %s %d %s", condition->sector, condition->wall, condition->sprite,
	env->event_links_types[condition->target_trigger.type],
	condition->target_trigger.index,
	ended);
	return (pos.y);
}
