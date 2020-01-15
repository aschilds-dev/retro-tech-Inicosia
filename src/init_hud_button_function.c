/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_hud_button_function.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 11:38:03 by sipatry           #+#    #+#             */
/*   Updated: 2020/01/14 16:00:19 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	save_texture(void *param)
{
	t_env	*env;
	int		i;

	env = ((t_button_target*)param)->env;
	i = ((t_button_target*)param)->i;
	env->editor.current_texture = i;
	env->editor.current_texture_selection.img_down = env->wall_textures[i].maps[6];
	env->editor.current_texture_selection.img_pressed = env->wall_textures[i].maps[6];
	env->editor.current_texture_selection.img_hover = env->wall_textures[i].maps[6];
	env->editor.current_texture_selection.img_up = env->wall_textures[i].maps[6];
	env->editor.draw_selection_tab = 0;
}

void	nothing(void *target)
{
	(void)target;
}

void	general_tab(void *target)
{
	t_env *env;

	env = (t_env *)target;
	env->editor.sprite_tab.state = UP;
	env->editor.sprite_tab.anim_state = REST;
	env->editor.sector_tab.state = UP;
	env->editor.sector_tab.anim_state = REST;
}

void	sector_tab(void *target)
{
	t_env *env;

	env = (t_env *)target;
	env->editor.sprite_tab.state = UP;
	env->editor.sprite_tab.anim_state = REST;
	env->editor.general_tab.state = UP;
	env->editor.general_tab.anim_state = REST;
	//print_floor_information(env);
}

void	sprite_tab(void *target)
{
	t_env *env;

	env = (t_env *)target;
	env->editor.general_tab.state = UP;
	env->editor.general_tab.anim_state = REST;
	env->editor.sector_tab.state = UP;
	env->editor.sector_tab.anim_state = REST;
	//print_floor_information(env);
}