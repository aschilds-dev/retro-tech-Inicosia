/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_projectiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:24:44 by gaerhard          #+#    #+#             */
/*   Updated: 2019/11/15 12:18:20 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "render.h"

static int	get_sprite_direction(t_projectile projectile)
{
	double	angle;

	angle = (int)((atan2(projectile.translated_pos.z, projectile.translated_pos.x)) * CONVERT_DEGREES) % 360;
	if (angle < 0)
		angle += 360;
	if (angle >= projectile.angle - 22.5 && angle < projectile.angle + 22.5)
		return (4);
	else if (angle >= projectile.angle + 22.5 && angle < projectile.angle + 67.5)
		return (5);
	else if (angle >= projectile.angle + 67.5 && angle < projectile.angle + 112.5)
		return (6);
	else if (angle >= projectile.angle + 112.5 && angle < projectile.angle + 157.5)
		return (7);
	else if (angle >= projectile.angle + 157.5 && angle < projectile.angle + 202.5)
		return (0);
	else if (angle >= projectile.angle + 202.5 && angle < projectile.angle + 247.5)
		return (1);
	else if (angle >= projectile.angle + 247.5 && angle < projectile.angle + 292.5)
		return (2);
	else if (angle >= projectile.angle + 292.5 && angle < projectile.angle + 337.5)
		return (3);
	else if (angle >= projectile.angle + 337.5)
		return (4);
	else if (angle < projectile.angle - 22.5 && angle >= projectile.angle - 67.5)
		return (3);
	else if (angle < projectile.angle - 67.5 && angle >= projectile.angle - 112.5)
		return (2);
	else if (angle < projectile.angle - 112.5 && angle >= projectile.angle - 157.5)
		return (1);
	else if (angle < projectile.angle - 157.5 && angle >= projectile.angle - 202.5)
		return (0);
	else if (angle < projectile.angle - 202.5 && angle >= projectile.angle - 247.5)
		return (7);
	else if (angle < projectile.angle - 247.5 && angle >= projectile.angle - 292.5)
		return (6);
	else if (angle < projectile.angle - 292.5 && angle >= projectile.angle - 337.5)
		return (5);
	else if (angle < projectile.angle - 337.5)
		return (4);
	else
		return (0);
}

static void		*projectile_loop(void *param)
{
	t_env				*env;
	t_projectile		projectile;
	t_render_projectile	prender;
	t_sprite			sprite;
	int					x;
	int					y;
	int					xend;
	int					yend;
	int					textx;
	int					texty;
	double				xalpha;
	double				yalpha;
	t_texture			texture;
	Uint32				*pixels;
	Uint32				*texture_pixels;
	double				*zbuffer;

	prender = ((t_projectile_thread*)param)->prender;
	env = ((t_projectile_thread*)param)->env;
	projectile = ((t_projectile_thread*)param)->projectile;
	sprite = env->object_sprites[projectile.sprite];
	texture = env->textures[sprite.texture];
	pixels = env->sdl.texture_pixels;
	texture_pixels = texture.str;
	zbuffer = env->zbuffer;
	x = ((t_projectile_thread*)param)->xstart;
	xend = ((t_projectile_thread*)param)->xend;
	yend = prender.yend;
	while (++x <= xend)
	{
		xalpha = (x - prender.x1) / prender.xrange;
		if (sprite.reversed[prender.index])
			xalpha = 1.0 - xalpha;
		textx = (1.0 - xalpha) * sprite.start[prender.index].x + xalpha * sprite.end[prender.index].x;
		y = prender.ystart;
		while (y < yend)
		{
			yalpha = (y - prender.y1) / prender.yrange;
			texty = (1.0 - yalpha) * sprite.start[prender.index].y + yalpha * sprite.end[prender.index].y;
			if ((projectile.rotated_pos.z < zbuffer[x + y * env->w]
						&& texture_pixels[textx + texty * texture.surface->w] != 0xFFC10099))
			{
				if (!env->options.lighting)
					pixels[x + y * env->w] = texture_pixels[textx + texty * texture.surface->w];
				else
					pixels[x + y * env->w] = apply_light(texture_pixels[textx + texty * texture.surface->w], prender.light_color, prender.brightness);
				zbuffer[x + y * env->w] = projectile.rotated_pos.z;
			}
			y++;
		}
	}
	return (NULL);
}

static void		threaded_projectile_loop(t_projectile projectile, t_render_projectile prender, t_env *env)
{
	t_projectile_thread	pt[THREADS];
	pthread_t			threads[THREADS];
	int					i;

	i = 0;
	while (i < THREADS)
	{
		pt[i].env = env;
		pt[i].projectile = projectile;
		pt[i].prender = prender;
		pt[i].xstart = prender.xstart + (prender.xend - prender.xstart) / (double)THREADS * i;
		pt[i].xend = prender.xstart + (prender.xend - prender.xstart) / (double)THREADS * (i + 1);
		pthread_create(&threads[i], NULL, projectile_loop, &pt[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(threads[i], NULL);
}

void		draw_projectile(t_camera camera, t_projectile *projectile, t_env *env)
{
	t_render_projectile	prender;
	t_sprite			sprite;

	sprite = env->object_sprites[projectile->sprite];
	prender.camera = camera;
	project_projectile(&prender, *projectile, env);
	prender.index = 0;
	if (sprite.oriented)
		prender.index = get_sprite_direction(*projectile);
	prender.x1 = prender.screen_pos.x - sprite.size[prender.index].x / 2.0 / (projectile->rotated_pos.z / projectile->scale);
	prender.y1 = prender.screen_pos.y - sprite.size[prender.index].y / (projectile->rotated_pos.z / projectile->scale);
	prender.x2 = prender.screen_pos.x + sprite.size[prender.index].x / 2.0 / (projectile->rotated_pos.z / projectile->scale);
	prender.y2 = prender.screen_pos.y;
	prender.light_color = projectile->light_color;
	prender.brightness = projectile->brightness;
	prender.xstart = ft_clamp(prender.x1, 0, env->w - 1);
	prender.ystart = ft_clamp(prender.y1 + 1, 0, env->h - 1);
	prender.xend = ft_clamp(prender.x2, 0, env->w - 1);
	prender.yend = ft_clamp(prender.y2, 0, env->h - 1);
	projectile->left = prender.xstart;
	projectile->right = prender.xend;
	projectile->top = prender.ystart;
	projectile->bottom = prender.yend;
	prender.xrange = prender.x2 - prender.x1;
	prender.yrange = prender.y2 - prender.y1;
	threaded_projectile_loop(*projectile, prender, env);
}

void		draw_projectiles(t_camera camera, t_env *env)
{
	t_list *tmp;

	get_projectile_relative_pos(camera, env);
	tmp = env->projectiles;
	if (tmp)
	{
		if (((t_projectile*)tmp->content)->rotated_pos.z > 1 && ((t_projectile*)tmp->content)->exists)
			draw_projectile(camera, ((t_projectile*)tmp->content), env);
		while (tmp->next)
		{
			tmp = tmp->next;
			if (((t_projectile*)tmp->content)->rotated_pos.z > 1 && ((t_projectile*)tmp->content)->exists)
				draw_projectile(camera, ((t_projectile*)tmp->content), env);
		}
	}
}