/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:26:04 by sipatry           #+#    #+#             */
/*   Updated: 2019/07/25 11:00:25 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	init_edit(t_env *env)
{
	env->edit.menu = 0;
	env->edit.select_mode = 0;
	env->edit.nb_vertex =  0;
	env->edit.center.x = env->h_w;
	env->edit.center.y = env->h_h;
	env->edit.scale = 20;
	env->edit.vertices = NULL;
}
