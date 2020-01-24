/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 17:47:23 by sipatry           #+#    #+#             */
/*   Updated: 2020/01/08 15:40:06 by gaerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/*
 **	Update camera position (save some computings)
 */

void	update_camera_position(t_camera *camera)
{
	camera->near_pos.x = camera->pos.x + camera->angle_cos * camera->near_z;
	camera->near_pos.y = camera->pos.y + camera->angle_sin * camera->near_z;
	camera->near_left_pos.x = camera->pos.x + (camera->angle_cos * camera->near_z - camera->angle_sin * camera->near_left);
	camera->near_left_pos.y = camera->pos.y + (camera->angle_sin * camera->near_z + camera->angle_cos * camera->near_left);
	camera->near_right_pos.x = camera->pos.x + (camera->angle_cos * camera->near_z - camera->angle_sin * camera->near_right);
	camera->near_right_pos.y = camera->pos.y + (camera->angle_sin * camera->near_z + camera->angle_cos * camera->near_right);
}

void	set_camera(t_camera *camera, t_env *env)
{
	camera->vfov = (180.0 / M_PI) * atan(tan((CONVERT_RADIANS * camera->hfov / 2)) / camera->ratio) * 2;
	//camera->hfov = (180.0 / M_PI) * atan(tan(((M_PI / 180.0) * camera->fov / 2)) * camera->ratio) * 2;
	//ft_printf("hfov = %f, vfov = %f\n", camera->hfov, camera->vfov);
	camera->near_left = -tan(CONVERT_RADIANS * camera->hfov / 2) * camera->near_z;
	camera->near_right = tan(CONVERT_RADIANS * camera->hfov / 2) * camera->near_z;
	camera->range = camera->near_right - camera->near_left;
	camera->near_up = -tan(CONVERT_RADIANS * camera->vfov / 2) * camera->near_z;
	camera->near_down = tan(CONVERT_RADIANS * camera->vfov / 2) * camera->near_z;
	camera->far_left = -tan(CONVERT_RADIANS * camera->hfov / 2) * camera->far_z;
	camera->far_right = tan(CONVERT_RADIANS * camera->hfov / 2) * camera->far_z;
	//ft_printf("near left = %f near right = %f\n", camera->near_left, camera->near_right);
	camera->x1 = (camera->near_left / camera->near_z);
	camera->x2 = (camera->near_right / camera->near_z);
	camera->y1 = (camera->near_up / camera->near_z);
	camera->y2 = (camera->near_down / camera->near_z);
	//ft_printf("x1 = %f x2 = %f\n", camera->x1, camera->x2);
	camera->hscale = env->h_w / camera->x2;
	camera->vscale = env->h_h / camera->y2;
	camera->scale = camera->vscale;
	//ft_printf("camera scale = %f\n", camera->scale);
	/*ft_printf("near_z = %f\nnear_left = %f near_right = %f\nfar_left = %f far_right = %f\n",
			camera->near_z,
			camera->near_left,
			camera->near_right,
			camera->far_left,
			camera->far_right);
	ft_printf("camera->x1 = %f camera->x2 = %f\n", camera->x1, camera->x2);
	ft_printf("near_up = %f near_down = %f\n", camera->near_up, camera->near_down);
	ft_printf("camera->y1 = %f camera->y2 = %f\n", camera->y1, camera->y2);
	ft_printf("hscale = %f\n", camera->hscale);
	ft_printf("vscale = %f\n", camera->vscale);
	ft_printf("final scale = %f\n", camera->scale);*/
}

int		set_camera_sprites_array(t_camera *camera, int i, int j, t_env *env)
{
	if (camera->v[i][j].sprite_scale)
		free(camera->v[i][j].sprite_scale);
	if (!(camera->v[i][j].sprite_scale = (t_v2*)ft_memalloc(sizeof(t_v2)
		* env->sectors[i].wall_sprites[j].nb_sprites)))
		return (ft_perror("Could not malloc camera sprites scales"));
	return (0);
}

int		set_camera_map_array(t_camera *camera, int i, int j, t_env *env)
{
	if (camera->v[i][j].texture_scale)
		free(camera->v[i][j].texture_scale);
	if (!(camera->v[i][j].texture_scale = (t_v2*)ft_memalloc(sizeof(t_v2) * env->wall_textures[env->sectors[i].textures[j]].nb_maps)))
		return (ft_perror("Could not malloc camera sprites scales"));
	if (camera->v[i][j].texture_align)
		free(camera->v[i][j].texture_align);
	if (!(camera->v[i][j].texture_align = (t_v2*)ft_memalloc(sizeof(t_v2) * env->wall_textures[env->sectors[i].textures[j]].nb_maps)))
		return (ft_perror("Could not malloc camera sprites scales"));
	return (0);
}

int		init_camera_arrays(t_camera *camera, t_env *env)
{
	int	i;
	int	j;

	camera->size = env->nb_sectors;
	if (!(camera->screen_pos = (int*)ft_memalloc(sizeof(int) * (env->w))))
		return (ft_printf("Could not malloc screen pos!\n", env));
	if (!(camera->v = (t_render_vertex**)
				malloc(sizeof(t_render_vertex*) * env->nb_sectors)))
		return (ft_perror("Could not malloc camera sectors"));
	if (!(camera->sector_computed = (int*)ft_memalloc(sizeof(int) * (env->nb_sectors))))
		return (ft_printf("Could not malloc xmins!\n", env));
	if (!(camera->sectors_size = (int*)ft_memalloc(sizeof(int) * (env->nb_sectors))))
		return (ft_printf("Could not malloc xmins!\n", env));
	if (!(camera->feet_y = (double*)ft_memalloc(sizeof(double) * (env->nb_sectors))))
		return (ft_printf("Could not malloc xmins!\n", env));
	if (!(camera->head_y = (double*)ft_memalloc(sizeof(double) * (env->nb_sectors))))
		return (ft_printf("Could not malloc xmins!\n", env));
	if (!(camera->xmin = (int*)ft_memalloc(sizeof(int) * (env->screen_sectors_size))))
		return (ft_printf("Could not malloc xmins!\n", env));
	if (!(camera->xmax = (int*)ft_memalloc(sizeof(int) * (env->screen_sectors_size))))
		return (ft_printf("Could not malloc xmaxs!\n", env));
	if (!(camera->screen_sectors = (int*)ft_memalloc(sizeof(int) * (env->screen_sectors_size))))
		return (ft_printf("Could not malloc screen sectors!\n", env));
	if (!(camera->rendered_sectors = (int*)ft_memalloc(sizeof(int) * (env->screen_sectors_size))))
		return (ft_printf("Could not malloc rendered sectors!\n", env));
	i = 0;
	while (i < env->nb_sectors)
	{
		if (!(camera->v[i] = (t_render_vertex*)ft_memalloc(sizeof(t_render_vertex)
			* (env->sectors[i].nb_vertices + 1))))
			return (ft_perror("Could not malloc camera sectors"));
		camera->sectors_size[i] = env->sectors[i].nb_vertices;
		j = 0;
		while (j < env->sectors[i].nb_vertices)
		{
			camera->v[i][j].sprite_scale = 0;
			if (set_camera_sprites_array(camera, i, j, env))
				return (-1);
			camera->v[i][j].texture_scale = 0;
			camera->v[i][j].texture_align = 0;
			if (set_camera_map_array(camera, i, j, env))
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int		init_camera(t_camera *camera, t_env *env)
{
	camera->hfov = 90;
	camera->near_z = 0.1;
	camera->far_z = 1000;
	camera->ratio_w = 16;
	camera->ratio_h = 9;
	camera->ratio = camera->ratio_w / camera->ratio_h;
	set_camera(camera, env);
	if (init_camera_arrays(camera, env))
		return (ft_printf("Could not init camera arrays\n"));
	return (0);
}
