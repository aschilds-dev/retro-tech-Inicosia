/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_global_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:19:38 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/19 11:10:38 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_parser.h"
#include "parser.h"

int		new_global_event(t_env *env, t_event_trigger trigger, t_event event)
{
	(void)trigger;
	if (!(env->global_events = (t_event*)ft_realloc(env->global_events,
		sizeof(t_event) * env->nb_global_events,
		sizeof(t_event) * (env->nb_global_events + 1))))
		return (ft_perror("Could not realloc global events"));
	env->global_events[env->nb_global_events] = event;
	env->nb_global_events++;
	return (0);
}

int		new_parser_global_event(t_env *env, t_map_parser *parser, char **line,
t_events_parser *eparser)
{
	(void)line;
	(void)parser;
	(void)eparser;
	if (!(env->global_events = (t_event*)ft_realloc(env->global_events,
		sizeof(t_event) * env->nb_global_events,
		sizeof(t_event) * (env->nb_global_events + 1))))
		return (ft_perror("Could not realloc global events"));
	env->global_events[env->nb_global_events] = eparser->event;
	env->nb_global_events++;
	return (0);
}
