/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:39:19 by lnicosia          #+#    #+#             */
/*   Updated: 2020/01/31 18:37:42 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static void	free_textures(t_env *env)
{
	int	i;

	i = 0;
	while (i < MAX_TEXTURES)
	{
		if (env->sprite_textures[i].surface)
			SDL_FreeSurface(env->sprite_textures[i].surface);
		i++;
	}
}

void		free_event(t_event *event)
{
	/*if (event->check_param)
		ft_memdel((void**)&event->check_param);
	if (event->exec_param)
		ft_memdel((void**)&event->exec_param);
	if (event->update_param)
		ft_memdel((void**)&event->update_param);*/
	if (event->exec_param)
		ft_memdel((void**)&event->exec_param);
	if (event->launch_conditions)
		ft_memdel((void**)&event->launch_conditions);
	if (event->exec_conditions)
		ft_memdel((void**)&event->exec_conditions);
}

void		free_events(t_event	*events, size_t size)
{
	size_t	j;

	j = 0;
	while (j < size)
	{
		free_event(&events[j]);
		j++;
	}
	if (events)
		ft_memdel((void**)&events);
}

static void	free_sectors(t_env *env)
{
	int		i;

	i = 0;
	while (i < env->nb_sectors)
	{
		free_sector(&env->sectors[i]);
		i++;
	}
	ft_memdel((void**)&env->sectors);
}

void		free_camera(t_camera *camera, t_env *env)
{
	int	i;
	int	j;

	(void)env;
	if (camera->screen_sectors)
		ft_memdel((void**)&camera->screen_sectors);
	if (camera->screen_pos)
		ft_memdel((void**)&camera->screen_pos);
	if (camera->rendered_sectors)
		ft_memdel((void**)&camera->rendered_sectors);
	if (camera->xmin)
		ft_memdel((void**)&camera->xmin);
	if (camera->xmax)
		ft_memdel((void**)&camera->xmax);
	if (camera->feet_y)
		ft_memdel((void**)&camera->feet_y);
	if (camera->head_y)
		ft_memdel((void**)&camera->head_y);
	if (camera->sector_computed)
		ft_memdel((void**)&camera->sector_computed);
	i = 0;
	if (camera->v)
	{
		i = 0;
		while (i < camera->size)
		{
			if (camera->v[i])
			{
				j = 0;
				// Va poser probleme si sector_nb_vertices est NULL
				while (j < camera->sectors_size[i])
				{
					if (camera->v[i][j].sprite_scale)
						ft_memdel((void**)&camera->v[i][j].sprite_scale);
					if (camera->v[i][j].texture_scale)
						ft_memdel((void**)&camera->v[i][j].texture_scale);
					if (camera->v[i][j].texture_align)
						ft_memdel((void**)&camera->v[i][j].texture_align);
					j++;
				}
				ft_memdel((void**)&camera->v[i]);
			}
			i++;
		}
		ft_memdel((void**)&camera->v);
	}
	if (camera->sectors_size)
		ft_memdel((void**)&camera->sectors_size);
}

void		free_all_sdl_relative(t_env *env)
{
	if (env->sdl.window)
		SDL_DestroyWindow(env->sdl.window);
	if (env->sdl.renderer)
		SDL_DestroyRenderer(env->sdl.renderer);
	if (env->sdl.texture)
		SDL_DestroyTexture(env->sdl.texture);
	if (env->sdl.texture_pixels)
		ft_memdel((void**)&env->sdl.texture_pixels);
	if (env->zbuffer)
		ft_memdel((void**)&env->zbuffer);
	if (env->ymin)
		ft_memdel((void**)&env->ymin);
	if (env->ymax)
		ft_memdel((void**)&env->ymax);
}

void		free_audio(t_env *env, int i)
{
	while (i < NB_WEAPONS)
	{
		FMOD_Sound_Release(env->weapons[i].shot);
		i++;
	}
	FMOD_Sound_Release(env->sound.footstep);
	FMOD_Sound_Release(env->sound.at_dooms_gate);
	FMOD_Sound_Release(env->sound.mt_erebus);
	FMOD_System_Close(env->sound.system);
	FMOD_System_Release(env->sound.system);
}

void		free_all(t_env *env)
{
	int 	i;
	t_list	*tmplst;

	ft_printf("Freeing data..\n");
	if (!env)
		exit(0);
	free_all_sdl_relative(env);
	if (env->sdl.fonts.amazdoom70)
		TTF_CloseFont(env->sdl.fonts.amazdoom70);
	if (env->sdl.fonts.amazdoom50)
		TTF_CloseFont(env->sdl.fonts.amazdoom50);
	if (env->sdl.fonts.amazdoom20)
		TTF_CloseFont(env->sdl.fonts.amazdoom20);
	if (env->sdl.fonts.alice30)
		TTF_CloseFont(env->sdl.fonts.alice30);
	if (env->sdl.fonts.alice70)
		TTF_CloseFont(env->sdl.fonts.alice70);
	if (env->sdl.fonts.lato10)
		TTF_CloseFont(env->sdl.fonts.lato10);
	if (env->sdl.fonts.lato15)
		TTF_CloseFont(env->sdl.fonts.lato15);
	if (env->sdl.fonts.lato20)
		TTF_CloseFont(env->sdl.fonts.lato20);
	if (env->sdl.fonts.lato50)
		TTF_CloseFont(env->sdl.fonts.lato50);
	if (env->sdl.fonts.bebasneue)
		TTF_CloseFont(env->sdl.fonts.bebasneue);
	free_camera(&env->player.camera, env);
	if (env->sectors)
		free_sectors(env);
	i = 0;
	// Leak peut etre si index 5 pas free
	while (i < 4)
	{
		if (env->skybox[i].texture_scale)
			ft_memdel((void**)&env->skybox[i].texture_scale);
		i++;
	};
	if (env->vertices)
		ft_memdel((void**)&env->vertices);
	if (env->objects)
		ft_memdel((void**)&env->objects);
	if (env->save_file)
		ft_strdel(&env->save_file);
	if (env->sector_list)
		ft_memdel((void**)&env->sector_list);
	if (env->events)
		ft_lstdelfront(&env->events);
	if (env->queued_values)
		ft_lstdelfront(&env->queued_values);
	if (env->res[0])
		ft_strdel(&env->res[0]);
	if (env->res[1])
		ft_strdel(&env->res[1]);
	if (env->res[2])
		ft_strdel(&env->res[2]);
	if (env->input_box.str)
		ft_strdel(&env->input_box.str);
	i = 0;
	free_events(env->global_events, env->nb_global_events);
	free_events(env->wall_bullet_holes_events,
	env->nb_wall_bullet_holes_events);
	free_events(env->floor_bullet_holes_events,
	env->nb_floor_bullet_holes_events);
	free_events(env->ceiling_bullet_holes_events,
	env->nb_ceiling_bullet_holes_events);
	if (env->projectiles)
	{
		while (env->projectiles)
		{
			tmplst = env->projectiles;
			tmplst = tmplst->next;
			free(env->projectiles);
			env->projectiles = tmplst;
		}
	}
	free_audio(env, 0);
	free_textures(env);
	TTF_Quit();
	SDL_Quit();
	ft_printf("Exiting..\n");
}

int			crash(char *str, t_env *env)
{
	ft_dprintf(STDERR_FILENO, "%s", str);
	ft_printf("{red}[Critical error]{reset}\n");
	free_all(env);
	return (-1);
}
