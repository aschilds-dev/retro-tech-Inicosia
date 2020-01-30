/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 11:52:14 by lnicosia          #+#    #+#             */
/*   Updated: 2020/01/30 11:08:07 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "save.h"

static int	get_main_sprite(int sprite, t_env *env)
{
	int		i;

	i = 0;
	while (i < MAX_OBJECTS)
	{
		if (sprite == env->objects_main_sprites[i])
			return (i);
		i++;
	}
	return (i);
}

static void	write_object(int fd, t_object object, t_env *env)
{
	ft_dprintf(fd, "[%.3f %.3f %.3f %.3f] ",
			object.pos.y, object.pos.x, object.pos.z, object.angle);
	ft_dprintf(fd, "[%d %.f]\n",
			get_main_sprite(object.sprite, env), object.scale);
}

void		write_objects(int fd, t_env *env)
{
	int	i;

	i = 0;
	ft_dprintf(fd, "\nO %d\n", env->nb_objects);
	while (i < env->nb_objects)
	{
		write_object(fd, env->objects[i], env);
		i++;
	}
}
