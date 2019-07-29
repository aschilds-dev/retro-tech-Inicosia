/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:15:58 by lnicosia          #+#    #+#             */
/*   Updated: 2019/07/24 14:55:33 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	set_camera(t_env *env)
{
	env->camera.vfov = (180.0 / M_PI) * atan(tan((CONVERT_RADIANS * env->camera.hfov / 2)) / env->camera.ratio) * 2;
	//env->camera.hfov = (180.0 / M_PI) * atan(tan(((M_PI / 180.0) * env->cameravfov / 2)) * env->camera.ratio) * 2;
	//ft_printf("hfov = %f, vfov = %f\n", env->camera.hfov, env->camera.vfov);
	env->camera.near_left = -tan(CONVERT_RADIANS * env->camera.hfov / 2) * env->camera.near_z;
	env->camera.near_right = tan(CONVERT_RADIANS * env->camera.hfov / 2) * env->camera.near_z;
	env->camera.near_up = -tan(CONVERT_RADIANS * env->camera.vfov / 2) * env->camera.near_z;
	env->camera.near_down = tan(CONVERT_RADIANS * env->camera.vfov / 2) * env->camera.near_z;
	env->camera.far_left = -tan(CONVERT_RADIANS * env->camera.hfov / 2) * env->camera.far_z;
	env->camera.far_right = tan(CONVERT_RADIANS * env->camera.hfov / 2) * env->camera.far_z;
	//ft_printf("near left = %f near right = %f\n", env->camera.near_left, env->camera.near_right);
	env->camera.x1 = (env->camera.near_left / env->camera.near_z);
	env->camera.x2 = (env->camera.near_right / env->camera.near_z);
	env->camera.y1 = (env->camera.near_up / env->camera.near_z);
	env->camera.y2 = (env->camera.near_down / env->camera.near_z);
	//ft_printf("x1 = %f x2 = %f\n", env->camera.x1, env->camera.x2);
	env->camera.hscale = env->h_w / env->camera.x2;
	env->camera.vscale = env->h_h / env->camera.y2;
	env->camera.scale = env->camera.vscale;
	/*ft_printf("near_z = %f\nnear_left = %f near_right = %f\nfar_left = %f far_right = %f\n",
			env->camera.near_z,
			env->camera.near_left,
			env->camera.near_right,
			env->camera.far_left,
			env->camera.far_right);
	ft_printf("camera x1 = %f camera x2 = %f\n", env->camera.x1, env->camera.x2);
	ft_printf("near_up = %f near_down = %f\n", env->camera.near_up, env->camera.near_down);
	ft_printf("camera y1 = %f camera y2 = %f\n", env->camera.y1, env->camera.y2);
	ft_printf("hscale = %f\n", env->camera.hscale);
	ft_printf("vscale = %f\n", env->camera.vscale);
	ft_printf("final scale = %f\n", env->camera.scale);*/
}

void	init_camera(t_env *env)
{
	env->camera.hfov = 90;
	env->camera.near_z = 0.1;
	env->camera.far_z = 1000;
	env->camera.ratio_w = 16;
	env->camera.ratio_h = 9;
	env->camera.ratio = env->camera.ratio_w / env->camera.ratio_h;
	set_camera(env);
}
