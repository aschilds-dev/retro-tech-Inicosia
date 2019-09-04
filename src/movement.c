/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:19:13 by lnicosia          #+#    #+#             */
/*   Updated: 2019/08/28 14:29:48 by gaerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "collision.h"

/*
 **	Update camera's position (save some computings)
 */

void	update_camera_position(t_env *env)
{
	env->player.camera_x = env->player.pos.x + env->player.angle_cos * env->camera.near_z;
	env->player.camera_y = env->player.pos.y + env->player.angle_sin * env->camera.near_z;
	env->player.near_left.x = env->player.pos.x + (env->player.angle_cos * env->camera.near_z - env->player.angle_sin * env->camera.near_left);
	env->player.near_left.y = env->player.pos.y + (env->player.angle_sin * env->camera.near_z + env->player.angle_cos * env->camera.near_left);
	env->player.near_right.x = env->player.pos.x + (env->player.angle_cos * env->camera.near_z - env->player.angle_sin * env->camera.near_right);
	env->player.near_right.y = env->player.pos.y + (env->player.angle_sin * env->camera.near_z + env->player.angle_cos * env->camera.near_right);
}

void	animations(t_env *env)
{
	update_floor(env);
	if (env->gravity.on_going)
		gravity(env);
	if (((env->inputs.space && !env->player.state) || env->jump.on_going))
		jump(env);
	if (((env->inputs.ctrl && !env->player.state && env->player.eyesight == 6) || env->crouch.on_going) && !env->jump.on_going)
		crouch(env);
}

/*
 **	Handles player movements
 **	TODO Protection / return values??
 */

void	move_player(t_env *env)
{
	int			movement;

	movement = 0;
	env->time.end = env->time.milli_s / 10;
	if (env->time.end - env->time.start >= 1)
	{
		env->time.start = env->time.end;
		if (env->inputs.forward && !env->inputs.backward)
		{	
			if (check_collision(env, env->player.angle_cos * env->player.speed, env->player.angle_sin * env->player.speed))
			{
				env->player.pos.x += env->player.angle_cos * env->player.speed;
				env->player.pos.y += env->player.angle_sin * env->player.speed;
				movement = 1;
			}
		}
		else if (env->inputs.backward && !env->inputs.forward)
		{
			if (check_collision(env, env->player.angle_cos * -env->player.speed, env->player.angle_sin * -env->player.speed))
			{
				env->player.pos.x -= env->player.angle_cos * env->player.speed;
				env->player.pos.y -= env->player.angle_sin * env->player.speed;
				movement = 1;
			}
		}
		if (env->inputs.left && !env->inputs.right)
		{
			if (check_collision(env, env->player.angle_sin * env->player.speed, env->player.angle_cos * -env->player.speed))
			{
				env->player.pos.x += env->player.angle_sin * env->player.speed;
				env->player.pos.y -= env->player.angle_cos * env->player.speed;
				movement = 1;
			}
		}
		else if (env->inputs.right && !env->inputs.left)
		{
			if (check_collision(env, env->player.angle_sin * -env->player.speed, env->player.angle_cos * env->player.speed))
			{
				env->player.pos.x -= env->player.angle_sin * env->player.speed;
				env->player.pos.y += env->player.angle_cos * env->player.speed;
				movement = 1;
			}
		}
		if (movement)
		{
			update_camera_position(env);
		}
	}
}
