/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:26:12 by lnicosia          #+#    #+#             */
/*   Updated: 2019/07/02 12:08:43 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
**void __attribute__((destructor)) end();
**
**void    end(void) //permet de mieux checker les leaks !
** {
**	ft_printf("destructor loop\n");
**	while(1);
**}
*/

int		main(int ac, char **av)
{	
	init_program(ac, av);
	return (0);
}
