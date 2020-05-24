/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_existing_files.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 14:48:21 by marvin            #+#    #+#             */
/*   Updated: 2020/05/22 20:05:03 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		wall_textures(t_env *env, char *name)
{
	int	i;

	i = 0;
	while (i < MAX_WALL_TEXTURE)
	{
		if (!(ft_strcmp(name, env->init.text_name[i]))
		&& env->init.textures[i] == 1)
			return (1);
		i++;
	}
	return (0);
}

int		sprites_textures2(t_env *env, char *name)
{
	int	i;

	i = 0;
	while (i < NB_EDITOR_SPRITES)
	{
		if (!(ft_strcmp(name, env->init.editor_names[i]))
		&& env->init.editor[i] == 1)
			return (1);
		i++;
	}
	i = 0;
	while (i < NB_OBJECTS_SPRITES)
	{
		if (!(ft_strcmp(name, env->init.objects_names[i]))
		&& env->init.objects[i] == 1)
			return (1);
		i++;
	}
	return (0);
}

int		sprites_textures(t_env *env, char *name)
{
	int	i;

	i = 0;
	while (i < MAX_ENEMIES)
	{
		if (!(ft_strcmp(name, env->init.enemy_names[i]))
		&& env->init.enemies[i] == 1)
			return (1);
		i++;
	}
	i = 0;
	while (i < NB_WALL_SPRITES)
	{
		if (!(ft_strcmp(name, env->init.sprites_names[i]))
		&& env->init.sprites[i] == 1)
			return (1);
		i++;
	}
	return (0);
}

int		ui_textures(t_env *env, char *name)
{
	int	i;

	i = 0;
	while (i < NB_UI_FILES)
	{
		if (!(ft_strcmp(name, env->init.ui_names[i]))
		&& env->init.ui[i] == 1)
			return (1);
		i++;
	}
	return (0);
}

int		check_existing_files(t_env *env, char *name)
{
	if (wall_textures(env, name))
		return (1);
	if (sprites_textures(env, name))
		return (2);
	if (sprites_textures2(env, name))
		return (2);
	if (skyboxes_textures(env, name))
		return (3);
	if (hud_textures(env, name))
		return (4);
	if (ui_textures(env, name))
		return (5);
	return (0);
}
