/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sector_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 12:07:13 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/19 16:00:09 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
#include "env.h"
#include "parser.h"

int		init_sector_data3(t_env *env, t_map_parser *parser)
{
	if (!(env->sectors[parser->sectors_count].floors = (double*)
		ft_memalloc(sizeof(double) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector floors:"));
	if (!(env->sectors[parser->sectors_count].clipped_ceilings1 = (double*)
		ft_memalloc(sizeof(double) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector clipped_ceilings1:"));
	if (!(env->sectors[parser->sectors_count].clipped_floors1 = (double*)
		ft_memalloc(sizeof(double) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector clipped_floors1:"));
	if (!(env->sectors[parser->sectors_count].clipped_ceilings2 = (double*)
		ft_memalloc(sizeof(double) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector clipped_ceilings2:"));
	if (!(env->sectors[parser->sectors_count].clipped_floors2 = (double*)
		ft_memalloc(sizeof(double) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector clipped_floors2:"));
	if (!(env->sectors[parser->sectors_count].wall_width = (double*)
		ft_memalloc(sizeof(double) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector wall_size:"));
	if (!(env->sectors[parser->sectors_count].selected = (int*)
		ft_memalloc(sizeof(int) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector vertices:"));
	if (!(env->sectors[parser->sectors_count].wall_bullet_holes = (t_list**)
		ft_memalloc(sizeof(t_list*) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector vertices:"));
	return (0);
}

int		init_sector_data2(t_env *env, t_map_parser *parser)
{
	if (!(env->sectors[parser->sectors_count].portals = (int*)
		ft_memalloc(sizeof(int) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector portals:"));
	if (!(env->sectors[parser->sectors_count].textures = (int*)
		ft_memalloc(sizeof(int) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector vertices:"));
	if (!(env->sectors[parser->sectors_count].wall_sprites = (t_wall_sprites*)
		ft_memalloc(sizeof(t_wall_sprites)
		* (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector vertices:"));
	if (!(env->sectors[parser->sectors_count].walls_map_lvl = (double**)
		ft_memalloc(sizeof(double*) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector vertices:"));
	if (!(env->sectors[parser->sectors_count].align = (t_v2*)
		ft_memalloc(sizeof(t_v2) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc textures alignement:"));
	if (!(env->sectors[parser->sectors_count].scale = (t_v2*)
		ft_memalloc(sizeof(t_v2) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc textures scale:"));
	if (!(env->sectors[parser->sectors_count].ceilings = (double*)
		ft_memalloc(sizeof(double) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector ceilings:"));
	return (init_sector_data3(env, parser));
}

int		init_sector_data(t_env *env, char *line, t_map_parser *parser)
{
	if (!*line)
		return (missing_data("vertices, neighbors, textures and light",
		parser));
		if (*line != '(')
		return (invalid_char("before sector vertices", "'('", *line, parser));
	line++;
	if ((parser->sector_vertices_count = count_vertices(line, parser)) == -1)
		return (custom_error("Error while counting vertices\n"));
	if (parser->sector_vertices_count < 3)
		return (custom_error("[Line %d] Sector need 3 vertices\n",
		parser->line_count, parser->sectors_count));
		env->sectors[parser->sectors_count].nb_vertices =
		parser->sector_vertices_count;
	if (!(env->sectors[parser->sectors_count].vertices = (int*)
		ft_memalloc(sizeof(int) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector vertices:"));
	if (!(env->sectors[parser->sectors_count].neighbors = (int*)
		ft_memalloc(sizeof(int) * (parser->sector_vertices_count + 1))))
		return (ft_perror("Could not malloc sector neighbors:"));
	return (init_sector_data2(env, parser));
}
