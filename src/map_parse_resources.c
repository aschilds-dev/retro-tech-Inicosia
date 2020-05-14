/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_resources.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 11:37:30 by sipatry           #+#    #+#             */
/*   Updated: 2020/05/12 12:01:59 by gaerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "map_parser.h"

int		map_parse_textures(t_env *env, t_map_parser *parser)
{
	int	i;

	i = 0;
	ft_strdel(&parser->line);
	ft_strdel(&parser->tmp);
	if (!(parser->tmp = ft_strnew(1)))
		return (custom_error("Memalloc failed\n"));
	if (!(parser->line = ft_strnew(1)))
		return (custom_error("Could not malloc line\n"));
	while ((parser->ret = read(parser->fd, parser->tmp, 1)) > 0
	&& ft_strlen(parser->line) < 100)
	{
		if (*(parser->tmp) == '\n')
			break;
		if (!(parser->line = ft_strjoin_free(parser->line, parser->tmp)))
			return (custom_error("Could not malloc line\n"));
	}
	if (*(parser->tmp) != '\n')
		return (custom_error("Expected a '\\n' at the end of file name\n"));
	if (*(parser->line) && *(parser->line) != 'T')
		return (custom_error("Expected letter: T\n"));
	parser->line++;
	if (*(parser->line) && *(parser->line) != ' ')
		return (custom_error("Expected a space\n"));
	parser->line++;
	if (valid_int(parser->line, parser))
		return (custom_error("Invalid int for textures number\n"));
	env->resource.nb_textures = atoi(parser->line);
	parser->line -= 2;
	if (env->resource.nb_textures > MAX_WALL_TEXTURE
	|| env->resource.nb_textures < 1)
		return (custom_error("Wrong number of textures\n"));
	ft_strdel(&(parser->line));
	ft_strdel(&(parser->tmp));
	while (i <  env->resource.nb_textures)
	{
		if (parse_bmp_file(env, parser))
			return (ft_printf("Error while parsing texture %d\n", i));
		i++;
	}
	return (0);
}

int		map_parse_sprites(t_env *env, t_map_parser *parser)
{
	int	i;

	i = 0;
	ft_strdel(&parser->line);
	ft_strdel(&parser->tmp);
	if (!(parser->tmp = ft_strnew(0)))
		return (custom_error("Memalloc failed\n"));
	if (!(parser->line = ft_strnew(1)))
		return (custom_error("Could not malloc line\n"));
	while ((parser->ret = read(parser->fd, parser->tmp, 1)) > 0
	&& ft_strlen(parser->line) < 100)
	{
		if (*(parser->tmp) == '\n')
			break;
		if (!(parser->line = ft_strjoin_free(parser->line, parser->tmp)))
			return (custom_error("Could not malloc line\n"));
	}
	if (*(parser->tmp) != '\n')
		return (custom_error("Expected a '\\n' at the end of file name\n"));
	if (*(parser->line) && *(parser->line) != 'S')
		return (custom_error("Expected letter: S\n"));
	parser->line++;
	if (*(parser->line) && *(parser->line) != 'P')
		return (custom_error("Expected letter: 'P'\n"));
	parser->line++;
	if (*(parser->line) && *(parser->line) != ' ')
		return (custom_error("Expected a space\n"));
	parser->line++;
	if (valid_int(parser->line, parser))
		return (custom_error("Invalid int for sprites number\n"));
	env->resource.nb_sprites = atoi(parser->line);
	parser->line -= 3;
	if (env->resource.nb_sprites > NB_BMP_SPRITES
	|| env->resource.nb_sprites < 1)
		return (custom_error("Wrong number of sprites\n"));
	ft_strdel(&(parser->tmp));
	ft_strdel(&(parser->line));
	while (i <  env->resource.nb_sprites)
	{
		if (parse_bmp_file(env, parser))
			return (ft_printf("Error while parsing sprite %d\n", i));
		i++;
	}
	return (0);
}

int		map_parse_sounds(t_env *env, t_map_parser *parser)
{
	int	i;

	i = 0;
	if (!(parser->tmp = ft_strnew(1)))
		return (custom_error("Memalloc failed\n"));
	if (!(parser->line = ft_strnew(1)))
		return (custom_error("Could not malloc line\n"));
	while ((parser->ret = read(parser->fd, parser->tmp, 1)) > 0
	&& ft_strlen(parser->line) < 100)
	{
		if (*(parser->tmp) == '\n')
			break;
		if (!(parser->line = ft_strjoin_free(parser->line, parser->tmp)))
			return (custom_error("Could not malloc line\n"));
	}
	if (*(parser->tmp) != '\n')
		return (custom_error("Expected a '\\n' at the end of file name\n"));
	if (*(parser->line) && *(parser->line) != 'S')
		return (custom_error("Expected letter: S\n"));
	parser->line++;
	if (*(parser->line) && *(parser->line) != ' ')
		return (custom_error("Expected a space\n"));
	parser->line++;
	if (valid_int(parser->line, parser))
		return (custom_error("Invalid int for sounds number\n"));
	env->resource.nb_sound = atoi(parser->line);
	parser->line -= 2;
	ft_strdel(&(parser->line));
	if (env->resource.nb_sound > NB_MUSICS + NB_SOUNDS
	  	|| env->resource.nb_sound < 0)
		return (custom_error("Wrong number of sounds\n"));
	while (i < env->resource.nb_sound)
	{
		if (parse_sound(env, parser))
			return (custom_error("Error while parsing a sound\n"));
		i++;
	}
	return (0);
}

int		map_parse_skyboxes(t_env *env, t_map_parser *parser)
{
	int	i;

	i = 0;
	ft_strdel(&parser->line);
	ft_strdel(&parser->tmp);
	if (!(parser->tmp = ft_strnew(0)))
		return (custom_error("Memalloc failed\n"));
	if (!(parser->line = ft_strnew(1)))
		return (custom_error("Could not malloc line\n"));
	while ((parser->ret = read(parser->fd, parser->tmp, 1)) > 0
	&& ft_strlen(parser->line) < 100)
	{
		if (*(parser->tmp) == '\n')
			break;
		if (!(parser->line = ft_strjoin_free(parser->line, parser->tmp)))
			return (custom_error("Could not malloc line\n"));
	}
	if (*(parser->tmp) != '\n')
		return (custom_error("Expected a '\\n' at the end of file name\n"));
	if (*(parser->line) && *(parser->line) != 'S')
		return (custom_error("Expected letter: S\n"));
	parser->line++;
	if (*(parser->line) && *(parser->line) != 'K')
		return (custom_error("Expected letter: 'K'\n"));
	parser->line++;
	if (*(parser->line) && *(parser->line) != 'Y')
		return (custom_error("Expected letter: 'Y'\n"));
	parser->line++;
	if (*(parser->line) && *(parser->line) != ' ')
		return (custom_error("Expected a space\n"));
	parser->line++;
	if (valid_int(parser->line, parser))
		return (custom_error("Invalid int for skybox images number\n"));
	env->resource.nb_skyboxes = atoi(parser->line);
	parser->line -= 2;
	if (env->resource.nb_skyboxes > MAX_SKYBOX * 6
	|| env->resource.nb_skyboxes < 1)
		return (custom_error("Wrong number of sprites\n"));
	ft_strdel(&parser->tmp);
	while (i <  env->resource.nb_skyboxes)
	{
		if (parse_bmp_file(env, parser))
			return (ft_printf("Error while parsing skybox %d\n", i));
		i++;
	}
	return (0);
}

int		map_parse_hud(t_env *env, t_map_parser *parser)
{
	int	i;

	i = 0;
	ft_strdel(&parser->line);
	ft_strdel(&parser->tmp);
	if (!(parser->tmp = ft_strnew(0)))
		return (custom_error("Memalloc failed\n"));
	if (!(parser->line = ft_strnew(1)))
		return (custom_error("Could not malloc line\n"));
	while ((parser->ret = read(parser->fd, parser->tmp, 1)) > 0
	&& ft_strlen(parser->line) < 100)
	{
		if (*(parser->tmp) == '\n')
			break;
		if (!(parser->line = ft_strjoin_free(parser->line, parser->tmp)))
			return (custom_error("Could not malloc line\n"));
	}
	if (*(parser->tmp) != '\n')
		return (custom_error("Expected a '\\n' at the end of file name\n"));
	if (*(parser->line) && *(parser->line) != 'H')
		return (custom_error("Expected letter: H\n"));
	parser->line++;
	if (*(parser->line) && *(parser->line) != ' ')
		return (custom_error("Expected a space\n"));
	parser->line++;
	if (valid_int(parser->line, parser))
		return (custom_error("Invalid int for hud images number\n"));
	env->resource.nb_hud_files = atoi(parser->line);
	parser->line -= 2;
	if (env->resource.nb_hud_files > NB_HUD_FILES
	|| env->resource.nb_hud_files < 1)
		return (custom_error("Wrong number of hud\n"));
	ft_strdel(&parser->line);
	ft_strdel(&parser->tmp);
	while (i <  env->resource.nb_hud_files)
	{
		if (parse_bmp_file(env, parser))
			return (custom_error("Error while parsing hud images\n"));
		i++;
	}
	return (0);
}

int		map_parse_fonts(t_env *env, t_map_parser *parser)
{
	int	i;

	i = 0;
	ft_strdel(&parser->line);
	if (!(parser->tmp = ft_strnew(1)))
		return (custom_error("Memalloc failed\n"));
	if (!(parser->line = ft_strnew(1)))
		return (custom_error("Could not malloc line\n"));
	while ((parser->ret = read(parser->fd, parser->tmp, 1)) > 0
	&& ft_strlen(parser->line) < 100)
	{
		if (*(parser->tmp) == '\n')
			break;
		if (!(parser->line = ft_strjoin_free(parser->line, parser->tmp)))
			return (custom_error("Could not malloc line\n"));
	}
	if (*(parser->tmp) != '\n')
		return (custom_error("Expected a '\\n' at the end of file name\n"));
	if (*(parser->line) && *(parser->line) != 'F')
		return (custom_error("Expected letter: 'F'\n"));
	parser->line++;
	if (*(parser->line) && *(parser->line) != ' ')
		return (custom_error("Expected a space\n"));
	parser->line++;
	if (valid_int(parser->line, parser))
		return (custom_error("Invalid int for fonts number\n"));
	env->resource.nb_fonts = atoi(parser->line);
	parser->line -= 2;
	if (env->resource.nb_fonts > NB_FONTS
	|| env->resource.nb_fonts < 1)
		return (custom_error("Wrong number of fonts\n"));
	ft_strdel(&(parser->tmp));
	i = 0;
	while (i < env->resource.nb_fonts)
	{
		if (parse_font_file(env, parser))
			return (ft_printf("Error while parsing font %d\n", i));
		i++;
	}
	return (0);
}

int		parse_resources(t_env *env, t_map_parser *parser)
{
	if (map_parse_textures(env, parser))
		return (custom_error("Error while parsing map textures\n"));
	if (map_parse_sprites(env, parser))
		return (custom_error("Error while parsing map sprites\n"));
	if (map_parse_skyboxes(env, parser))
		return (custom_error("Error while parsing map skyboxes\n"));
	if (map_parse_hud(env, parser))
		return (custom_error("Error while parsing map hud\n"));
	if (map_parse_sounds(env, parser))
		return (custom_error("Error while parsing map sounds\n"));
	if (map_parse_fonts(env, parser))
		return (custom_error("Error while parsing map fonts\n"));
	return (0);
}
