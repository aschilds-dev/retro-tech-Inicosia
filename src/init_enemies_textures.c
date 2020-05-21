/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies_textures.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/26 16:10:52 by marvin            #+#    #+#             */
/*   Updated: 2020/05/15 20:05:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "parser.h"

int	init_enemies_sprites_textures(t_env *env)
{
	int	start;

	start = env->enemies_start;
	if (parse_bmp("images/sprites/lost_soul.bmp", start + 0, env))
		return (custom_error("Failed to load lost soul\n"));
	if (parse_bmp("images/sprites/cyber_demon.bmp", start + 1, env))
		return (custom_error("Failed to load cyber"
		"demon sprite sheet\n"));
	return (0);
}
