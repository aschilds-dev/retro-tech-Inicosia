/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_maths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 09:57:35 by lnicosia          #+#    #+#             */
/*   Updated: 2019/06/04 16:28:51 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "render.h"

/*
**	Get the translated vertices coord for the current wall
*/

void	get_translated_vertices(t_render *render, t_env *env, t_sector sector, int i)
{
	if (i != 0)
	{
		render->v1.x = render->v2.x;
		render->v1.z = render->v2.z;
	}
	else
	{
		render->v1.x = env->vertices[sector.vertices[i]].x - env->player.pos.x;
		render->v1.z = env->vertices[sector.vertices[i]].y - env->player.pos.y;
	}
	render->v2.x = env->vertices[sector.vertices[i + 1]].x - env->player.pos.x;
	render->v2.z = env->vertices[sector.vertices[i + 1]].y - env->player.pos.y;
}

/*
**	Get the rotated vertices coord for the current wall
*/

void	get_rotated_vertices(t_render *render, t_env *env, t_sector sector, int i)
{
	double	y1;
	double	y2;

	if (i != 0)
	{
		render->vx1 = render->vx2;
		render->vz1 = render->vz2;
	}
	else
	{
		render->vx1 = render->v1.x * env->player.angle_sin - render->v1.z * env->player.angle_cos;
		render->vz1 = render->v1.x * env->player.angle_cos + render->v1.z * env->player.angle_sin;
		render->v0_vz1 = render->vz1;
	}
	render->vx2 = render->v2.x * env->player.angle_sin - render->v2.z * env->player.angle_cos;
	render->vz2 = render->v2.x * env->player.angle_cos + render->v2.z * env->player.angle_sin;
	if (i == 0)
		render->v0_vz2 = render->vz2;
	y1 = sector.clipped_floors1[i] - env->player.pos.z;
	y2 = sector.clipped_floors2[i + 1] - env->player.pos.z;
	render->vfy1 = y1 + (render->vz1 * env->player.angle_z);
	render->vfy2 = y2 + (render->vz2 * env->player.angle_z);
	y1 = sector.clipped_ceilings1[i] - env->player.pos.z;
	y2 = sector.clipped_ceilings2[i + 1] - env->player.pos.z;
	render->vcy1 = y1 + (render->vz1 * env->player.angle_z);
	render->vcy2 = y2 + (render->vz2 * env->player.angle_z);
}

/*
** Translate and rotate vertices z into player's view
*/

void	get_relative_heights(t_render *render, t_env *env, t_sector sector, int i)
{
	double	y1;
	double	y2;

	y1 = sector.clipped_floors1[i] - env->player.pos.z;
	y2 = sector.clipped_floors2[i + 1] - env->player.pos.z;
	render->vfy1 = y1 + (render->clipped_vz1 * env->player.angle_z);
	render->vfy2 = y2 + (render->clipped_vz2 * env->player.angle_z);
	/*render->vfy1 = y1 * env->player.angle_z_cos + render->vz1 * env->player.angle_z_sin;
	render->vfy2 = y2 * env->player.angle_z_cos + render->vz2 * env->player.angle_z_sin;*/
	y1 = sector.clipped_ceilings1[i] - env->player.pos.z;
	y2 = sector.clipped_ceilings2[i + 1] - env->player.pos.z;
	render->vcy1 = y1 + (render->clipped_vz1 * env->player.angle_z);
	render->vcy2 = y2 + (render->clipped_vz2 * env->player.angle_z);
	/*render->vcy1 = y1 * env->player.angle_z_cos + render->vz1 * env->player.angle_z_sin;
	render->vcy2 = y2 * env->player.angle_z_cos + render->vz2 * env->player.angle_z_sin;*/
}

/*
** Translate and rotate vertices z into player's view
*/

void	get_relative_heights_preclip(t_render *render, t_env *env, t_sector sector, int i)
{
	double	y1;
	double	y2;

	y1 = sector.floors[i] - env->player.pos.z;
	y2 = sector.floors[i + 1] - env->player.pos.z;
	render->vfy1 = y1 + (render->vz1 * env->player.angle_z);
	render->vfy2 = y2 + (render->vz2 * env->player.angle_z);
	/*render->vfy1 = y1 * env->player.angle_z_cos + render->vz1 * env->player.angle_z_sin;
	render->vfy2 = y2 * env->player.angle_z_cos + render->vz2 * env->player.angle_z_sin;*/
	y1 = sector.ceilings[i] - env->player.pos.z;
	y2 = sector.ceilings[i + 1] - env->player.pos.z;
	render->vcy1 = y1 + (render->vz1 * env->player.angle_z);
	render->vcy2 = y2 + (render->vz2 * env->player.angle_z);
	/*render->vcy1 = y1 * env->player.angle_z_cos + render->vz1 * env->player.angle_z_sin;
	render->vcy2 = y2 * env->player.angle_z_cos + render->vz2 * env->player.angle_z_sin;*/
}

/*
** Translate and rotate neighbor's vertices z into player's view
*/

void	get_neighbor_relative_heights(t_render *render, t_env *env, t_sector neighbor)
{
	double	y1;
	double	y2;

	y1 = neighbor.clipped_floors1[render->nv1] - env->player.pos.z;
	y2 = neighbor.clipped_floors2[render->nv2] - env->player.pos.z;
	render->nvfy1 = y1 + (render->clipped_vz1 * env->player.angle_z);
	render->nvfy2 = y2 + (render->clipped_vz2 * env->player.angle_z);
	/*render->nvfy1 = y1 * env->player.angle_z_cos + render->vz1 * env->player.angle_z_sin;
	render->nvfy2 = y2 * env->player.angle_z_cos + render->vz2 * env->player.angle_z_sin;*/
	y1 = neighbor.clipped_ceilings1[render->nv1] - env->player.pos.z;
	y2 = neighbor.clipped_ceilings2[render->nv2] - env->player.pos.z;
	render->nvcy1 = y1 + (render->clipped_vz1 * env->player.angle_z);
	render->nvcy2 = y2 + (render->clipped_vz2 * env->player.angle_z);
	/*render->nvcy1 = y1 * env->player.angle_z_cos + render->vz1 * env->player.angle_z_sin;
	render->nvcy2 = y2 * env->player.angle_z_cos + render->vz2 * env->player.angle_z_sin;*/
}

/*
**	Get the floor and ceiling position on the screen
*/

void	project_floor_and_ceiling(t_render *render, t_env *env, t_sector sector, int i)
{
	double	scale;

	scale = env->camera.scale;
	get_relative_heights(render, env, sector, i);
	render->floor1 = env->h / 2 +
		(int)(render->vfy1 * scale / -render->clipped_vz1);
	render->floor2 = env->h / 2 +
		(int)(render->vfy2 * scale / -render->clipped_vz2);
	render->ceiling1 = env->h / 2 +
		(int)(render->vcy1 * scale / -render->clipped_vz1);
	render->ceiling2 = env->h / 2 +
		(int)(render->vcy2 * scale / -render->clipped_vz2);
	render->x1 = env->w / 2 + (int)(render->clipped_vx1 * (scale / -render->clipped_vz1));
	render->x2 = env->w / 2 + (int)(render->clipped_vx2 * (scale / -render->clipped_vz2));
	/*if (i == 0)
		ft_printf("v0_floor1 = %d v0_floor2 = %d\n", render->floor1, render->floor2);*/
}

/*
**	Get the neighbor floor and ceiling position on the screen
*/

void	project_neighbor_floor_and_ceiling(t_render *render, t_env *env, t_sector neighbor)
{
	double	scale;

	scale = env->camera.scale;
	get_neighbor_relative_heights(render, env, neighbor);
	render->neighbor_floor1 = env->h / 2 +
		(int)(render->nvfy1 * scale / -render->clipped_vz1);
	render->neighbor_floor2 = env->h / 2 +
		(int)(render->nvfy2 * scale / -render->clipped_vz2);
	render->neighbor_ceiling1 = env->h / 2 +
		(int)(render->nvcy1 * scale / -render->clipped_vz1);
	render->neighbor_ceiling2 = env->h / 2 +
		(int)(render->nvcy2 * scale / -render->clipped_vz2);
}

/*
**	Get the floor and ceiling position on the screen before clipping
*/

void	project_floor_and_ceiling_preclip(t_render *render, t_env *env, t_sector sector, int i)
{
	double	scale;

	scale = env->camera.scale;
	get_relative_heights_preclip(render, env, sector, i);
	render->preclip_floor1 = env->h / 2 +
		(int)(render->vfy1 * scale / -render->vz1);
	render->preclip_floor2 = env->h / 2 +
		(int)(render->vfy2 * scale / -render->vz2);
	render->preclip_ceiling1 = env->h / 2 +
		(int)(render->vcy1 * scale / -render->vz1);
	render->preclip_ceiling2 = env->h / 2 +
		(int)(render->vcy2 * scale / -render->vz2);
	render->preclip_x1 = env->w / 2 + (int)(render->vx1 * (scale / -render->vz1));
	render->preclip_x2 = env->w / 2 + (int)(render->vx2 * (scale / -render->vz2));
	if (i == 0)
	{
		render->projected_v0_floor.x = render->preclip_x1;
		render->projected_v0_floor.y = render->preclip_floor1;
		render->projected_v0_ceiling.x = render->preclip_x1;
		render->projected_v0_ceiling.y = render->preclip_ceiling1;
		render->projected_v1_floor.x = render->preclip_x2;
		render->projected_v1_floor.y = render->preclip_floor2;
		render->projected_v1_ceiling.x = render->preclip_x2;
		render->projected_v1_ceiling.y = render->preclip_ceiling2;
		/*ft_printf("v0_floor1 = %.f v0_floor2 = %.f\n", render->projected_v0_floor.y,
				render->projected_v1_floor.y);
		ft_printf("x1 = %f x2 = %f\n", render->projected_v0_floor.x,
				render->projected_v1_floor.x);*/
	}
}
