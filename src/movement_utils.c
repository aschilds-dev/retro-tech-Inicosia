/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 19:09:06 by gaerhard          #+#    #+#             */
/*   Updated: 2019/10/23 16:06:07 by gaerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "collision.h"

t_movement  new_movement(int sector, double size_2d, double eyesight, t_v3 pos)
{
    t_movement motion;

    motion.sector = sector;
    motion.size_2d = size_2d;
    motion.eyesight = eyesight;
    motion.pos = pos;
    return (motion);
}

double     sector_height(t_env *env, t_movement motion, int sector_dest)
{
    double  height;
    
    height = motion.eyesight + env->sectors[sector_dest].floor + (env->sectors[sector_dest].normal.x
        * (motion.pos.x - FUTURE_V0X) - env->sectors[sector_dest].normal.y * (motion.pos.y - FUTURE_V0Y)) * env->sectors[sector_dest].floor_slope;
    return (height);
}

void     iter_sectors_rec(t_env *env, t_v3 pos, t_wall wall, double size_2d)
{
    short       i;

    i = 0;
    env->sector_list[wall.sector_dest] = 1;
    while (i < env->sectors[wall.sector_dest].nb_vertices)
    {
        if (hitbox_collision(new_v2(X1R, Y1R), new_v2(X2R, Y2R), new_v2(pos.x, pos.y), size_2d) && RNEIGHBOR >= 0 &&
            env->sector_list[RNEIGHBOR] == 0)
        {
            wall.sector_or = wall.sector_dest;
            wall.sector_dest = RNEIGHBOR;
            iter_sectors_rec(env, pos, wall, size_2d);
        }
        i++;
    }
    return;
}

void     iter_sectors(t_env *env, t_movement motion)
{
    short		i;
    t_wall      wall;
    //static int a = 0;

    i = 0;
    init_sector_list(env, motion.sector);
    while (i < env->sectors[motion.sector].nb_vertices)
    {
        if ((distance_two_points(X1, Y1, motion.pos.x, motion.pos.y) <= motion.size_2d || distance_two_points(X2, Y2, motion.pos.x, motion.pos.y) <= motion.size_2d
            || hitbox_collision(new_v2(X1, Y1), new_v2(X2, Y2), new_v2(motion.pos.x, motion.pos.y), motion.size_2d)) && NEIGHBOR >= 0)
        {
            wall.sector_or = motion.sector;
            wall.sector_dest = NEIGHBOR;
            iter_sectors_rec(env, motion.pos, wall, motion.size_2d);
        }
        i++;
    }
    return ;
}

int        find_highest_sector(t_env *env, t_movement motion)
{
    int     i;
    double  height;
    double  s_height;
    int     tmp;

    i = 0;
    if (motion.sector == -1)
        return (0);
    iter_sectors(env, motion);
    tmp = motion.sector;
    height = sector_height(env, motion, motion.sector);
    while (i < env->nb_sectors)
    {
        if (env->sector_list[i])
        {
            s_height = sector_height(env, motion, i);
            if (height < s_height)
            {
                height = s_height;
                tmp = i;
            }
        }
        i++;
    }
    return (tmp);
}

int        find_lowest_sector(t_env *env, t_movement motion)
{
    int     i;
    double  height;
    double  s_height;
    int     tmp;

    i = 0;
    iter_sectors(env, motion);
    tmp = motion.sector;
    height = sector_height(env, motion, motion.sector);
    while (i < env->nb_sectors)
    {
        if (env->sector_list[i])
        {
            s_height = sector_height(env, motion, i);
            if (height > s_height)
            {
                height = s_height;
                tmp = i;
            }
        }
        i++;
    }
    return (tmp);
}
