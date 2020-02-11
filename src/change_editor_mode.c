/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_editor_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:44:36 by sipatry           #+#    #+#             */
/*   Updated: 2020/02/11 10:51:13 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		going_in_3D_mode(t_env *env)
{
	reset_selection(env);
	new_tabs_position(env);
	env->editor.in_game = 1;
	env->screen_sectors_size = ft_min(env->nb_sectors, env->w);
	free_camera(&env->player.camera, env);
	precompute_slopes(env);
	if (init_camera_arrays(&env->player.camera, env))
		return (ft_printf("Could not init camera arrays\n"));
	if (env->sector_list)
		ft_memdel((void**)&env->sector_list);
	if (!(env->sector_list = (int*)ft_memalloc(sizeof(int) * env->nb_sectors)))
		return (ft_printf("Could not allocate sector list\n", env));
	update_camera_position(&env->player.camera);
	update_player_z(env);
	ft_bzero(&env->inputs, sizeof(env->inputs));
	env->options.mouse = 1;
	if (!env->editor.tab)
	{
		SDL_SetRelativeMouseMode(1);
		SDL_GetRelativeMouseState(&env->sdl.mouse_x, &env->sdl.mouse_y);
		SDL_GetRelativeMouseState(&env->sdl.mouse_x, &env->sdl.mouse_y);
	}
	return (0);
}

int		going_in_2D_mode(t_env *env)
{
	reset_selection(env);
	new_tabs_position(env);
	SDL_SetRelativeMouseMode(0);
	env->editor.in_game = 0;
	env->inputs.enter = 0;
	env->editor.sprite_tab.state = UP;
	env->editor.general_tab.state = UP;
	env->editor.sector_tab.state = UP;
	env->editor.sprite_tab.anim_state = REST;
	env->editor.general_tab.anim_state = REST;
	env->editor.sector_tab.anim_state = REST;
	env->editor.center.x = -env->player.pos.x * env->editor.scale +
	env->h_w + 200;
	env->editor.center.y = -env->player.pos.y * env->editor.scale + env->h_h;
	return (0);
}
