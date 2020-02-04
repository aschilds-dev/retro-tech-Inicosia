/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_ceiling_tabs.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:40:14 by sipatry           #+#    #+#             */
/*   Updated: 2020/02/04 12:20:06 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		print_ceiling_sprite_tab(t_env *env)
{
	env->editor.next_sprite_env.type = CEILING_S;	
	env->editor.previous_sprite_env.type = CEILING_S;	
	print_text(new_point(560, 60), new_printable_text("Pos: ", env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	env->editor.hud.sp_ceiling_sprite.pos_x.str = ft_sitoa(
	env->sectors[env->selected_ceiling].ceiling_sprites.pos[env->selected_ceiling_sprite].x);
	env->editor.hud.sp_ceiling_sprite.t_pos_x.target =
	&env->sectors[env->selected_ceiling].ceiling_sprites.pos[env->selected_ceiling_sprite].x;
	draw_button(env, env->editor.hud.sp_ceiling_sprite.pos_x);
	env->editor.hud.sp_ceiling_sprite.pos_y.str = ft_sitoa(
	env->sectors[env->selected_ceiling].ceiling_sprites.pos[env->selected_ceiling_sprite].y);
	env->editor.hud.sp_ceiling_sprite.t_pos_y.target =
	&env->sectors[env->selected_ceiling].ceiling_sprites.pos[env->selected_ceiling_sprite].y;
	draw_button(env, env->editor.hud.sp_ceiling_sprite.pos_y);
	print_text(new_point(600, 60), new_printable_text("Scale: ", env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	env->editor.hud.sp_ceiling_sprite.scale_x.str = ft_sitoa(
	env->sectors[env->selected_ceiling].ceiling_sprites.scale[env->selected_ceiling_sprite].x);
	env->editor.hud.sp_ceiling_sprite.t_scale_x.target =
	&env->sectors[env->selected_ceiling].ceiling_sprites.scale[env->selected_ceiling_sprite].x;
	draw_button(env, env->editor.hud.sp_ceiling_sprite.scale_x);
	env->editor.hud.sp_ceiling_sprite.scale_y.str = ft_sitoa(
	env->sectors[env->selected_ceiling].ceiling_sprites.scale[env->selected_ceiling_sprite].y);
	env->editor.hud.sp_ceiling_sprite.t_scale_y.target =
	&env->sectors[env->selected_ceiling].ceiling_sprites.scale[env->selected_ceiling_sprite].y;
	draw_button(env, env->editor.hud.sp_ceiling_sprite.scale_y);
	return (0);
}

int		print_ceiling_sector_tab(t_env *env)
{
	print_text(new_point(480, 60), new_printable_text("Sector:", env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	print_text(new_point(480, 230), new_printable_text(ft_sitoa(env->selected_ceiling),
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	print_text(new_point(520, 60), new_printable_text("Brightness:", env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	env->editor.hud.s_ceilling.brightness.str = ft_itoa(env->sectors[env->selected_ceiling].brightness);
	env->editor.hud.s_ceilling.t_brightness.target = &env->sectors[env->selected_ceiling].brightness;
	draw_button(env, env->editor.hud.s_ceilling.brightness);
	print_text(new_point(560, 60), new_printable_text("Light_color:", env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	env->editor.hud.s_ceilling.color.str = ft_sitoa(env->sectors[env->selected_ceiling].light_color);
	env->editor.hud.s_ceilling.t_color.target = &env->sectors[env->selected_ceiling].light_color;
	draw_button(env, env->editor.hud.s_ceilling.color);
	print_text(new_point(600, 60), new_printable_text("Intensity:", env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	env->editor.hud.s_ceilling.intensity.str = ft_sitoa(env->sectors[env->selected_ceiling].intensity);
	env->editor.hud.s_ceilling.t_intensity.target = &env->sectors[env->selected_ceiling].intensity;
	draw_button(env, env->editor.hud.s_ceilling.intensity);
	print_text(new_point(640, 60), new_printable_text("Gravity:", env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	env->editor.hud.s_ceilling.gravity.str = ft_sitoa(env->sectors[env->selected_ceiling].gravity);
	env->editor.hud.s_ceilling.t_gravity.target = &env->sectors[env->selected_ceiling].gravity;
	draw_button(env, env->editor.hud.s_ceilling.gravity);
	return (0);
}

int		print_ceiling_general_tab(t_env *env)
{
	print_text(new_point(520, 60), new_printable_text("Height: ", env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	env->editor.hud.g_ceilling.height.str = ft_sitoa(env->sectors[env->selected_ceiling].ceiling);
	env->editor.hud.g_ceilling.t_height.target = &env->sectors[env->selected_ceiling].ceiling;
	draw_button(env, env->editor.hud.g_ceilling.height);	
	print_text(new_point(560, 60), new_printable_text("Slope: ", env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	env->editor.hud.g_ceilling.slope.str = ft_sitoa(env->sectors[env->selected_ceiling].ceiling_slope);
	env->editor.hud.g_ceilling.t_slope.target = &env->sectors[env->selected_ceiling].ceiling_slope;
	draw_button(env, env->editor.hud.g_ceilling.slope);
	print_text(new_point(600, 100), new_printable_text("Slope direction", env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	draw_button(env, env->editor.previous_slope_swap);
	draw_button(env, env->editor.next_slope_swap);
	print_text(new_point(640, 60), new_printable_text("Scale X: ", env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	env->editor.hud.g_ceilling.texture_scale_x.str = ft_sitoa(env->sectors[env->selected_ceiling].ceiling_map_scale.x);
	env->editor.hud.g_ceilling.t_texture_scale_x.target = &env->sectors[env->selected_ceiling].ceiling_map_scale.x;
	draw_button(env, env->editor.hud.g_ceilling.texture_scale_x);
	print_text(new_point(680, 60), new_printable_text("Scale Y: ", env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	env->editor.hud.g_ceilling.texture_scale_y.str = ft_sitoa(env->sectors[env->selected_ceiling].ceiling_map_scale.y);
	env->editor.hud.g_ceilling.t_texture_scale_y.target = &env->sectors[env->selected_ceiling].ceiling_map_scale.y;
	draw_button(env, env->editor.hud.g_ceilling.texture_scale_y);
	print_text(new_point(720, 60), new_printable_text("Align X: ", env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	env->editor.hud.g_ceilling.texture_align_x.str = ft_sitoa(env->sectors[env->selected_ceiling].ceiling_map_align.x);
	env->editor.hud.g_ceilling.t_texture_align_x.target
	= &env->sectors[env->selected_ceiling].ceiling_map_align.x;
	draw_button(env, env->editor.hud.g_ceilling.texture_align_x);
	print_text(new_point(760, 60), new_printable_text("Align Y: ", env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	env->editor.hud.g_ceilling.texture_align_y.str = ft_sitoa(env->sectors[env->selected_ceiling].ceiling_map_align.y);
	env->editor.hud.g_ceilling.t_texture_align_y.target = &env->sectors[env->selected_ceiling].ceiling_map_align.y;
	draw_button(env, env->editor.hud.g_ceilling.texture_align_y);
	return (0);
}