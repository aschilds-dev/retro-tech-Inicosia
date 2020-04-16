/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_slope.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:04:57 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/20 10:15:36 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "render.h"

/*
**	rotate vertices in selected sector wich make the slope rotate too
*/

t_sector	rotate_vertices(t_env *env, int i, int index)
{
	t_sector	sector;
	int			j;

	sector = env->sectors[index];
	if (i == 1)
		j = 0;
	else
		j = sector.nb_vertices;
	while ((j < sector.nb_vertices && i == 1) || (j > 0 && i == -1))
	{
		if (i == 1)
		{
			sector.vertices[j] = sector.vertices[j + 1];
			j++;
		}
		if (i == -1)
		{
			sector.vertices[j] = sector.vertices[j - 1];
			j--;
		}
	}
	if (i == 1)
	{
		sector.vertices[sector.nb_vertices] = sector.vertices[0];
	}
	else if (i == -1)
	{
		sector.vertices[0] = sector.vertices[sector.nb_vertices];
	}
	return (sector);
}

/*
** Returns the given sector's normal starting from its first vertex.
*/

t_v2	get_sector_normal(t_sector *sector, t_env *env, int start_slope)
{
	t_vertex	v1;
	t_vertex	v2;
	t_v2		normal;
	double		norm;

	v1 = env->vertices[sector->vertices[start_slope]];
	v2 = env->vertices[sector->vertices[start_slope + 1]];
	norm = sqrt(pow(v2.x - v1.x, 2) + pow(v2.y - v1.y, 2));
	normal.x = -((v2.y - v1.y) / norm);
	normal.y = -((v2.x - v1.x) / norm);
	return (normal);
}

/*
** Returns the floor height at a certain pos in a given sector
** (according to the sector's slope)
*/

double	get_floor_at_pos(t_sector *sector, t_v3 pos, t_env *env)
{
	double		res;
	t_vertex	v0;

	v0 = env->vertices[sector->vertices[sector->start_floor_slope]];
	res = sector->floor_normal.x * (pos.x - v0.x) - sector->floor_normal.y
	* (pos.y - v0.y);
	res = res * sector->floor_slope * CONVERT_RADIANS + sector->floor;
	return (res);
}

/*
** Returns the ceiling height at a certain pos in a given sector
** (according to the sector's slope)
*/

double	get_ceiling_at_pos(t_sector *sector, t_v3 pos, t_env *env)
{
	double		res;
	t_vertex	v0;

	v0 = env->vertices[sector->vertices[sector->start_ceiling_slope]];
	res = sector->ceiling_normal.x * (pos.x - v0.x) - sector->ceiling_normal.y
	* (pos.y - v0.y);
	res = res * sector->ceiling_slope * CONVERT_RADIANS + sector->ceiling;
	return (res);
}

void	update_sector_slope(t_env *env, t_sector *sector)
{
	int			i;
	t_vertex	v1;

	if (sector->num < 0 || sector->num > env->nb_sectors)
	{
		ft_printf("Error when updating sector %d slope:"
		" sector does not exist\n");
	}
	sector->floor_max = sector->floor;
	sector->floor_min = sector->floor;
	sector->ceiling_max = sector->ceiling;
	sector->ceiling_min = sector->ceiling;
	i = 0;
	while (i < sector->nb_vertices)
	{
		v1 = env->vertices[sector->vertices[i]];
		if (sector->floor_slope != 0)
			sector->floors[i] = get_floor_at_pos(sector,
				new_v3(v1.x, v1.y, 0), env);
		else
			 sector->floors[i] = sector->floor;
		if (sector->ceiling_slope != 0)
			sector->ceilings[i] = get_ceiling_at_pos(sector,
				new_v3(v1.x, v1.y, 0), env);
		else
			sector->ceilings[i] = sector->ceiling;
		if (sector->floors[i]
				< sector->floor_min)
			sector->floor_min
				= sector->floors[i];
		if (sector->floors[i] 
			> sector->floor_max)
			sector->floor_max
				= sector->floors[i];
		if (sector->ceilings[i]
				> sector->ceiling_max)
			sector->ceiling_max
				= sector->ceilings[i];
		if (sector->ceilings[i]
				< sector->ceiling_min)
			sector->ceiling_min
				= sector->ceilings[i];
		sector->wall_width[i] = sqrt(
				pow(env->vertices[sector->vertices[i + 1]].x
					- env->vertices[sector->vertices[i]].x, 2)
				+ pow(env->vertices[sector->vertices[i + 1]].y
					- env->vertices[sector->vertices[i]].y, 2));
		i++;
	}
	sector->floors[i] = sector->floors[0];
	sector->ceilings[i] = sector->ceilings[0];
	set_sector_xmax(env, sector);
}

void	precompute_slopes(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_sectors)
	{
		env->sectors[i].floor_normal = get_sector_normal(&env->sectors[i],
		env, env->sectors[i].start_floor_slope);
		env->sectors[i].ceiling_normal = get_sector_normal(&env->sectors[i],
		env, env->sectors[i].start_ceiling_slope);
		update_sector_slope(env, &env->sectors[i]);
		i++;
	}
}
