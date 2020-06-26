/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_new_sector2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 10:57:56 by lnicosia          #+#    #+#             */
/*   Updated: 2020/04/30 11:03:36 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		revert_sector(t_sector *sector, t_env *env)
{
	int			i;
	int			index;
	int			j;
	int			*tmp;

	i = 1;
	j = 1;
	if (!(tmp = (int *)ft_memalloc(sizeof(int) * (sector->nb_vertices + 1))))
		return (ft_perror("Could not malloc revert sector tmp"));
	tmp[0] = sector->vertices[0];
	while (i < sector->nb_vertices)
	{
		if (env->editor.reverted)
			index = sector->nb_vertices - j;
		else
			index = j;
		tmp[i] = sector->vertices[index];
		i++;
		j++;
	}
	tmp[sector->nb_vertices] = tmp[0];
	free(sector->vertices);
	sector->vertices = tmp;
	return (0);
}

int		fill_sector_first_vertex(t_sector *sector, t_env *env)
{
	sector->portals[0] = 1;
	sector->vertices[0] = sector->vertices[sector->nb_vertices];
	sector->neighbors[0] = sector->neighbors[sector->nb_vertices];
	sector->textures[0] = sector->textures[sector->nb_vertices];
	sector->wall_sprites[0] = sector->wall_sprites[sector->nb_vertices];
	sector->align[0] = sector->align[sector->nb_vertices];
	sector->scale[0] = sector->scale[sector->nb_vertices];
	sector->wall_sprites[0].nb_sprites = 0;
	(void)env;
	return (0);
}

int		fill_sector_last_vertex(t_sector *sector, t_env *env)
{
	sector->portals[sector->nb_vertices] = 1;
	sector->vertices[sector->nb_vertices] = sector->vertices[0];
	sector->neighbors[sector->nb_vertices] = sector->neighbors[0];
	sector->textures[sector->nb_vertices] = sector->textures[0];
	sector->wall_sprites[sector->nb_vertices] = sector->wall_sprites[0];
	sector->align[sector->nb_vertices] = sector->align[0];
	sector->scale[sector->nb_vertices] = sector->scale[0];
	sector->wall_sprites[sector->nb_vertices].nb_sprites = 0;
	(void)env;
	return (0);
}
