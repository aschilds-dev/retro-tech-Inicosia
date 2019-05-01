/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 11:47:52 by lnicosia          #+#    #+#             */
/*   Updated: 2019/05/01 15:04:02 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "bmp_parser.h"

/*
**	Main function: parse every part of the BMP file:
**	-File header
**	-Image header
**	-Image data
*/

static int	parse(int fd, t_env *env)
{
	t_bmp_parser	parser;

	if (parse_file_header(fd, &parser))
		return (ft_printf("Error in file header\n"));
	if (get_image_header_size(fd, &parser))
		return (ft_printf("Error in image header\n"));
	if (parse_image_header(fd, &parser))
		return (ft_printf("Error in image header\n"));
	if (!(env->sdl.image = SDL_CreateRGBSurfaceWithFormat(
					0,
					parser.w,
					parser.h,
					parser.bpp,
					SDL_PIXELFORMAT_RGBA8888)))
		return (ft_printf("SDL_CreateRGBSurface error: %s\n", SDL_GetError()));
	env->sdl.image_str = env->sdl.image->pixels;
	if (parse_pixel_data(fd, &parser, env))
		return (ft_printf("Error in pixel data\n"));
	check_bmp_parsing(parser);
	return (0);
}

/*
**	Init function:
**	-Create a new SDL surface to store the image
**	-Open the given file
**	-Parse it
**	-Close the file
*/

int			parse_bmp(char *file, t_env *env)
{
	int	fd;

	ft_printf("Parsing \"%s\"\n{red}", file);
	if ((fd = open(file, O_RDONLY)) == -1)
		return (ft_printf("Could not open \"%s\"\n", file));
	if (parse(fd, env))
		return (ft_printf("Error while parsing \"%s\"\n", file));
	if (close(fd))
		return (ft_printf("Could not close \"%s\"\n", file));
	ft_printf("{reset}");
	return (0);
}
