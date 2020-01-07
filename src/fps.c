/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 12:21:11 by lnicosia          #+#    #+#             */
/*   Updated: 2019/11/28 11:43:18 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	fps(t_env *env)
{
	Uint32			new_time;
	double			fps;

	new_time = SDL_GetTicks();
	//ft_printf("time = %d\n", (int)(new_time - env->sdl.time));
	fps = 1000 / (new_time - env->sdl.time);
	env->fps_count++;
	if (new_time - env->frame_timer >= 1000)
	{
		env->frame_timer = new_time;
		env->fps = env->fps_count;
		env->fps_count = 0;
	}
	if (new_time > 2000)
	{
		if (env->options.p)
		{
			if (!env->avrg_fps)
				env->avrg_fps = fps;
			if (fps > env->max_fps)
				env->max_fps = fps;
			if (fps < env->min_fps)
				env->min_fps = fps;
			env->avrg_fps = (env->avrg_fps + fps) / 2;
		}
		else
		{
			if (!env->avrg_fps2)
				env->avrg_fps2 = fps;
			if (fps > env->max_fps2)
				env->max_fps2 = fps;
			if (fps < env->min_fps2)
				env->min_fps2 = fps;
			env->avrg_fps2 = (env->avrg_fps2 + fps) / 2;
		}
	}
	print_text(new_point(0, 10), new_printable_text(
				ft_sitoa(env->fps),
				env->sdl.fonts.lato20,
				0xFFFFFFFF,
				0),
			env);
	env->sdl.time = new_time;
}
