/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:07:41 by lnicosia          #+#    #+#             */
/*   Updated: 2019/07/29 15:07:43 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int			editor_keys(t_env *env)
{
	int		clicked_vertex;

	if (env->inputs.space)
	{
		clicked_vertex = get_existing_vertex(env);
		if (clicked_vertex == -1)
		{
			if (add_vertex(env))
				return (ft_printf("Could not add new vertex\n"));
			if (!env->editor.new_sector) //Nouveau secteur
				env->editor.new_sector = 1;
			add_vertex_to_current_sector(env, env->nb_vertices - 1);
		}
		else
		{
			if (!env->editor.new_sector)
			{
				env->editor.new_sector = 1;
				add_vertex_to_current_sector(env, clicked_vertex);
			}
			else
			{
				if (clicked_vertex == ((t_vertex*)env->editor.current_vertices->content)->num)
				{
					if (!get_clockwise_order(env))
						env->editor.reverted = 1;
					else
						env->editor.reverted = 0;
					env->editor.new_sector = 0;
					/*if (create_sector(env))
						return (ft_printf("Error while creating new sector\n"));*/
					free_current_vertices(env);
				}
				else
					add_vertex_to_current_sector(env, clicked_vertex);
			}
		}
		env->inputs.space = 0;
	}
	if (env->inputs.right_click)
	{
		env->editor.center.x += env->sdl.mouse_x;
		env->editor.center.y += env->sdl.mouse_y;
	}
	return (0);
}
