/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:19:13 by lnicosia          #+#    #+#             */
/*   Updated: 2019/09/23 16:52:16 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "collision.h"

void	animations(t_env *env)
{
	if ((env->player.pos.z > env->sectors[env->player.highest_sect].floor
		|| env->player.state.fall)
		&& !env->player.state.climb && !env->player.state.drop)
		gravity(env);
	if ((env->inputs.space || env->player.state.jump)
		&& !env->player.state.climb && !env->player.state.drop)
		jump(env);
/*	if (((env->inputs.ctrl && env->player.eyesight == 6) || env->crouch.on_going) && !env->jump.on_going)
		crouch(env);*/
	env->player.camera.pos.z = env->player.head_z;
}

/*
 **	Handles player movements
 **	TODO Protection / return values??
 */

void	check_blocage(t_env *env, t_movement motion, int index)
{
	int nb;
	t_v2 move;
	static int a = 0;

	nb = 0;
	if (index != 1)
	{
		move = check_collision(env, new_v2(env->player.camera.angle_cos * env->player.speed, env->player.camera.angle_sin * env->player.speed), motion, 0);
		if (move.x == 0 && move.y == 0)
			nb++;
	}
	if (index != 2)
	{
		move = check_collision(env, new_v2(env->player.camera.angle_cos * -env->player.speed, env->player.camera.angle_sin * -env->player.speed), motion, 0);
		if (move.x == 0 && move.y == 0)
			nb++;
	}
	if (index != 3)
	{
		move = check_collision(env, new_v2(env->player.camera.angle_sin * env->player.speed, env->player.camera.angle_cos * -env->player.speed), motion, 0);
		if (move.x == 0 && move.y == 0)
			nb++;
	}
	if (index != 4)
	{
		move = check_collision(env, new_v2(env->player.camera.angle_sin * -env->player.speed, env->player.camera.angle_cos * env->player.speed), motion, 0);
		if (move.x == 0 && move.y == 0)
			nb++;
	}
	if (nb == 3)
		ft_printf("I'm stuck .... . .-.. .--.   ... --- ...%d\n", a++);
}

void	move_player(t_env *env)
{
	int			movement;
	t_movement	motion;
	t_v2		move;

	movement = 0;
	env->time.end = env->time.milli_s / 10;
	if (env->time.end - env->time.start >= 1)
	{
		env->time.start = env->time.end;
		motion = new_movement(env->player.sector, env->player.size_2d, env->player.eyesight, env->player.pos);
		if (env->inputs.forward && !env->inputs.backward)
		{
			move = check_collision(env, new_v2(env->player.camera.angle_cos * env->player.speed, env->player.camera.angle_sin * env->player.speed), motion, 0);
			env->player.pos.x += move.x;
			env->player.pos.y += move.y;
			if (move.x != 0 || move.y != 0)
				movement = 1;
			if (move.x == 0 && move.y == 0)
				check_blocage(env, motion, 1);
		}
		else if (env->inputs.backward && !env->inputs.forward)
		{
			move = check_collision(env, new_v2(env->player.camera.angle_cos * -env->player.speed, env->player.camera.angle_sin * -env->player.speed), motion, 0);
				env->player.pos.x += move.x;
				env->player.pos.y += move.y;
				if (move.x != 0 || move.y != 0)
					movement = 1;
				if (move.x == 0 && move.y == 0)
					check_blocage(env, motion, 2);
		}
		if (env->inputs.left && !env->inputs.right)
		{
			move = check_collision(env, new_v2(env->player.camera.angle_sin * env->player.speed, env->player.camera.angle_cos * -env->player.speed), motion, 0);
				env->player.pos.x += move.x;
				env->player.pos.y += move.y;
				if (move.x != 0 || move.y != 0)
					movement = 1;
				if (move.x == 0 && move.y == 0)
					check_blocage(env, motion, 3);
		}
		else if (env->inputs.right && !env->inputs.left)
		{
			move = check_collision(env, new_v2(env->player.camera.angle_sin * -env->player.speed, env->player.camera.angle_cos * env->player.speed), motion, 0);
			env->player.pos.x += move.x;
			env->player.pos.y += move.y;
			if (move.x != 0 || move.y != 0)
				movement = 1;
			if (move.x == 0 && move.y == 0)
					check_blocage(env, motion, 4);
		}
		if (!movement && (env->player.state.climb || env->player.state.drop))
			movement = 1;
		if (movement)
		{
			env->player.sector = get_sector_no_z_origin(env, env->player.pos, env->player.sector);
			if (find_highest_sector(env, motion) != env->player.highest_sect
			&& env->sectors[find_highest_sector(env, motion)].floor < env->sectors[env->player.highest_sect].floor)
				env->player.drop_flag = 1;
			env->player.highest_sect = find_highest_sector(env, motion);
			env->player.lowest_sect = find_lowest_sector(env, motion);
			env->player.camera.pos = env->player.pos;
			env->player.camera.pos.z = env->player.head_z;
			if (((env->sectors[env->player.highest_sect].floor > env->player.pos.z
			&& env->sectors[env->player.highest_sect].floor - env->player.pos.z <= 2)
			|| (env->player.state.climb))
			&& !env->player.state.drop && !env->player.state.jump)
				climb(env);
			else if ((((env->sectors[env->player.highest_sect].floor < env->player.pos.z
			&& env->player.pos.z - env->sectors[env->player.highest_sect].floor <= 2)
			|| env->player.state.drop)
			&& !env->player.state.jump && !env->player.state.fall && !env->player.state.climb)
			&& env->player.drop_flag)
				drop(env);
			else if (!env->player.state.climb && !env->player.state.jump
			&& !env->player.state.drop && !env->player.state.fall)
				update_player_z(env);
			env->player.head_z = env->player.pos.z + env->player.eyesight;
			update_camera_position(&env->player.camera);
		}
	}
}
