/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_enemy_sprite.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 17:55:55 by lnicosia          #+#    #+#             */
/*   Updated: 2020/04/30 18:03:18 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		parse_enemy_sprite2(t_env *env, char **line, t_map_parser *parser)
{
	if (!**line || **line == ']')
		return (missing_data("enemy scale", parser));
	if (valid_double(*line, parser))
		return (custom_error("Invalid double for enemy %d scale",
		parser->enemies_count));
		env->enemies[parser->enemies_count].scale = ft_atof(*line);
	if (env->enemies[parser->enemies_count].scale
	+ env->enemies[parser->enemies_count].pos.z
	> get_ceiling_at_pos(&env->sectors[env->enemies[parser->enemies_count].
	sector], env->enemies[parser->enemies_count].pos, env))
		return (custom_error("Enemy's head is too high compared to ceiling"
		" height\n"));
	*line = skip_number(*line);
	if (!**line)
		return (missing_data("']' after enemy scale", parser));
	if (**line != ']')
		return (invalid_char("after enemy scale", "a digit or ']'",
			**line, parser));
		(*line)++;
	if (!**line)
		return (missing_data("enemy data, health speed and damage", parser));
	if (**line != ' ')
		return (invalid_char("after enemy scale", "space(s)", **line, parser));
	*line = skip_spaces(*line);
	return (0);
}

int		parse_enemy_sprite(t_env *env, char **line, t_map_parser *parser)
{
	int	parse;

	if (**line != '[')
		return (invalid_char("before enemy sprite", "'['", **line, parser));
	(*line)++;
	if (!**line || **line == ']')
		return (missing_data("enemy sprite and scale", parser));
	if (valid_int(*line, parser))
		return (custom_error("Invalid int for enemy %d texture",
		parser->enemies_count));
		parse = ft_atoi(*line);
	if (parse < 0
			|| parse >= MAX_ENEMIES)
		return (custom_error_with_line("Invalid sprite texture", parser));
	env->enemies[parser->enemies_count].sprite =
	env->enemies_main_sprites[parse];
	*line = skip_number(*line);
	if (!**line || **line == ']')
		return (missing_data("enemy scale", parser));
	if (**line && **line != ' ')
		return (invalid_char("after enemy sprite", "a digit or space(s)",
			**line, parser));
		*line = skip_spaces(*line);
	return (parse_enemy_sprite2(env, line, parser));
}
