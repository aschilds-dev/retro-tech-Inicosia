/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectiles_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:40:42 by gaerhard          #+#    #+#             */
/*   Updated: 2020/02/05 19:13:07 by gaerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "utils.h"

t_projectile_data	new_projectile_data(t_v3 pos, double angle, double scale,
int sprite)
{
	t_projectile_data new;

	new.pos = pos;
	new.angle = angle;
	new.scale = scale;
	new.sprite = sprite;
	return (new);
}

t_projectile_stats	new_projectile_stats(double size_2d, int damage,
double speed, double height)
{
	t_projectile_stats new;

	new.size_2d = size_2d;
	new.speed = speed;
	new.damage = damage;
	new.height = height;
	return (new);
}

t_projectile_data_2	new_projectile_data_2(double angle_z, double radius,
int hurts_player, int hurts_enemies)
{
	t_projectile_data_2	new;

	new.angle_z = angle_z;
	new.radius = radius;
	new.hurts_player = hurts_player;
	new.hurts_enemies = hurts_enemies;
	return (new);
}
