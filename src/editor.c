/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 17:14:57 by sipatry           #+#    #+#             */
/*   Updated: 2019/11/15 11:20:13 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		editor(t_env *env)
{
	while (env->running)
	{
		clear_image(env);
		SDL_GetRelativeMouseState(&env->sdl.mouse_x, &env->sdl.mouse_y);
		SDL_GetMouseState(&env->sdl.mx, &env->sdl.my);
		while (SDL_PollEvent(&env->sdl.event))
		{
			if (env->sdl.event.type == SDL_QUIT || (env->sdl.event.type == SDL_KEYUP && env->sdl.event.key.keysym.sym == SDLK_ESCAPE))
				env->running = 0;
			else if (env->sdl.event.type == SDL_KEYDOWN
					|| env->sdl.event.type == SDL_KEYUP || env->sdl.event.type == SDL_MOUSEBUTTONDOWN
					|| env->sdl.event.type == SDL_MOUSEBUTTONUP || env->sdl.event.type == SDL_MOUSEWHEEL)
				update_inputs(env);
			if (!env->input_box.state && (env->sdl.event.type == SDL_KEYUP || env->sdl.event.type == SDL_MOUSEBUTTONUP))
			{
				if (editor_keyup(env))
					return (-1);
			}
			if (!env->editor.in_game && env->sdl.event.type == SDL_MOUSEWHEEL)
			{
				if (env->sdl.event.wheel.y > 0 && env->editor.scale * 1.1 < 100)
				{
					env->editor.center.x = env->sdl.mx + ((env->editor.center.x - env->sdl.mx) * 1.1);
					env->editor.center.y = env->sdl.my + ((env->editor.center.y - env->sdl.my) * 1.1);
					env->editor.scale *= 1.1;
			}
				if (env->sdl.event.wheel.y < 0 && env->editor.scale / 1.1 > 1)
				{
	
					env->editor.center.x = env->sdl.mx + ((env->editor.center.x - env->sdl.mx) / 1.1);
					env->editor.center.y = env->sdl.my + ((env->editor.center.y - env->sdl.my) / 1.1);
					env->editor.scale /= 1.1;
				}
			}
			if (env->input_box.state)
				input_box_keys(&env->input_box, env);
		}
		if (!env->editor.in_game)
		{
			if (!env->input_box.state)
			{
				if (editor_keys(env))
					return (ft_printf("Error in inputs\n"));
			}
			env->frame_timer = SDL_GetTicks();
			draw_grid(env);
			draw_grid_vertices(env);
			if (env->editor.new_player || env->editor.dragged_player == 1)
				draw_grid_player(env);
			if (env->editor.dragged_object != -1 || env->nb_objects > 0)
				draw_grid_objects(env);
			if (env->editor.dragged_enemy != -1 || env->nb_enemies > 0)
				draw_grid_enemies(env);
			if (env->editor.start_vertex != -1)
				draw_grid_current_sector(env);
			draw_grid_sectors(env);
		}
		else
		{
			if (env->player.sector != -1)
				start_event(env->sectors[env->player.sector].walk_on_me_event,
				env->sectors[env->player.sector].nb_walk_events, env);
			if (editor_render(env))
				return (crash("Render function failed\n", env));
		}
		if (!env->input_box.state && env->saving)
			save_map(env);
		if (env->events)
			pop_events2(env);
		editor_hud(env);
		if (env->confirmation_box.state)
			draw_confirmation_box(env->confirmation_box, env);
		if (env->input_box.state)
			draw_input_box(&env->input_box, env);
		print_text(new_point(env->h - 50, 300), new_printable_text("Mipmapping",
		env->sdl.fonts.lato20, 0xFFFFFFFF, 20), env);
		if (env->options.show_minimap)
		print_text(new_point(env->h - 50, 450), new_printable_text("[ON]",
		env->sdl.fonts.lato20, 0x00FF00FF, 20), env);
		else
		print_text(new_point(env->h - 50, 450), new_printable_text("[OFF]",
		env->sdl.fonts.lato20, 0xFF0000FF, 20), env);

		/*
		**	Show the result of the mipmap generation
		*/
		/*size_t	i = 0;
		t_point	pos = new_point(env->h_h - env->textures[1].surface->h / 2,
		env->h_w - env->textures[1].surface->w / 2);
		while (i < env->textures[1].nb_maps)
		{
			apply_surface(env->textures[1].maps[i], pos,
			new_point(env->textures[1].maps[i]->w, env->textures[1].maps[i]->h),
			env);
			pos.y += env->textures[1].maps[i]->w;
			i++;
		}*/
		if (env->options.zbuffer && env->editor.in_game)
			update_screen_zbuffer(env);
		else
			update_screen(env);
	}
	free_all(env);
	return (0);
}
