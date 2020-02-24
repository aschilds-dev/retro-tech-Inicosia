/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_entities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:32:35 by gaerhard          #+#    #+#             */
/*   Updated: 2020/02/19 19:01:13 by gaerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "collision.h"

void	update_entities_sectors(t_env *env)
{
	int i;

	i = 0;
	env->player.sector = get_sector_no_z(env, env->player.pos);
	env->player.highest_sect = find_highest_sector(env,
		new_movement(env->player.sector, env->player.size_2d,
		env->player.eyesight, env->player.pos));
	while (i < env->nb_enemies)
	{
		env->enemies[i].sector = get_sector_no_z(env, env->enemies[i].pos);
		if (env->enemies[i].sector < 0)
		{
			env->selected_enemy = i;
			delete_enemy(env);
		}
		i++;
	}
	i = 0;
	while (i < env->nb_objects)
	{
		env->objects[i].sector = get_sector_no_z(env, env->objects[i].pos);
		if (env->objects[i].sector < 0)
		{
			env->selected_object = i;
			delete_object(env);
		}
		i++;
	}
}
