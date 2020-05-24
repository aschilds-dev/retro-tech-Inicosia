/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_skybox_floor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 10:06:35 by lnicosia          #+#    #+#             */
/*   Updated: 2020/04/29 17:32:22 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"

void	get_skybox_floor_texture(t_drawer *drawer, t_render *render,
t_skybox_data wall_data, t_env *env)
{
	t_texture	*texture;

	if (wall_data.mode == CEILING)
		texture = &env->skyboxes[abs(env->sectors[render->sector->num].
		ceiling_texture) - 1].textures[0];
	else if (wall_data.mode == FLOOR)
		texture = &env->skyboxes[abs(env->sectors[render->sector->num].
		floor_texture) - 1].textures[0];
	else
		texture = &env->skyboxes[abs(env->sectors[render->sector->num].
		textures[wall_data.i]) - 1].textures[0];
	drawer->texture_w = texture->surface->w;
	drawer->texture_h = texture->surface->h;
	drawer->texture_pixels = texture->str;
}

void	get_skybox_floor_z(t_drawer *drawer, t_render *render,
t_skybox_data wall_data)
{
	drawer->alpha =
	render->floor_start / (double)(drawer->i - render->floor_horizon);
	if (wall_data.mode == CEILING)
	{
		drawer->salpha =
		(wall_data.max_ceiling - drawer->i) / render->ceiling_height;
		drawer->divider =
		1 / (render->camera->near_z + drawer->salpha * render->zrange);
		drawer->z = render->z_near_z * drawer->divider;
	}
	else if (wall_data.mode == FLOOR)
	{
		drawer->salpha =
		(drawer->i - wall_data.max_floor) / render->floor_height;
		drawer->divider =
		1 / (render->camera->near_z + drawer->salpha * render->zrange);
		drawer->z = render->z_near_z * drawer->divider;
	}
	else
		drawer->z = wall_data.z;
}

void	click_on_skybox_floor(t_render *render, t_skybox_data wall_data,
t_env *env)
{
	if (env->playing)
		reset_hover(env);
	if (env->editor.select)
	{
		reset_selection(env);
		if (wall_data.mode == CEILING)
			env->selected_ceiling = render->sector->num;
		else if (wall_data.mode == FLOOR)
			env->selected_floor = render->sector->num;
		else
		{
			if (env->editor.in_game)
			{
				env->editor.selected_sector = render->sector->num;
				env->editor.selected_wall = wall_data.i;
			}
			env->selected_wall1 =
			env->sectors[render->sector->num].vertices[wall_data.i];
			env->selected_wall2 =
			env->sectors[render->sector->num].vertices[wall_data.i + 1];
		}
		tabs_gestion(env);
	}
}

void	put_skybox_floor_pixel(t_drawer *drawer, t_render *render,
t_skybox_data wall_data, t_env *env)
{
	drawer->y = (drawer->alpha * render->texel.y + (1.0 - drawer->alpha) * 5)
	* drawer->texture_h / 10;
	drawer->x = (drawer->alpha * render->texel.x + (1.0 - drawer->alpha) * 5)
	* drawer->texture_w / 10;
	if (drawer->y >= drawer->texture_h || drawer->y < 0)
		drawer->y = ft_abs((int)drawer->y % drawer->texture_h);
	if (drawer->x >= drawer->texture_w || drawer->x < 0)
		drawer->x = ft_abs((int)drawer->x % drawer->texture_w);
	drawer->y = drawer->texture_h - drawer->y;
	drawer->x = drawer->texture_w - drawer->x;
	if (drawer->x >= 0 && drawer->x < drawer->texture_w
		&& drawer->y >= 0 && drawer->y < drawer->texture_h)
	{
		env->sdl.texture_pixels[drawer->coord] = drawer->texture_pixels[
		(int)drawer->x + drawer->texture_w * (int)drawer->y];
		if (env->editor.in_game && render->selected && !env->editor.select
			&& (wall_data.mode != CEILING || env->selected_ceiling_sprite == -1)
			&& (wall_data.mode != FLOOR || env->selected_floor_sprite == -1))
			env->sdl.texture_pixels[drawer->coord] =
			blend_alpha(env->sdl.texture_pixels[drawer->coord], 0x1ABC9C, 128);
		env->zbuffer[drawer->coord] = drawer->z;
	}
}

/*
**	Draw a vertical vline on the screen at vline.x
*/

void	draw_skybox_floor(t_vline vline, t_skybox_data wall_data,
t_render *render, t_env *env)
{
	t_drawer	drawer;

	drawer.vline = vline;
	get_skybox_floor_texture(&drawer, render, wall_data, env);
	drawer.i = drawer.vline.start;
	while (drawer.i <= drawer.vline.end)
	{
		drawer.coord = drawer.vline.x + env->w * drawer.i;
		get_skybox_floor_z(&drawer, render, wall_data);
		if (drawer.z >= env->zbuffer[drawer.coord])
		{
			drawer.i++;
			continue;
		}
		if ((env->editor.tab && drawer.vline.x == env->sdl.mx
			&& drawer.i == env->sdl.my)
			|| (!env->editor.tab && drawer.vline.x == env->h_w
			&& drawer.i == env->h_h))
		{
			click_on_skybox_floor(render, wall_data, env);
		}
		put_skybox_floor_pixel(&drawer, render, wall_data, env);
		drawer.i++;
	}
}
