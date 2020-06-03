/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_editor_mode.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:44:36 by sipatry           #+#    #+#             */
/*   Updated: 2020/05/11 17:36:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "init.h"

int		going_in_3d_mode(t_env *env)
{
	reset_selection(env);
	new_tabs_position(env);
	env->editor.in_game = 1;
	env->screen_sectors_size = ft_min(env->nb_sectors, env->w);
	free_camera(&env->player.camera);
	precompute_slopes(env);
	if (init_camera_arrays(&env->player.camera, env))
		return (custom_error("Could not init camera arrays\n"));
	ft_memdel((void**)&env->sector_list);
	if (!(env->sector_list = (int*)ft_memalloc(sizeof(int) * env->nb_sectors)))
		return (ft_perror("Could not allocate sector list\n"));
	update_camera_position(&env->player.camera);
	update_player_z(env);
	ft_bzero(&env->inputs, sizeof(env->inputs));
	if (!env->editor.tab)
	{
		SDL_SetRelativeMouseMode(1);
		SDL_GetRelativeMouseState(&env->sdl.mouse_x, &env->sdl.mouse_y);
		SDL_GetRelativeMouseState(&env->sdl.mouse_x, &env->sdl.mouse_y);
	}
	env->editor.draw_enemy_tab = 0;
	env->editor.draw_object_tab = 0;
	env->editor.draw_texture_tab = 0;
	env->editor.draw_sprite_tab = 0;
	return (0);
}

int		going_in_2d_mode(t_env *env)
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
