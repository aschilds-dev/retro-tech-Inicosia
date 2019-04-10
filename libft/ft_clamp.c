/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 15:13:26 by lnicosia          #+#    #+#             */
/*   Updated: 2018/11/12 15:15:33 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_clamp(int nb, int min, int max)
{
	if (nb < min)
		nb = min;
	else if (nb > max)
		nb = max;
	return (nb);
}
