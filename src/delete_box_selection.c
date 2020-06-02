/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_box_selection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:52:18 by lnicosia          #+#    #+#             */
/*   Updated: 2020/04/29 15:54:03 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

static int	find_period(t_input_box *box)
{
	size_t	i;

	i = 0;
	while (box->str[i])
	{
		if (box->str[i] == '.')
			return (i);
		i++;
	}
	return (0);
}

int			set_double_stats(t_input_box *box)
{
	if (box->period)
	{
		if (box->add_period)
		{
			box->period_index = box->cursor;
			if (add_char(box, '.'))
				return (-1);
			box->cursor--;
			box->add_period = 0;
		}
		else
			box->period_index = find_period(box);
		box->int_count = box->period_index - box->minus;
		box->float_count = ft_strlen(box->str)
		- box->period_index - box->minus;
	}
	else
	{
		box->period_index = 0;
		box->int_count = ft_strlen(box->str) - box->minus;
		box->float_count = 0;
	}
	return (0);
}

int			delete_box_selection3(t_input_box *box, size_t start, char *res)
{
	ft_strdel(&box->str);
	box->str = res;
	box->cursor = start;
	if (box->type == DOUBLE)
		set_double_stats(box);
	if (box->minus && !ft_strchr(box->str, '-'))
		box->minus--;
	return (0);
}

int			delete_box_selection2(t_input_box *box, size_t start, size_t end)
{
	char	*res;
	char	*s1;
	char	*s2;

	s1 = ft_strsub(box->str, 0, start);
	if (start > 0 && !s1)
		return (-1);
	s2 = ft_strsub(box->str, end, ft_strlen(box->str) - end);
	if (ft_strlen(box->str) - end > 0 && !s2)
	{
		ft_strdel(&s1);
		return (-1);
	}
	if (!(res = ft_strnew(ft_strlen(box->str) - (end - start))))
	{
		ft_strdel(&s1);
		ft_strdel(&s2);
		return (-1);
	}
	res = ft_strcpy(res, s1);
	res = ft_strcat(res, s2);
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (delete_box_selection3(box, start, res));
}

int			delete_box_selection(t_input_box *box)
{
	size_t	start;
	size_t	end;

	if (box->select_start > box->select_end)
	{
		start = box->select_end;
		end = box->select_start;
	}
	else
	{
		start = box->select_start;
		end = box->select_end;
	}
	if (box->type == DOUBLE && box->period
		&& start <= box->period_index && end >= box->period_index)
	{
		if (end != ft_strlen(box->str) && start > box->minus)
			box->add_period = 1;
		else
			box->period = 0;
	}
	box->select_start = 0;
	box->select_end = 0;
	box->selecting = 0;
	return (delete_box_selection2(box, start, end));
}
