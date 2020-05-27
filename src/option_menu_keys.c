/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_menu_keys.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:10:33 by gaerhard          #+#    #+#             */
/*   Updated: 2020/05/14 19:20:26 by gaerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		option_menu_ig_keys(t_env *env)
{
	if (button_keys(&env->return_button, env))
		return (-1);
	if (button_keys(&env->exit_button, env))
		return (-1);
	if (button_keys(&env->music_vol_down, env))
		return (-1);
	if (button_keys(&env->music_vol_up, env))
		return (-1);
	if (button_keys(&env->sounds_vol_up, env))
		return (-1);
	if (button_keys(&env->sounds_vol_down, env))
		return (-1);
	if (button_keys(&env->fps_option, env))
		return (-1);
	return (0);
}

int		option_menu_ig_keyup(t_env *env)
{
	if (button_keyup(&env->return_button, env))
		return (-1);
	if (button_keyup(&env->exit_button, env))
		return (-1);
	if (button_keyup(&env->music_vol_down, env))
		return (-1);
	if (button_keyup(&env->music_vol_up, env))
		return (-1);
	if (button_keyup(&env->sounds_vol_up, env))
		return (-1);
	if (button_keyup(&env->sounds_vol_down, env))
		return (-1);
	if (button_keyup(&env->fps_option, env))
		return (-1);
	if (env->sdl.event.key.keysym.sym == SDLK_o)
	{
		env->option = 0;
		if (env->in_game)
			SDL_SetRelativeMouseMode(1);
	}
	return (0);
}
