/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_wall_tabs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 13:26:37 by sipatry           #+#    #+#             */
/*   Updated: 2020/02/04 14:37:02 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		print_wall_sprite_sector_tab(t_env *env)
{
	print_text(new_point(480, 60), new_printable_text("Sector:",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "%d", env->editor.selected_sector);
	print_text(new_point(480, 230), new_printable_text(env->snprintf,
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	print_text(new_point(520, 60), new_printable_text("Brightness:",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "%d",
	env->sectors[env->editor.selected_sector].brightness);
	env->editor.hud.s_wall_sprite.t_brightness.target =
	&env->sectors[env->editor.selected_sector].brightness;
	draw_button(env, env->editor.hud.s_wall_sprite.brightness, env->snprintf);
	print_text(new_point(560, 60), new_printable_text("Light_color:",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "0x%X",
	env->sectors[env->editor.selected_sector].light_color);
	env->editor.hud.s_wall_sprite.t_color.target =
	&env->sectors[env->editor.selected_sector].light_color;
	draw_button(env, env->editor.hud.s_wall_sprite.color, env->snprintf);
	print_text(new_point(600, 60), new_printable_text("Intensity:",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "%d",
	env->sectors[env->editor.selected_sector].intensity);
	env->editor.hud.s_wall_sprite.t_intensity.target =
	&env->sectors[env->editor.selected_sector].intensity;
	draw_button(env, env->editor.hud.s_wall_sprite.intensity, env->snprintf);
	print_text(new_point(640, 60), new_printable_text("Gravity:", 
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "%.5f",
	env->sectors[env->editor.selected_sector].gravity);
	env->editor.hud.s_wall_sprite.t_gravity.target =
	&env->sectors[env->editor.selected_sector].gravity;
	draw_button(env, env->editor.hud.s_wall_sprite.gravity, env->snprintf);
	return (0);
}

int		print_wall_sprite_tab(t_env *env)
{
	
	env->editor.next_sprite_env.type = WALL_S;
	env->editor.previous_sprite_env.type = WALL_S;
	env->editor.current_sprite = env->selected_wall_sprite_sprite;
	env->editor.current_sprite_selection.img_down =
	env->mini_objects_textures[env->selected_wall_sprite_sprite].surface;
	env->editor.current_sprite_selection.img_pressed =
	env->mini_objects_textures[env->selected_wall_sprite_sprite].surface;
	env->editor.current_sprite_selection.img_hover =
	env->mini_objects_textures[env->selected_wall_sprite_sprite].surface;
	env->editor.current_sprite_selection.img_up =
	env->mini_objects_textures[env->selected_wall_sprite_sprite].surface;
	print_text(new_point(560, 60), new_printable_text("Pos: ",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "%.5f", env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	pos[env->selected_wall_sprite_sprite].x);
	env->editor.hud.sp_wall_sprite.t_pos_x.target = &env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	pos[env->selected_wall_sprite_sprite].x;
	draw_button(env, env->editor.hud.sp_wall_sprite.pos_x, env->snprintf);
	ft_snprintf(env->snprintf, 20, "%.5f", env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	pos[env->selected_wall_sprite_sprite].y);
	env->editor.hud.sp_wall_sprite.t_pos_y.target = &env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	pos[env->selected_wall_sprite_sprite].y;
	draw_button(env, env->editor.hud.sp_wall_sprite.pos_y, env->snprintf);
	print_text(new_point(600, 60), new_printable_text("Scale: ",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "%.5f", env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	scale[env->selected_wall_sprite_sprite].x);
	env->editor.hud.sp_wall_sprite.t_scale_x.target = &env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	scale[env->selected_wall_sprite_sprite].x;
	draw_button(env, env->editor.hud.sp_wall_sprite.scale_x, env->snprintf);
	ft_snprintf(env->snprintf, 20, "%.5f", env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	scale[env->selected_wall_sprite_sprite].y);
	env->editor.hud.sp_wall_sprite.t_scale_y.target = &env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	scale[env->selected_wall_sprite_sprite].y;
	draw_button(env, env->editor.hud.sp_wall_sprite.scale_y, env->snprintf);
	return (0);
}

int		print_wall_sector_tab(t_env *env)
{
	print_text(new_point(480, 60), new_printable_text("Sector:",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "%d", 
	env->editor.selected_sector),
	print_text(new_point(480, 230), new_printable_text(env->snprintf,
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	print_text(new_point(520, 60), new_printable_text("Brightness:",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "%d", 
	env->sectors[env->editor.selected_sector].brightness);
	env->editor.hud.s_wall.t_brightness.target =
	&env->sectors[env->editor.selected_sector].brightness;
	draw_button(env, env->editor.hud.s_wall.brightness, env->snprintf);
	print_text(new_point(560, 60), new_printable_text("Light_color:",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "0x%X", 
	env->sectors[env->editor.selected_sector].light_color);
	env->editor.hud.s_wall.t_color.target =
	&env->sectors[env->editor.selected_sector].light_color;
	draw_button(env, env->editor.hud.s_wall.color, env->snprintf);
	print_text(new_point(600, 60), new_printable_text("Intensity:",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "%d", 
	env->sectors[env->editor.selected_sector].intensity);
	env->editor.hud.s_wall.t_intensity.target =
	&env->sectors[env->editor.selected_sector].intensity;
	draw_button(env, env->editor.hud.s_wall.intensity, env->snprintf);
	print_text(new_point(640, 60), new_printable_text("Gravity:",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "%.5f", 
	env->sectors[env->editor.selected_sector].gravity);
	env->editor.hud.s_wall.t_gravity.target =
	&env->sectors[env->editor.selected_sector].gravity;
	draw_button(env, env->editor.hud.s_wall.gravity, env->snprintf);
	return (0);
}

int		print_wall_general_tab(t_env *env)
{
	draw_button(env, env->editor.next_wall, env->editor.next_wall.str);
	draw_button(env, env->editor.previous_wall, env->editor.previous_wall.str);
	print_text(new_point(560, 60), new_printable_text("Scale X: ",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "%.5f", env->sectors[env->editor.
	selected_sector].scale[env->editor.selected_wall].x);
	env->editor.hud.g_wall.t_texture_scale_x.target =
	&env->sectors[env->editor.selected_sector].
	scale[env->editor.selected_wall].x;
	draw_button(env, env->editor.hud.g_wall.texture_scale_x, env->snprintf);
	print_text(new_point(600, 60), new_printable_text("Scale Y: ",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "%.5f", env->sectors[env->editor.
	selected_sector].scale[env->editor.selected_wall].y);
	env->editor.hud.g_wall.t_texture_scale_y.target =
	&env->sectors[env->editor.selected_sector].
	scale[env->editor.selected_wall].y;
	draw_button(env, env->editor.hud.g_wall.texture_scale_y, env->snprintf);
	print_text(new_point(640, 60), new_printable_text("Align X: ",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "%.5f", env->sectors[env->editor.
	selected_sector].align[env->editor.selected_wall].x);
	env->editor.hud.g_wall.t_texture_align_x.target =
	&env->sectors[env->editor.selected_sector].
	align[env->editor.selected_wall].x;
	draw_button(env, env->editor.hud.g_wall.texture_align_x, env->snprintf);
	print_text(new_point(680, 60), new_printable_text("Align Y: ",
	env->sdl.fonts.alice30, 0xFFFFFFFF, 30), env);
	ft_snprintf(env->snprintf, 20, "%.5f", env->sectors[env->editor.
	selected_sector].align[env->editor.selected_wall].y);
	env->editor.hud.g_wall.t_texture_align_y.target =
	&env->sectors[env->editor.selected_sector].
	align[env->editor.selected_wall].y;
	draw_button(env, env->editor.hud.g_wall.texture_align_y, env->snprintf);
	return (0);
}
