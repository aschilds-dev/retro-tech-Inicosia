/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 18:53:59 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/22 16:36:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pop_events.h"
#include "events.h"
#include "free.h"

int		execute_event2(int *res, t_event *event, t_env *env)
{
	if (event->type == INT)
	{
		if ((*res = int_event(event)) == -1)
			return (-1);
	}
	else if (event->type == UINT32)
	{
		if ((*res = uint32_event(event)) == -1)
			return (-1);
	}
	else if (event->type == FUNC)
	{
		if ((*res = func_event(event, env)) == -1)
			return (-1);
	}
	if (event->update_func)
	{
		if (event->update_func(event, env))
			return (-1);
	}
	return (*res);
}

int		execute_event(t_event *event, t_env *env)
{
	int	res;
	int	check;

	res = 1;
	check = 0;
	if (event->exec_conditions
		&& !check_exec_conditions(event, event->exec_conditions,
		event->nb_exec_conditions, env))
		return (1);
	if (event->check_func)
	{
		check = event->check_func(event, env);
		if (check == -1)
			return (-1);
		else if (check)
			return (1);
	}
	if (event->type == DOUBLE)
	{
		if ((res = double_event(event)) == -1)
			return (-1);
	}
	return (execute_event2(&res, event, env));
}

void	set_next_event(t_events_executer *executer)
{
	executer->prec = executer->tmp;
	executer->tmp = executer->tmp->next;
	executer->prec_values = executer->tmp_values;
	executer->tmp_values = executer->tmp_values->next;
}

int		pop_event(t_events_executer *executer, t_env *env)
{
	int		res;
	t_event	*event;

	event = (t_event*)executer->tmp->content;
	res = execute_event(event, env);
	if (res == 1)
	{
		if (event->max_uses > 0 && event->uses >= event->max_uses)
			free_event(event);
		ft_lstpopfront(&executer->tmp);
		if (executer->prec)
			executer->prec->next = executer->tmp;
		else
			env->events = executer->tmp;
		ft_lstpopfront(&executer->tmp_values);
		if (executer->prec_values)
			executer->prec_values->next = executer->tmp_values;
		else
			env->queued_values = executer->tmp_values;
	}
	else if (res == 0)
		set_next_event(executer);
	return (res == -1 ? -1 : 0);
}

/*
**	Executes every event in the list
**	and delete a node only when the event is done
*/

int		pop_events(t_env *env)
{
	t_events_executer	executer;

	executer.tmp = env->events;
	executer.tmp_values = env->queued_values;
	executer.prec_values = NULL;
	executer.prec = NULL;
	while (executer.tmp)
	{
		if (pop_event(&executer, env))
			return (-1);
	}
	return (0);
}
