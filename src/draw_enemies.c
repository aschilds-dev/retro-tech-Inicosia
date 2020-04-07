/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:50:05 by sipatry           #+#    #+#             */
/*   Updated: 2020/03/06 14:42:53 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void		update_enemies_z(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_enemies)
	{
		if (env->enemies[i].sector == env->sectors[env->selected_floor].num)
			env->enemies[i].pos.z =
			get_floor_at_pos(env->sectors[env->selected_floor],
			new_v3(env->enemies[i].pos.x, env->enemies[i].pos.y, 0), env);
		i++;
	}
}

int	get_enemy_direction2(t_enemy *enemy, double angle)
{
	if (angle < enemy->angle - 22.5 && angle >= enemy->angle - 67.5)
		return (3);
	else if (angle < enemy->angle - 67.5 && angle >= enemy->angle - 112.5)
		return (2);
	else if (angle < enemy->angle - 112.5 && angle >= enemy->angle - 157.5)
		return (1);
	else if (angle < enemy->angle - 157.5 && angle >= enemy->angle - 202.5)
		return (0);
	else if (angle < enemy->angle - 202.5 && angle >= enemy->angle - 247.5)
		return (7);
	else if (angle < enemy->angle - 247.5 && angle >= enemy->angle - 292.5)
		return (6);
	else if (angle < enemy->angle - 292.5 && angle >= enemy->angle - 337.5)
		return (5);
	else if (angle < enemy->angle - 337.5)
		return (4);
	else
		return (0);
}

int	get_enemy_direction(t_enemy *enemy)
{
	double	angle;

	angle = (int)((atan2(enemy->translated_pos.z, enemy->translated_pos.x))
	* CONVERT_DEGREES) % 360;
	if (angle < 0)
		angle += 360;
	if (angle >= enemy->angle - 22.5 && angle < enemy->angle + 22.5)
		return (4);
	else if (angle >= enemy->angle + 22.5 && angle < enemy->angle + 67.5)
		return (5);
	else if (angle >= enemy->angle + 67.5 && angle < enemy->angle + 112.5)
		return (6);
	else if (angle >= enemy->angle + 112.5 && angle < enemy->angle + 157.5)
		return (7);
	else if (angle >= enemy->angle + 157.5 && angle < enemy->angle + 202.5)
		return (0);
	else if (angle >= enemy->angle + 202.5 && angle < enemy->angle + 247.5)
		return (1);
	else if (angle >= enemy->angle + 247.5 && angle < enemy->angle + 292.5)
		return (2);
	else if (angle >= enemy->angle + 292.5 && angle < enemy->angle + 337.5)
		return (3);
	else if (angle >= enemy->angle + 337.5)
		return (4);
	else
	  	return(get_enemy_direction2(enemy, angle));
}

static int	threaded_get_relative_pos(t_camera *camera, t_env *env)
{
	int				i;
	t_enemy_thread	enemies_threads[THREADS];
	pthread_t		threads[THREADS];

	i = 0;
	while (i < THREADS)
	{
		enemies_threads[i].env = env;
		enemies_threads[i].camera = camera;
		enemies_threads[i].xstart = env->nb_enemies / (double)THREADS * i;
		enemies_threads[i].xend = env->nb_enemies / (double)THREADS * (i + 1);
		if (pthread_create(&threads[i], NULL, get_enemy_relative_pos,
		&enemies_threads[i]))
			return (-1);
		i++;
	}
	while (i-- > 0)
		if (pthread_join(threads[i], NULL))
			return (-1);
	return (0);
}

int			draw_current_enemy(t_camera *camera, int i, t_env *env)
{
	int dying_sprite;

	dying_sprite = -1;
	if (env->enemies[i].state == FIRING)
		enemy_firing_anim(env, i);
	if (env->enemies[i].rotated_pos.z > 1 && env->enemies[i].exists)
	{
		env->enemies[i].seen = 0;
		if (!env->editor.in_game)
		{
			if (env->enemies[i].health <= 0)
				dying_sprite = dying_enemy(env, i,
				env->enemy_sprites[env->enemies[i].sprite].nb_death_sprites);
			if (env->enemies[i].state == RESTING)
				resting_enemy(env, i);
			else if (env->enemies[i].state == PURSUING)
				pursuing_enemy(env, i);
		}
		if (env->enemies[i].exists)
			if (draw_enemy(camera, &env->enemies[i], env, dying_sprite))
				return (-1);
	}
	return (0);
}

int			draw_enemies(t_camera *camera, t_env *env)
{
	int	i;

	if (threaded_get_relative_pos(camera, env))
		return (-1);
	i = 0;
	while (i < env->nb_enemies)
	{
	  	if (draw_current_enemy(camera, i, env))
		  	return (-1);
		i++;
	}
	return (0);
}
