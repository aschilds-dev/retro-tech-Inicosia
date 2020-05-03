/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_sprite_modifier.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:01:15 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/01 14:10:22 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_SPRITE_MODIFIER_H
# define WALL_SPRITE_MODIFIER_H

enum				e_wall_sprite_modifier_type
{
	SPRITE,
	POSX,
	POSY,
	SCALEX,
	SCALEY
};

typedef struct		s_wall_sprite_modifier
{
	int				type;
	double			value;
	int				sector;
	int				wall;
	int				sprite;
}					t_wall_sprite_modifier;

typedef struct		s_floor_sprite_modifier
{
	int				type;
	int				value;
	int				sector;
	int				sprite;
}					t_floor_sprite_modifier;

#endif
