/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_3d_keyup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:34:09 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/03 17:21:40 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		editor_3d_keyup(t_env *env)
{
	int i;

	i = 0;
	if (env->sdl.event.key.keysym.sym == env->keys.enter
			&& !env->confirmation_box.state && !env->input_box.state
			&& !env->editor.enter_locked)
	{
		reset_selection(env);
		env->editor.in_game = 0;
		env->inputs.enter = 0;
		env->editor.sprite_tab.state = UP;
		env->editor.general_tab.state = UP;
		env->editor.sector_tab.state = UP;
		env->editor.sprite_tab.anim_state = REST;
		env->editor.general_tab.anim_state = REST;
		env->editor.sector_tab.anim_state = REST;
		SDL_SetRelativeMouseMode(0);
		return (0);
	}
	if (env->editor.in_game
			&& env->sdl.event.button.button == SDL_BUTTON_LEFT && !env->editor.tab)
		env->editor.select = 1;
	if (env->sdl.event.key.keysym.sym == SDLK_c)
		env->options.contouring = env->options.contouring ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_l)
		env->options.lighting = env->options.lighting ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_m)
	{
		env->options.show_minimap = env->options.show_minimap ? 0 : 1;
		env->options.mipmapping = env->options.mipmapping ? 0 : 1;
	}
	if (env->sdl.event.key.keysym.sym == SDLK_x)
		env->options.wall_lover = env->options.wall_lover ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_j)
		env->options.color_clipping = env->options.color_clipping ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_g)
		env->options.wall_color = env->options.wall_color ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_t)
	{
		env->options.test = env->options.test ? 0 : 1;
		if (env->editor.selected_sector != -1
				&& env->editor.current_texture >= 0
				&& env->editor.current_texture < MAX_WALL_TEXTURE)
		{
			if (apply_texture(env->editor.current_texture,
						&env->sectors[env->editor.selected_sector], env))
				return (-1);
		}
	}
	if (env->sdl.event.key.keysym.sym == SDLK_n)
		env->drawing = env->drawing ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_l)
		env->options.l = env->options.l ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_o)
		env->options.o = env->options.o ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_f)
	{
		env->player.state.fly = env->player.state.fly ? 0 : 1;
		env->player.pos.z += 0.01;
	}
	if (env->sdl.event.key.keysym.sym == SDLK_TAB)
	{
		if (env->editor.tab)
			SDL_SetRelativeMouseMode(1);
		else
			SDL_SetRelativeMouseMode(0);
		env->editor.tab = env->editor.tab ? 0 : 1;
		//env->options.mouse = env->options.mouse ? 0 : 1;
		SDL_GetRelativeMouseState(&env->sdl.mouse_x,
				&env->sdl.mouse_y);
		SDL_GetRelativeMouseState(&env->sdl.mouse_x,
				&env->sdl.mouse_y);
		if (!env->editor.tab)
		{
			env->editor.sprite_tab.state = UP;
			env->editor.general_tab.state = UP;
			env->editor.sector_tab.state = UP;
			env->editor.sprite_tab.anim_state = REST;
			env->editor.general_tab.anim_state = REST;
			env->editor.sector_tab.anim_state = REST;
		}
	}
		if (env->sdl.event.key.keysym.sym == env->keys.enter
			&& env->editor.enter_locked)
		env->editor.enter_locked = 0;
	if (env->sdl.event.key.keysym.sym == SDLK_z)
		env->options.zbuffer = env->options.zbuffer ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_g)
		env->editor.game = env->editor.game ? 0 : 1;
	if (env->confirmation_box.state)
	{
		if (confirmation_box_keyup(&env->confirmation_box, env))
			return (-1);
	}
	if (env->editor.tab)
	{
		if (button_keyup(&env->editor.save, env))
			return (-1);
		if (button_keyup(&env->editor.sprite_tab, env))
			return (-1);
		else if (button_keyup(&env->editor.general_tab, env))
			return (-1);
		else if (button_keyup(&env->editor.sector_tab, env))
			return (-1);
		if (button_keyup(&env->editor.change_mode, env))	
			return (-1);
		if (button_keyup(&env->editor.launch_game, env))
			return (-1);
		if (button_keyup(&env->editor.texture_background, env))
			return (-1);
		if (is_events_tab_visible(env))
		{
			if (button_keyup(&env->editor.events_tab, env))
				return (-1);
			if (env->editor.events_tab.state == DOWN)
			{
				if (button_keyup(&env->editor.next_events, env))
					return (-1);
				if (button_keyup(&env->editor.previous_events, env))
					return (-1);
			}
			if (are_event_selection_buttons_visible(env))
			{
				if (button_keyup(&env->editor.next_event, env))
					return (-1);
				if (button_keyup(&env->editor.previous_event, env))
					return (-1);
			}
			if (are_launch_condition_selection_buttons_visible(env))
			{
				if (button_keyup(&env->editor.next_launch_condition, env))
					return (-1);
				if (button_keyup(&env->editor.previous_launch_condition, env))
					return (-1);
			}
			if (are_exec_condition_selection_buttons_visible(env))
			{
				if (button_keyup(&env->editor.next_exec_condition, env))
					return (-1);
				if (button_keyup(&env->editor.previous_exec_condition, env))
					return (-1);
			}
		}
		if (env->selected_ceiling != -1 && ceiling_buttons_up(env))
				return (-1);
		if (env->editor.selected_wall != -1 && wall_buttons_up(env))
				return (-1);
		if (env->selected_floor != -1 && floor_buttons_up(env))
				return (-1);
		if (env->selected_enemy != -1 && enemy_buttons_up(env))
				return (-1);
		if (env->selected_object != -1 && object_buttons_up(env))
				return (-1);
		if (env->selected_floor_sprite != -1 && floor_sprite_buttons_up(env))
				return (-1);
		if (env->selected_ceiling_sprite != -1 && ceiling_sprite_buttons_up(env))
				return (-1);
		if (env->selected_wall_sprite_sprite != -1 && wall_sprite_buttons_up(env))
				return (-1);
		if ((env->selected_floor_sprite != -1 || env->selected_ceiling_sprite != -1
		|| env->selected_wall_sprite_sprite != -1) && env->editor.sprite_tab.state == DOWN)
		{
			if (button_keyup(&env->editor.next_sprite, env))
				return (-1);
			if (button_keyup(&env->editor.previous_sprite, env))
				return (-1);
			if (button_keyup(&env->editor.current_sprite_selection, env))
				return (-1);
		}
		if (env->editor.draw_selection_tab)
		{
			i = 0;
			while (i < MAX_WALL_TEXTURE)
			{
				if (button_keyup(&env->editor.textures[i], env))
					return (-1);
				i++;
			}
			i = 0;
			while (i < MAX_SKYBOX)
			{
				if (button_keyup(&env->editor.skyboxes[i], env))
					return (-1);
				i++;
			}
		}
		if (env->editor.draw_enemy_tab)
		{
			i = 0;
			while (i < MAX_ENEMIES)
			{
				if (button_keyup(&env->editor.enemy_tab[i], env))
					return (-1);
				i++;
			}
		}
		if (env->editor.draw_sprite_tab)
		{
			i = 0;
			while (i < MAX_OBJECTS)
			{
				if (button_keyup(&env->editor.sprite_selection[i], env))
				return (-1);
				i++;
			}
		}
		if (env->sdl.event.button.button == SDL_BUTTON_LEFT && (env->sdl.mx < 74 && env->sdl.mx > 10)
				&& (env->sdl.my < 414 && env->sdl.my > 350))
			env->editor.draw_selection_tab = 1;
		else if (env->editor.draw_selection_tab && env->sdl.event.button.button == SDL_BUTTON_LEFT
		&& env->editor.current_enemy_selection.state == UP)
			env->editor.draw_selection_tab = 0;
		if (env->editor.draw_enemy_tab && env->sdl.event.button.button == SDL_BUTTON_LEFT
		&& env->editor.current_enemy_selection.state == DOWN)
		{
			env->editor.current_enemy_selection.state = UP;
			env->editor.current_enemy_selection.anim_state = REST;
		}
		else if (env->editor.draw_enemy_tab && env->sdl.event.button.button == SDL_BUTTON_LEFT
		&& env->editor.current_enemy_selection.state == UP)
			env->editor.draw_enemy_tab = 0;
		if (env->editor.draw_sprite_tab && env->sdl.event.button.button == SDL_BUTTON_LEFT
		&& env->editor.current_sprite_selection.state == DOWN)
		{
			env->editor.current_sprite_selection.state = UP;
			env->editor.current_sprite_selection.anim_state = REST;
		}
		else if (env->editor.draw_sprite_tab && env->sdl.event.button.button == SDL_BUTTON_LEFT
		&& env->editor.current_sprite_selection.state == UP)
			env->editor.draw_sprite_tab = 0;
	}
	return (0);
}
