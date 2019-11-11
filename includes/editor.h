/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:21:53 by sipatry           #+#    #+#             */
/*   Updated: 2019/11/11 11:21:22 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "utils.h"

typedef struct	s_hud
{
	int			draw_hud;
	int			x;
	int			y;
	t_button	plr;
}				t_hud;


typedef struct	s_plr
{
	double		x;
	double		y;
	double		z;
	double		angle;
	int			sector;
}				t_plr;

typedef struct	s_editor
{
	t_v2		start_pos;
	int			selected_sector;
	int			selected_object;
	int			selected_player;
	int			selected_vertex;
	int			selected_wall;
	int			dragged_object;
	int			selected_wall_sprite;
	int			dragged_player;
	int			dragged_vertex;
	int			dragged_enemy;
	int			start_vertex;
	int			nb_vertex;
	int			new_player;
	int			tab;
	int			select;
	t_v2		center;
	double		scale;
	t_list		*vertices;
	t_hud		hud;
	t_plr		player;
	t_list		*current_vertices;
	int			reverted;
	int			in_game;
	int			game;
}				t_editor;

#endif
