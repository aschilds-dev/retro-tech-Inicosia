/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increase_texture_scales_functions.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 18:48:19 by sipatry           #+#    #+#             */
/*   Updated: 2020/02/11 18:51:40 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		increase_ceiling_texture_scale(t_env *env)
{
	t_sector *sector;

	sector = &env->sectors[env->selected_ceiling];
	if (env->inputs.shift && !env->inputs.ctrl)
	{
		sector->ceiling_map_scale.y *= 1.1;
		sector->ceiling_map_scale.x *= 1.1;
	}
	else if (env->inputs.ctrl)
		sector->ceiling_map_scale.y *= 1.1;
	else
		sector->ceiling_map_scale.x *= 1.1;
	if (set_sector_ceiling_map_array(sector,
	env->wall_textures[sector->ceiling_texture], env))
		return (-1);		
	return (0);
}

int		increase_floor_texture_scale(t_env *env)
{
	t_sector *sector;

	sector = &env->sectors[env->selected_floor];
	if (env->inputs.shift && !env->inputs.ctrl)
	{
		sector->floor_map_scale.y *= 1.1;
		sector->floor_map_scale.x *= 1.1;
	}
	else if (env->inputs.ctrl)
		sector->floor_map_scale.y *= 1.1;
	else
		sector->floor_map_scale.x *= 1.1;
	if (set_sector_floor_map_array(sector,
	env->wall_textures[sector->floor_texture],
	env))
		return (-1);
	return (0);
}

int		increase_wall_texture_scale(t_env *env)
{
	t_sector *sector;

	sector = &env->sectors[env->editor.selected_sector];
	if (env->inputs.shift && !env->inputs.ctrl)
	{
		sector->scale[env->editor.selected_wall].y *= 1.1;
		sector->scale[env->editor.selected_wall].x *= 1.1;
	}
	else if (env->inputs.ctrl)
		sector->scale[env->editor.selected_wall].y *= 1.1;
	else
		sector->scale[env->editor.selected_wall].x *= 1.1;
	if (set_sector_wall_map_array(sector,
	env->wall_textures[sector->textures[env->editor.selected_wall]],
	env->editor.selected_wall, env))
		return (-1);
	if (set_camera_map_array(&env->player.camera,
	env->editor.selected_sector, env->editor.selected_wall, env))
		return (-1);
	return (0);
}