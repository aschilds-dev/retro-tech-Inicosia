/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 15:17:30 by lnicosia          #+#    #+#             */
/*   Updated: 2020/01/31 18:37:06 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		init_screen_size(t_env *env)
{
	env->screen_w[2] = 2560;
	env->screen_h[2] = 1440;
	env->screen_w[1] = 1920;
	env->screen_h[1] = 1080;
	env->screen_w[0] = 1600;
	env->screen_h[0] = 900;
	if (!(env->res[2] = ft_strdup("2560 x 1440")))
		return (ft_printf("Could not malloc screen size 0\n"));
	if (!(env->res[1] = ft_strdup("1920 x 1080")))
		return (ft_printf("Could not malloc screen size 1\n"));
	if (!(env->res[0] = ft_strdup("1600 x 900")))
		return (ft_printf("Could not malloc screen size 2\n"));
	set_screen_size(env);
	return (0);
}

void	set_screen_size(t_env *env)
{
	env->w = env->screen_w[env->i];
	env->h = env->screen_h[env->i];
	env->h_w = env->w / 2;
	env->h_h = env->h / 2;
}

int		keyup(t_env *env)
{
	if (env->sdl.event.key.keysym.sym == SDLK_c)
		env->options.contouring = env->options.contouring ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_r)
		ft_printf("will reload one day\n");
	if (env->sdl.event.key.keysym.sym == SDLK_m)
	{
		env->options.show_minimap = env->options.show_minimap ? 0 : 1;
		env->options.mipmapping = env->options.mipmapping ? 0 : 1;
	}
	if (env->sdl.event.key.keysym.sym == SDLK_f)
		env->options.show_fps = env->options.show_fps ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_x)
		env->options.wall_lover = env->options.wall_lover ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_j)
		env->options.color_clipping = env->options.color_clipping ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_g)
		env->options.wall_color = env->options.wall_color ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_t)
		env->options.test = env->options.test ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_i)
		env->options.clipping = env->options.clipping ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_n)
		env->drawing = env->drawing ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_p)
		env->options.p = env->options.p ? 0 : 1;
	if (env->sdl.event.key.keysym.sym == SDLK_e
		&& env->hovered_wall_sprite_sprite != -1
		&& env->hovered_wall_sprite_wall != -1
		&& env->hovered_wall_sprite_sector != -1
		&& env->sectors[env->hovered_wall_sprite_sector]
		.wall_sprites[env->hovered_wall_sprite_wall]
		.nb_press_events[env->hovered_wall_sprite_sprite]
		&& env->sectors[env->hovered_wall_sprite_sector]
		.wall_sprites[env->hovered_wall_sprite_wall]
		.press_events[env->hovered_wall_sprite_sprite])
	{
		if (start_event(&env->sectors[env->hovered_wall_sprite_sector]
		.wall_sprites[env->hovered_wall_sprite_wall]
		.press_events[env->hovered_wall_sprite_sprite],
		&env->sectors[env->hovered_wall_sprite_sector]
		.wall_sprites[env->hovered_wall_sprite_wall]
		.nb_press_events[env->hovered_wall_sprite_sprite], env))
			return (-1);
		if (env->sectors[env->hovered_wall_sprite_sector]
		.wall_sprites[env->hovered_wall_sprite_wall]
		.nb_press_events[env->hovered_wall_sprite_sprite] == 0)
		{
			env->hovered_wall_sprite_wall = -1;
			env->hovered_wall_sprite_sector = -1;
			env->hovered_wall_sprite_sprite = -1;
		}
	}
	if (env->sdl.event.key.keysym.sym == SDLK_o)
	{
		//env->option = env->option ? 0 : 1;
		if (env->option)
			SDL_SetRelativeMouseMode(0);
		else if (env->player.health > 0)
			SDL_SetRelativeMouseMode(1);
	}
	if (env->sdl.event.key.keysym.sym == SDLK_TAB)
		env->options.zbuffer = env->options.zbuffer ? 0 : 1;
	if (env->confirmation_box.state)
	{
		if (confirmation_box_keyup(&env->confirmation_box, env))
			return (-1);
	}
	return (0);
}

int		open_options(t_env *env)
{
	SDL_SetRelativeMouseMode(0);
	clear_image(env);
	update_screen(env);
	if (env->aplicate_changes)
	{
		free_all_sdl_relative(env);
		set_screen_size(env);
		set_camera(&env->player.camera, env);
		if (set_sdl(env))
			return (ft_printf("Could not re load sdl\n"));
		env->inputs.left_click = 0;
		env->aplicate_changes = 0;
	}
	return (0);
}
