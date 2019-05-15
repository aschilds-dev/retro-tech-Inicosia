/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 10:06:35 by lnicosia          #+#    #+#             */
/*   Updated: 2019/05/15 17:55:42 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "render.h"

/*
**	Draw a vertical vline on the screen at vline.x
*/

void	draw_vline(t_vline vline, t_env *env)
{
	if (env->options.contouring)
	{
		if (!(vline.x >= env->w - 300 && vline.x < env->w && vline.start >= 0 && vline.start <= 300) || !env->options.show_minimap)
			env->sdl.img_str[vline.x + env->w * vline.start] = 0xFF;
		if (!(vline.x >= env->w - 300 && vline.x < env->w && vline.end >= 0 && vline.end <= 300) || !env->options.show_minimap)
		env->sdl.img_str[vline.x + env->w * vline.end] = 0xFF;
		vline.start++;
		vline.end--;
	}
	while (vline.start <= vline.end)
	{
		if (!(vline.x >= env->w - 300 && vline.x < env->w && vline.start >= 0 && vline.start <= 300) || !env->options.show_minimap)
			env->sdl.img_str[vline.x + env->w * vline.start] = vline.color;
		vline.start++;
	}
}

/*
**	Draw the ceiling of the current wall
*/

void	draw_ceiling(t_render render, t_env *env)
{
	t_vline	vline;

	vline.x = render.currentx;
	vline.start = render.ymin;
	vline.end = render.current_ceiling;
	vline.color = 0x222222FF;
	if (env->options.lighting)
		vline.color = ((int)render.light / 5) << 24
			| ((int)render.light / 5) << 16
			| ((int)render.light / 5) << 8
			| 255;
	//ft_printf("floor end = %d\n", vline.end);
	draw_vline(vline, env);
}

/*
**	Draw the floor of the current wall
*/

void	draw_floor(t_render render,t_env *env)
{
	t_vline	vline;

	vline.x = render.currentx;
	vline.start = render.current_floor;
	vline.end = render.ymax;
	vline.color = 0x444444FF;
	if (env->options.lighting)
		vline.color = ((int)render.light / 3) << 24
			| ((int)render.light / 3) << 16
			| ((int)render.light / 3) << 8
			| 255;
	//ft_printf("ceiling start = %d\n", vline.start);
	draw_vline(vline, env);
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
	vline.color = 0x07C00D9FF;
	if (env->options.lighting)
		vline.color = (int)render.light / 3 << 24
			| (int)render.light / 3 << 16
			| (int)render.light / 3<< 8
			| 255;
	//ft_printf("floor end = %d\n", vline.end);
	if (env->options.contouring && (render.currentx == render.x1 || render.currentx == render.x2))
			vline.color = 0xFF;
	draw_vline(vline, env);
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
	vline.color = 0x7C00D9FF;
	if (env->options.lighting)
		vline.color = (int)render.light / 3 << 24
			| (int)render.light / 3 << 16
			| (int)render.light / 3 << 8
			| 255;
	//ft_printf("ceiling start = %d\n", vline.start);
	if (env->options.contouring && (render.currentx == render.x1 || render.currentx == render.x2))
			vline.color = 0xFF;
	draw_vline(vline, env);
}
