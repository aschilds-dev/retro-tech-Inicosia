/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/29 15:07:41 by lnicosia          #+#    #+#             */
/*   Updated: 2019/08/01 14:38:42 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	create_player(t_env *env)
{
	if (env->inputs.left_click
			&& env->sdl.mx > 80
			&& env->sdl.mx < 120
			&& env->sdl.my > 180
			&& env->sdl.my < 220
			&& !env->editor.new_sector)
	{
		env->editor.drag_player = 1;
		env->editor.new_player = 1;
	}
	if (!env->inputs.left_click && env->editor.drag_player)
	{
		env->editor.drag_player = 0;
		add_player(env);
	}
}
void	create_object(t_env *env)
{
	if (env->inputs.left_click
			&& env->sdl.mx > 80
			&& env->sdl.mx < 120
			&& env->sdl.my > 280
			&& env->sdl.my < 320
			&& !env->editor.new_sector)
	{
		env->editor.objects = 1;
		env->editor.drag_object = 2;
	}
	if (!env->inputs.left_click && env->editor.drag_object == 2)
	{
		env->editor.drag_object = 0;
		add_object(env);
		env->nb_objects++;
	}
}

void	drag_element(t_env *env)
{
	t_point	center;
	double	scale;

	scale = 0;
	if (env->editor.select_object != -1)
	{
		if (env->inputs.left_click)
		{
		//	ft_printf("dragging an element\n");
			env->editor.drag_object = 1;
			scale = env->editor.scale;
			center.x = env->sdl.mx;
			center.y= env->sdl.my;
			draw_circle(new_circle(0xFF00FF00, 0xFF00FF00, center, scale), env);
			ft_printf("x: %d y: %d\n",  env->objects[env->editor.select_object].pos.x, env->objects[env->editor.select_object].pos.y);

		}
		else if (env->editor.drag_object)
		{	
	//		env->objects[env->editor.select_object].pos.x = env->sdl.mx;
	//		env->objects[env->editor.select_object].pos.y = env->sdl.my;
			ft_printf("x: %d y: %d\n",  env->objects[env->editor.select_object].pos.x, env->objects[env->editor.select_object].pos.y);
			env->editor.select_object = -1;
			env->editor.drag_object = 0;
		}
	}
	if (env->editor.select_player != -1)
	{

	}
	if (env->editor.select_vertex != -1)
	{

	}
}

int			editor_keys(t_env *env)
{
	int		clicked_vertex;

	if (env->inputs.space)
	{
		clicked_vertex = get_existing_vertex(env);
		if (clicked_vertex == -1)
		{
			if (add_vertex(env))
				return (ft_printf("Could not add new vertex\n"));
			if (!env->editor.new_sector) //Nouveau secteur
				env->editor.new_sector = 1;
			add_vertex_to_current_sector(env, env->nb_vertices - 1);
		}
		else
		{
			if (!env->editor.new_sector)
			{
				env->editor.new_sector = 1;
				add_vertex_to_current_sector(env, clicked_vertex);
			}
			else
			{
				if (clicked_vertex == ((t_vertex*)env->editor.current_vertices->content)->num)
				{
					env->editor.reverted = get_clockwise_order(env) ? 0 : 1;
					env->editor.new_sector = 0;
					if (add_sector(env))
						return (ft_printf("Error while creating new sector\n"));
					free_current_vertices(env);
				}
				else
					add_vertex_to_current_sector(env, clicked_vertex);
			}
		}
		env->inputs.space = 0;
	}
	create_player(env);
	create_object(env);
	drag_element(env);
	if (env->inputs.right_click)
	{
		env->editor.center.x += env->sdl.mouse_x;
		env->editor.center.y += env->sdl.mouse_y;
	}
	if (env->inputs.enter)
	{
		if (!valid_map(env))
		{
			env->editor.in_game = 1;
			env->inputs.enter = 0;
			free_screen_sectors(env);
			if (init_screen_pos(env))
				return (ft_printf("Could not init screen pos\n"));
			update_camera_position(env);
			update_player_z(env);
			update_floor(env);
			SDL_SetRelativeMouseMode(1);
		}
		env->inputs.enter = 0;
	}
	if (env->inputs.s && env->inputs.ctrl && !valid_map(env))
	{
		if (save_map("maps/test.map", env))
			return (ft_printf("Could not save the map\n"));
		env->inputs.s = 0;
		env->inputs.ctrl = 0;
	}
	return (0);
}
