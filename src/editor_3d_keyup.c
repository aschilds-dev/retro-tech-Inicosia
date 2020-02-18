/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_3d_keyup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 15:34:09 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/18 13:46:44 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		editor_3d_keyup(t_env *env)
{
	int i;

	i = 0;
	if (env->editor.creating_event && !env->confirmation_box.state
		&& env->editor.tab)
	{
		if (event_panel_keyup(env))
			return (-1);
	}
	if (env->sdl.event.key.keysym.sym == env->keys.enter
	&& !env->confirmation_box.state && !env->input_box.state
	&& !env->editor.enter_locked)
	{
		going_in_2D_mode(env);
		return (0);
	}
	editor_options_tab_keyup(env);
	if (env->sdl.event.button.button == SDL_BUTTON_LEFT
		&& env->editor.event_panel_dragged)
		env->editor.event_panel_dragged = -1;
	if (env->editor.in_game && env->sdl.event.button.button == SDL_BUTTON_LEFT
		&& env->sdl.mx > 400
		&& !env->confirmation_box.state
		&& ((!env->editor.creating_event && !env->editor.creating_condition)
		|| env->editor.selecting_event))
		env->editor.select = 1;

	if (env->sdl.event.key.keysym.sym == SDLK_t
	&& (env->editor.selected_wall != -1 || env->selected_ceiling != -1
	|| env->selected_floor != -1))
	{
		if (change_target_texture(env))
			return (-1);
	} 
	if (env->sdl.event.key.keysym.sym == SDLK_f)
	{
		if (env->player.state.fly == 0)
			env->player.state.fly = 1;
		else if (env->sectors[env->player.sector].gravity)
			env->player.state.fly = 0;
		env->player.pos.z += 0.01;
	}

	if (env->sdl.event.key.keysym.sym == env->keys.enter
	&& env->editor.enter_locked)
		env->editor.enter_locked = 0;

	if (env->sdl.event.key.keysym.sym == SDLK_g)
		env->editor.game = env->editor.game ? 0 : 1;
	if (env->confirmation_box.state)
	{
		if (confirmation_box_keyup(&env->confirmation_box, env))
			return (-1);
	}
	if (env->sdl.event.key.keysym.sym == SDLK_TAB)
		editor_show_tab(env);
	if (env->editor.tab)
	{
		if (editor_3d_tabs_keyup(env))
			return (-1);		
		if (env->editor.draw_texture_tab)
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
		if (env->sdl.event.button.button == SDL_BUTTON_LEFT && (env->sdl.mx < 348 && env->sdl.mx > 230)
		&& (env->sdl.my < 208 && env->sdl.my > 80))
			env->editor.draw_texture_tab = 1;
		else if (env->editor.draw_texture_tab && env->sdl.event.button.button == SDL_BUTTON_LEFT
		&& env->editor.current_enemy_selection.state == UP)
			env->editor.draw_texture_tab = 0;
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
