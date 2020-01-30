/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ttf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:43:13 by lnicosia          #+#    #+#             */
/*   Updated: 2020/01/30 14:40:51 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
** TODO Protection
*/

int		init_ttf(t_env *env)
{
	ft_printf("Initializing fonts..\n");
	if (TTF_Init() == -1)
		return (ft_printf("SDL_Init Error: %s\n", TTF_GetError()));
	if (!(env->sdl.fonts.amazdoom70 =
		TTF_OpenFont("fonts/amazdoom/AmazDoomLeft.ttf", 70)))
	{
		ft_printf("TTF_OpenFont error: %s\n", TTF_GetError());
		return (-1);
	}
	if (!(env->sdl.fonts.amazdoom50 =
		TTF_OpenFont("fonts/amazdoom/AmazDoomLeft.ttf", 50)))
	{
		ft_printf("TTF_OpenFont error: %s\n", TTF_GetError());
		return (-1);
	}
	if (!(env->sdl.fonts.amazdoom20 =
		TTF_OpenFont("fonts/amazdoom/AmazDoomLeft.ttf", 20)))
	{
		ft_printf("TTF_OpenFont error: %s\n", TTF_GetError());
		return (-1);
	}
	if (!(env->sdl.fonts.alice30 =
		TTF_OpenFont("fonts/alice/Alice-Regular.ttf", 30)))
	{
		ft_printf("TTF_OpenFont error: %s\n", TTF_GetError());
		return (-1);
	}
	if (!(env->sdl.fonts.alice70 =
		TTF_OpenFont("fonts/alice/Alice-Regular.ttf", 70)))
	{
		ft_printf("TTF_OpenFont error: %s\n", TTF_GetError());
		return (-1);
	}
	if (!(env->sdl.fonts.bebasneue =
		TTF_OpenFont("fonts/bebas_neue/BebasNeue-Regular.ttf", 20)))
	{
		ft_printf("TTF_OpenFont error: %s\n", TTF_GetError());
		return (-1);
	}
	if (!(env->sdl.fonts.montserrat20 =
		TTF_OpenFont("fonts/montserrat/Montserrat-Regular.ttf", 20)))
	{
		ft_printf("TTF_OpenFont error: %s\n", TTF_GetError());
		return (-1);
	}
	if (!(env->sdl.fonts.playfair_display20 =
		TTF_OpenFont("fonts/playfair-display/PlayfairDisplay-Regular.ttf",
		20)))
	{
		ft_printf("TTF_OpenFont error: %s\n", TTF_GetError());
		return (-1);
	}
	if (!(env->sdl.fonts.lato20 =
		TTF_OpenFont("fonts/lato/Lato-Regular.ttf", 20)))
	{
		ft_printf("TTF_OpenFont error: %s\n", TTF_GetError());
		return (-1);
	}
	if (!(env->sdl.fonts.lato10 =
		TTF_OpenFont("fonts/lato/Lato-Regular.ttf", 10)))
	{
		ft_printf("TTF_OpenFont error: %s\n", TTF_GetError());
		return (-1);
	}
	if (!(env->sdl.fonts.lato15 =
		TTF_OpenFont("fonts/lato/Lato-Regular.ttf", 15)))
	{
		ft_printf("TTF_OpenFont error: %s\n", TTF_GetError());
		return (-1);
	}
	if (!(env->sdl.fonts.lato50 =
		TTF_OpenFont("fonts/lato/Lato-Regular.ttf", 50)))
	{
		ft_printf("TTF_OpenFont error: %s\n", TTF_GetError());
		return (-1);
	}
	return (0);
}
