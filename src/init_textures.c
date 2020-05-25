/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:30:20 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/23 20:05:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "parser.h"

/*
** Init images needed for game menu
*/

int		init_game_ui_textures(t_env *env)
{
	if (parse_bmp_ui_textures("images/ui/hud-button-up.bmp", 39, env))
		return (custom_error("Invalid bmp files\n"));
	if (parse_bmp_ui_textures("images/ui/hud-button-pressed.bmp", 40, env))
		return (custom_error("Invalid bmp files\n"));
	if (parse_bmp_ui_textures("images/ui/hud-button-hover.bmp", 41, env))
		return (custom_error("Invalid bmp files\n"));
	if (parse_bmp_ui_textures("images/ui/next-up2.bmp", 15, env))
		return (custom_error("Invalid bmp files\n"));
	if (parse_bmp_ui_textures("images/ui/next-pressed2.bmp", 16, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/next-hover2.bmp", 17, env))
		return (custom_error("Invalid bmp files\n"));
	if (parse_bmp_ui_textures("images/ui/previous-up2.bmp", 18, env))
		return (custom_error("Invalid bmp files\n"));
	if (parse_bmp_ui_textures("images/ui/previous-pressed2.bmp", 19, env))
		return (custom_error("Invalid bmp files\n"));
	if (parse_bmp_ui_textures("images/ui/previous-hover2.bmp", 20, env))
		return (custom_error("Invalid bmp files\n"));
	if (parse_bmp_ui_textures("images/ui/dialog_box.bmp", 60, env))
		return (custom_error("Invalid bmp files\n"));
	return (0);
}

int		init_sprites_textures(t_env *env)
{
	if (init_enemies_sprites_textures(env))
		return (custom_error("Error in init enemies sprites textures"));
	if (init_objects_sprites_textures(env))
		return (custom_error("Error in init obejcts sprites textures"));
	if (init_wall_sprites_textures(env))
		return (custom_error("Error in init wall sprites textures"));
	if (init_editor_sprites(env))
		return (custom_error("Error in init editor sprites textures"));
	return (0);
}

int		init_textures(t_env *env)
{
	if (!env->playing && init_ui_textures(env))
		return (custom_error("Could not init ui textures\n"));
	if (init_game_ui_textures(env))
		return (custom_error("Could not init game menu ui textures\n"));
	if (init_wall_textures(env))
		return (custom_error("Could not init walls textures\n"));
	if (init_skyboxes_textures(env))
		return (custom_error("Could not init skyboxes textures\n"));
	if (init_skyboxes_textures1(env))
		return (custom_error("Could not init skyboxes textures\n"));
	if (init_sprites_textures(env))
		return (custom_error("Could not init sprites tetxures\n"));
	if (init_hud_textures(env))
		return (custom_error("Could not init hud textures\n"));
	return (0);
}
