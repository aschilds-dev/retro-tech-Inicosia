/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_projectile_no_light.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:24:44 by gaerhard          #+#    #+#             */
/*   Updated: 2020/04/29 16:30:03 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "draw.h"

int		projectile_loop_no_light(void *param)
{
	t_env				*env;
	t_render_projectile	*prender;
	t_sprite_drawer		drawer;

	prender = ((t_projectile_thread*)param)->prender;
	env = ((t_projectile_thread*)param)->env;
	drawer.projectile = ((t_projectile_thread*)param)->projectile;
	drawer.sprite = &env->object_sprites[drawer.projectile->sprite];
	drawer.texture = &env->sprite_textures[drawer.sprite->texture];
	drawer.x = ((t_projectile_thread*)param)->xstart;
	drawer.xend = ((t_projectile_thread*)param)->xend;
	drawer.yend = prender->yend;
	while (++drawer.x <= drawer.xend)
	{
		get_projectile_x(prender, &drawer);
		while (drawer.y < drawer.yend)
		{
			draw_vline_projectile_no_light(prender, &drawer, env);
			drawer.y++;
		}
	}
	return (0);
}

int		threaded_projectile_loop_no_light(t_projectile *projectile,
t_render_projectile *prender, t_env *env)
{
	t_projectile_thread	pt[MAX_PROC];
	int					i;

	i = 0;
	while (i < env->nprocs)
	{
		pt[i].env = env;
		pt[i].projectile = projectile;
		pt[i].prender = prender;
		pt[i].xstart = prender->xstart + (prender->xend - prender->xstart)
		/ (double)env->nprocs * i;
		pt[i].xend = prender->xstart + (prender->xend - prender->xstart)
		/ (double)env->nprocs * (i + 1);
		if (tpool_work(&env->tpool, projectile_loop_no_light, &pt[i]))
			return (-1);
		i++;
	}
	if (tpool_wait(&env->tpool))
		return (-1);
	return (0);
}

int		draw_projectile_no_light(t_camera *camera, t_projectile *projectile,
t_env *env)
{
	t_render_projectile	prender;
	t_sprite			*sprite;
	t_v2				size;
	double				sprite_ratio;

	sprite = &env->object_sprites[projectile->sprite];
	prender.camera = camera;
	project_projectile(&prender, projectile, env);
	prender.index = 0;
	if (sprite->oriented)
		prender.index = get_sprite_direction_projectile(projectile);
	size.x = env->w * projectile->scale / projectile->rotated_pos.z;
	sprite_ratio = sprite->size[prender.index].x
		/ (double)sprite->size[prender.index].y;
	size.y = size.x * sprite_ratio;
	init_projectile_render(&prender, projectile, size, env);
	if (threaded_projectile_loop_no_light(projectile, &prender, env))
		return (-1);
	return (0);
}
