/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_sprite_parser.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:50:08 by lnicosia          #+#    #+#             */
/*   Updated: 2020/01/16 11:23:29 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_parser.h"

int		floor_sprite_parser(t_env *env, t_map_parser *parser, char **line,
t_events_parser *eparser)
{
	if (!**line || **line == ']')
		return (missing_data("sector data", parser));
	if (**line != ' ')
		return (invalid_char("before sector number", "a space",
		**line, parser));
	(*line)++;
	if (!**line || **line == ']')
		return (missing_data("sector data", parser));
	if (**line != '(')
		return (invalid_char("before sector number", "'('", **line, parser));
	(*line)++;
	if (!**line || **line == ']' || **line == ')')
		return (missing_data("sector, floor_sprite and sprite", parser));
	if (valid_number(*line, parser))
		return (invalid_char("before sector number", "a digit", **line,
		parser));
	eparser->trigger_sector = ft_atoi(*line);
	if (eparser->trigger_sector < 0
		|| eparser->trigger_sector >= env->nb_sectors)
		return (custom_error_with_line("Invalid sector index", parser));
		*line = skip_number(*line);
	if (!**line || **line == ']' || **line == ')')
		return (missing_data("floor_sprite number", parser));
	if (**line != ' ')
		return (invalid_char("after sector number", "a space", **line,
		parser));
		(*line)++;
	if (!**line || **line == ']' || **line == ')')
		return (missing_data("floor_sprite and sprite", parser));
	if (valid_number(*line, parser))
		return (invalid_char("before floor_sprite number", "a digit", **line,
		parser));
	eparser->trigger_sprite = ft_atoi(*line);
	if (eparser->trigger_sprite < 0 || eparser->trigger_sprite >=
		env->sectors[eparser->trigger_sector].floor_sprites.nb_sprites)
		return (custom_error_with_line("Invalid floor_sprite index", parser));
		*line = skip_number(*line);
	if (!**line || **line != ')')
		return (invalid_char("after sprite index", "')'", **line, parser));
	(*line)++;
	return (0);
}
