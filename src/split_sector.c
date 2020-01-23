/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_sector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:17:28 by sipatry           #+#    #+#             */
/*   Updated: 2019/12/02 12:31:49 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	check_next_to_vertex(t_env *env, int i, int j)
{
	t_sector sector;

	sector = env->sectors[i];
	if (((j > 0 && sector.vertices[j] == env->editor.split.v1 && (sector.vertices[j - 1] == env->editor.split.v2
		|| sector.vertices[j + 1] == env->editor.split.v2)))
		|| (sector.vertices[j] == env->editor.split.v1 && j == 0
		&& (sector.vertices[sector.nb_vertices - 1] == env->editor.split.v2
		|| sector.vertices[j + 1] == env->editor.split.v2)))
		return (0);
	else if (((j > 0 && sector.vertices[j] == env->editor.split.v2 && (sector.vertices[j - 1] == env->editor.split.v1
		|| sector.vertices[j + 1] == env->editor.split.v1)))
		|| (sector.vertices[j] == env->editor.split.v2 && j == 0
		&& (sector.vertices[sector.nb_vertices - 1] == env->editor.split.v1
		|| sector.vertices[j + 1] == env->editor.split.v1)))
		return (0);
	return (1);
}

int	check_sectors(t_env *env)
{
	int	i;
	int	j;
	int	first;

	first = 0;
	i = 0;
	while (i < env->nb_sectors)
	{
		j = 0;
		while (j < env->sectors[i].nb_vertices)
		{
			if ((env->sectors[i].vertices[j] == env->editor.split.v1
			|| env->sectors[i].vertices[j] == env->editor.split.v2) && !first)
			{
				first = 1;
			}
			else if (first && (env->sectors[i].vertices[j] == env->editor.split.v1
			|| env->sectors[i].vertices[j] == env->editor.split.v2))
			{
				if (!check_next_to_vertex(env, i, j))
					return (0);
				env->editor.split.sector = i;
				return (1);
			}
			j++;
		}
		first = 0;
		i++;
	}
	return (0);
}

int	check_pos_vertices(t_env *env)
{
	t_list	*tmp;

	tmp = env->editor.current_vertices;
	env->editor.split.v1 = ((t_vertex*)tmp->content)->num;
	tmp = env->editor.current_vertices->next;
	env->editor.split.v2 = ((t_vertex*)tmp->content)->num;
	if (check_sectors(env))
		return (1);
	return (0);
}

void	update_sector_data(t_env *env, int start, int end, t_sector *sector)
{
	int	i;

	i = end - 1;
	
	while (i > start)
	{
		update_neighbors(env, i, sector->vertices[i], sector);
		update_int_tab(i, (int)sector->nb_vertices + 1, &env->sectors[sector->num].vertices);
		update_int_tab(i, (int)sector->nb_vertices + 1, &env->sectors[sector->num].textures);
		update_double_tab(i, sector->nb_vertices + 1, &env->sectors[sector->num].floors);
		update_double_tab(i, sector->nb_vertices + 1, &env->sectors[sector->num].ceilings);
		update_double_tab(i, sector->nb_vertices + 1, &env->sectors[sector->num].clipped_floors1);
		update_double_tab(i, sector->nb_vertices + 1, &env->sectors[sector->num].clipped_floors2);
		update_double_tab(i, sector->nb_vertices + 1, &env->sectors[sector->num].clipped_ceilings1);
		update_double_tab(i, sector->nb_vertices + 1, &env->sectors[sector->num].clipped_ceilings2);
		update_double_tab(i, sector->nb_vertices + 1, &env->sectors[sector->num].wall_width);
		sector->nb_vertices--;
		i--;
	}
	clear_portals(env);
	i = 0;
	while (i < env->nb_sectors)
	{
		create_portals(env, env->sectors[i]);
		i++;
	}
}

void	copying_original_sector_data(t_env *env)
{
	int	origin;
	int	new;
	int	i;

	i = 0;
	origin = env->editor.split.sector;
	new = env->nb_sectors - 1;
	while (i < env->sectors[new].nb_vertices)
	{
		env->sectors[new].textures[i] = env->sectors[origin].textures[0];
		i++;
	}
	env->sectors[new].ceiling_texture = env->sectors[origin].ceiling_texture;
	env->sectors[new].floor_texture = env->sectors[origin].floor_texture;
	env->sectors[new].floor = env->sectors[origin].floor;
	env->sectors[new].floor_slope = env->sectors[origin].floor_slope;
	env->sectors[new].ceiling = env->sectors[origin].ceiling;
	env->sectors[new].ceiling_slope = env->sectors[origin].ceiling_slope;
}

int		create_new_sector(t_env *env, int start, int end, t_sector *sector)
{
	int	i;

	i = start;
	while (i <= end)
	{
		add_vertex_to_current_sector(env, (int)sector->vertices[i]);
		i++;
	}
	env->editor.reverted = get_clockwise_order(env) ? 0 : 1;
	env->editor.start_vertex = -1;
	if (add_sector(env))
		return (ft_printf("Error while creating new sector\n"));
	copying_original_sector_data(env);
	return (0);
}

void	split_sector(t_env *env)
{
	int			i;
	int			start;
	int			end;
	t_sector	*sector;

	i = 0;
	start = -1;
	end = -1;
	sector = &env->sectors[env->editor.split.sector];
	while (i < sector->nb_vertices)
	{
		if (start == -1 && (sector->vertices[i] == env->editor.split.v1
		|| sector->vertices[i] == env->editor.split.v2))
			start = i;
		else if (start != -1 && (sector->vertices[i] == env->editor.split.v1
		|| sector->vertices[i] == env->editor.split.v2))
			end = i;
		i++;
	}
	free_current_vertices(env);
	create_new_sector(env, start, end, sector);
	sector = &env->sectors[env->editor.split.sector];
	free_current_vertices(env);
	update_sector_data(env, start, end , sector);
	env->editor.split.sector = -1;
	env->editor.split.v1 = -1;
	env->editor.split.v2 = -1;
	env->editor.divide_sector = 0;
}
