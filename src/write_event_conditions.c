/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_event_conditions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 18:25:41 by lnicosia          #+#    #+#             */
/*   Updated: 2020/01/20 18:57:12 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_parser.h"

void	write_condition(int fd, void (*writers[])(int, t_condition),
t_condition condition)
{
	ft_dprintf(fd, "{%d %f %d", condition.type, condition.value,
	condition.target_index);
	writers[condition.target_index](fd, condition);
	ft_dprintf(fd, "}");
}

void	write_event_conditions(int fd, t_event event)
{
	size_t	i;
	void	(*writers[MAX_TARGET_TYPES + 1])(int, t_condition);

	init_event_conditions_writers(writers);
	i = 0;
	ft_dprintf(fd, "[");
	while (i < event.nb_launch_conditions)
	{
		write_condition(fd, writers, event.launch_conditions[i]);
		i++;
	}
	ft_dprintf(fd, "]");
	i = 0;
	ft_dprintf(fd, "[");
	while (i < event.nb_exec_conditions)
	{
		write_condition(fd, writers, event.exec_conditions[i]);
		i++;
	}
	ft_dprintf(fd, "]");
}
