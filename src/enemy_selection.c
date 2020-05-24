/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_selection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:03:44 by sipatry           #+#    #+#             */
/*   Updated: 2020/03/02 11:24:11 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "enemies.h"
#include "draw.h"

void	enemy_tab(t_env *env, int nb_slots)
{
	int mod;
	int	test;
	int	i;

	i = 0;
	test = nb_slots;
	if (nb_slots > 25)
		mod = 10;
	else
		mod = 5;
	while (test % mod != 0)
		test++;
	draw_rectangle(env,
				new_rectangle(0x00000000, 0xFF333333, 1, 5),
				env->editor.enemy_selection_pos,
				env->editor.enemy_selection_size);
	while (i < MAX_ENEMIES)
	{
		apply_sprite(env->enemy_sprites[env->enemies_main_sprites[i]],
		new_point(380 + 8 + (66 * (i / mod)),
			280 + 8 + (66 * (i % mod))), new_point(64, 64), env);
		i++;
	}
}
