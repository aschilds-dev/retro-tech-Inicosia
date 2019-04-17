/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:26:12 by lnicosia          #+#    #+#             */
/*   Updated: 2019/04/17 13:28:03 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int		main(int ac, char **av)
{
	t_env	env;

	if (ac != 2)
		return (ft_printf("No map file.\n"));
	env.w = 1366;
	env.h = 768;
	env.running = 1;
	if (init_sdl(&env) != 0)
	{
		free_all(&env);
		return (ft_printf("Init error\nExiting the programm..\n"));
	}
	ft_printf("Parsing\n");
	parsing(open(av[1], O_RDONLY), &env);
	init_options(&env);
	ft_printf("Origin sector: %d\n", env.player.sector);
	//check_parsing(&env);
	ft_printf("[OK]\n");
	SDL_SetRelativeMouseMode(1);
	env.player.speed = 0.5;
	//draw(&env);
	while (env.running)
	{
		if (env.sdl.render)
		{
			clear_image(&env);
			draw(&env);
			env.sdl.render = 0;
		}
		if (env.options.show_minimap)
			minimap(&env);
		if (env.options.show_fps)
			fps(&env);
		update_screen(&env);
		while (SDL_PollEvent(&env.sdl.event))
		{
			env.sdl.render = 1;
			if (env.sdl.event.type == SDL_QUIT || (env.sdl.event.type == SDL_KEYUP && env.sdl.event.key.keysym.sym == SDLK_ESCAPE))
				env.running = 0;
			else if (env.sdl.event.type == SDL_KEYDOWN)
				move_player(&env);
			else if (env.sdl.event.type == SDL_KEYUP)
				options(&env);
		}
		SDL_GetRelativeMouseState(&env.sdl.mouse_x, &env.sdl.mouse_y);
		view(&env);
		SDL_Delay(5);
	}
	return (0);
}
