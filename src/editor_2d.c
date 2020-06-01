/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 17:52:15 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/15 22:57:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "enemies.h"
#include "draw.h"

int		draw_current_creation(t_env *env)
{
	t_sprite	sprite;
	t_point		size;

	if (env->editor.create_object)
	{
		sprite = env->object_sprites[env->editor.current_object];
		size = new_point(env->editor.scale * 4, env->editor.scale * 4
		/ (sprite.size[0].x / (double)sprite.size[0].y));
		apply_sprite(sprite, new_point(env->sdl.my - env->editor.scale,
		env->sdl.mx - env->editor.scale), size, env);
	}
	if (env->editor.create_enemy)
	{
		sprite = env->enemy_sprites[env->editor.current_enemy];
		size = new_point(env->editor.scale * 4, env->editor.scale * 4
		/ (sprite.size[0].x / (double)sprite.size[0].y));
		apply_sprite(sprite, new_point(env->sdl.my - env->editor.scale,
		env->sdl.mx - env->editor.scale), size, env);
	}
	return (0);
}

int		draw_grid_informations(t_env *env)
{
	if (env->editor.player_exist || env->editor.dragged_start_player == 1)
	{
		if (draw_grid_start_player(env))
			return (-1);
	}
	if (env->editor.player_exist || env->editor.dragged_player == 1)
	{
		if (draw_grid_player(env))
			return (-1);
	}
	if (env->editor.dragged_object != -1 || env->nb_objects > 0)
	{
		if (draw_grid_objects(env))
			return (-1);
	}
	if (env->editor.dragged_enemy != -1 || env->nb_enemies > 0)
	{
		if (draw_grid_enemies(env))
			return (-1);
	}
	if (env->editor.start_vertex != -1)
		draw_grid_current_sector(env);
	return (0);
}

int		editor_2d(t_env *env)
{
	if (!env->input_box.state && !env->options.editor_options)
	{
		if (editor_keys(env))
			return (custom_error("Crash from editor 2D keys\n"));
	}
	else if (!env->input_box.state)
	{
		if (editor_options_keys(env))
			return (custom_error("Error in inputs\n"));
	}
	draw_grid(env);
	if (draw_grid_informations(env))
		return (-1);
	draw_grid_current_sector(env);
	draw_current_creation(env);
	if (draw_grid_vertices(env))
		return (-1);
	if (draw_grid_sectors(env))
		return (-1);
	return (0);
}

void	zoom(t_env *env)
{
	if (!env->editor.in_game && env->sdl.event.type == SDL_MOUSEWHEEL)
	{
		if (env->sdl.event.wheel.y > 0 && env->editor.scale * 1.1 < 100)
		{
			env->editor.center.x = env->sdl.mx
			+ ((env->editor.center.x - env->sdl.mx) * 1.1);
			env->editor.center.y = env->sdl.my
			+ ((env->editor.center.y - env->sdl.my) * 1.1);
			env->editor.scale *= 1.1;
		}
		if (env->sdl.event.wheel.y < 0 && env->editor.scale / 1.1 > 1)
		{
			env->editor.center.x =
			env->sdl.mx + ((env->editor.center.x - env->sdl.mx) / 1.1);
			env->editor.center.y =
			env->sdl.my + ((env->editor.center.y - env->sdl.my) / 1.1);
			env->editor.scale /= 1.1;
		}
	}
}
