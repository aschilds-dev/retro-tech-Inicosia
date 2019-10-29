/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleporter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 14:36:18 by sipatry           #+#    #+#             */
/*   Updated: 2019/10/29 14:13:44 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	create_teleport(t_env *env)
{
	t_v3	futur_pos;
	
	env->teleport.create = 1;
	futur_pos.x = env->teleport.tmp_pos.x;
	futur_pos.y = env->teleport.tmp_pos.y;
	futur_pos.z = 0;
	ft_printf("x: %f | y: %f\n", env->teleport.tmp_pos.x, env->teleport.tmp_pos.y);
	env->teleport.sector = 0;
	if ((env->teleport.sector = get_sector_no_z(env, futur_pos)) != -1)
	{
		ft_printf("tp created | sector od destination: %d\n", env->teleport.sector);
		futur_pos.y = env->sectors[env->teleport.sector].floor;
		env->sectors[env->editor.selected_sector].tp.x = futur_pos.x;
		env->sectors[env->editor.selected_sector].tp.y = futur_pos.y;
		env->sectors[env->editor.selected_sector].tp.y = futur_pos.y;
	}
	else
	{
		env->sectors[env->editor.selected_sector].status = 0;
		ft_printf("Destination is outside of the map\n");
	}
	env->teleport.create = 0;
}

void	activate_teleport(t_env *env)
{	
	ft_printf("teleporting sir\n");
	env->player.pos.x = env->sectors[env->player.sector].tp.x;
	env->player.pos.y = env->sectors[env->player.sector].tp.y;
	env->player.pos.z = env->sectors[env->player.sector].tp.z;
	env->player.sector = env->teleport.sector;
	update_camera_position(&env->player.camera);
}