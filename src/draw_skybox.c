/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   draw_skybox.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: lnicosia <marvin@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2019/09/10 18:09:18 by lnicosia		  #+#	#+#			 */
/*   Updated: 2019/09/18 14:31:59 by lnicosia		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "env.h"
#include "render.h"
#include "render.h"

void	skybox_loop(t_render skybox, t_skybox_data wall_data, t_render render,
		t_env *env)
{
	t_vline			vline;
	t_render_vertex	v1;
	int				x;
	int				max;
	int				min;

	v1 = env->skybox[skybox.i];
	x = render.x;
	vline.color = 0xFFFF0000;
	if ((!wall_data.mode && env->selected_ceiling == render.sector)
			|| (wall_data.mode && env->sectors[render.sector].selected[render.i]))
		skybox.selected = 1;
	if (!wall_data.mode)
	{
		max = render.current_ceiling;
		min = env->ymin[x];
	}
	else
	{
		max = render.current_floor;
		min = render.current_ceiling;
	}
	skybox.alpha = (x - v1.x) / v1.xrange;
	skybox.clipped_alpha = (x - v1.clipped_x1) / v1.clipped_xrange;
	skybox.z = 1.0 / ((1.0 - skybox.alpha) / v1.vz
			+ skybox.alpha / env->skybox[skybox.i + 1].vz);
	skybox.divider = 1 / (env->skybox[skybox.i + 1].vz
			+ skybox.alpha * v1.zrange);
	skybox.z = v1.zcomb * skybox.divider;
	skybox.texel.x = (v1.x0z1 + skybox.alpha * v1.xzrange) * skybox.divider;
	skybox.texel.y = (v1.y0z1 + skybox.alpha * v1.yzrange) * skybox.divider;
	skybox.max_ceiling = skybox.clipped_alpha * v1.ceiling_range + v1.c1;
	skybox.current_ceiling = ft_clamp(skybox.max_ceiling,
			env->ymin[x], env->ymax[x]);
	skybox.max_floor = skybox.clipped_alpha * v1.floor_range + v1.f1;
	skybox.current_floor = ft_clamp(skybox.max_floor,
			env->ymin[x], env->ymax[x]);
	skybox.line_height = skybox.max_floor - skybox.max_ceiling;
	skybox.ceiling_start = skybox.max_ceiling - skybox.ceiling_horizon;
	skybox.floor_start = skybox.max_floor - skybox.floor_horizon;
	vline.x = x;
	if (min < skybox.current_ceiling)
	{
		vline.start = min;
		vline.end = ft_min(skybox.current_ceiling, max);
		draw_skybox_ceiling(vline, wall_data, skybox, env);
	}
	if (skybox.current_ceiling < max)
	{
		vline.start = ft_max(min, skybox.current_ceiling);
		vline.end = ft_min(skybox.current_floor, max);
		draw_skybox_wall(vline, wall_data, skybox, env);
		if ((env->options.zbuffer || env->options.contouring)
				&& (x == (int)v1.x || x == (int)env->skybox[skybox.i + 1].x))
			draw_vline_color2(vline, env);
	}
	if (skybox.current_floor < max)
	{
		vline.start = skybox.current_floor;
		vline.end = max;
		draw_skybox_floor(vline, wall_data, skybox, env);
	}
}

void	draw_skybox2(t_render render, int mode, t_env *env)
{
	int				i;
	t_render		skybox;
	t_skybox_data	wall_data;

	i = -1;
	wall_data.mode = mode;
	wall_data.z = render.z;
	wall_data.ceiling_start = render.ceiling_start;
	wall_data.ceiling_horizon = render.ceiling_horizon;
	while (++i < 4)
	{
		if (!env->skybox[i].draw
				|| env->skybox[i].clipped_x1 >= env->skybox[i].clipped_x2
				|| env->skybox[i].clipped_x1 > render.x
				|| env->skybox[i].clipped_x2 < render.x)
			continue;
		skybox.texture = 40 + i;
		skybox.i = i;
		skybox.selected = 0;
		skybox.sector = render.sector;
		skybox.ceiling_horizon = env->player.camera.horizon;
		skybox.floor_horizon = env->player.camera.horizon;
		skybox_loop(skybox, wall_data, render, env);
	}
}
