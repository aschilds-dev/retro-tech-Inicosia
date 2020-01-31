/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:50:05 by sipatry           #+#    #+#             */
/*   Updated: 2020/01/31 18:38:48 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "render.h"

void		update_enemies_z(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_enemies)
	{
		if (env->enemies[i].sector == env->sectors[env->selected_floor].num)
			env->enemies[i].pos.z = get_floor_at_pos(env->sectors[env->selected_floor], new_v3(env->enemies[i].pos.x, env->enemies[i].pos.y, 0), env);
		i++;
	}
}

static int	get_sprite_direction(t_enemies enemy)
{
	double	angle;

	angle = (int)((atan2(enemy.translated_pos.z, enemy.translated_pos.x)) * CONVERT_DEGREES) % 360;
	if (angle < 0)
		angle += 360;
	if (angle >= enemy.angle - 22.5 && angle < enemy.angle + 22.5)
		return (4);
	else if (angle >= enemy.angle + 22.5 && angle < enemy.angle + 67.5)
		return (5);
	else if (angle >= enemy.angle + 67.5 && angle < enemy.angle + 112.5)
		return (6);
	else if (angle >= enemy.angle + 112.5 && angle < enemy.angle + 157.5)
		return (7);
	else if (angle >= enemy.angle + 157.5 && angle < enemy.angle + 202.5)
		return (0);
	else if (angle >= enemy.angle + 202.5 && angle < enemy.angle + 247.5)
		return (1);
	else if (angle >= enemy.angle + 247.5 && angle < enemy.angle + 292.5)
		return (2);
	else if (angle >= enemy.angle + 292.5 && angle < enemy.angle + 337.5)
		return (3);
	else if (angle >= enemy.angle + 337.5)
		return (4);
	else if (angle < enemy.angle - 22.5 && angle >= enemy.angle - 67.5)
		return (3);
	else if (angle < enemy.angle - 67.5 && angle >= enemy.angle - 112.5)
		return (2);
	else if (angle < enemy.angle - 112.5 && angle >= enemy.angle - 157.5)
		return (1);
	else if (angle < enemy.angle - 157.5 && angle >= enemy.angle - 202.5)
		return (0);
	else if (angle < enemy.angle - 202.5 && angle >= enemy.angle - 247.5)
		return (7);
	else if (angle < enemy.angle - 247.5 && angle >= enemy.angle - 292.5)
		return (6);
	else if (angle < enemy.angle - 292.5 && angle >= enemy.angle - 337.5)
		return (5);
	else if (angle < enemy.angle - 337.5)
		return (4);
	else
		return (0);
}

static void		*enemy_loop(void *param)
{
	t_env			*env;
	t_enemies		enemy;
	t_render_object	orender;
	t_sprite		sprite;
	int				x;
	int				y;
	int				xend;
	int				yend;
	int				textx;
	int				texty;
	double			xalpha;
	double			yalpha;
	t_texture		texture;
	Uint32			*pixels;
	Uint32			*texture_pixels;
	double			*zbuffer;
	t_sector		sector;


	orender = ((t_enemy_thread*)param)->orender;
	env = ((t_enemy_thread*)param)->env;
	enemy = ((t_enemy_thread*)param)->enemy;
	sprite = env->enemy_sprites[enemy.sprite];
	texture = env->sprite_textures[sprite.texture];
	pixels = env->sdl.texture_pixels;
	texture_pixels = texture.str;
	zbuffer = env->zbuffer;
	x = ((t_enemy_thread*)param)->xstart;
	xend = ((t_enemy_thread*)param)->xend;
	yend = orender.yend;
	sector = env->sectors[enemy.sector];
	while (++x <= xend)
	{
		xalpha = (x - orender.x1) / orender.xrange;
		if (sprite.reversed[orender.index])
			xalpha = 1.0 - xalpha;
		textx = (1.0 - xalpha) * sprite.start[orender.index].x + xalpha * sprite.end[orender.index].x;
		y = orender.ystart;
		while (y < yend)
		{
			yalpha = (y - orender.y1) / orender.yrange;
			texty = (1.0 - yalpha) * sprite.start[orender.index].y + yalpha * sprite.end[orender.index].y;
			if ((enemy.rotated_pos.z < zbuffer[x + y * env->w]
				&& texture_pixels[textx
				+ texty * texture.surface->w] != 0xFFC10099))
			{
				env->enemies[enemy.num].seen = 1;
				if (env->editor.select && x == env->h_w && y == env->h_h)
				{
					reset_selection(env);
					env->selected_enemy = enemy.num;
				}
				if (!env->options.lighting
					|| (!sector.brightness && !sector.intensity))
					pixels[x + y * env->w] = texture_pixels[textx
					+ texty * texture.surface->w];
				else if (!sector.brightness)
					pixels[x + y * env->w] = apply_light_color(
					texture_pixels[textx + texty * texture.surface->w],
					orender.light_color, orender.intensity);
				else if (!sector.intensity)
					pixels[x + y * env->w] = apply_light_brightness(
					texture_pixels[textx + texty * texture.surface->w],
					orender.brightness);
				else
					pixels[x + y * env->w] = apply_light_both(
					texture_pixels[textx + texty * texture.surface->w],
					orender.light_color, orender.intensity, orender.brightness);
				if (env->enemies[enemy.num].hit)
					pixels[x + y * env->w] = blend_alpha(pixels[x + y * env->w], 0xFFFF0000, enemy_hurt(env, enemy.num));
				if (!env->editor.select && env->selected_enemy == enemy.num)
					pixels[x + y * env->w] = blend_alpha(pixels[x + y * env->w], 0x1abc9c, 128);
				zbuffer[x + y * env->w] = enemy.rotated_pos.z;
			}
			y++;
		}
	}
	return (NULL);
}

static int		threaded_enemy_loop(t_enemies enemy, t_render_object orender, t_env *env)
{
	t_enemy_thread	et[THREADS];
	pthread_t		threads[THREADS];
	int				i;

	i = 0;
	while (i < THREADS)
	{
		et[i].env = env;
		et[i].enemy = enemy;
		et[i].orender = orender;
		et[i].xstart = orender.xstart + (orender.xend - orender.xstart) / (double)THREADS * i;
		et[i].xend = orender.xstart + (orender.xend - orender.xstart) / (double)THREADS * (i + 1);
		if (pthread_create(&threads[i], NULL, enemy_loop, &et[i]))
			return (-1);
		i++;
	}
	while (i-- > 0)
		if (pthread_join(threads[i], NULL))
			return (-1);
	return (0);
}

int				draw_enemy(t_camera camera, t_enemies *enemy, t_env *env, int death_sprite)
{
	t_render_object	orender;
	t_sprite		sprite;
	t_v2			size;
	double			sprite_ratio;

	if (death_sprite >= 0)
		enemy->sprite = env->enemy_sprites[enemy->sprite].death_counterpart;
	orender.camera = camera;
	sprite = env->enemy_sprites[enemy->sprite];	
	project_enemy(&orender, *enemy, env);
	if (sprite.oriented)
		orender.index = get_sprite_direction(*enemy);
	else if (death_sprite >= 0)
		orender.index = death_sprite;
	else
		orender.index = 0;
	size.x = env->w * enemy->scale / enemy->rotated_pos.z;
	sprite_ratio = sprite.size[orender.index].x
	/ (double)sprite.size[orender.index].y;
	size.y = size.x * sprite_ratio;
	orender.x1 = orender.screen_pos.x - size.y / 4;
	orender.x2 = orender.screen_pos.x + size.y / 4;
	orender.y1 = orender.screen_pos.y - size.x / 2;
	orender.y2 = orender.screen_pos.y;
	orender.light_color = enemy->light_color;
	orender.brightness = enemy->brightness;
	orender.intensity = enemy->intensity;
	orender.xstart = ft_clamp(orender.x1, 0, env->w - 1);
	orender.ystart = ft_clamp(orender.y1 + 1, 0, env->h - 1);
	orender.xend = ft_clamp(orender.x2, 0, env->w - 1);
	orender.yend = ft_clamp(orender.y2, 0, env->h - 1);
	enemy->left = orender.xstart;
	enemy->right = orender.xend;
	enemy->top = orender.ystart;
	enemy->bottom = orender.yend;
	orender.xrange = orender.x2 - orender.x1;
	orender.yrange = orender.y2 - orender.y1;
	if (threaded_enemy_loop(*enemy, orender, env))
		return (-1);
	return (0);
}

static int	threaded_get_relative_pos(t_camera camera, t_env *env)
{
	int				i;
	t_enemy_thread	enemies_threads[THREADS];
	pthread_t		threads[THREADS];

	i = 0;
	while (i < THREADS)
	{
		enemies_threads[i].env = env;
		enemies_threads[i].camera = camera;
		enemies_threads[i].xstart = env->nb_enemies / (double)THREADS * i;
		enemies_threads[i].xend = env->nb_enemies / (double)THREADS * (i + 1);
		if (pthread_create(&threads[i], NULL, get_enemy_relative_pos,
		&enemies_threads[i]))
			return (-1);
		i++;
	}
	while (i-- > 0)
		if (pthread_join(threads[i], NULL))
			return (-1);
	return (0);
}

int			draw_enemies(t_camera camera, t_env *env)
{
	int	i;
	int dying_sprite;

	if (threaded_get_relative_pos(camera, env))
		return (-1);
	i = 0;
	while (i < env->nb_enemies)
	{
		dying_sprite = -1;
		if (env->enemies[i].state == FIRING)
			enemy_firing_anim(env, i);
		if (env->enemies[i].rotated_pos.z > 1 && env->enemies[i].exists)
		{
			env->enemies[i].seen = 0;
			if (!env->editor.in_game)
			{
				if (env->enemies[i].health <= 0)
					dying_sprite = dying_enemy(env, i,
					env->enemy_sprites[env->enemies[i].sprite].nb_death_sprites);
				if (env->enemies[i].state == RESTING)
					resting_enemy(env, i);
				else if (env->enemies[i].state == PURSUING)
					pursuing_enemy(env, i);
			}
			if (env->enemies[i].exists)
				if (draw_enemy(camera, &env->enemies[i], env, dying_sprite))
					return (-1);
		}
		i++;
	}
	return (0);
}
