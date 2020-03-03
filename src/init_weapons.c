/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapons.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 14:59:37 by gaerhard          #+#    #+#             */
/*   Updated: 2020/03/03 10:48:57 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** Weapon switch is only in the first weapon because it's common to every weapon
*/

void    init_weapons(t_env *env)
{
	env->weapons[0].name = "Rocket launcher";
	env->weapons[0].possessed = 1;
    env->weapons[0].weapon_switch = 0;
    env->weapons[0].first_sprite = 0;
    env->weapons[0].nb_sprites = 15;
	env->weapons[0].ammo_type = ROCKET;
    env->weapons[0].ammo = 20;
    env->weapons[0].damage = 125;
    env->weapons[0].max_ammo = 20;
    env->weapons[0].splash = 1;
    env->weapons[0].range = 25;
	env->weapons[0].sprite = env->object_sprites[31];


	env->weapons[1].name = "Raygun";
	env->weapons[1].possessed = 1;
    env->weapons[1].first_sprite = 15;
	env->weapons[1].ammo_type = ENERGY;
    env->weapons[1].nb_sprites = 7;
    env->weapons[1].ammo = 40;
    env->weapons[1].damage = 25;
    env->weapons[1].max_ammo = 40;
    env->weapons[1].range = 50;
    env->weapons[1].splash = 0;
	env->weapons[1].sprite = env->object_sprites[32];

	env->weapons[2].name = "Shotgun";
	env->weapons[2].possessed = 1;
	env->weapons[2].first_sprite = 0;
	env->weapons[2].nb_sprites = 15;
	env->weapons[2].ammo_type = SHELL;
	env->weapons[2].ammo = 25;
	env->weapons[2].damage = 125;
	env->weapons[2].max_ammo = 25;
	env->weapons[2].splash = 1;
	env->weapons[2].range = 30;
	env->weapons[2].sprite = env->object_sprites[31];
}
