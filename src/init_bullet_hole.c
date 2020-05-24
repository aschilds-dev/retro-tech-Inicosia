/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bullet_hole.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 11:46:54 by lnicosia          #+#    #+#             */
/*   Updated: 2020/04/30 11:46:55 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	init_bullet_hole(t_env *env)
{
	env->object_sprites[26].texture = env->wall_sprites_start;
	env->object_sprites[26].death_counterpart = 3;
	env->object_sprites[26].pursuit_sprite = 3;
	env->object_sprites[26].rest_sprite = 26;
	env->object_sprites[26].curr_sprite = 0;
	env->object_sprites[26].oriented = 0;
	env->object_sprites[26].nb_death_sprites = 0;
	env->object_sprites[26].start[0].x = 0;
	env->object_sprites[26].start[0].y = 0;
	env->object_sprites[26].end[0].x = 600;
	env->object_sprites[26].end[0].y = 600;
	env->object_sprites[26].size[0].x = 600;
	env->object_sprites[26].size[0].y = 600;
	env->object_sprites[26].reversed[0] = 0;
}
