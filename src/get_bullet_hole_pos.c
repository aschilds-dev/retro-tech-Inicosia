/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bullet_hole_pos.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 09:24:51 by lnicosia          #+#    #+#             */
/*   Updated: 2019/12/02 15:24:03 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

t_v2	get_floor_bullet_hole_pos(t_sector *sector, t_projectile *projectile,
t_env *env)
{
	t_v3	inter;

	inter = get_intersection_line_plane(projectile->pos, projectile->dest,
	new_plane(new_v3(env->vertices[sector->vertices[0]].x,
	env->vertices[sector->vertices[0]].y,
	sector->floors[0]),
	new_v3(env->vertices[sector->vertices[1]].x,
	env->vertices[sector->vertices[1]].y,
	sector->floors[1]),
	new_v3(env->vertices[sector->vertices[2]].x,
	env->vertices[sector->vertices[2]].y,
	sector->floors[2])),
	new_v3(env->vertices[sector->vertices[0]].x,
	env->vertices[sector->vertices[0]].y,
	sector->floors[0]));
	return (new_v2(inter.x, inter.y));
}

t_v2	get_ceiling_bullet_hole_pos(t_sector *sector, t_projectile *projectile,
t_env *env)
{
	t_v3	inter;

	inter = get_intersection_line_plane(projectile->pos, projectile->dest,
	new_plane(new_v3(env->vertices[sector->vertices[0]].x,
	env->vertices[sector->vertices[0]].y,
	sector->ceilings[0]),
	new_v3(env->vertices[sector->vertices[1]].x,
	env->vertices[sector->vertices[1]].y,
	sector->ceilings[1]),
	new_v3(env->vertices[sector->vertices[2]].x,
	env->vertices[sector->vertices[2]].y,
	sector->ceilings[2])),
	new_v3(env->vertices[sector->vertices[0]].x,
	env->vertices[sector->vertices[0]].y,
	sector->ceilings[0]));
	return (new_v2(inter.x, inter.y));
}

t_v2	get_wall_bullet_hole_pos(t_sector *sector, t_projectile *projectile,
int i, t_env *env)
{
	t_v3	inter;
	double	dist;

	inter = get_intersection_line_plane(projectile->pos, projectile->dest,
	new_plane(new_v3(env->vertices[sector->vertices[i]].x,
	env->vertices[sector->vertices[i]].y,
	sector->floors[i]),
	new_v3(env->vertices[sector->vertices[i]].x,
	env->vertices[sector->vertices[i]].y,
	sector->ceilings[i]),
	new_v3(env->vertices[sector->vertices[i + 1]].x,
	env->vertices[sector->vertices[i + 1]].y,
	sector->floors[i])),
	new_v3(env->vertices[sector->vertices[i]].x,
	env->vertices[sector->vertices[i]].y,
	sector->floors[i]));
	dist = sqrt(pow((inter.x - env->vertices[sector->vertices[i]].x), 2)
	+ pow((inter.y - env->vertices[sector->vertices[i]].y), 2));
	return (new_v2(dist, sector->ceiling - inter.z - projectile->scale / 2));
}
