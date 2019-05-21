/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:19:13 by lnicosia          #+#    #+#             */
/*   Updated: 2019/05/21 17:25:26 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "collision.h"

/*
 **	Returns camera sector according to the last player movement
 */

int		get_sector(t_env *env, t_v2 p)
{
	int		i;

	if (is_in_sector(env, env->player.sector, p.x, p.y))
		return (env->player.sector);
	i = 0;
	while (i < env->sectors[env->player.sector].nb_vertices)
	{
		if (env->sectors[env->player.sector].neighbors[i] >= 0)
		{
			if (is_in_sector(env, env->sectors[env->player.sector].neighbors[i], p.x, p.y))
				return (env->sectors[env->player.sector].neighbors[i]);
		}
		i++;
	}
	i = 0;
	while (i < env->nb_sectors)
	{
		if (is_in_sector(env, i, p.x, p.y) && env->player.pos.z > env->sectors[i].floor_min)
			return (i);
		i++;
	}
	return (-1);
}

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

/*
 ** Contains calculs to allow a jump
 */
void	jump(t_env *env, t_sector sector, t_vertex v0)
{
	double	x;
	double	player_feet;
	double	tmp_height;
	
	x = 0.5;
	player_feet = sector.floor + (sector.normal.x * (env->player.pos.x - v0.x) - sector.normal.y * (env->player.pos.y - v0.y)) * sector.floor_slope;
	tmp_height = env->player.eyesight + player_feet;
	env->jump.on_going = 1;
	if (env->jump.start == 0)
		env->jump.start = SDL_GetTicks();
	env->jump.end = SDL_GetTicks();
	if (env->jump.end < env->jump.start + 150 && env->flag == 0)
	{
		env->player.eyesight += x;
		tmp_height = env->player.eyesight + player_feet;
	}
	if (env->jump.end > env->jump.start + 150 && env->flag == 0)
		env->flag = 1;
	if (env->player.eyesight > env->player.z && env->flag == 1)
	{
		env->player.eyesight -= x * env->player.gravity;
		tmp_height = env->player.eyesight + player_feet;
	}
	if (env->player.eyesight == env->player.z && env->jump.end > env->jump.start + 400)
	{
		env->flag = 0;
		env->jump.start = 0;
		env->jump.on_going = 0;
	}
	env->player.pos.z = env->player.eyesight + player_feet;
	//env->player.pos.z = tmp_height;
}

void	squat(t_env *env, t_sector sector, t_vertex v0)
{
	env->squat.on_going = 1;
	if (env->flag == 0 && env->squat.on_going)
	{
		env->player.z -= 0.5;
		if (env->player.eyesight > 3)
			env->player.eyesight -= 0.5;
		if (env->player.eyesight == 3)
		{
			env->flag = 1;
			env->squat.on_going = 0;
		}
	}
	else if (env->flag == 1 && env->squat.on_going && !env->inputs.ctrl)
	{
		env->player.z = 6;
		if (env->player.eyesight < env->player.z)
			env->player.eyesight += 0.5;
		if (env->player.eyesight == env->player.z)
		{
			env->flag = 0;
			env->squat.on_going = 0;
		}
	}
	// player height: eyesight + the floors height
	env->player.pos.z = env->player.eyesight + sector.floor + (sector.normal.x * (env->player.pos.x - v0.x) - sector.normal.y * (env->player.pos.y - v0.y)) * sector.floor_slope;
}

/*
 **	Handles player movements
 **	TODO Protection / return values??
 */


void	move_player(t_env *env)
{
	t_sector	sector;
	t_vertex	v0;
	t_v3		origin_pos;
	short		origin_camera_sect;
	short		origin_left_sect;
	short		origin_right_sect;
	short		origin_sect;
	double		tmp_speed;
	int			movement;

	tmp_speed = env->player.speed;
	sector = env->sectors[env->player.sector];
	movement = 0;
	origin_pos = env->player.pos;
	origin_sect = env->player.sector;
	origin_camera_sect = env->player.camera_sector;
	origin_right_sect = env->player.near_left_sector;
	origin_left_sect = env->player.near_right_sector;
	if (env->inputs.forward)
	{	
		if (check_collision(env, env->player.angle_cos * env->player.speed, env->player.angle_sin * env->player.speed) == 1)
		{
			env->player.pos.x += env->player.angle_cos * env->player.speed;
			env->player.pos.y += env->player.angle_sin * env->player.speed;
			movement = 1;
		}
	}
	if (env->inputs.backward)
	{
		if (check_collision(env, env->player.angle_cos * -env->player.speed, env->player.angle_sin * -env->player.speed) == 1)
		{
			env->player.pos.x -= env->player.angle_cos * env->player.speed;
			env->player.pos.y -= env->player.angle_sin * env->player.speed;
			movement = 1;
		}
	}
	if (env->inputs.left)
	{
		if (check_collision(env, env->player.angle_sin * env->player.speed, env->player.angle_cos * -env->player.speed) == 1)
		{
			env->player.pos.x += env->player.angle_sin * env->player.speed;
			env->player.pos.y -= env->player.angle_cos * env->player.speed;
			movement = 1;
		}
	}
	if (env->inputs.right)
	{
		if (check_collision(env, env->player.angle_sin * -env->player.speed, env->player.angle_cos * env->player.speed) == 1)
		{
			env->player.pos.x -= env->player.angle_sin * env->player.speed;
			env->player.pos.y += env->player.angle_cos * env->player.speed;
			movement = 1;
		}
	}
	if (movement)
	{
		update_camera_position(env);
		env->player.camera_sector = get_sector(env, new_v2(env->player.camera_x, env->player.camera_y));
		env->player.near_left_sector = get_sector(env, new_v2(env->player.near_left.x, env->player.near_left.y));
		env->player.near_right_sector = get_sector(env, new_v2(env->player.near_right.x, env->player.near_right.y));
		if (env->player.near_left_sector == -1 || env->player.near_right_sector == -1)
		{
			env->player.pos = origin_pos; 
			env->player.sector = origin_sect;
			env->player.camera_sector = origin_camera_sect;
			env->player.near_left_sector = origin_left_sect;
			env->player.near_right_sector = origin_right_sect;
		}
	}
	if (env->inputs.space || env->jump.on_going == 1)
	{
		v0 = env->vertices[sector.vertices[0]];
		jump(env, sector, v0);
	}
	if (env->inputs.ctrl || env->squat.on_going == 1 || (env->flag == 1 && !env->inputs.ctrl))
	{
		v0 = env->vertices[sector.vertices[0]];
		squat(env, sector, v0);
	}
	else
	{
		v0 = env->vertices[sector.vertices[0]];
		env->player.pos.z = env->player.eyesight + sector.floor + (sector.normal.x * (env->player.pos.x - v0.x) - sector.normal.y * (env->player.pos.y - v0.y)) * sector.floor_slope;
	}
	env->player.speed = tmp_speed;
	sector = env->sectors[env->player.sector];
}
