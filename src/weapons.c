/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:07:34 by gaerhard          #+#    #+#             */
/*   Updated: 2019/07/03 15:26:25 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void    draw_weapon(t_env *env, int sprite)
{
    int			x;
    int			y;
    int			window_w;
    int			window_h;
    int			texture_w;
    int			texture_h;
	Uint32		*pixels;
	Uint32		*texture_pixels;

	pixels = env->sdl.texture_pixels;
	texture_pixels = env->textures[sprite].str;
	texture_w = env->textures[sprite].surface->w;
	texture_h = env->textures[sprite].surface->h;
    window_w = (int)(env->w - texture_w) / 1.5;
    window_h = (env->h - texture_h) + env->weapons[0].weapon_switch;
    x = 0;
    while (x < texture_w)
    {
        y = 0;
        while (y < texture_h  && (window_h + y) < env->h)
        {
            if (texture_pixels[x + texture_w * y] != 0xFFC10099)
                pixels[(window_w + x) + env->w * (window_h + y)] = 
                    texture_pixels[x + texture_w * y];
            y++;
        }
        x++;
    }
}

void    weapon_animation(t_env *env, int nb)
{
    if (env->shot.start == 0)
	{
        env->shot.on_going = 1;
		env->shot.start = SDL_GetTicks();
        if (env->weapons[nb].ammo <= 0)
        {
            env->weapons[nb].no_ammo = 1;
			Mix_PlayChannel(2, env->weapons[nb].empty, 0);
        }
        else
        {
            env->weapons[nb].no_ammo = 0;
            Mix_PlayChannel(2, env->weapons[nb].sound, 0);
            env->weapons[nb].ammo--;
        }
    }
    if (!env->weapons[nb].no_ammo)
    {
        if (env->time.milli_s > env->shot.start + 70 && ((env->time.milli_s - env->shot.start) / 70 < env->weapons[nb].nb_sprites))
            draw_weapon(env, env->weapons[nb].first_sprite + (int)((env->time.milli_s - env->shot.start) / 70));
        else
            draw_weapon(env, env->weapons[nb].first_sprite);
    }
    else
    {
        draw_weapon(env, env->weapons[nb].first_sprite);
    }
    if ((int)((env->time.milli_s - env->shot.start)) >= env->weapons[nb].nb_sprites * 70)
    {
        env->shot.start = 0;
        env->shot.on_going = 0;
    }
}

void    weapon_change(t_env *env)
{
    int time_spent;

    if (env->weapon_change.start == 0)
    {
        env->weapon_change.start = SDL_GetTicks();
        env->weapon_change.on_going = 1;
    }
    time_spent = env->time.milli_s - env->weapon_change.start;
    if (time_spent > 70 && time_spent / 70 <= 4)
        env->weapons[0].weapon_switch  = 75 * (int)(time_spent / 70);
    if (time_spent > 4 * 70)
    {
        if (env->sdl.event.wheel.y > 0)
		    env->player.curr_weapon = (env->player.curr_weapon >= NB_WEAPONS - 1 ? 0 : env->player.curr_weapon + 1);
	    else if (env->sdl.event.wheel.y < 0)
	        env->player.curr_weapon = (env->player.curr_weapon <= 0 ? NB_WEAPONS - 1 : env->player.curr_weapon - 1);
        env->weapons[0].weapon_switch = 0;
        env->weapon_change.start = 0;
        env->weapon_change.on_going = 0;
    }
}

void    print_ammo(t_env *env)
{
    char *str;

    str = ft_itoa(env->weapons[env->player.curr_weapon].ammo);
    print_text(new_point(env->h - env->h / 12, env->w - env->w / 14 - 5), new_printable_text(str, env->sdl.fonts.amazdoom50, 0xA1A1A100, 0), env);
    str = "/";
    print_text(new_point(env->h - env->h / 12, env->w - env->w / 19), new_printable_text(str, env->sdl.fonts.amazdoom50, 0xA1A1A100, 0), env);
    str = ft_itoa(env->weapons[env->player.curr_weapon].max_ammo);
    print_text(new_point(env->h - env->h / 12, env->w - env->w / 24), new_printable_text(str, env->sdl.fonts.amazdoom50, 0xA1A1A100, 0), env);
}
