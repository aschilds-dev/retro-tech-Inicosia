/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 11:01:42 by lnicosia          #+#    #+#             */
/*   Updated: 2020/04/30 11:01:43 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_projectiles(t_env *env)
{
	free_events(&env->wall_bullet_holes_events,
	&env->nb_wall_bullet_holes_events);
	free_events(&env->floor_bullet_holes_events,
	&env->nb_floor_bullet_holes_events);
	free_events(&env->ceiling_bullet_holes_events,
	&env->nb_ceiling_bullet_holes_events);
	if (env->projectiles)
		ft_lstdelfront(&env->projectiles);
	if (env->explosions)
		ft_lstdelfront(&env->explosions);
}

void	free_map2(t_env *env)
{
	if (env->rendered_sectors)
		ft_memdel((void**)&env->rendered_sectors);
	if (env->rendered_enemies)
		ft_memdel((void**)&env->rendered_enemies);
	if (env->rendered_objects)
		ft_memdel((void**)&env->rendered_objects);
}

void	free_on_going_events(t_env *env)
{
	t_event	*event;

	ft_printf("Freeing on going event\n");
	while (env->events)
	{
		event = (t_event*)env->events->content;
		if (event->max_uses > 0 && event->uses >= event->max_uses)
			free_event(event);
		ft_lstpopfront(&env->events);
	}
}

void	free_map(t_env *env)
{
	if (env->enemies)
		free_enemies(env);
	if (env->objects)
		free_objects(env);
	if (env->vertices)
		ft_memdel((void**)&env->vertices);
	if (env->player.colliding_objects)
		ft_memdel((void**)&env->player.colliding_objects);
	if (env->player.colliding_enemies)
		ft_memdel((void**)&env->player.colliding_enemies);
	if (env->sector_list)
		ft_memdel((void**)&env->sector_list);
	free_projectiles(env);
	free_events(&env->global_events, &env->nb_global_events);
	if (env->sectors)
		free_sectors(env);
	free_camera(&env->player.camera);
	free_camera(&env->fixed_camera);
	if (env->events)
		free_on_going_events(env);
	if (env->queued_values)
		ft_lstdelfront(&env->queued_values);
	if (env->dialog_box_str)
		ft_strdel(&env->dialog_box_str);
	free_map2(env);
}
