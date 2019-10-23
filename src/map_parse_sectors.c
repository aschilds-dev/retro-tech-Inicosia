/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_sectors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 16:14:16 by lnicosia          #+#    #+#             */
/*   Updated: 2019/10/23 16:03:38 by gaerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
#include "env.h"

int			parse_floor(t_env *env, char **line, t_map_parser *parser)
{
	if (**line != '[')
		return (invalid_char("before floor data", "'['", **line, parser));
	(*line)++;
	if (!**line || **line == ']')
		return (missing_data("floor height", parser));
	if (valid_number(*line, parser))
		return (invalid_char("before floor height", "a digit", **line, parser));
	env->sectors[parser->sectors_count].floor = ft_atof(*line);
	env->sectors[parser->sectors_count].floor_min = env->sectors[parser->
		sectors_count].floor;
	env->sectors[parser->sectors_count].floor_max = env->sectors[parser->
		sectors_count].floor;
	*line = skip_number(*line);
	if (!**line || **line == ']')
		return (missing_data("floor slope", parser));
	if (**line && **line != ' ')
		return (invalid_char("after floor height", "a digit or space(s)",
					**line, parser));
	*line = skip_spaces(*line);
	if (!**line || **line == ']')
		return (missing_data("floor slope", parser));
	if (valid_number(*line, parser))
		return (invalid_char("before floor slope", "a digit or space(s)",
					**line, parser));
		env->sectors[parser->sectors_count].floor_slope = ft_atof(*line);
/*	if (env->sectors[parser->sectors_count].floor_slope > 45
			|| env->sectors[parser->sectors_count].floor_slope < -45)
		return (custom_error_with_line("Slopes must be between -45"
					"and 45 degrees", parser));*/
		env->sectors[parser->sectors_count].floor_slope = env->
				sectors[parser->sectors_count].floor_slope;
	*line = skip_number(*line);
	if (!**line || **line == ']')
		return (missing_data("floor texture", parser));
	if (**line && **line != ' ')
		return (invalid_char("after floor slope", "a digit or space(s)",
					**line, parser));
	*line = skip_spaces(*line);
	if (!**line || **line == ']')
		return (missing_data("floor texture", parser));
	if (valid_number(*line, parser))
		return (invalid_char("before floor texture", "a digit or space(s)",
					**line, parser));
	env->sectors[parser->sectors_count].floor_texture = ft_atoi(*line);
	if (env->sectors[parser->sectors_count].floor_texture < 0
			|| env->sectors[parser->sectors_count].floor_texture >= MAX_TEXTURE)
		return (custom_error_with_line("Invalid floor texture", parser));
	env->sectors[parser->sectors_count].floor_scale.x = env->textures[env->sectors[parser->sectors_count].floor_texture].surface->w / 10;
	env->sectors[parser->sectors_count].floor_scale.y = env->textures[env->sectors[parser->sectors_count].floor_texture].surface->h / 10;
	env->sectors[parser->sectors_count].floor_align = new_v2(0, 0);
	*line = skip_number(*line);
	if (!**line)
		return (missing_data("']' after floor texture",parser));
	if (**line != ']')
		return (invalid_char("after floor texture", "a digit or ']'",
					**line, parser));
	(*line)++;
	if (!**line)
		return (missing_data("ceiling, vertices, neighbors, textures and light",
					parser));
	if (**line != ' ')
		return (invalid_char("after floor data", "space(s)", **line, parser));
	*line = skip_spaces(*line);
	return (0);
}

int			parse_ceiling(t_env *env, char **line, t_map_parser *parser)
{
	if (!**line)
		return (missing_data("ceiling, vertices, neighbors, textures and light",
					parser));
	if (**line != '[')
		return (invalid_char("before ceiling data", "'['",
					**line, parser));
	(*line)++;
	if (!**line || **line == ']')
		return (missing_data("ceiling height", parser));
	if (valid_number(*line, parser))
		return (invalid_char("before ceiling height", "a digit",
					**line, parser));
	env->sectors[parser->sectors_count].ceiling = ft_atof(*line);
	env->sectors[parser->sectors_count].ceiling_min = env->sectors[parser->
		sectors_count].ceiling;
	env->sectors[parser->sectors_count].ceiling_max = env->sectors[parser->
		sectors_count].ceiling;
	*line = skip_number(*line);
	if (!**line || **line == ']')
		return (missing_data("ceiling slope", parser));
	if (**line && **line != ' ')
		return (invalid_char("after ceiling height", "a digit or space(s)",
					**line, parser));
	*line = skip_spaces(*line);
	if (!**line || **line == ']')
		return (missing_data("ceiling slope", parser));
	if (valid_number(*line, parser))
		return (invalid_char("before ceiling slope", "a digit or space(s)",
					**line, parser));
	env->sectors[parser->sectors_count].ceiling_slope = ft_atof(*line);
	if (env->sectors[parser->sectors_count].ceiling_slope > 45
			|| env->sectors[parser->sectors_count].ceiling_slope < -45)
		return (custom_error_with_line("Slopes must be between -45"
					"and 45 degrees", parser));
	env->sectors[parser->sectors_count].ceiling_slope = tan(env->
			sectors[parser->sectors_count].ceiling_slope * CONVERT_RADIANS);
	*line = skip_number(*line);
	if (!**line || **line == ']')
		return (missing_data("ceiling texture", parser));
	if (**line && **line != ' ')
		return (invalid_char("after ceiling slope", "a digit or space(s)",
					**line, parser));
	*line = skip_spaces(*line);
	if (!**line || **line == ']')
		return (missing_data("ceiling texture", parser));
	if (valid_number(*line, parser))
		return (invalid_char("before ceiling texture", "a digit or space(s)",
					**line, parser));
	env->sectors[parser->sectors_count].ceiling_texture = ft_atoi(*line);
	if (env->sectors[parser->sectors_count].ceiling_texture < -1 || env->
			sectors[parser->sectors_count].ceiling_texture >= MAX_TEXTURE)
		return (custom_error_with_line("Invalid ceiling texture", parser));
	env->sectors[parser->sectors_count].skybox = 0;
	if (env->sectors[parser->sectors_count].ceiling_texture == -1)
	{
		env->sectors[parser->sectors_count].skybox = 1;
		env->sectors[parser->sectors_count].ceiling_texture = 38;
	}
	env->sectors[parser->sectors_count].ceiling_scale.x = env->textures[env->sectors[parser->sectors_count].ceiling_texture].surface->w / 10;
	env->sectors[parser->sectors_count].ceiling_scale.y = env->textures[env->sectors[parser->sectors_count].ceiling_texture].surface->h / 10;
	env->sectors[parser->sectors_count].ceiling_align = new_v2(0, 0);
	*line = skip_number(*line);
	if (!**line)
		return (missing_data("']' after ceiling texture",parser));
	if (**line != ']')
		return (invalid_char("after ceiling texture", "a digit or ']'",
					**line, parser));
	(*line)++;
	if (!**line)
		return (missing_data("vertices, neighbors, textures and light",
					parser));
	if (**line != ' ')
		return (invalid_char("after ceiling data", "space(s)",
					**line, parser));
	*line = skip_spaces(*line);
	return (0);
}

int			init_sector_data(t_env *env, char *line, t_map_parser *parser)
{
	if (!*line)
		return (missing_data("vertices, neighbors, textures and light",
					parser));
	if (*line != '(')
		return (invalid_char("before sector vertices", "'('", *line, parser));
	line++;
	if ((parser->sector_vertices_count = count_vertices(line, parser)) == -1)
		return (custom_error("Error while counting vertices"));
	if (parser->sector_vertices_count < 3)
	{
		ft_dprintf(STDERR_FILENO,
				"[Line %d] Sector %d must contain at least 3 vertices\n",
				parser->line_count, parser->sectors_count);
		return (-1);
	}
	env->sectors[parser->sectors_count].nb_vertices = parser->
		sector_vertices_count;
	if (!(env->sectors[parser->sectors_count].vertices = (short*)
				malloc(sizeof(short) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector vertices:"));
	if (!(env->sectors[parser->sectors_count].neighbors = (short*)
				malloc(sizeof(short) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector neighbors:"));
	if (!(env->sectors[parser->sectors_count].textures = (short*)
				malloc(sizeof(short) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector vertices:"));
	if (!(env->sectors[parser->sectors_count].sprites = (t_wall_sprite*)
				malloc(sizeof(t_wall_sprite) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector vertices:"));
	if (!(env->sectors[parser->sectors_count].align = (t_v2*)
				malloc(sizeof(t_v2) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc textures alignement:"));
	if (!(env->sectors[parser->sectors_count].scale = (t_v2*)
				malloc(sizeof(t_v2) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc textures scale:"));
	if (!(env->sectors[parser->sectors_count].ceilings = (double*)
				malloc(sizeof(double) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector ceilings:"));
	if (!(env->sectors[parser->sectors_count].floors = (double*)
				malloc(sizeof(double) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector floors:"));
	if (!(env->sectors[parser->sectors_count].clipped_ceilings1 = (double*)
				malloc(sizeof(double) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector clipped_ceilings1:"));
	if (!(env->sectors[parser->sectors_count].clipped_floors1 = (double*)
				malloc(sizeof(double) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector clipped_floors1:"));
	if (!(env->sectors[parser->sectors_count].clipped_ceilings2 = (double*)
				malloc(sizeof(double) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector clipped_ceilings2:"));
	if (!(env->sectors[parser->sectors_count].clipped_floors2 = (double*)
				malloc(sizeof(double) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector clipped_floors2:"));
	if (!(env->sectors[parser->sectors_count].wall_width = (double*)
				malloc(sizeof(double) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector wall_size:"));
	if (!(env->sectors[parser->sectors_count].selected = (short*)
				malloc(sizeof(short) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector vertices:"));
	return (0);
}

int			parse_sector_vertices(t_env *env, char **line, t_map_parser *parser)
{
	int	i;

	i = 0;
	while (i < parser->sector_vertices_count)
	{
		env->sectors[parser->sectors_count].vertices[i] = ft_atoi(*line);
		if (env->sectors[parser->sectors_count].vertices[i] < 0 || env->
				sectors[parser->sectors_count].vertices[i] >= env->nb_vertices)
		{
			ft_dprintf(STDERR_FILENO,
					"[Line %d] Vertex \'%d\' in sector %d does not exist\n",
					parser->line_count,
					env->sectors[parser->sectors_count].vertices[i],
					parser->sectors_count);
			return (-1);
		}
		*line = skip_number(*line);
		*line = skip_spaces(*line);
		i++;
	}
	env->sectors[parser->sectors_count].vertices[parser->sector_vertices_count]
		= env->sectors[parser->sectors_count].vertices[0];
	if (check_vertices_uniqueness(env->sectors[parser->sectors_count]))
		return (sector_error("has duplicate vertices", parser->sectors_count,
					parser));
	if (check_sector_duplicate(env, env->sectors[parser->sectors_count],
				parser->sectors_count))
		return (sector_error("already exists", parser->sectors_count, parser));
	(*line)++;
	if (!**line)
		return (missing_data("neighbors, textures and light", parser));
	if (**line != ' ')
		return (invalid_char("after vertices data", "space(s)",
					**line, parser));
	*line = skip_spaces(*line);
	return (0);
}

int			parse_sector_neighbors(t_env *env, char **line, t_map_parser *parser)
{
	int	i;

	if (!**line)
		return (missing_data("neighbors, textures and light", parser));
	if (**line != '(')
		return (invalid_char("before sector neighbors", "'('", **line, parser));
	(*line)++;
	if ((parser->sector_neighbors_count = count_neighbors(*line, parser)) == -1)
		return (custom_error("Error while counting neighbors"));
	if (parser->sector_neighbors_count < parser->sector_vertices_count)
		return (sector_error("is missing one or more neighbors",
					parser->sectors_count, parser));
	if (parser->sector_neighbors_count > parser->sector_vertices_count)
		return (sector_error("has too much neighbors",
					parser->sectors_count, parser));
	i = 0;
	while (i < parser->sector_neighbors_count)
	{
		env->sectors[parser->sectors_count].neighbors[i] = ft_atoi(*line);
		if (env->sectors[parser->sectors_count].neighbors[i] < -1 || env->
				sectors[parser->sectors_count].neighbors[i] >= env->nb_sectors)
		{
			ft_dprintf(STDERR_FILENO,
					"[Line %d] Neighbor \'%d\' in sector %d does not exist\n",
					parser->line_count,
					env->sectors[parser->sectors_count].neighbors[i],
					parser->sectors_count);
			return (-1);
		}
		if (env->sectors[parser->sectors_count].neighbors[i] == parser->sectors_count)
			return (sector_error("can not contain a portal to itself", parser->sectors_count, parser));
		*line = skip_number(*line);
		*line = skip_spaces(*line);
		i++;
	}
	(*line)++;
	if (!**line)
		return (missing_data("texures and light", parser));
	if (**line != ' ')
		return (invalid_char("after neighbors data", "space(s)",
					**line, parser));
	*line = skip_spaces(*line);
	return (0);
}

int			parse_sector_textures(t_env *env, char **line, t_map_parser *parser)
{
	int	i;

	if (!**line)
		return (missing_data("textures, sprite and light", parser));
	if (**line != '(')
		return (invalid_char("before sector textures", "'('", **line, parser));
	(*line)++;
	if ((parser->sector_textures_count = count_textures(*line, parser)) == -1)
		return (custom_error("Error while counting textures"));
	if (parser->sector_textures_count < parser->sector_vertices_count)
		return (sector_error("is missing one or more textures", parser->sectors_count, parser));
	if (parser->sector_textures_count > parser->sector_vertices_count)
		return (sector_error("has too much textures", parser->sectors_count, parser));
	i = 0;
	while (i < parser->sector_textures_count)
	{
		env->sectors[parser->sectors_count].textures[i] = ft_atoi(*line);
		if (env->sectors[parser->sectors_count].textures[i] < -1 || env->sectors[parser->sectors_count].textures[i] >= MAX_TEXTURE)
		{
			ft_dprintf(STDERR_FILENO,
					"[Line %d] Texture \'%d\' in sector %d does not exist\n",
					parser->line_count,
					env->sectors[parser->sectors_count].textures[i],
					parser->sectors_count);
			return (-1);
		}
		env->sectors[parser->sectors_count].align[i] = new_v2(0, 0);
		if (env->sectors[parser->sectors_count].textures[i] == -1)
		{
			env->sectors[parser->sectors_count].scale[i] = new_v2(
					env->textures[38].surface->w,
					env->textures[38].surface->h / 10);
		}
		else
		{
			env->sectors[parser->sectors_count].scale[i] = new_v2(
					env->textures[env->sectors[parser->sectors_count].textures[i]].surface->w,
					env->textures[env->sectors[parser->sectors_count].textures[i]].surface->h);
		}
		*line = skip_number(*line);
		*line = skip_spaces(*line);
		i++;
	}
	(*line)++;
	if (!**line)
		return (missing_data("sprite and light", parser));
	if (**line != ' ')
		return (invalid_char("after textures data", "space(s)", **line, parser));
	*line = skip_spaces(*line);
	return (0);
}

int			parse_sector_sprite(t_env *env, char **line, t_map_parser *parser)
{
	int	i;

	if (!**line)
		return (missing_data("sprites and light", parser));
	if (**line != '(')
		return (invalid_char("before sector sprites", "'('", **line, parser));
	(*line)++;
	if ((parser->sector_sprites_count = count_sprites(*line, parser)) == -1)
		return (custom_error("Error while counting sprites"));
	if (parser->sector_sprites_count < parser->sector_vertices_count)
		return (sector_error("is missing one or more sprites", parser->sectors_count, parser));
	if (parser->sector_sprites_count > parser->sector_vertices_count)
		return (sector_error("has too much sprites", parser->sectors_count, parser));
	i = 0;
	while (i < parser->sector_sprites_count)
	{
		(*line)++;
		env->sectors[parser->sectors_count].sprites[i].sprite = ft_atoi(*line);
		if (env->sectors[parser->sectors_count].sprites[i].sprite < -1
				|| env->sectors[parser->sectors_count].sprites[i].sprite > MAX_SPRITES)
			return (custom_error_with_line("Invalid sprite texture", parser));
		*line = skip_number(*line);
		*line = skip_spaces(*line);
		env->sectors[parser->sectors_count].sprites[i].pos.x = ft_atof(*line);
		*line = skip_number(*line);
		*line = skip_spaces(*line);
		env->sectors[parser->sectors_count].sprites[i].pos.y = ft_atof(*line);
		*line = skip_number(*line);
		*line = skip_spaces(*line);
		env->sectors[parser->sectors_count].sprites[i].scale.x = ft_atof(*line);
		if (env->sectors[parser->sectors_count].sprites[i].scale.x <= 0)
			return (custom_error_with_line("Sprite scale must be positive", parser));
		*line = skip_number(*line);
		*line = skip_spaces(*line);
		env->sectors[parser->sectors_count].sprites[i].scale.y = ft_atof(*line);
		if (env->sectors[parser->sectors_count].sprites[i].scale.y <= 0)
			return (custom_error_with_line("Sprite scale must be positive", parser));
		*line = skip_number(*line);
		(*line)++;
		i++;
	}
	(*line)++;
	if (!**line)
		return (missing_data("light", parser));
	if (**line != ' ')
		return (invalid_char("after sector sprites", "space(s)",
					**line, parser));
	*line = skip_spaces(*line);
	/*(void)line;
	int	i = 0;
	while (i < parser->sector_vertices_count)
	{
		env->sectors[parser->sectors_count].sprites[i].sprite = -1;
		env->sectors[parser->sectors_count].sprites[i].pos = new_v2(0, 0);
		if (env->sectors[parser->sectors_count].textures[i] == -1)
		{
			env->sectors[parser->sectors_count].sprites[i].scale = 
				new_v2(env->textures[38].surface->w, env->textures[38].surface->h);
			env->sectors[parser->sectors_count].scale[i] = 
				new_v2(env->textures[38].surface->w, env->textures[38].surface->h);
		}
		else
		{
			env->sectors[parser->sectors_count].sprites[i].scale = 
				new_v2(env->textures[env->sectors[parser->sectors_count].textures[i]].surface->w, env->textures[env->sectors[parser->sectors_count].textures[i]].surface->h);
			env->sectors[parser->sectors_count].scale[i] = 
				new_v2(env->textures[env->sectors[parser->sectors_count].textures[i]].surface->w, env->textures[env->sectors[parser->sectors_count].textures[i]].surface->h);
		}
		env->sectors[parser->sectors_count].align[i] = new_v2(0, 0);
		i++;
	}*/
	return (0);
}

int			parse_sector_light(t_env *env, char **line, t_map_parser *parser)
{
	if (!**line)
		return (missing_data("light", parser));
	if (valid_number(*line, parser))
		return (invalid_char("before light", "a digit", **line, parser));
	env->sectors[parser->sectors_count].brightness = ft_atoi(*line);
	env->sectors[parser->sectors_count].light_color = 0xFFFFFFFF;
	if (env->sectors[parser->sectors_count].brightness < -255 ||
			env->sectors[parser->sectors_count].brightness > 255)
		return (custom_error("Light must be between -255 and 255"));
	*line = skip_number(*line);
	if (!**line)
		return (missing_data("sector statue", parser));
	if (**line != ' ')
		return (invalid_char("after light data", "space(s)",
					**line, parser));
	*line = skip_spaces(*line);
	return (0);
}

int			parse_sector_statue(t_env *env, char **line, t_map_parser *parser)
{
	if (!**line)
		return (missing_data("sector statue", parser));
	if (valid_number(*line, parser))
		return (invalid_char("before sector statue", "a digit", **line, parser));
	env->sectors[parser->sectors_count].statue = ft_atoi(*line);
	if (env->sectors[parser->sectors_count].statue > 2 ||
			env->sectors[parser->sectors_count].statue < 0)
		return (custom_error_with_line("sector statue must be between 0 and 2", parser));
	*line = skip_number(*line);
	if (**line != '\0')
		return (extra_data(*line, parser));
	return (0);
}

static int	parse_sector(t_env *env, char *line, t_map_parser *parser)
{
	parser->sector_vertices_count = 0;
	parser->sector_neighbors_count = 0;
	parser->sector_textures_count = 0;
	parser->sector_sprites_count = 0;
	env->sectors[parser->sectors_count].num = parser->sectors_count;
	if (parse_floor(env, &line, parser))
		return (-1);
	//return (custom_error("Error while parsing floor"));
	if (parse_ceiling(env, &line, parser))
		return (-1);
	//return (custom_error("Error while parsing ceiling"));
	if (env->sectors[parser->sectors_count].ceiling
			<= env->sectors[parser->sectors_count].floor)
		return (-1);
	//return (sector_error("ceiling must be higher than its floor",
	//parser->sectors_count, parser));
	if (init_sector_data(env, line, parser))
		return (-1);
	//return (custom_error("Could not init sector data"));
	line++;
	if (parse_sector_vertices(env, &line, parser))
		return (-1);
	//return (custom_error("Error while parsing sector vertices"));
	if (parse_sector_neighbors(env, &line, parser))
		return (-1);
	//return (custom_error("Error while parsing sector neighbors"));
	if (parse_sector_textures(env, &line, parser))
		return (-1);
	//return (custom_error("Error while parsing sector textures"));
	if (parse_sector_sprite(env, &line, parser))
		return (-1);
	if (parse_sector_light(env, &line, parser))
		return (-1);
		//return (custom_error("Error while parsing sector light"));
	if (parse_sector_statue(env, &line, parser))
		return (-1);
	return (0);
}

int			parse_sectors(t_env *env, t_map_parser *parser)
{
	char	*line;
	char	*tmp;

	line = NULL;
	while (parser->sectors_count < env->nb_sectors
			&& (parser->ret = get_next_line(parser->fd, &line)))
	{
		tmp = line;
		parser->line_count++;
		if (*tmp)
		{
			if (parse_sector(env, tmp, parser))
				return (-1);
			parser->sectors_count++;
		}
		else
		{
			ft_dprintf(STDERR_FILENO,
					"[Line %d] You must still declare %d sector(s)\n",
					parser->line_count,
					env->nb_sectors - parser->sectors_count);
			return (-1);
		}
		ft_strdel(&line);
	}
	if ((parser->ret = get_next_line(parser->fd, &line)))
	{
		parser->line_count++;
		if (*line)
			return (custom_error_with_line("Must be an empty line "
						"(every sector has been declared)",
						parser));
		ft_strdel(&line);
	}
	else
		return (missing_data("objects and player data", parser));
	return (0);
}
