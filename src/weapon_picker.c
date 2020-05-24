/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_picker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 15:17:22 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/20 13:39:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "draw.h"

int		print_weapon_name(t_env *env)
{
	t_point		text_size;

	if (TTF_SizeText(env->sdl.fonts.lato_black30,
	env->weapons[env->editor.current_weapon].name, &text_size.x, &text_size.y))
		return (-1);
	if (print_text(new_point(env->editor.weapon_picker.pos.y
	+ env->editor.event_panel.top_size + 10,
	env->editor.weapon_picker.pos.x + env->editor.weapon_picker.size.x / 2
	- text_size.x / 2),
	new_printable_text(env->weapons[env->editor.current_weapon].name,
	env->sdl.fonts.lato_black30, 0x333333FF, 0), env))
		return (-1);
	return (0);
}

int		draw_weapon_picker2(t_point sprite_size, t_point text_size, t_env *env)
{
	if (print_text(new_point(env->editor.weapon_picker.pos.y
	+ env->editor.event_panel.top_size / 2 - text_size.y / 2,
	env->editor.weapon_picker.pos.x + 20),
	new_printable_text("Weapon picker", env->sdl.fonts.lato_black30,
	0x333333FF, 0), env))
		return (-1);
	sprite_size.x = env->editor.weapon_picker.size.x / 2;
	sprite_size.y = sprite_size.x / (env->weapons[env->editor.current_weapon].
	sprite.size[0].x / (double)env->weapons[env->editor.current_weapon].sprite.
	size[0].y);
	apply_sprite(env->weapons[env->editor.current_weapon].sprite,
	new_point(env->editor.weapon_picker.pos.y
	+ env->editor.weapon_picker.size.y / 2 - sprite_size.y / 2
	+ env->editor.event_panel.top_size / 2,
	env->editor.weapon_picker.pos.x + env->editor.weapon_picker.size.x / 2
	- sprite_size.x / 2), sprite_size, env);
	if (print_weapon_name(env))
		return (-1);
	return (0);
}

int		draw_weapon_picker(t_env *env)
{
	t_point		text_size;

	draw_rectangle(env, new_rectangle(0xc8ccd0, 0xc8ccd0, 1, 0),
	env->editor.weapon_picker.pos, env->editor.weapon_picker.size);
	draw_rectangle(env, new_rectangle(0xFFf1f2f3, 0xc8ccd0, 1, 0),
	env->editor.weapon_picker.pos,
	new_point(env->editor.weapon_picker.size.x - 200,
	env->editor.event_panel.top_size - 2));
	draw_rectangle(env, new_rectangle(0xFFe3e4e8, 0xc8ccd0, 1, 0),
	new_point(env->editor.weapon_picker.pos.x,
	env->editor.event_panel.top_size + env->editor.weapon_picker.pos.y),
	new_point(env->editor.weapon_picker.size.x,
	env->editor.weapon_picker.size.y - env->editor.event_panel.top_size));
	if (draw_button(env, env->editor.weapon_picker.next, NULL))
		return (-1);
	if (draw_button(env, env->editor.weapon_picker.previous, NULL))
		return (-1);
	if (draw_button(env, env->editor.weapon_picker.ok, "OK"))
		return (-1);
	if (draw_button(env, env->editor.weapon_picker.cancel, "X"))
		return (-1);
	if (TTF_SizeText(env->sdl.fonts.lato_black30, "Weapon picker",
	&text_size.x, &text_size.y))
		return (-1);
	return (draw_weapon_picker2(new_point(0, 0), new_point(0, 0), env));
}
