/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_resources2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:14:55 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/21 18:07:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "save.h"
#include "bmp_parser.h"

int		writing_bmp(int file, int fd, char *name)
{
	unsigned char	resource[10000];
	unsigned char	header[14];
	int				ret;
	int32_t			size;

	if (read(file, header, 14) != 14)
	{
		if (close(file))
			return (custom_error(
			"Invalid bmp file and could not close the file\n"));
			return (custom_error("Invalid bmp file\n"));
	}
	size = read_int32(header, 2);
	ft_dprintf(fd, "%s\n%d\n", name, size);
	write(fd, header, 14);
	while ((ret = (read(file, resource, 10000))) > 0)
		write(fd, resource, ret);
	write(fd, "\n", 1);
	if (close(file))
		return (custom_error("Could not close the resource\n"));
	return (0);
}

int		write_textures(int fd, t_env *env)
{
	(void)env;
	ft_printf("{reset}Saving textures..\n");
	ft_dprintf(fd, "T %d\n", MAX_WALL_TEXTURE);
	if (write_textures1(env, fd))
		return (-1);
	return (0);
}
