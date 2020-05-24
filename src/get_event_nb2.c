/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_event_nb2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 11:20:34 by lnicosia          #+#    #+#             */
/*   Updated: 2020/04/30 11:20:35 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_parser.h"
#include "parser.h"

size_t	*get_walk_out_event_nb(t_env *env, t_events_parser *eparser, int mode)
{
	if (!mode)
		return (&env->sectors[eparser->source_sector].
			walk_out_events[eparser->source_index].
			nb_launch_conditions);
	else
		return (&env->sectors[eparser->target_sector].
			walk_out_events[eparser->target_index].
			nb_launch_conditions);
}

size_t	*get_death_event_nb(t_env *env, t_events_parser *eparser, int mode)
{
	(void)env;
	(void)eparser;
	(void)mode;
	return (0);
}
