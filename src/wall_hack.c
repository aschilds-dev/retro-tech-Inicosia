/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_hack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:00:56 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/01 12:00:56 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "draw.h"

/*
**	Shows enemies hitboxes (event through walls)
*/

void	wall_hack(t_env *env)
{
	int i;

	i = 0;
	while (i < env->nb_enemies)
	{
		if (env->enemies[i].exists)
		{
			draw_line(new_point(env->enemies[i].left, env->enemies[i].top),
			new_point(env->enemies[i].right, env->enemies[i].top), env,
			0xFF00FF00);
			draw_line(new_point(env->enemies[i].right, env->enemies[i].top),
			new_point(env->enemies[i].right, env->enemies[i].bottom), env,
			0xFF00FF00);
			draw_line(new_point(env->enemies[i].right, env->enemies[i].bottom),
			new_point(env->enemies[i].left, env->enemies[i].bottom), env,
			0xFF00FF00);
			draw_line(new_point(env->enemies[i].left, env->enemies[i].bottom),
			new_point(env->enemies[i].left, env->enemies[i].top), env,
			0xFF00FF00);
		}
		i++;
	}
}
