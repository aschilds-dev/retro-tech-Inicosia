/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectiles_collisions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:48:32 by gaerhard          #+#    #+#             */
/*   Updated: 2020/01/08 14:44:39 by gaerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "collision.h"

int     projectiles_ceil(t_env *env, t_movement motion, int sector_dest)
{
    t_v3    pos;

    pos.x = FUTURE_X;
    pos.y = FUTURE_Y;
    pos.z = FUTURE_Z;
    if (pos.z > get_ceiling_at_pos(env->sectors[sector_dest], pos,env) - 1)
        return (0);
    return (1);
}

int     projectiles_floor(t_env *env, t_movement motion, int sector_dest)
{
    t_v3    pos;
    double  floor;

    pos.x = FUTURE_X;
    pos.y = FUTURE_Y;
    pos.z = FUTURE_Z;
    floor = get_floor_at_pos(env->sectors[sector_dest], pos, env);
    if (floor > motion.pos.z)
		return (0);
    return (1);
}

int     collision_projectiles_rec(t_env *env, t_v3 move, t_movement motion)
{
    int       i;
    t_wall      wall;

    i = 0;
    wall = motion.wall;
    FUTURE_X = move.x + motion.pos.x;
    FUTURE_Y = move.y + motion.pos.y;
    FUTURE_Z = motion.pos.z + move.z;
    env->sector_list[wall.sector_dest] = 1;
    if ((!projectiles_ceil(env, motion, wall.sector_dest) || !projectiles_floor(env, motion, wall.sector_dest)))
        return (0);
    while (i < env->sectors[wall.sector_dest].nb_vertices)
    {
        if (hitbox_collision(new_v2(X1R, Y1R), new_v2(X2R, Y2R), new_v2(FUTURE_X, FUTURE_Y), motion.size_2d) && RNEIGHBOR < 0)
            return (0);
        i++;
    }
    i = 0;
    while (i < env->sectors[wall.sector_dest].nb_vertices)
    {
        if (hitbox_collision(new_v2(X1R, Y1R), new_v2(X2R, Y2R), new_v2(FUTURE_X, FUTURE_Y), motion.size_2d) && RNEIGHBOR >= 0 &&
            env->sector_list[RNEIGHBOR] == 0)
        {
            if ((!projectiles_ceil(env, motion, wall.sector_dest) || !projectiles_floor(env, motion, RNEIGHBOR)))
                return (0);
            motion.wall.sector_or = wall.sector_dest;
            motion.wall.sector_dest = RNEIGHBOR;
            return (collision_projectiles_rec(env, move, motion));
        }
        i++;
    }
    return (1);
}

int     collision_projectiles(t_env *env, t_v3 move, t_movement motion)
{
    int		i;

    FUTURE_X = motion.pos.x + move.x;
    FUTURE_Y = motion.pos.y + move.y;
    FUTURE_Z = motion.pos.z + move.z;
    i = 0;
    init_sector_list(env, motion.sector);
    if (motion.sector == -1)
        return (-4);
    if (!projectiles_ceil(env, motion, motion.sector))
        return (-2);
	else if (!projectiles_floor(env, motion, motion.sector))
        return (-3);
    while (i < env->sectors[motion.sector].nb_vertices)
    {
        if ((hitbox_collision(new_v2(X1, Y1), new_v2(X2, Y2), new_v2(FUTURE_X, FUTURE_Y), motion.size_2d)) && NEIGHBOR < 0)
            return (i);
        i++;
    }
    i = 0;
    while (i < env->sectors[motion.sector].nb_vertices)
    {
        if ((hitbox_collision(new_v2(X1, Y1), new_v2(X2, Y2), new_v2(FUTURE_X, FUTURE_Y), motion.size_2d)) && NEIGHBOR >= 0)
        {
            motion.wall.sector_or = motion.sector;
            motion.wall.sector_dest = NEIGHBOR;
            if (!collision_projectiles_rec(env, move, motion))
                return (i);
        }
        i++;
    }
    return (-1);
}

int			projectile_player_collision(t_env *env, t_v3 pos, t_v3 dest, double radius)
{
	if (env->player.health > 0 && distance_two_points_2d(env->player.pos.x, env->player.pos.y, pos.x, pos.y) < env->player.size_2d + radius
		&& pos.z <= env->player.head_z && pos.z >= env->player.pos.z)
		return (1);
	if (env->player.health > 0 && hitbox_collision(new_v2(pos.x, pos.y), new_v2(dest.x, dest.y),
			new_v2(env->player.pos.x, env->player.pos.y), radius + env->player.size_2d)
			&& pos.z <= env->player.head_z && pos.z >= env->player.pos.z)
		return (1);
	return (0);
}

int			projectile_object_collision(t_env *env, t_v3 pos, t_v3 dest, double radius)
{
	int		i;
	int		object;
	double	nearest_dist;
	double	distance;

	i = 0;
	object = -1;
	nearest_dist = 2147483647;
	while (i < env->nb_objects)
	{
		if (env->objects[i].health > 0 && distance_two_points_2d(env->objects[i].pos.x, env->objects[i].pos.y, pos.x, pos.y) < env->objects[i].size_2d + radius && env->objects[i].exists
			&& env->objects[i].solid && pos.z <= env->objects[i].height + env->objects[i].pos.z && pos.z >= env->objects[i].pos.z)
		{
			distance = distance_two_points_2d(env->objects[i].pos.x, env->objects[i].pos.y, pos.x, pos.y);
			if (distance < nearest_dist)
			{
				nearest_dist = distance;
				object = i;
			}
		}
		if (hitbox_collision(new_v2(pos.x, pos.y), new_v2(dest.x, dest.y),
			new_v2(env->objects[i].pos.x, env->objects[i].pos.y), radius + env->objects[i].size_2d) && env->objects[i].exists
			&& env->objects[i].solid && pos.z <= env->objects[i].height + env->objects[i].pos.z && pos.z >= env->objects[i].pos.z)
		{
			distance = distance_two_points_2d(env->objects[i].pos.x, env->objects[i].pos.y, pos.x, pos.y);
			if (distance < nearest_dist)
			{
				nearest_dist = distance;
				object = i;
			}
		}
		i++;
	}
	return (object);
}
