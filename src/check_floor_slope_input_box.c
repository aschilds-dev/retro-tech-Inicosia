/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_floor_slope_input_box.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 16:08:13 by lnicosia          #+#    #+#             */
/*   Updated: 2020/04/30 16:08:14 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		check_floor_slope_input_box(void *penv)
{
	t_env		*env;
	double		prec;
	t_sector	*sector;

	env = (t_env*)penv;
	if (env->editor.selected_sector != -1)
		sector = &env->sectors[env->editor.selected_sector];
	else
		sector = &env->sectors[env->selected_floor];
	prec = sector->floor_slope;
	sector->floor_slope = ft_atof(env->input_box.str);
	update_sector_slope(env, sector);
	if (sector->floor_max > sector->ceiling_min
		|| check_entities_height(env))
	{
		sector->floor_slope = prec;
		update_sector_slope(env, sector);
		update_player_z(env);
		update_start_player_z(env);
		return (1);
	}
	return (0);
}
