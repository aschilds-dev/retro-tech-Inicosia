/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 15:35:23 by lnicosia          #+#    #+#             */
/*   Updated: 2019/08/26 15:43:52 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
**	Returns 0 if the given vertex does not belong to any sector
*/

int		is_vertex_used_by_others(t_env *env, int vertex, int sector)
{
	int	i;
	int	j;

	i = 0;
	while (i < env->nb_sectors)
	{
		if (i != sector)
		{
			j = 0;
			while (j < env->sectors[i].nb_vertices)
			{
				if (env->sectors[i].vertices[j] == vertex)
					return (1);
				j++;
			}
		}
		i++;
	}
	return (0);
}

/*
**	Returns 0 if the given vertex does not belong to any sector
*/

int		is_vertex_used(t_env *env, int vertex)
{
	int	i;
	int	j;

	i = 0;
	while (i < env->nb_sectors)
	{
		j = 0;
		while (j < env->sectors[i].nb_vertices)
		{
			if (env->sectors[i].vertices[j] == vertex)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/*
**	Returns 0 if the given vertex does not belong to the current sector
*/

int		current_vertices_contains(t_env *env, int vertex)
{
	t_list		*tmp;
	t_vertex	*v;

	tmp = env->editor.current_vertices;
	while (tmp)
	{
		v = (t_vertex*)tmp->content;
		if (v->num == vertex)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
