/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_wall_tabs2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 18:47:26 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/20 16:49:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "draw.h"

int		print_wall_sprite_tab3(t_env *env)
{
	env->editor.hud.sp_wall_sprite.t_scale_x.target = &env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	scale[env->selected_wall_sprite_sprite].x;
	if (draw_button(env, env->editor.hud.sp_wall_sprite.scale_x, env->snprintf))
		return (-1);
	if (print_text(new_point(680, 60), new_printable_text("Scale Y",
		env->sdl.fonts.lato20, 0x00000000, 30), env))
		return (-1);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	get_decimal_len(env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	scale[env->selected_wall_sprite_sprite].y),
	env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	scale[env->selected_wall_sprite_sprite].y);
	env->editor.hud.sp_wall_sprite.t_scale_y.target = &env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	scale[env->selected_wall_sprite_sprite].y;
	if (draw_button(env, env->editor.hud.sp_wall_sprite.scale_y, env->snprintf))
		return (-1);
	if (draw_button(env, env->editor.hud.sp_wall_sprite.add_sprite,
	env->editor.hud.sp_wall_sprite.add_sprite.str))
		return (-1);
	return (0);
}

int		print_wall_sprite_tab2(t_env *env)
{
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	get_decimal_len(env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	pos[env->selected_wall_sprite_sprite].y),
	env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	pos[env->selected_wall_sprite_sprite].y);
	env->editor.hud.sp_wall_sprite.t_pos_y.target = &env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	pos[env->selected_wall_sprite_sprite].y;
	if (draw_button(env, env->editor.hud.sp_wall_sprite.pos_y, env->snprintf))
		return (-1);
	if (print_text(new_point(640, 60), new_printable_text("Scale X",
		env->sdl.fonts.lato20, 0x00000000, 30), env))
		return (-1);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	get_decimal_len(env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	scale[env->selected_wall_sprite_sprite].x),
	env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	scale[env->selected_wall_sprite_sprite].x);
	return (print_wall_sprite_tab3(env));
}

int		print_wall_sprite_tab(t_env *env)
{
	env->editor.next_sprite_env.type = WALL_S;
	env->editor.previous_sprite_env.type = WALL_S;
	if (print_text(new_point(560, 60), new_printable_text("X",
		env->sdl.fonts.lato20, 0x00000000, 30), env))
		return (-1);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%.*f",
	get_decimal_len(env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	pos[env->selected_wall_sprite_sprite].x),
	env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	pos[env->selected_wall_sprite_sprite].x);
	env->editor.hud.sp_wall_sprite.t_pos_x.target = &env->sectors[env->editor.
	selected_sector].wall_sprites[env->selected_wall_sprite_wall].
	pos[env->selected_wall_sprite_sprite].x;
	if (draw_button(env, env->editor.hud.sp_wall_sprite.pos_x, env->snprintf))
		return (-1);
	if (print_text(new_point(600, 60), new_printable_text("Y",
		env->sdl.fonts.lato20, 0x00000000, 30), env))
		return (-1);
	return (print_wall_sprite_tab2(env));
}
