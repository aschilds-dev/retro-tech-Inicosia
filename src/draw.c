/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 15:50:14 by sipatry           #+#    #+#             */
/*   Updated: 2019/06/26 16:34:32 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	draw_game(t_env *env)
{
	SDL_GetRelativeMouseState(&env->sdl.mouse_x, &env->sdl.mouse_y);
	if (env->options.show_minimap)
		minimap(env);
	if (draw(env) != 0)
		return (crash("Render function failed\n", env));
	if ((env->inputs.leftclick && !env->shot.on_going && !env->weapon_change.on_going) || env->shot.on_going)
		weapon_animation(env, env->player.curr_weapon);
	else
		draw_weapon(env, env->weapons[env->player.curr_weapon].first_sprite);
	if (env->weapon_change.on_going && !env->shot.on_going)
		weapon_change(env);
	draw_crosshair(env);
	print_ammo(env);
	if (env->options.show_fps)
		fps(env);
	if (env->options.test)
		print_debug(env);
	time(env);
	animations(env);
	update_screen(env);
	view(env);
	return (0);
}
