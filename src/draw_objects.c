/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   draw_objects.c									 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: gaerhard <gaerhard@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2019/06/20 15:04:12 by lnicosia		  #+#	#+#			 */
/*   Updated: 2019/11/28 18:32:35 by lnicosia         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "env.h"
#include "render.h"

void		update_objects_z(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_objects)
	{
		if (env->objects[i].sector == env->sectors[env->selected_floor].num)
			env->objects[i].pos.z = get_floor_at_pos(env->sectors[env->selected_floor], new_v3(env->objects[i].pos.x, env->objects[i].pos.y, 0), env);
		i++;
	}
}

static int	get_sprite_direction(t_object object)
{
	double	angle;

	angle = (int)((atan2(object.translated_pos.z, object.translated_pos.x)) * CONVERT_DEGREES) % 360;
	if (angle < 0)
		angle += 360;
	if (angle >= object.angle - 22.5 && angle < object.angle + 22.5)
		return (4);
	else if (angle >= object.angle + 22.5 && angle < object.angle + 67.5)
		return (5);
	else if (angle >= object.angle + 67.5 && angle < object.angle + 112.5)
		return (6);
	else if (angle >= object.angle + 112.5 && angle < object.angle + 157.5)
		return (7);
	else if (angle >= object.angle + 157.5 && angle < object.angle + 202.5)
		return (0);
	else if (angle >= object.angle + 202.5 && angle < object.angle + 247.5)
		return (1);
	else if (angle >= object.angle + 247.5 && angle < object.angle + 292.5)
		return (2);
	else if (angle >= object.angle + 292.5 && angle < object.angle + 337.5)
		return (3);
	else if (angle >= object.angle + 337.5)
		return (4);
	else if (angle < object.angle - 22.5 && angle >= object.angle - 67.5)
		return (3);
	else if (angle < object.angle - 67.5 && angle >= object.angle - 112.5)
		return (2);
	else if (angle < object.angle - 112.5 && angle >= object.angle - 157.5)
		return (1);
	else if (angle < object.angle - 157.5 && angle >= object.angle - 202.5)
		return (0);
	else if (angle < object.angle - 202.5 && angle >= object.angle - 247.5)
		return (7);
	else if (angle < object.angle - 247.5 && angle >= object.angle - 292.5)
		return (6);
	else if (angle < object.angle - 292.5 && angle >= object.angle - 337.5)
		return (5);
	else if (angle < object.angle - 337.5)
		return (4);
	else
		return (0);
}

static void		*object_loop(void *param)
{
	t_env			*env;
	t_object		object;
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


	orender = ((t_object_thread*)param)->orender;
	env = ((t_object_thread*)param)->env;
	object = ((t_object_thread*)param)->object;
	sprite = env->object_sprites[object.sprite];
	texture = env->sprite_textures[sprite.texture];
	pixels = env->sdl.texture_pixels;
	texture_pixels = texture.str;
	zbuffer = env->zbuffer;
	xend = ((t_object_thread*)param)->xend;
	y = orender.ystart;
	yend = orender.yend;
	sector = env->sectors[object.sector];
	while (++y <= yend)
	{
		yalpha = (y - orender.y1) / orender.yrange;
		texty = (1.0 - yalpha) * sprite.start[orender.index].y + yalpha * sprite.end[orender.index].y;
		x = ((t_object_thread*)param)->xstart;
		while (x < xend)
		{
			xalpha = (x - orender.x1) / orender.xrange;
			if (sprite.reversed[orender.index])
				xalpha = 1.0 - xalpha;
			textx = (1.0 - xalpha) * sprite.start[orender.index].x + xalpha * sprite.end[orender.index].x;
			if ((object.rotated_pos.z < zbuffer[x + y * env->w]
						&& texture_pixels[textx + texty * texture.surface->w] != 0xFFC10099))
			{
				env->objects[object.num].seen = 1;
				if (env->editor.select && x == env->h_w && y == env->h_h)
				{
					reset_selection(env);
					env->selected_object = object.num;
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
				if (!env->editor.select && env->selected_object == object.num)
					pixels[x + y * env->w] = blend_alpha(pixels[x + y * env->w], 0xFF00FF00, 128);
				zbuffer[x + y * env->w] = object.rotated_pos.z;
			}
			x++;
		}
	}
	return (NULL);
}

static void		threaded_object_loop(t_object object, t_render_object orender, t_env *env)
{
	t_object_thread	ot[THREADS];
	pthread_t		threads[THREADS];
	int				i;

	i = 0;
	while (i < THREADS)
	{
		ot[i].env = env;
		ot[i].object = object;
		ot[i].orender = orender;
		ot[i].xstart = orender.xstart + (orender.xend - orender.xstart) / (double)THREADS * i;
		ot[i].xend = orender.xstart + (orender.xend - orender.xstart) / (double)THREADS * (i + 1);
		pthread_create(&threads[i], NULL, object_loop, &ot[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(threads[i], NULL);
}

void		draw_object(t_camera camera, t_object *object, t_env *env, int death_sprite)
{
	t_render_object	orender;
	t_sprite		sprite;

	if (death_sprite >= 0)
		object->sprite = env->object_sprites[object->sprite].death_counterpart;
	sprite = env->object_sprites[object->sprite];
	orender.camera = camera;
	project_object(&orender, *object, env);
	if (sprite.oriented)
		orender.index = get_sprite_direction(*object);
	else if (death_sprite >= 0)
		orender.index = death_sprite;
	else
		orender.index = 0;
	orender.x1 = orender.screen_pos.x - sprite.size[orender.index].x / 2.0 / (object->rotated_pos.z / object->scale);
	orender.y1 = orender.screen_pos.y - sprite.size[orender.index].y / (object->rotated_pos.z / object->scale);
	orender.x2 = orender.screen_pos.x + sprite.size[orender.index].x / 2.0 / (object->rotated_pos.z / object->scale);
	orender.y2 = orender.screen_pos.y;
	orender.light_color = object->light_color;
	orender.brightness = object->brightness;
	orender.intensity = object->intensity;
	orender.xstart = ft_clamp(orender.x1, 0, env->w - 1);
	orender.ystart = ft_clamp(orender.y1 + 1, 0, env->h - 1);
	orender.xend = ft_clamp(orender.x2, 0, env->w - 1);
	orender.yend = ft_clamp(orender.y2, 0, env->h - 1);
	object->left = orender.xstart;
	object->right = orender.xend;
	object->top = orender.ystart;
	object->bottom = orender.yend;
	orender.xrange = orender.x2 - orender.x1;
	orender.yrange = orender.y2 - orender.y1;
	threaded_object_loop(*object, orender, env);
}

static void	threaded_get_relative_pos(t_camera camera, t_env *env)
{
	int				i;
	t_object_thread	object_threads[THREADS];
	pthread_t		threads[THREADS];

	env->current_object = 0;
	i = 0;
	while (i < THREADS)
	{
		object_threads[i].env = env;
		object_threads[i].camera = camera;
		object_threads[i].xstart = env->nb_objects / (double)THREADS * i;
		object_threads[i].xend = env->nb_objects / (double)THREADS * (i + 1);
		pthread_create(&threads[i], NULL, get_object_relative_pos, &object_threads[i]);
		i++;
	}
	while (i-- > 0)
		pthread_join(threads[i], NULL);
}

void		draw_objects(t_camera camera, t_env *env)
{
	int	i;
	int	death_sprite;

	threaded_get_relative_pos(camera, env);
	i = 0;
	while (i < env->nb_objects)
	{
		death_sprite = -1;
		if (env->objects[i].rotated_pos.z > 1 && env->objects[i].exists)
		{
			env->objects[i].seen = 0;
			if (env->objects[i].health <= 0 && env->objects[i].exists)
			{
				if (env->object_sprites[env->objects[i].sprite].nb_death_sprites > 1)
					death_sprite = object_destruction(env, i, env->object_sprites[env->objects[i].sprite].nb_death_sprites);
				else
					env->objects[i].sprite = env->object_sprites[env->objects[i].sprite].death_counterpart;
			}
			if (env->objects[i].exists && env->objects[i].nb_rest_state > 1)
				object_anim_loop(env, i);
			draw_object(camera, &env->objects[i], env, death_sprite);
		}
		i++;
	}
}
