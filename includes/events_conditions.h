/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_conditions.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:43:03 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/15 18:21:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_CONDITIONS_H
# define EVENTS_CONDITIONS_H
# include "events.h"
# define MAX_CONDITION_TYPES 9

typedef enum		e_condition_type
{
	EQUALS,
	DIFFERENT,
	LESS,
	GREATER,
	LESS_OR_EQUALS,
	GREATER_OR_EQUALS,
	EVENT_ENDED,
	EVENT_ENDED_START,
	FUNCTION
}					t_condition_type;

int		equals_condition(t_condition *condition);
int		different_condition(t_condition *condition);
int		less_condition(t_condition *condition);
int		greater_condition(t_condition *condition);
int		less_or_equals_condition(t_condition *condition);
int		greater_or_equals_condition(t_condition *condition);
int		event_ended_condition(t_condition *condition, t_event *event);
int		event_ended_start_condition(t_condition *condition, t_event *event);
int		print_event_link_condition(t_condition *condition, t_event_panel *panel,
t_env *env);
int		draw_condition(t_env *env, t_condition *condition);
#endif
