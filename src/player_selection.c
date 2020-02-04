/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_selection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:35:07 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/03 15:31:37 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "collision.h"

void	player_selection(t_env *env)
{
	if (env->inputs.left_click && env->editor.dragged_player == 1)
	{
		env->player.pos.x = (env->sdl.mx - env->editor.center.x)
		/ env->editor.scale;
		env->player.pos.y = (env->sdl.my - env->editor.center.y)
		/ env->editor.scale;
		env->player.sector = get_sector_no_z_origin(env, env->player.pos,
		env->player.sector);
		if (env->player.sector != -1)
			update_player_z(env);
	}
	else
		env->editor.dragged_player = -1;
}
