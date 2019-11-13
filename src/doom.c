/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 17:59:58 by lnicosia          #+#    #+#             */
/*   Updated: 2019/11/13 14:26:54 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "collision.h"

int		doom(t_env *env)
{
	while (env->running)
	{
		if (env->player.sector == -1)
			ft_printf("Rip :/ \n");
		Mix_VolumeMusic(MIX_MAX_VOLUME/env->sound.g_music);
		reset_clipped(env);
		clear_image(env);
		SDL_GetRelativeMouseState(&env->sdl.mouse_x, &env->sdl.mouse_y);
		SDL_GetMouseState(&env->sdl.mx, &env->sdl.my);
		while (SDL_PollEvent(&env->sdl.event))
		{
			if (env->sdl.event.type == SDL_QUIT || (env->sdl.event.type == SDL_KEYUP && env->sdl.event.key.keysym.sym == SDLK_ESCAPE))
				env->running = 0;
			else if (env->sdl.event.type == SDL_KEYDOWN
					|| env->sdl.event.type == SDL_KEYUP || env->sdl.event.type == SDL_MOUSEBUTTONDOWN
					|| env->sdl.event.type == SDL_MOUSEBUTTONUP || env->sdl.event.type == SDL_MOUSEWHEEL)
				update_inputs(env);
			if (env->sdl.event.type == SDL_KEYUP || env->sdl.event.type == SDL_MOUSEBUTTONUP)
				keyup(env);
			if (env->sdl.event.type == SDL_MOUSEWHEEL && !env->weapon_change.on_going && !env->shot.on_going && env->player.health > 0)
				weapon_change(env);
		}
		update_sprites_state(env);
		if (env->player.health > 0)
		{
			enemy_ai(env);
			objects_collision(env);
			enemy_collision(env);
			keys(env);
		}
		if (env->player.health <= 0)
			death(env);
		if (env->confirmation_box.state)
			confirmation_box_keys(&env->confirmation_box, env);
		if (env->events)
				pop_events(env);
		if (env->menu_start)
			start_game_menu(env);
		else
		{
			if (env->option)
			{
				if (open_options(env))
					return (crash("Could not process options pannel\n", env));
			}
			else if (draw_game(env))
				return (ft_printf("Crash in game loop\n"));
		}
	}
	ft_printf("User quit the game\n");
	free_all(env);
	return (0);
}
