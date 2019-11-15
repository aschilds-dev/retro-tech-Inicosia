/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectiles_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 11:40:42 by gaerhard          #+#    #+#             */
/*   Updated: 2019/11/15 16:14:38 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "utils.h"

t_projectile_data		new_projectile_data(t_v3 pos, double angle, double scale, int sprite)
{
	t_projectile_data new;

	new.pos = pos;
	new.angle = angle;
	new.scale = scale;
	new.sprite = sprite;
	return (new);
}

t_projectile_stats		new_projectile_stats(double size_2d, int damage, double speed)
{
	t_projectile_stats new;

	new.size_2d = size_2d;
	new.speed = speed;
	new.damage = damage;
	return (new);
}