/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:08:19 by lnicosia          #+#    #+#             */
/*   Updated: 2020/04/30 11:01:57 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void		free_sector5(t_sector *sector)
{
	int	j;

	if (sector->wall_bullet_holes)
	{
		j = 0;
		while (j <= sector->nb_vertices)
		{
			ft_lstdelfront(&sector->wall_bullet_holes[j]);
			j++;
		}
		ft_memdel((void**)&sector->wall_bullet_holes);
	}
	ft_lstdelfront(&sector->ceiling_bullet_holes);
	ft_lstdelfront(&sector->floor_bullet_holes);
}

void		free_sector4(t_sector *sector)
{
	int	j;

	if (sector->walls_map_lvl)
	{
		j = 0;
		while (j <= sector->nb_vertices)
		{
			if (sector->walls_map_lvl[j])
				ft_memdel((void**)&sector->walls_map_lvl[j]);
			j++;
		}
		ft_memdel((void**)&sector->walls_map_lvl);
	}
	if (sector->wall_sprites)
	{
		j = 0;
		while (j < sector->nb_vertices)
		{
			free_wall_sprites(&sector->wall_sprites[j]);
			j++;
		}
		ft_memdel((void**)&sector->wall_sprites);
	}
	free_sector5(sector);
}

void		free_sector3(t_sector *sector)
{
	if (sector->ceiling_sprites.sprite)
		ft_memdel((void**)&sector->ceiling_sprites.sprite);
	if (sector->ceiling_sprites.scale)
		ft_memdel((void**)&sector->ceiling_sprites.scale);
	if (sector->ceiling_sprites.pos)
		ft_memdel((void**)&sector->ceiling_sprites.pos);
	if (sector->floor_sprites.sprite)
		ft_memdel((void**)&sector->floor_sprites.sprite);
	if (sector->floor_sprites.scale)
		ft_memdel((void**)&sector->floor_sprites.scale);
	if (sector->floor_sprites.pos)
		ft_memdel((void**)&sector->floor_sprites.pos);
	free_wall_sprites(&sector->floor_sprites);
	free_wall_sprites(&sector->ceiling_sprites);
	free_events(&sector->stand_events, &sector->nb_stand_events);
	free_events(&sector->walk_in_events, &sector->nb_walk_in_events);
	free_events(&sector->walk_out_events, &sector->nb_walk_out_events);
	free_sector4(sector);
}

void		free_sector2(t_sector *sector)
{
	if (sector->scale)
		ft_memdel((void**)&sector->scale);
	if (sector->portals)
		ft_memdel((void**)&sector->portals);
	if (sector->floor_map_lvl)
		ft_memdel((void**)&sector->floor_map_lvl);
	if (sector->ceiling_map_lvl)
		ft_memdel((void**)&sector->ceiling_map_lvl);
	if (sector->floor_align)
		ft_memdel((void**)&sector->floor_align);
	if (sector->floor_scale)
		ft_memdel((void**)&sector->floor_scale);
	if (sector->ceiling_align)
		ft_memdel((void**)&sector->ceiling_align);
	if (sector->ceiling_scale)
		ft_memdel((void**)&sector->ceiling_scale);
	if (sector->selected)
		ft_memdel((void**)&sector->selected);
	if (sector->ceiling_sprites_scale)
		ft_memdel((void**)&sector->ceiling_sprites_scale);
	if (sector->floor_sprites_scale)
		ft_memdel((void**)&sector->floor_sprites_scale);
	free_sector3(sector);
}

void		free_sector(t_sector *sector)
{
	if (sector->vertices)
		ft_memdel((void**)&sector->vertices);
	if (sector->neighbors)
		ft_memdel((void**)&sector->neighbors);
	if (sector->textures)
		ft_memdel((void**)&sector->textures);
	if (sector->ceilings)
		ft_memdel((void**)&sector->ceilings);
	if (sector->floors)
		ft_memdel((void**)&sector->floors);
	if (sector->clipped_ceilings1)
		ft_memdel((void**)&sector->clipped_ceilings1);
	if (sector->clipped_floors1)
		ft_memdel((void**)&sector->clipped_floors1);
	if (sector->clipped_ceilings2)
		ft_memdel((void**)&sector->clipped_ceilings2);
	if (sector->clipped_floors2)
		ft_memdel((void**)&sector->clipped_floors2);
	if (sector->wall_width)
		ft_memdel((void**)&sector->wall_width);
	if (sector->align)
		ft_memdel((void**)&sector->align);
	free_sector2(sector);
}
