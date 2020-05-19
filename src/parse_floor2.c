/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_floor2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:08:42 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/19 11:13:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parser.h"
#include "parser.h"

int		parse_floor6(t_env *env, char **line, t_map_parser *parser)
{
	env->sectors[parser->sectors_count].floor_map_scale.y = ft_atof(*line);
	if (env->sectors[parser->sectors_count].floor_map_scale.y < 1
		|| env->sectors[parser->sectors_count].floor_map_scale.y > 100)
		return (custom_error_with_line("Floor scale value: 1 to 100", parser));
	*line = skip_number(*line);
	if (!**line)
		return (missing_data("']' after floor scale", parser));
	if (**line != ']')
		return (invalid_char("after floor scale", "a digit or ']'",
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
