/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_wall_tabs3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:48:18 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/18 15:02:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "draw.h"

int		print_wall_sector_tab3(t_env *env)
{
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	get_decimal_len(env->sectors[env->editor.selected_sector].gravity),
	env->sectors[env->editor.selected_sector].gravity);
	env->editor.hud.s_wall.t_gravity.target =
	&env->sectors[env->editor.selected_sector].gravity;
	if (draw_button(env, env->editor.hud.s_wall.gravity, env->snprintf))
		return (-1);
	return (0);
}

int		print_wall_sector_tab2(t_env *env)
{
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "0x%X",
	env->sectors[env->editor.selected_sector].light_color);
	env->editor.hud.s_wall.t_color.target =
	&env->sectors[env->editor.selected_sector].light_color;
	if (draw_button(env, env->editor.hud.s_wall.color, env->snprintf))
		return (-1);
	if (print_text(new_point(600, 60), new_printable_text("Intensity",
	env->sdl.fonts.lato20, 0x00000000, 30), env))
		return (-1);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d",
	env->sectors[env->editor.selected_sector].intensity);
	env->editor.hud.s_wall.t_intensity.target =
	&env->sectors[env->editor.selected_sector].intensity;
	if (draw_button(env, env->editor.hud.s_wall.intensity, env->snprintf))
		return (-1);
	if (print_text(new_point(640, 60), new_printable_text("Gravity",
	env->sdl.fonts.lato20, 0x00000000, 30), env))
		return (-1);
	return (print_wall_sector_tab3(env));
}

int		print_wall_sector_tab(t_env *env)
{
	t_point		size;

	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "Sector %d",
	env->editor.selected_sector);
	if (TTF_SizeText(env->sdl.fonts.lato_black30,
		env->snprintf, &size.x, &size.y))
		return (-1);
	if (print_text(new_point(465, 200 - size.x / 2),
	new_printable_text(env->snprintf,
	env->sdl.fonts.lato_black30, 0x333333FF, 30), env))
		return (-1);
	if (print_text(new_point(520, 60), new_printable_text("Brightness",
	env->sdl.fonts.lato20, 0x00000000, 30), env))
		return (-1);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d",
	env->sectors[env->editor.selected_sector].brightness);
	env->editor.hud.s_wall.t_brightness.target =
	&env->sectors[env->editor.selected_sector].brightness;
	if (draw_button(env, env->editor.hud.s_wall.brightness, env->snprintf))
		return (-1);
	if (print_text(new_point(560, 60), new_printable_text("Light_color",
	env->sdl.fonts.lato20, 0x00000000, 30), env))
		return (-1);
	return (print_wall_sector_tab2(env));
}
