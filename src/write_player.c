/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 11:52:29 by lnicosia          #+#    #+#             */
/*   Updated: 2019/09/06 11:59:34 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "save.h"

void	write_player(int fd, t_env *env)
{
	ft_dprintf(fd, "\n%.3f %.3f %d\n",
			env->player.pos.y, env->player.pos.x,
			(int)(env->player.angle * CONVERT_DEGREES) % 360);
}
