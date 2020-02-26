/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:57:40 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/25 15:34:25 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** Returns -1 if the vertex is inside a sector
** returns 1 otherwise
*/

int		check_vertex_inside_sector(t_env *env, t_v2 vertex)
{
	int			i;
	int			j;

	i = 0;
	while (i < env->nb_sectors)
	{
		j = 0;
		while (j < env->sectors[i].nb_vertices)
		{
			if (vertex.x == env->vertices[env->sectors[i].vertices[j]].x
			&& vertex.y == env->vertices[env->sectors[i].vertices[j]].y)
				return (1);
			j++;
		}
		if (is_in_sector_no_z(env, i, vertex))
			return (custom_error("Vertex is inside a sector"));
		i++;
	}
	return (1);
}

/*
**	Check if the current sector is inside another sector
*/

int			compare_sectors(int start_v1, int start_v2,
t_sector sect1, t_sector sect2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (start_v1 < sect1.nb_vertices)
	{
		if (sect1.vertices[start_v1] == sect2.vertices[start_v2])
			i++;
		else
		{
			if (start_v2 + 1 < sect2.nb_vertices)
				j = start_v2 + 1;
			else
				j = 0;
			while ((j > start_v2 && j < sect2.nb_vertices)
			|| (j < start_v2))
			{
				if (sect1.vertices[start_v1] == sect2.vertices[j])
				{
					start_v2 = j;
					i++;
					break;
				}
				if (j < sect2.nb_vertices)
					j++;
				else
					j = 0;
			}
		}
		if (start_v2 < sect2.nb_vertices)
			start_v2++;
		else
			start_v2 = 0;
		start_v1++;
	}
	if (i == sect1.nb_vertices)
		return (-1);
	return (0);
}

int			check_portals(t_sector sect1, t_sector sect2)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (i < sect1.nb_vertices)
	{
		j = 0;
		while (j < sect2.nb_vertices)
		{
			if (sect1.vertices[i] == sect2.vertices[j])
			{
				k = 0;
				while (k < sect2.nb_vertices)
				{
					if (sect1.vertices[i + 1] == sect2.vertices[k]
					&& sect1.neighbors[i] == -1)
						return (-1);					
					k++;
				}
			}
			j++;
		}
		i++;
	}
	return (0);
}

int			check_sectors_inside(t_sector sector, int sect, t_env *env)
{
	int			i;
	int			j;
	t_sector	sector2;

	i = 0;
	sector2 = env->sectors[sect];
	while (i < sector.nb_vertices)
	{
		j = 0;

		while (j < sector2.nb_vertices)
		{
			if (sector.vertices[i] == sector2.vertices[j])
				break;
			j++;
		}
		if (sector.vertices[i] == sector2.vertices[j])
			break;
		i++;
	}
	if (compare_sectors(i, j, sector, sector2))
		return (-1);
	if (check_portals(sector, sector2))
		return(-1);
	return (0);
}

int			check_inside_sector(t_sector sector, int sect, t_env *env)
{
	int			i;
	int			j;
	t_sector	sector2;;
	t_v2		vertex;
	
	i = 0;
	sector2 = env->sectors[sect];
	while (i < sector2.nb_vertices)
	{
		j = 0;
		vertex = new_v2(env->vertices[sector2.vertices[i]].x,
		env->vertices[sector2.vertices[i]].y);
		while (j < sector.nb_vertices)
		{
			if (vertex.x == env->vertices[sector.vertices[j]].x
			&& vertex.y == env->vertices[sector.vertices[j]].y)
				break;
			j++;
		}
		if (j == sector.nb_vertices
		&& is_in_sector_no_z(env, sector.num, vertex))
			return (-1);
		i++;
	}
	return (0);
}

static int	is_inside(t_sector sector, t_env *env)
{
	int		i;

	i = 0;
	while(i < env->nb_sectors)
	{
		if (i != sector.num)
		{
			if (check_inside_sector(sector, i, env))
				return (-1);
			if (check_sectors_inside(sector, i, env))
				return (-1);
		}
		i++;
	}
	return (0);
}


int			check_duplicate_vertices(t_sector sector, t_env *env)
{
	int	i;
	int	j;

	i = 0;
	while (i  <sector.nb_vertices)
	{
		j =  i + 1;
		while (j < sector.nb_vertices)
		{
			if ((env->vertices[sector.vertices[i]].x ==
			env->vertices[sector.vertices[j]].x)
			&& (env->vertices[sector.vertices[i]].y ==
			env->vertices[sector.vertices[j]].y))
			{
				return (ft_printf("vertex %d is a duplicate of vertex %d",
				sector.vertices[j], sector.vertices[i]));
			}
			j++;
		}
		i++;
	}
	return (0);
}

int			is_neighbor_valid(t_sector neighbor, t_vertex v1, t_vertex v2)
{
	int			i;

	i = 0;
	while (i < neighbor.nb_vertices)
	{
		if (neighbor.vertices[i] == v2.num &&
		neighbor.vertices[i + 1] == v1.num)
			return (0);
		else if (i == neighbor.nb_vertices - 1 
		&& (neighbor.vertices[i] == v2.num &&
			neighbor.vertices[0] == v1.num))
			return (0);
		i++;
	}
	return (-1);
}

int			check_neighbor_validity(t_sector sector, t_env *env)
{
	int			i;
	t_vertex	v1;
	t_vertex	v2;
	t_sector	neighbor;

	i = 0;
	while (i < env->sectors[sector.num].nb_vertices)
	{
		if (env->sectors[sector.num].neighbors[i] != -1)
		{
			v1 = env->vertices[sector.vertices[i]];	
			v2 = env->vertices[sector.vertices[i + 1]];
			neighbor = env->sectors[env->sectors[sector.num].neighbors[i]];
			if (is_neighbor_valid(neighbor, v1, v2))
				return (-1);
		}
		i++;
	}
	return (0);
}

int			check_intersection_with_sector(t_sector sector, t_env *env,
t_vertex vt1, t_vertex vt2)
{
	int		i;
	t_v2	v1;
	t_v2	v2;
	t_v2	v3;
	t_v2	v4;

	i = 0;
	v1 = new_v2(vt1.x, vt1.y);
	v2 = new_v2(vt2.x, vt2.y);
	while (i < sector.nb_vertices)
	{
		v3 = new_v2(env->vertices[sector.vertices[i]].x,
		env->vertices[sector.vertices[i]].y);
		v4 = new_v2(env->vertices[sector.vertices[i + 1]].x,
		env->vertices[sector.vertices[i + 1]].y);
			if (segments_intersect(v1, v2, v3, v4))
			{
				if ((env->vertices[sector.vertices[i]].num == vt1.num
				&& env->vertices[sector.vertices[i + 1]].num != vt2.num)
				|| (env->vertices[sector.vertices[i]].num == vt2.num
				&& env->vertices[sector.vertices[i + 1]].num != vt1.num)
				|| (env->vertices[sector.vertices[i]].num != vt1.num
				&& env->vertices[sector.vertices[i + 1]].num == vt2.num)
				|| (env->vertices[sector.vertices[i]].num != vt2.num
				&& env->vertices[sector.vertices[i + 1]].num == vt1.num))
					i = i - 0;
				else
					return (-1);
			}
		i++;
	}
	return (0);
}

int			is_sector_concave(t_sector sector, t_env *env)
{
	int			i;
	t_v2		*p;
	int			straight;
	int			res;
	t_vertex	current;

	i = 0;
	res = 0;
	straight = 0;
	if (!(p = (t_v2*)ft_memalloc(sizeof(t_v2) * (sector.nb_vertices + 2))))
		return (-1);
	while (i < sector.nb_vertices + 2)
	{
		if (i >= sector.nb_vertices)
		{
			if (i == sector.nb_vertices)
			{
				p[i].x = p[0].x;
				p[i].y = p[0].y;
			}
			else if (i == sector.nb_vertices + 1)
			{
				p[i].x = p[1].x;
				p[i].y = p[1].y;
			}
		}
		else
		{
			current = env->vertices[env->sectors[sector.num].vertices[i]];
			p[i].x = current.x;
			p[i].y = current.y;
		}
		i++;
	}
	i = 0;
	while (i < sector.nb_vertices)
	{
		res = check_all_angles(p, res, i, straight);
		if (!res)
			straight++;
		else
			straight = 0;
		i++;
	}
	free(p);
	if (res != -(sector.nb_vertices) && res != sector.nb_vertices && res)
		return (-1);
	if (!res)
		env->sector_is_straight = 1;
	else
		env->sector_is_straight = 0;
	return (0);
}

int			check_vertices(t_sector sector, t_env *env)
{
	int			i;
	int			j;
	t_vertex	v1;
	t_vertex	v2;

	i = 0;
	while (i < sector.nb_vertices)
	{
		v1 = env->vertices[sector.vertices[i]];
		v2 = env->vertices[sector.vertices[i + 1]];
		j = 0;
		while (j < env->nb_sectors)
		{
			if (check_intersection_with_sector(env->sectors[j], env, v1, v2))
				return (-1);
			j++;
		}
		i++;
	}
	if (is_sector_concave(sector, env))
		return (ft_printf("Sector %d is concave\n", sector.num));
	if (check_neighbor_validity(sector, env))
		return(ft_printf("Sector %d has a invalid neighbor\n", sector.num));
	
	return (0);
}

int			check_slopes_start(t_sector sector)
{
	if (sector.start_ceiling_slope > sector.nb_vertices
	|| sector.start_ceiling_slope < 0)
		return (ft_printf("Ceiling "));
	if (sector.start_floor_slope > sector.nb_vertices
	|| sector.start_floor_slope < 0)
		return (ft_printf("Floor "));
	return (0);
}

int			distance_bewteen_ceiling_and_floor(t_sector sector)
{
	if (sector.ceiling - sector.floor > 1000)
		return (-1);
	return (0);
}

/*
**	Check sector validity
*/

int			check_sector(t_sector sector, t_env *env)
{
	if (is_inside(sector, env))
		return (ft_printf("Sector %d is inside or contains a sector\n", sector.num));
	if (check_vertices(sector, env))
		return (ft_printf("Vertices invalid\n"));
	if (check_slopes_start(sector))
		return (ft_printf("slope direction isn't valid\n"));
	if (distance_bewteen_ceiling_and_floor(sector))
		return (ft_printf("Distance between floor and ceiling exceed 1000\n"));
	if (env->sector_is_straight)
		return (ft_printf("Sector %d is on a staight line\n", sector.num));
	return (0);
}

int			valid_map(t_env *env)
{
	int	i;

	ft_printf("{reset}Checking map validity..{red}\n");
	i = 0;
	env->player.sector = get_sector_no_z(env, env->player.pos);
	env->player.starting_sector = get_sector_no_z(env, env->player.starting_pos);
	if (!env->nb_sectors)
		return (ft_printf("You need at least one sector to go in 3d mode{reset}\n"));
	if (!env->editor.player_exist)
		return (ft_printf("You need to place the player\n"));
	if (env->player.sector == -1 || env->player.starting_sector == -1)
		return (ft_printf("Player position is not valid{reset}\n"));
	while (i < env->nb_sectors)
	{

		if (check_sector(env->sectors[i], env))
			return (ft_printf("Sector %d was not valid\n", i));
		i++;
	}
	ft_printf("{reset}");
	return (0);
}
