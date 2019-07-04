/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 17:44:04 by sipatry           #+#    #+#             */
/*   Updated: 2019/07/04 12:31:19 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double		ft_atof(const char *str)
{
	double	res;
	double	res1;
	double	res2;
	int		count;
	int		neg;

	neg = 1;
	if (*str == '-')
	{
		neg = -1;
		str++;
	}
	count = 0;
	res1 = ft_abs(ft_atoi(str));
	while (*str >= '0' && *str <= '9')
	{
		str++;
		count++;
	}
	if (!*str || *str != '.')
		return (res1);
	str++;
	count = 0;
	res2 = ft_abs(ft_atoi(str));
	while (*str >= '0' && *str <= '9')
	{
		str++;
		count++;
	}
	while (count > 0)
	{
		res2 /= 10;
		count--;
	}
	res = res1 + res2;
	return (neg * res);
}
