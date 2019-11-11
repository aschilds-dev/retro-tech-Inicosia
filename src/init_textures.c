/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 15:30:20 by lnicosia          #+#    #+#             */
/*   Updated: 2019/11/11 16:58:02 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"



int		init_buttons(t_env *env)
{
	if (parse_bmp("images/HUD/Ammo_hud.bmp", 1, env))
		return (ft_printf("Invalid bmp file\n"));
	if (parse_bmp("images/HUD/Life_armor_hud.bmp", 2, env))
		return (ft_printf("Invalid bmp file\n"));
	if (parse_bmp("images/button-default-up.bmp", 3, env))
		return (ft_printf("Failed to load default button\n"));
	if (parse_bmp("images/button-default-pressed.bmp", 4, env))
		return (ft_printf("Failed to load default button\n"));
	if (parse_bmp("images/button-default-hover.bmp", 5, env))
		return (ft_printf("Failed to load default button\n"));
	return (0);
}

int		init_skyboxes(t_env *env)
{
	env->init_max = MAX_SKYBOX_SPRITE;
	/*if (parse_bmp("images/skyboxes/bottom.bmp", 38, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/top.bmp", 39, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/back.bmp", 40, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/left.bmp", 41, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/front.bmp", 42, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/right.bmp", 43, env))
		return (ft_printf("Failed to load skybox\n"));*/
	/*if (parse_bmp("images/skyboxes/nebula_bottom.bmp", 38, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/nebula_top.bmp", 39, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/nebula_back.bmp", 40, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/nebula_left.bmp", 41, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/nebula_front.bmp", 42, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/nebula_right.bmp", 43, env))
		return (ft_printf("Failed to load skybox\n"));*/
	if (parse_bmp("images/skyboxes/night_bottom.bmp", 0, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/night_top.bmp", 1, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/night_back.bmp", 2, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/night_left.bmp", 3, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/night_front.bmp", 4, env))
		return (ft_printf("Failed to load skybox\n"));
	if (parse_bmp("images/skyboxes/night_right.bmp", 5, env))
		return (ft_printf("Failed to load skybox\n"));
	return (0);
}

int		init_wall_textures(t_env *env)
{
	env->init_max = MAX_WALL_TEXTURE;
	if (parse_bmp("images/textures/wall0.bmp", 0, env))
		return (ft_printf("Invalid bmp file\n"));
	if (parse_bmp("images/textures/wall1.bmp", 1, env))
		return (ft_printf("Invalid bmp file\n"));
	if (parse_bmp("images/textures/wall2.bmp", 2, env))
		return (ft_printf("Invalid bmp file\n"));
	if (parse_bmp("images/textures/wall3.bmp", 3, env))
		return (ft_printf("Invalid bmp file\n"));
	if (parse_bmp("images/textures/floor0.bmp", 4, env))
		return (ft_printf("Invalid bmp file\n"));
	if (parse_bmp("images/textures/floor1.bmp", 5, env))
		return (ft_printf("Invalid bmp file\n"));
	if (parse_bmp("images/textures/rust.bmp", 6, env))
		return (ft_printf("Failed to load sprite sheet\n"));
	if (parse_bmp("images/textures/black_tiles.bmp", 8, env))
		return (ft_printf("Failed to load black_tiles\n"));
	if (parse_bmp("images/textures/rock.bmp", 9, env))
		return (ft_printf("Failed to load black_tiles\n"));
	 if (parse_bmp("images/textures/grass1.bmp", 10, env))
		return (ft_printf("Failed to load black_tiles\n"));
	if (parse_bmp("images/textures/grass2.bmp", 11, env))
		return (ft_printf("Failed to load black_tiles\n"));
	if (parse_bmp("images/textures/grass3.bmp", 12, env))
		return (ft_printf("Failed to load black_tiles\n"));
	if (parse_bmp("images/textures/tiles.bmp", 13, env))
		return (ft_printf("Failed to load black_tiles\n"));
	if (parse_bmp("images/textures/sand.bmp", 14, env))
		return (ft_printf("Failed to load sand\n"));
	if (parse_bmp("images/textures/grey.bmp", 15, env))
		return (ft_printf("Failed to load grey\n"));
	return (0);
}

int		init_sprites(t_env *env)
{
	en->init_max = MAX_ENEMY_SPRITES;
	if (parse_bmp("images/sprite_sheet.bmp", 1, env))
		return (ft_printf("Failed to load sprite sheet\n"));
	if (parse_bmp("images/lost_soul.bmp", 2, env))
		return (ft_printf("Failed to load sprite sheet\n"));
	if (parse_bmp("images/cyber_demon.bmp", 3, env))
		return (ft_printf("Failed to load cyber demon sprite sheet\n"));
	if (parse_bmp("images/projectiles_sprites.bmp", 1, env))
		return (ft_printf("Failed to load projectiles sprite sheet\n"));
	return (0);
}

int		init_wall_sprites(t_env *env)
{
	if (parse_bmp("images/MIDSPACE.bmp", 46, env))
		return (ft_printf("Failed to load midspace\n"));
}


int		init_textures(t_env *env)
{
	if (init_buttons(env))
		return (ft_printf("Could not load wallpapers and button\n"));
	if (init_wall_textures(env))
		return (ft_printf("Could not load Wall textures\n"));
	if (init_skyboxes(env))
		return (ft_printf("Could not load skyboxes textures\n"));				
	if (int_weapons_sprites(env))
		return (ft_printf("Could not load enemies sprite sheets\n"));
	return (0);
}
