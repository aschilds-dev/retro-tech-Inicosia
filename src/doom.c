/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:39:16 by sipatry           #+#    #+#             */
/*   Updated: 2020/04/29 16:05:15 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "collision.h"
#include "events.h"

int		doom4(t_env *env)
{
	if (env->menu && !env->in_game && !env->option)
		start_game_menu(env);
	else
	{
		if (env->option)
		{
			option_menu_ig(env);
		}
		else if (draw_game(env))
			return (ft_printf("Crash in game loop\n"));
	}
	return (0);
}

int		doom3(t_env *env)
{
	if (env->player.health <= 0)
		death(env);
	if (env->confirmation_box.state)
	{
		if (confirmation_box_keys(&env->confirmation_box, env))
			return (crash("Crash from a confirmation box\n", env));
	}
	return (0);
}

int		doom_events(t_env *env)
{
	if (env->events)
	{
		if (pop_events(env))
			return (crash("Events failed\n", env));
	}
	if (launch_events(env))
		return (crash("Events Failed\n", env));
	return (0);
}

int		doom2(t_env *env)
{
	update_sprites_state(env);
	if (projectiles_movement(env))
		return (crash("Projectile creation or impact creation failed\n", env));
	if (!env->confirmation_box.state)
	{
		if (enemy_ai(env))
			return (-1);
		objects_collision(env, env->player.pos);
		if (explosion_collision_objects(env))
			return (-1);
		if (explosion_collision_enemies(env))
			return (-1);
		if (explosion_collision_player(env))
			return (-1);
		if (enemy_melee_hit(env))
			return (crash("Collision with a melee enemy failed\n", env));
		player_combat_state(env);
		if (keys(env))
			return (crash("Keys failed\n", env));
	}
	if (doom_events(env))
		return (-1);
	return (0);
}

int		doom(t_env *env)
{
	if (env->in_game && !env->menu && !env->option && first_frame(env))
		return (crash("First frame failed\n", env));
	while (env->running)
	{
		reset_clipped(env);
		clear_image(env);
		SDL_GetRelativeMouseState(&env->sdl.mouse_x, &env->sdl.mouse_y);
		SDL_GetMouseState(&env->sdl.mx, &env->sdl.my);
		if (env->in_game && !env->menu & !env->option)
		{
			if (doom_poll_event(env))
				return (crash("", env));
			if (doom2(env))
				return (crash("", env));
			if (doom3(env))
				return (crash("", env));
		}
		if (doom4(env))
			return (crash("", env));
		FMOD_System_Update(env->sound.system);
	}
	free_all(env);
	return (0);
}
