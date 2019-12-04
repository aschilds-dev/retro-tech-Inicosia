/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sector.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 10:08:19 by lnicosia          #+#    #+#             */
/*   Updated: 2019/12/04 11:10:12 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h" 

void		free_sector(t_sector *sector)
{
	int	i;
	int	j;

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
	if (sector->scale)
		ft_memdel((void**)&sector->scale);
	if (sector->xmin)
		ft_memdel((void**)&sector->xmin);
	if (sector->xmax)
		ft_memdel((void**)&sector->xmax);
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
	if (sector->levels)
		ft_memdel((void**)&sector->levels);
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
		while (j <= sector->nb_vertices)
		{
			if (sector->wall_sprites[j].sprite)
				ft_memdel((void**)&sector->wall_sprites[j].sprite);
			if (sector->wall_sprites[j].pos)
				ft_memdel((void**)&sector->wall_sprites[j].pos);
			if (sector->wall_sprites[j].scale)
				ft_memdel((void**)&sector->wall_sprites[j].scale);
			if (sector->wall_sprites[j].shoot_events)
			{
				i = 0;
				while (i < sector->wall_sprites[j].nb_sprites)
				{
					if (sector->wall_sprites[j].shoot_events[i])
						ft_memdel((void**)&sector->wall_sprites[j].shoot_events[i]);
					i++;
				}
			}
			if (sector->wall_sprites[j].nb_shoot_events)
				ft_memdel((void**)&sector->wall_sprites[j].nb_shoot_events);
			if (sector->wall_sprites[j].nb_press_events)
				ft_memdel((void**)&sector->wall_sprites[j].nb_press_events);
			j++;
		}
		ft_memdel((void**)&sector->wall_sprites);
	}
	if (sector->ceiling_sprites_scale)
		ft_memdel((void**)&sector->ceiling_sprites_scale);
	if (sector->floor_sprites_scale)
		ft_memdel((void**)&sector->floor_sprites_scale);
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
	//if (sector->nb_sprites)
		//ft_memdel((void**)&sector->nb_sprites);
	free_events(sector->walk_on_me_event,
			sector->nb_walk_events);
}
