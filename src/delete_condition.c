/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_condition.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 09:41:54 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/18 16:00:23 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	delete_selected_launch_condition(void *param)
{
	t_env	*env;

	env = (t_env*)param;
	env->editor.event_panel.event.launch_conditions =
	(t_condition*)ft_delindex(env->editor.event_panel.event.launch_conditions,
	sizeof(t_condition) * env->editor.event_panel.event.nb_launch_conditions,
	sizeof(t_condition),
	sizeof(t_condition) * env->editor.selected_launch_condition);
	env->editor.event_panel.event.nb_launch_conditions--;
	if (env->editor.selected_launch_condition ==
		env->editor.event_panel.event.nb_launch_conditions
		&& env->editor.selected_launch_condition > 0)
		env->editor.selected_launch_condition--;
}

void	delete_selected_exec_condition(void *param)
{
	t_env	*env;

	env = (t_env*)param;
	env->editor.event_panel.event.exec_conditions =
	(t_condition*)ft_delindex(env->editor.event_panel.event.exec_conditions,
	sizeof(t_condition) * env->editor.event_panel.event.nb_exec_conditions,
	sizeof(t_condition),
	sizeof(t_condition) * env->editor.selected_exec_condition);
	env->editor.event_panel.event.nb_exec_conditions--;
	if (env->editor.selected_exec_condition ==
		env->editor.event_panel.event.nb_exec_conditions
		&& env->editor.selected_exec_condition > 0)
		env->editor.selected_exec_condition--;
}

int		delete_condition(void *param)
{
	t_env	*env;

	env = (t_env*)param;
	if (update_confirmation_box(&env->confirmation_box,
		"Delete this condition?", YESNO, env))
		return (-1);
	if (env->editor.event_panel.launch_conditions_tab.state == DOWN)
		env->confirmation_box.yes_action = &delete_selected_launch_condition;
	else if (env->editor.event_panel.exec_conditions_tab.state == DOWN)
		env->confirmation_box.yes_action = &delete_selected_exec_condition;
	env->confirmation_box.yes_target = env;
	return (0);
}
