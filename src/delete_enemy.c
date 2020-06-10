/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_enemy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 10:34:27 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/25 14:48:21 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	update_enemies(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_enemies)
	{
		env->enemies[i].num = i;
		i++;
	}
}

int		delete_enemy(void *param)
{
	t_env	*env;
	int		enemy;

	env = (t_env*)param;
	enemy = env->selected_enemy;
	free_events(&env->enemies[enemy].collision_events,
	&env->enemies[enemy].nb_collision_events);
	free_events(&env->enemies[enemy].death_events,
	&env->enemies[enemy].nb_death_events);
	env->enemies = (t_enemy*)ft_delindex(env->enemies,
			sizeof(t_enemy) * env->nb_enemies,
			sizeof(t_enemy),
			sizeof(t_enemy) * enemy);
	env->nb_enemies--;
	if (env->nb_enemies > 0 && !env->enemies)
		return (-1);
	env->selected_enemy = -1;
	ft_memdel((void**)&env->rendered_enemies);
	if (env->nb_enemies > 0 && !(env->rendered_enemies =
		(int*)ft_memalloc(sizeof(int) * env->nb_enemies)))
		return (custom_error("Could not realloc rendered enemies\n"));
	update_enemies(env);
	return (0);
}
