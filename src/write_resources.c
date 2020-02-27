/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_resources.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 10:06:40 by sipatry           #+#    #+#             */
/*   Updated: 2020/02/27 17:44:34 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		write_textures(int fd, t_env *env)
{
	(void)env;
	
	ft_dprintf(fd, "T %d\n", MAX_WALL_TEXTURE);
	if (write_textures1(fd))
		return (-1);
//	write_textures2(fd);
//	write_textures3(fd);
	return (0);
}

int		write_resources(int fd, t_env *env)
{
	if (write_textures(fd, env))
		return (-1);
	return (0);
}