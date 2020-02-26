/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ui_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/09 11:42:47 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/14 14:12:04 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		init_mini_ui_textures(t_env *env)
{
	if (parse_bmp_mini_enemies_textures("images/ui/mini/lost_soul_mini.bmp", 0,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_enemies_textures("images/ui/mini/cyber_demon_mini.bmp",
		1, env))
		return (custom_error("Invalid bmp files"));
	return (0);
}

int		init_mini_skyboxes_selection(t_env *env)
{
	if (parse_bmp_mini_skyboxes_textures("images/ui/skyboxes/moonlight.bmp", 0,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_skyboxes_textures("images/ui/skyboxes/nebula.bmp", 1,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_skyboxes_textures("images/ui/skyboxes/beautifull_scenery"
		".bmp", 2, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_skyboxes_textures("images/ui/skyboxes/moonlight_128.bmp", 3, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_skyboxes_textures("images/ui/skyboxes/nebula_128.bmp", 4, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_skyboxes_textures("images/ui/skyboxes/beautifull_scenery_128.bmp", 5, env))
		return (custom_error("Invalid bmp files"));
	return (0);
}

int		init_ui_mini_objects_textures(t_env *env)
{
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 0,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 1,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 2,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 3,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 4,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 5,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 6,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 7,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 8,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 9,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 10,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 11,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 12,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 13,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 14,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 15,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 16,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 17,
		env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_mini_objects_textures("images/ui/mini/mini_object.bmp", 18,
		env))
		return (custom_error("Invalid bmp files"));
	return (0);
}

int		init_ui_textures(t_env *env)
{
	if (parse_bmp_ui_textures("images/ui/button-default-up.bmp", 0, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/button-default-pressed.bmp", 1, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/button-default-hover.bmp", 2, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/background-up-64.bmp", 3, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/background-pressed-64.bmp", 4, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/background-hover-64.bmp", 5, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/onglet-up.bmp", 6, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/onglet-pressed.bmp", 7, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/onglet-hover.bmp", 8, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/tab-button-up.bmp", 9, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/tab-button-pressed.bmp", 10, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/tab-button-hover.bmp", 11, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/plus-button-up.bmp", 12, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/plus-button-pressed.bmp", 13, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/plus-button-hover.bmp", 14, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/next-up2.bmp", 15, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/next-pressed2.bmp", 16, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/next-hover2.bmp", 17, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/previous-up2.bmp", 18, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/previous-pressed2.bmp", 19, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/previous-hover2.bmp", 20, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/minus-button-up.bmp", 21, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/minus-button-pressed.bmp", 22, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/minus-button-hover.bmp", 23, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/file.bmp", 24, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/file_straight.bmp", 25, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/plus-button-up2.bmp", 26, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/plus-button-pressed2.bmp", 27, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/plus-button-hover2.bmp", 28, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/minus-button-up2.bmp", 29, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/minus-button-pressed2.bmp", 30, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/minus-button-hover2.bmp", 31, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/background-up2.bmp", 32, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/background-pressed2.bmp", 33, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/background-hover2.bmp", 34, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/add_button.bmp", 35, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/onglet-up2.bmp", 36, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/onglet-pressed2.bmp", 37, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/onglet-hover2.bmp", 38, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/hud-button-up.bmp", 39, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/hud-button-pressed.bmp", 40, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/hud-button-hover.bmp", 41, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/play_icon.bmp", 42, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/target_icon.bmp", 43, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/event_icon.bmp", 44, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/condition_icon.bmp", 45, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/play_icon_down.bmp", 46, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/target_icon_down_blue.bmp", 47, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/event_icon_down_blue.bmp", 48, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/condition_icon_down_blue.bmp", 49, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/play_icon_hover.bmp", 50, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/target_icon_hover.bmp", 51, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/event_icon_hover.bmp", 52, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/condition_icon_hover.bmp", 53, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/previous_arrow.bmp", 54, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/next_arrow.bmp", 55, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/previous_arrow_down.bmp", 56, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/next_arrow_down.bmp", 57, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/previous_arrow_hover.bmp", 58, env))
		return (custom_error("Invalid bmp files"));
	if (parse_bmp_ui_textures("images/ui/next_arrow_hover.bmp", 59, env))
		return (custom_error("Invalid bmp files"));
	if (init_mini_ui_textures(env))
		return (custom_error("error while parsing the miniatures of"
		" the enemies"));
	if (init_ui_mini_objects_textures(env))
		return (custom_error("error while parsing the miniatures of"
		" the objects"));
	if (init_mini_skyboxes_selection(env))
		return (custom_error("error while parsing the miniatures of"
		" the skyboxes"));
	return (0);
}
