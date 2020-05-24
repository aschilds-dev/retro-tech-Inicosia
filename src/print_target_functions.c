/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_target_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 12:04:01 by lnicosia          #+#    #+#             */
/*   Updated: 2020/04/30 18:41:36 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		print_sector_target(t_env *env, t_event *event, t_point pos, int size)
{
	(void)event;
	(void)pos;
	(void)size;
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "Target: Sector %d %s",
	event->update_param.sector, env->event_types[event->target_index]);
	return (0);
}

int		print_wall_target(t_env *env, t_event *event, t_point pos, int size)
{
	(void)event;
	(void)pos;
	(void)size;
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "Target: Sector %d wall %d %s",
	event->update_param.sector, event->update_param.wall,
	env->event_types[event->target_index]);
	return (0);
}

int		print_floor_sprite_target(t_env *env, t_event *event, t_point pos,
int size)
{
	(void)event;
	(void)size;
	(void)pos;
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "Target: Sector %d floor sprite"
	" %d %s", event->update_param.sector, event->update_param.sprite,
	env->event_types[event->target_index]);
	return (0);
}

int		print_wall_sprite_target(t_env *env, t_event *event, t_point pos,
int size)
{
	(void)event;
	(void)pos;
	(void)size;
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "Target: Sector %d wall"
	" %d sprite %d %s", event->update_param.sector, event->update_param.wall,
	event->update_param.sprite, env->event_types[event->target_index]);
	return (0);
}

int		print_vertex_target(t_env *env, t_event *event, t_point pos, int size)
{
	(void)event;
	(void)pos;
	(void)size;
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "Target: Vertex %d %s",
	event->update_param.vertex, env->event_types[event->target_index]);
	return (0);
}
