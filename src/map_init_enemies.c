/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_enemies.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 14:19:25 by gaerhard          #+#    #+#             */
/*   Updated: 2020/04/30 17:03:11 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		parse_enemies_init2(t_env *env, t_map_parser *parser)
{
	if (env->nb_enemies < 0)
		return (custom_error("You can not declare less than 0 enemies"));
	if (env->nb_enemies
			&& !(env->enemies = (t_enemy*)ft_memalloc(sizeof(t_enemy)
					* (env->nb_enemies))))
		return (ft_perror("Could not malloc enemies:"));
	ft_strdel(&parser->line);
	return (0);
}

int		parse_enemies_init(t_env *env, t_map_parser *parser, char *line)
{
	if (*line != 'E')
		return (invalid_char("at enemies number", "'E'", *line,
		parser));
		line++;
	if (!*line)
		return (missing_data("at enemies number", parser));
	if (*line != ' ')
		return (invalid_char("at enemies number", "space of a digit",
			*line, parser));
		line = skip_spaces(line);
	if (!*line)
		return (missing_data("before enemies number", parser));
	if (valid_int(line, parser) == WRONG_CHAR)
		return (invalid_char("before enemies number",
		"space of a digit", *line, parser));
		env->nb_enemies = ft_atoi(line);
	line = skip_number(line);
	if (*line && *line == ' ')
		return (extra_data("enemies number", parser));
	if (*line)
		return (invalid_char("after enemies number",
			"a digit or the end of the line", *line, parser));
		return (parse_enemies_init2(env, parser));
}

int		init_enemies(t_env *env, t_map_parser *parser)
{
	char	*line;

	while ((parser->ret = get_next_line(parser->fd, &parser->line)))
	{
		parser->line_count++;
		line = parser->line;
		if (*line && *line != '#')
		{
			return (parse_enemies_init(env, parser, line));
		}
		else if (*line != '#')
			return (missing_data("enemies number declaration", parser));
		ft_strdel(&parser->line);
	}
	return (0);
}
