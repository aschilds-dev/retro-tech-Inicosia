/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 16:59:51 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/21 21:06:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include <sys/wait.h>

int		free_launch_game(char *str, char *map_name, char **tmp)
{
	ft_strdel(&str);
	ft_strdel(&map_name);
	if (tmp)
	{
		ft_strdel(&tmp[0]);
		ft_strdel(&tmp[1]);
	}
	ft_memdel((void**)&tmp);
	return (-1);
}

void	save_current_player_pos(t_v3 *tmp_pos, double *tmp_angle, t_env *env)
{
	*tmp_pos = env->player.starting_pos;
	env->player.starting_pos = env->player.pos;
	*tmp_angle = env->player.init_data.camera.angle;
	env->player.init_data.camera.angle =
	env->player.camera.angle * CONVERT_DEGREES;
}

int		launch_game2(t_env *env, char *map_name, char *str, char **tmp)
{
	t_v3	tmp_pos;
	double	tmp_angle;

	save_current_player_pos(&tmp_pos, &tmp_angle, env);
	if (save_map(env))
		return (free_launch_game(str, map_name, tmp));
	env->pid = fork();
	if (env->pid == 0)
	{
		if (execv(str, tmp) == -1)
			return (free_launch_game(str, map_name, tmp));
	}
	else if ((env->pid = wait(NULL)) < 0)
		return (free_launch_game(str, map_name, tmp));
	env->player.starting_pos = tmp_pos;
	env->player.init_data.camera.angle = tmp_angle;
	ft_strdel(&env->save_file);
	if (!(env->save_file = ft_strdup(map_name)))
		return (free_launch_game(str, map_name, tmp));
	free_launch_game(str, map_name, tmp);
	return (0);
}

int		set_map(char **map_name, char **str, char ***tmp, t_env *env)
{
	if (!(*map_name = ft_strdup(env->save_file)))
		return (custom_error("Could not malloc map name\n"));
	if (!(*str = ft_strdup("./doom-nukem")))
		return (custom_error("Could not malloc \"./doom-nukem\" str\n"));
	if (!(*tmp = ft_strsplit("./doom-nukem tmp.map", ' ')))
		return (custom_error("Could not strsplit\n"));
	if (env->save_file)
		ft_strdel(&env->save_file);
	if (!(env->save_file = ft_strdup("tmp.map")))
		return (custom_error("Could not malloc new env map name\n"));
	return (0);
}

/*
**	Launch the game from the editor
*/

int		launch_game(void *target)
{
	t_env	*env;
	char	*str;
	char	**tmp;
	char	*map_name;

	return (0);
	env = (t_env*)target;
	tmp = NULL;
	str = NULL;
	map_name = NULL;
	if (env->editor.in_game)
	{
		if (going_in_2d_mode(env))
			return (-1);
	}
	if (env->editor.creating_event)
	{
		if (update_confirmation_box(&env->confirmation_box,
			"Please save your event before saving the map", ERROR, env))
			return (-1);
		return (0);
	}
	if (set_map(&map_name, &str, &tmp, env))
		return (free_launch_game(str, map_name, tmp));
	return (launch_game2(env, map_name, str, tmp));
}
