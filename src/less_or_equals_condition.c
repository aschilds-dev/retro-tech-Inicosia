/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less_or_equals_condition.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 13:45:23 by lnicosia          #+#    #+#             */
/*   Updated: 2020/04/30 17:00:02 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events_conditions.h"

int		less_or_equals_condition(t_condition *condition)
{
	if (condition->target_type == INT
		&& *(int*)condition->target <= condition->value)
		return (0);
	else if (condition->target_type == DOUBLE
		&& *(double*)condition->target <= condition->value)
		return (0);
	else if (condition->target_type == UINT32
		&& *(Uint32*)condition->target <= condition->value)
		return (0);
	return (1);
}
