/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_press_event.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:19:38 by lnicosia          #+#    #+#             */
/*   Updated: 2020/01/15 17:50:44 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_parser.h"

int		new_press_event(t_env *env, t_map_parser *parser, char **line,
t_events_parser *eparser)
{
	(void)line;
	(void)parser;
	(void)env;
	(void)eparser;
	if (wall_sprite_parser(env, parser, line, eparser))
		return (-1);
	if (!(env->sectors[eparser->trigger_sector].wall_sprites[eparser->trigger_wall]
		.press_events[eparser->trigger_sprite] = (t_event*)ft_realloc(
		env->sectors[eparser->trigger_sector].wall_sprites[eparser->trigger_wall]
		.press_events[eparser->trigger_sprite],
		sizeof(t_event) * env->sectors[eparser->trigger_sector]
		.wall_sprites[eparser->trigger_wall].nb_press_events[eparser->trigger_sprite],
		sizeof(t_event) * (env->sectors[eparser->trigger_sector]
		.wall_sprites[eparser->trigger_wall].nb_press_events[eparser->trigger_sprite]
		+ 1))))
		return (ft_perror("Could not realloc global events"));
	env->sectors[eparser->trigger_sector].wall_sprites[eparser->trigger_wall]
	.nb_press_events[eparser->trigger_sprite]++;
	return (0);
}
