/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_screen_sectors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 15:08:25 by lnicosia          #+#    #+#             */
/*   Updated: 2019/08/14 17:47:00 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		get_screen_sectors(t_env *env)
{
	int		size;
	t_v3	curr;
	double	tmp;
	int		sect;
	int		sect_count;
	int		x;
	int		i;
	double	camera_range;

	size = env->screen_sectors_size;
	x = 0;
	sect_count = 0;
	camera_range = env->camera.near_right - env->camera.near_left;
	while (x < env->w)
	{
		tmp = (x / (double)(env->w - 1)) * camera_range + env->camera.near_left;
		curr.y = -env->camera.near_z;
		curr.x = tmp * -env->player.angle_sin - curr.y * env->player.angle_cos + env->player.pos.x;
		curr.y = tmp * env->player.angle_cos - curr.y * env->player.angle_sin + env->player.pos.y;
		curr.z = env->player.head_z;
		env->screen_pos[x] = new_v2(curr.x, curr.y);
		i = 0;
		sect = get_sector(env, curr, env->player.sector);
		while (i < env->screen_sectors_size && env->screen_sectors[i] != -1 && env->screen_sectors[i] != sect)
			i++;
		if (i < env->screen_sectors_size && env->screen_sectors[i] == -1 && sect != -1)
		{
			env->screen_sectors[i] = sect;
			env->xmin[i] = x;
			sect_count++;
		}
		else if (i < env->screen_sectors_size && env->screen_sectors[i] == sect)
			env->xmax[i] = x;
		x++;
	}
	return (sect_count);
}
