/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:54:57 by gaerhard          #+#    #+#             */
/*   Updated: 2020/03/02 12:18:37 by gaerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "collision.h"

/*
** Returns the movomement along the z axis by checking if the entity is
** flying, following a slope.
*/

t_v3	collisions_z_axis(t_env *env, t_motion motion, t_v3 move)
{
	if (get_ceiling_at_pos(&env->sectors[motion.lowest_ceiling],
		motion.future, env) - get_floor_at_pos(&env->sectors[motion.sector],
		motion.future, env) < motion.eyesight + 1)
		return (new_v3(0, 0, 0));
	if (!check_ceiling(env, motion, motion.lowest_ceiling))
		move.z =
			get_ceiling_at_pos(&env->sectors[motion.lowest_ceiling],
			motion.pos, env) - 1 - (motion.pos.z + motion.eyesight);
	if (!check_floor(env, motion, motion.sector) && motion.flight)
		move.z = get_floor_at_pos(&env->sectors[motion.sector], motion.pos, env)
		- motion.pos.z;
	else if (!(check_floor(env, motion, motion.sector)))
		return (new_v3(0, 0, 0));
	return (move);
}

int		collision_object(t_env *env, int i, t_motion motion, t_v3 futur)
{
	double eyesight;

	eyesight = motion.eyesight;
	if (distance_two_points_2d(env->objects[i].pos.x,
		env->objects[i].pos.y, futur.x, futur.y) <
		env->objects[i].size_2d + motion.size_2d &&
		((motion.pos.z <= env->objects[i].pos.z +
		env->objects[i].height && motion.pos.z >=
		env->objects[i].pos.z) || (motion.pos.z + eyesight + 1 <=
		env->objects[i].pos.z + env->objects[i].height && motion.pos.z +
		eyesight + 1 >= env->objects[i].pos.z)))
		return (1);
	return (0);
}

int		collision_objects_event(t_env *env, int i)
{
	if (env->checking_collisions_with_player
		&& env->in_game && !env->player.colliding_objects[i]
		&& env->objects[i].nb_collision_events > 0
		&& env->objects[i].collision_events)
	{
		if (start_event(&env->objects[i].collision_events,
			&env->objects[i].nb_collision_events, env))
		{
			env->fatal_error = 1;
			return (-1);
		}
	}
	if (env->checking_collisions_with_player)
		env->player.colliding_objects[i] = 1;
	if (env->objects[i].solid)
		return (0);
	return (1);
}

/*
** Checks if the entity which is moving collides with any solid object
*/

int		check_objects(t_env *env, t_v3 move, t_motion motion)
{
	int		i;
	int		coll_event;
	t_v3	futur;

	i = 0;
	futur = calculate_motion_future(motion, move);
	while (i < env->nb_objects)
	{
		if (env->objects[i].exists)
		{
			if (collision_object(env, i, motion, futur))
			{
				if ((coll_event = collision_objects_event(env, i)) != 1)
					return (coll_event);
			}
			else if (env->checking_collisions_with_player)
				env->player.colliding_objects[i] = 0;
		}
		i++;
	}
	return (1);
}
