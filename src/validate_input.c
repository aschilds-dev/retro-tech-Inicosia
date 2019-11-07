/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:52:19 by lnicosia          #+#    #+#             */
/*   Updated: 2019/11/07 16:08:35 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	validate_input(t_input_box *box, t_env *env)
{
	(void)env;
	ft_printf("validating\n");
	if (box->type == INT)
	{
		if (!box->int_target)
		{
			ft_printf("Error: no int target for input box\n");
			return (-1);
		}
		*(box->int_target) = ft_atoi(box->str);
	}
	else if (box->type == DOUBLE)
	{
		if (!box->double_target)
		{
			ft_printf("Error: no double target for input box\n");
			return (-1);
		}
		*(box->double_target) = ft_atof(box->str);
	}
	else if (box->type == STRING)
	{
		if (!box->str_target)
		{
			ft_printf("Error: no string target for input box\n");
			return (-1);
		}
		box->str_target = box->str;
	}
	if (box->str_target)
		ft_strdel(&box->str_target);
	box->state = 0;
	precompute_slopes(env);
	return (0);
}
