/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_vertex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 11:53:28 by sipatry           #+#    #+#             */
/*   Updated: 2020/02/25 16:05:14 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <math.h>

int		del_last_vertex2(t_env *env)
{
	t_list		*tmp;
	t_vertex	*v;

	tmp = env->editor.current_vertices;
	while (tmp && tmp->next && tmp->next->next)
		tmp = tmp->next;
	v = (t_vertex*)tmp->next->content;
	if (!is_vertex_used(env, v->num))
	{
		env->editor.selected_vertex = v->num;
		if (delete_vertex(env))
			return (-1);
	}
	ft_memdel((void**)&tmp->next->content);
	tmp->next->content = NULL;
	ft_memdel((void**)&tmp->next);
	tmp->next = NULL;
	return (0);
}

int		del_last_vertex(t_env *env)
{
	t_vertex	*v;

	if (!env->editor.current_vertices)
		return (0);
	if (!env->editor.current_vertices->next)
	{
		v = (t_vertex*)env->editor.current_vertices->content;
		if (!is_vertex_used(env, v->num))
		{
			env->editor.selected_vertex = v->num;
			if (delete_vertex(env))
				return (-1);
		}
		ft_memdel((void**)&env->editor.current_vertices->content);
		ft_memdel((void**)&env->editor.current_vertices);
		env->editor.current_vertices = NULL;
		env->editor.start_vertex = -1;
		return (0);
	}
	return (del_last_vertex2(env));
}

void	free_current_vertices(t_env *env)
{
	t_list	*tmp;

	while (env->editor.current_vertices)
	{
		tmp = env->editor.current_vertices;
		env->editor.current_vertices = env->editor.current_vertices->next;
		ft_memdel(&tmp->content);
		ft_memdel((void**)&tmp);
		tmp = NULL;
	}
}

int		add_vertex_to_current_sector(t_env *env, int num)
{
	t_list	*new;

	if (!(new = ft_lstnew(&env->vertices[num], sizeof(t_vertex))))
		return (ft_perror("Error when creating new vertex\n"));
	ft_lstpushback(&env->editor.current_vertices, new);
	return (0);
}

int		add_vertex(t_env *env)
{
	t_vertex	vertex;

	vertex.num = env->nb_vertices;
	vertex.x = round((env->sdl.mx - env->editor.center.x) / env->editor.scale);
	vertex.y = round((env->sdl.my - env->editor.center.y) / env->editor.scale);
	if (!(env->vertices = (t_vertex*)ft_realloc(env->vertices,
		sizeof(t_vertex) * env->nb_vertices,
		sizeof(t_vertex) * (env->nb_vertices + 1))))
		return (ft_perror("Could not realloc vertices\n"));
	env->vertices[env->nb_vertices] = vertex;
	env->nb_vertices++;
	return (0);
}
