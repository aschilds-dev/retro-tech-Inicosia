/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ceiling_sprite.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 15:15:12 by sipatry           #+#    #+#             */
/*   Updated: 2020/04/28 15:35:12 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	update_ceiling_sprite_arrays3(t_env *env, t_sector *sector,
t_wall_sprites *ceiling)
{
	if (!(ceiling->press_events =
		(t_event**)ft_realloc(ceiling->press_events,
		sizeof(t_event *) * ceiling->nb_sprites, sizeof(t_event*)
		* (ceiling->nb_sprites + 1))))
		return (ft_perror("Could not realloc ceiling sprite press events"));
	if (!(ceiling->nb_shoot_events =
		(size_t*)ft_realloc(ceiling->nb_shoot_events,
		sizeof(size_t) * ceiling->nb_sprites, sizeof(size_t)
		* (ceiling->nb_sprites + 1))))
		return (ft_perror("Could not realloc ceiling sprite nb shoot events"));
	if (!(ceiling->shoot_events = (t_event**)ft_realloc(ceiling->shoot_events,
		sizeof(t_event *) * ceiling->nb_sprites, sizeof(t_event*)
		* (ceiling->nb_sprites + 1))))
		return (ft_perror("Could not realloc ceiling sprite shoot events"));
	if (!(sector->ceiling_sprites_scale =
		(t_v2*)ft_realloc(sector->ceiling_sprites_scale,
		sizeof(t_v2) * ceiling->nb_sprites, sizeof(t_v2)
		* (ceiling->nb_sprites + 1))))
		return (ft_perror("Could not realloc ceiling sprite map scale"));
	precompute_ceiling_sprite_scales(env->selected_ceiling,
		ceiling->nb_sprites, env);
	ceiling->nb_sprites++;
	return (0);
}

int	update_ceiling_sprite_arrays2(t_env *env, t_sector *sector,
t_wall_sprites *ceiling)
{
	int		i;

	i = 0;
	while (i < sector->nb_vertices)
	{
		ceiling->pos[ceiling->nb_sprites].x +=
		(env->vertices[sector->vertices[i]].x);
		ceiling->pos[ceiling->nb_sprites].y +=
		(env->vertices[sector->vertices[i]].y);
		i++;
	}
	ceiling->pos[ceiling->nb_sprites].x /= sector->nb_vertices;
	ceiling->pos[ceiling->nb_sprites].y /= sector->nb_vertices;
	if (!(ceiling->scale = (t_v2*)ft_realloc(ceiling->scale,
	sizeof(t_v2) * ceiling->nb_sprites, sizeof(t_v2)
	* (ceiling->nb_sprites + 1))))
		return (ft_perror("Could not realloc ceiling sprite scale"));
	ceiling->scale[ceiling->nb_sprites] = new_v2(2, 2);
	if (!(ceiling->nb_press_events =
		(size_t*)ft_realloc(ceiling->nb_press_events,
		sizeof(size_t) * ceiling->nb_sprites, sizeof(size_t)
		* (ceiling->nb_sprites + 1))))
		return (ft_perror("Could not realloc ceiling sprite nb press events"));
	return (update_ceiling_sprite_arrays3(env, sector, ceiling));
}

int	update_ceiling_sprite_arrays(t_env *env)
{
	t_wall_sprites	*ceiling;
	t_sector		*sector;

	sector = &env->sectors[env->selected_ceiling];
	ceiling = &env->sectors[env->selected_ceiling].ceiling_sprites;
	if (!(ceiling->sprite = (int*)ft_realloc(ceiling->sprite,
	sizeof(int) * ceiling->nb_sprites, sizeof(int)
	* (ceiling->nb_sprites + 1))))
		return (ft_perror("Could not realloc ceiling sprite index"));
	ceiling->sprite[ceiling->nb_sprites] =
	env->objects_main_sprites[env->editor.current_sprite];
	if (!(ceiling->pos = (t_v2*)ft_realloc(ceiling->pos,
	sizeof(t_v2) * ceiling->nb_sprites, sizeof(t_v2)
	* (ceiling->nb_sprites + 1))))
		return (ft_perror("Could not realloc ceiling sprite pos"));
	ceiling->pos[ceiling->nb_sprites] = new_v2(0, 0);
	return (update_ceiling_sprite_arrays2(env, sector, ceiling));
}
