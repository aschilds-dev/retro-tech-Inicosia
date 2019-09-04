/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 10:06:35 by lnicosia          #+#    #+#             */
/*   Updated: 2019/09/04 17:49:58 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "render.h"

/*
**	Draw a vertical vline on the screen at vline.x
*/

void	draw_vline(t_vline vline, t_render render, t_env *env)
{
	int			i;
	double		yalpha;
	double		y;
	double		x;
	Uint32		*pixels;
	Uint32		*texture_pixels;
	double		*zbuffer;
	t_texture	texture;
	int			texture_w;
	int			texture_h;
	int			start_coord;
	int			end_coord;
	int			coord;

	texture = env->textures[render.texture];
	pixels = env->sdl.texture_pixels;
	texture_pixels = texture.str;
	zbuffer = env->depth_array;
	texture_w = texture.surface->w;
	texture_h = texture.surface->h;
	x = render.alpha * render.projected_texture_w * render.z;
	if (x != x)
		return ;
	while (x >= texture_w)
		x -= texture_w;
	while (x < 0)
		x += texture_w;
	x = ft_fclamp(x, 0, texture_w);
	i = vline.start;
	while (i <= vline.end)
	{
		coord = vline.x + env->w * i;
		if (render.z >= zbuffer[coord])
		{
			i++;
			continue;
		}
		if (env->editor.select && vline.x == env->h_w && i == env->h_h)
		{
			if (env->editor.in_game)
			{
				env->editor.selected_sector = env->sectors[render.sector].num;
				env->editor.selected_wall = render.i;
			}
			env->selected_wall1 = env->sectors[render.sector].vertices[render.i];
			env->selected_wall2 = env->sectors[render.sector].vertices[render.i + 1];
			env->selected_floor = -1;
			env->selected_ceiling = -1;
			env->selected_object = -1;
			env->selected_enemy = -1;
			//env->editor.select = 0;
		}
		yalpha = 1 - (i - render.max_ceiling) / render.line_height;
		y = yalpha * render.projected_texture_h;
		while (y >= texture_h)
			y -= texture_h;
		while (y < 0)
			y += texture_h;
		if (!env->options.lighting)
			pixels[coord] = texture_pixels[(int)x + texture_w * (int)y];
		else
			pixels[coord] = apply_light(texture_pixels[(int)x + texture_w * (int)y], render.light);
		if (env->editor.in_game && render.selected)
			pixels[coord] = blend_alpha(pixels[coord], 0xFF00FF00, 128);
		zbuffer[coord] = render.z;
		/*if (i == (int)render.floor_horizon)
			pixels[coord] = 0xFF00FF00;*/
		/*if (i == (int)render.floor_horizon1)
			pixels[coord] = 0xFF0000FF;
		if (i == (int)render.floor_horizon2)
			pixels[coord] = 0xFFFF0000;*/
		/*if (i == (int)render.ceiling_horizon)
			pixels[coord] = 0xFFFF0000;*/
		i++;
	}
	if (env->options.zbuffer || env->options.contouring)
	{
		if (vline.start == (int)render.max_ceiling)
		{
			start_coord = vline.x + env->w * vline.start;
			pixels[start_coord] = 0xFFFF0000;
			zbuffer[start_coord] = 100000000;
		}
		if (vline.end == (int)render.max_floor)
		{
			end_coord = vline.x + env->w * vline.end;
			pixels[end_coord] = 0xFFFF0000;
			zbuffer[end_coord] = 100000000;
		}
	}
}

/*
**	Draw a vertical vline on the screen at vline.x
*/

void	draw_vline_color(t_vline vline, t_render render, t_env *env)
{
	int		coord;
	Uint32	*pixels;
	double	*zbuffer;

	(void)render;
	pixels = env->sdl.texture_pixels;
	zbuffer = env->depth_array;
	while (vline.start <= vline.end)
	{
		coord = vline.x + env->w * vline.start;
		pixels[coord] = vline.color;
		zbuffer[coord] = 100000000;
		vline.start++;
	}
}

/*
**	Draw a vertical vline on the screen at vline.x
*/

void	draw_vline_ceiling(t_vline vline, t_render render, t_env *env)
{
	int		i;
	double	y;
	double	x;
	double	alpha;
	Uint32	*pixels;
	Uint32	*texture_pixels;
	double	*zbuffer;
	int		coord;
	int		texture_w;
	int		texture_h;
	double	z;

	pixels = env->sdl.texture_pixels;
	zbuffer = env->depth_array;
	texture_w = env->textures[render.ceiling_texture].surface->w;
	texture_h = env->textures[render.ceiling_texture].surface->h;
	texture_pixels = env->textures[render.ceiling_texture].str;
	i = vline.start;
	while (i <= vline.end)
	{
		coord = vline.x + env->w * i;
		alpha = render.ceiling_start / (double)(i - render.ceiling_horizon);
		z = alpha * render.z;
		if (z >= zbuffer[coord])
		{
			i++;
			continue;
		}
		if (env->editor.select && vline.x == env->h_w && i == env->h_h)
		{
			env->selected_wall1 = -1;
			env->selected_wall2 = -1;
			env->selected_ceiling = render.sector;
			env->selected_floor = -1;
			env->selected_object = -1;
			env->selected_enemy = -1;
			env->editor.selected_wall = -1;
			//env->editor.select = 0;
		}
		y = alpha * render.texel.y + (1.0 - alpha) * env->player.pos.y;
		x = alpha * render.texel.x + (1.0 - alpha) * env->player.pos.x;
		y *= render.ceiling_yscale;
		x *= render.ceiling_xscale;
		if (y >= texture_h || y < 0)
			y = ft_abs((int)y % texture_h);
		if (x >= texture_w || x < 0)
			x = ft_abs((int)x % texture_w);
		if (x >= 0 && x < texture_w && y >= 0 && y < texture_h)
		{
			if (!env->options.lighting)
				pixels[coord] = texture_pixels[(int)x + texture_w * (int)y];
			else
				pixels[coord] = apply_light(texture_pixels[(int)x + texture_w * (int)y], render.light);
		if (env->editor.in_game && env->selected_ceiling == render.sector)
			pixels[coord] = blend_alpha(pixels[coord], 0xFF00FF00, 128);
			zbuffer[coord] = z;
		/*if (i == (int)render.floor_horizon)
			pixels[coord] = 0xFF00FF00;*/
		/*if (i == (int)render.ceiling_horizon)
			pixels[coord] = 0xFFFF0000;*/
		}
		i++;
	}
	if (env->options.zbuffer || env->options.contouring)
	{
		if (vline.start >= 0 && vline.start < env->h - 1)
		{
			pixels[vline.x + env->w * vline.start] = 0xFFFF0000;
			zbuffer[vline.x + env->w * vline.start] = 100000000;
		}
		if (vline.end == (int)render.max_ceiling - 1
				&& vline.end >= 0 && vline.end < env->h)
		{
			pixels[vline.x + env->w * vline.end] = 0xFFFF0000;
			zbuffer[vline.x + env->w * vline.end] = 100000000;
		}
	}
}

/*
**	Draw a vertical vline on the screen at vline.x
*/

void	draw_vline_floor(t_vline vline, t_render render, t_env *env)
{
	int		i;
	double	y;
	double	x;
	double	alpha;
	Uint32	*pixels;
	Uint32	*texture_pixels;
	double	*zbuffer;
	int		coord;
	int		texture_w;
	int		texture_h;
	double	z;

	pixels = env->sdl.texture_pixels;
	zbuffer = env->depth_array;
	texture_w = env->textures[render.floor_texture].surface->w;
	texture_h = env->textures[render.floor_texture].surface->h;
	texture_pixels = env->textures[render.floor_texture].str;
	i = vline.start;
	while (i <= vline.end)
	{
		coord = vline.x + env->w * i;
		alpha = render.floor_start / (double)(i - render.floor_horizon);
		z = alpha * render.z;
		if (z >= zbuffer[coord])
		{
			i++;
			continue;
		}
		if (env->editor.select && vline.x == env->h_w && i == env->h_h)
		{
			env->selected_wall1 = -1;
			env->selected_wall2 = -1;
			env->selected_floor = render.sector;
			env->selected_ceiling = -1;
			env->selected_object = -1;
			env->selected_enemy = -1;
			env->editor.selected_wall = -1;
			//env->editor.select = 0;
		}
		//y = alpha * render.texel.y + (1.0 - alpha) * env->player.pos.y;
		y = alpha * render.texel.y + (1.0 - alpha) * env->player.camera_y;
		/*y = ((1.0 - alpha) * env->player.camera_y / env->camera.near_z + alpha * render.texel.y / render.z)
			/ ((1.0 - alpha) / env->camera.near_z + alpha / render.z);*/
		//x = alpha * render.texel.x + (1.0 - alpha) * env->player.pos.x;
		x = alpha * render.texel.x + (1.0 - alpha) * env->player.camera_x;
		/*x = ((1.0 - alpha) * env->player.camera_x / env->camera.near_z + alpha * render.texel.y / render.z)
			/ ((1.0 - alpha) / env->camera.near_z + alpha / render.z);*/
		y *= render.floor_yscale;
		x *= render.floor_xscale;
		if (y >= texture_h || y < 0)
			y = ft_abs((int)y % texture_h);
		if (x >= texture_w || x < 0)
			x = ft_abs((int)x % texture_w);
		if (x >= 0 && x < texture_w && y >= 0 && y < texture_h)
		{
			if (!env->options.lighting)
				pixels[coord] = texture_pixels[(int)x + texture_w * (int)y];
			else
				pixels[coord] = apply_light(texture_pixels[(int)x + texture_w * (int)y], render.light);
		if (env->editor.in_game && env->selected_floor == render.sector)
			pixels[coord] = blend_alpha(pixels[coord], 0xFF00FF00, 128);
			zbuffer[coord] = z;
		/*if (i == (int)render.floor_horizon)
			pixels[coord] = 0xFF00FF00;*/
		/*if (i == (int)render.ceiling_horizon)
			pixels[coord] = 0xFFFF0000;*/
		}
		i++;
	}
	if (env->options.zbuffer || env->options.contouring)
	{
		if (vline.start == (int)render.max_floor + 1
				&& vline.start >= 0 && vline.start < env->h)
		{
			pixels[vline.x + env->w * vline.start] = 0xFFFF0000;
			zbuffer[vline.x + env->w * vline.start] = 100000000;
		}
		if (vline.end < env->h - 1 && vline.end >= 0)
		{
			pixels[vline.x + env->w * vline.end] = 0xFFFF0000;
			zbuffer[vline.x + env->w * vline.end] = 100000000;
		}
	}
}

/*
**	Draw the ceiling of the current wall
*/

void	draw_ceiling(t_render render, t_env *env)
{
	t_vline	vline;

	vline.x = render.currentx;
	vline.start = env->ymin[vline.x];
	vline.end = ft_min(render.current_ceiling - 1, env->h - 1);
	vline.color = 0xFFFF0000;
	if (env->options.lighting)
		vline.color = apply_light(vline.color, render.light);
	/*if (env->sectors[render.sector].ceiling_slope)
		draw_vline_color(vline, render, env);
	else*/
		draw_vline_ceiling(vline, render, env);
}

/*
**	Draw the floor of the current wall
*/

void	draw_floor(t_render render,t_env *env)
{
	t_vline	vline;

	vline.x = render.currentx;
	vline.start = ft_max(0, render.current_floor + 1);
	vline.end = env->ymax[vline.x];
	vline.color = 0xFF0B6484;
	vline.color = 0xFFFF0000;
	if (env->options.lighting)
		vline.color = apply_light(vline.color, render.light);
	/*if (env->sectors[render.sector].floor_slope)
		draw_vline_color(vline, render, env);
	else*/
		draw_vline_floor(vline, render, env);
}

/*
**	Draw the neighbor upper wall (corniche)
*/

void	draw_upper_wall(t_render render, t_env *env)
{
	t_vline	vline;

	vline.x = render.currentx;
	vline.start = render.current_ceiling;
	vline.end = render.current_neighbor_ceiling;
	vline.color = 0xFF0B6484;
	vline.color = 0xFFFF0000;
	if (env->options.lighting)
		vline.color = apply_light(vline.color, render.light);
	//ft_printf("floor end = %d\n", vline.end);
	draw_vline(vline, render, env);
	//draw_vline_color(vline, render, env);
	if ((env->options.zbuffer || env->options.contouring) && (render.currentx == render.preclip_x1 || render.currentx == render.preclip_x2))
		draw_vline_color(vline, render, env);
	if ((env->options.zbuffer || env->options.contouring) && vline.end == (int)render.max_neighbor_ceiling)
	{
		env->sdl.texture_pixels[env->w * (vline.end - 1) + vline.x] = 0xFFFF0000;
		env->depth_array[env->w * (vline.end - 1) + vline.x] = 100000000;
	}
}

/*
**	Draw the neighbor bottom wall (marche)
*/

void	draw_bottom_wall(t_render render,t_env *env)
{
	t_vline	vline;

	vline.x = render.currentx;
	vline.start = render.current_neighbor_floor;
	vline.end = render.current_floor;
	vline.color = 0xFF444444;
	vline.color = 0xFFFF0000;
	if (env->options.lighting)
		vline.color = apply_light(vline.color, render.light);
	//ft_printf("ceiling start = %d\n", vline.start);
	draw_vline(vline, render, env);
	//draw_vline_color(vline, render, env);
	if ((env->options.zbuffer || env->options.contouring) && (render.currentx == render.preclip_x1 || render.currentx == render.preclip_x2))
		draw_vline_color(vline, render, env);
	if ((env->options.zbuffer || env->options.contouring) && vline.start == (int)render.max_neighbor_floor)
	{
		env->sdl.texture_pixels[env->w * (vline.start + 1) + vline.x] = 0xFFFF0000;
		env->depth_array[env->w * (vline.start + 1) + vline.x] = 100000000;
	}
}
