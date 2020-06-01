/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_hud.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 10:25:22 by marvin            #+#    #+#             */
/*   Updated: 2020/04/29 16:24:26 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "draw.h"

void	armor_life_hud(t_env *env)
{
	int x;
	int y;
	int window_h;
	int window_w;

	x = 0;
	window_w = 0;
	window_h = (env->h - env->sprite_textures[ARMOR_LIFE_HUD].surface->h);
	while (x < env->sprite_textures[ARMOR_LIFE_HUD].surface->w && window_w +
		x < env->w)
	{
		y = 0;
		while (y < env->sprite_textures[ARMOR_LIFE_HUD].surface->h
			&& (window_h + y) < env->h)
		{
			if (env->sprite_textures[ARMOR_LIFE_HUD].str[x + env->
				sprite_textures[ARMOR_LIFE_HUD].surface->w * y] != 0xFFC10099)
				env->sdl.texture_pixels[(window_w + x) + env->w
				* (window_h + y)] = env->sprite_textures[ARMOR_LIFE_HUD].
				str[x + env->sprite_textures[ARMOR_LIFE_HUD].surface->w * y];
			y++;
		}
		x++;
	}
}

void	ammo_hud(t_env *env)
{
	int x;
	int y;
	int window_h;
	int window_w;

	x = 0;
	window_w = (int)(env->w) - env->sprite_textures[AMMO_HUD].surface->w;
	window_h = (env->h - env->sprite_textures[AMMO_HUD].surface->h);
	while (x < env->sprite_textures[AMMO_HUD].surface->w)
	{
		y = 0;
		while (y < env->sprite_textures[AMMO_HUD].surface->h
			&& (window_h + y) < env->h)
		{
			if (env->sprite_textures[AMMO_HUD].str[x +
				env->sprite_textures[AMMO_HUD].surface->w * y] != 0xFFC10099)
				env->sdl.texture_pixels[(window_w + x) + env->w
				* (window_h + y)] = env->sprite_textures[AMMO_HUD].
				str[x + env->sprite_textures[AMMO_HUD].surface->w * y];
			y++;
		}
		x++;
	}
}

int		draw_hud(t_env *env)
{
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d", env->player.health);
	armor_life_hud(env);
	ammo_hud(env);
	if (print_text(new_point(830, 300), new_printable_text(env->snprintf,
	env->sdl.fonts.amazdoom50, 0xFFf1f2f3, 0), env))
		return (-1);
	ft_snprintf(env->snprintf, SNPRINTF_SIZE, "%d", env->player.armor);
	if (print_text(new_point(830, 80), new_printable_text(env->snprintf,
	env->sdl.fonts.amazdoom50, 0xFFf1f2f3, 0), env))
		return (-1);
	if (print_ammo(env))
		return (-1);
	draw_inventory(env);
	return (0);
}
