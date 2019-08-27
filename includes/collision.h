/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/03 12:30:04 by gaerhard          #+#    #+#             */
/*   Updated: 2019/08/27 12:20:13 by gaerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLLISION_H
# define COLLISION_H
# define X1 env->vertices[env->sectors[env->player.sector].vertices[i]].x
# define X2 env->vertices[env->sectors[env->player.sector].vertices[i + 1]].x
# define Y1 env->vertices[env->sectors[env->player.sector].vertices[i]].y
# define Y2 env->vertices[env->sectors[env->player.sector].vertices[i + 1]].y
# define SECTOR_X1 env->vertices[env->sectors[sector].vertices[i]].x
# define SECTOR_X2 env->vertices[env->sectors[sector].vertices[i + 1]].x
# define SECTOR_Y1 env->vertices[env->sectors[sector].vertices[i]].y
# define SECTOR_Y2 env->vertices[env->sectors[sector].vertices[i + 1]].y
# define FUTURE_V0X env->vertices[env->sectors[sector_dest].vertices[0]].x
# define FUTURE_V0Y env->vertices[env->sectors[sector_dest].vertices[0]].y
# define FUTURE_X motion.future_x
# define FUTURE_Y motion.future_y
# define FUTURE_Z motion.future_z
# define VERTICES_AMOUNT env->sectors[env->player.sector].nb_vertices
# define NEIGHBOR env->sectors[env->player.sector].neighbors[i]
# define PLAYER_XPOS env->player.pos.x
# define PLAYER_YPOS env->player.pos.y
# define PLAYER_ZPOS env->player.pos.z
# define X1R env->vertices[env->sectors[wall.sector_dest].vertices[i]].x
# define X2R env->vertices[env->sectors[wall.sector_dest].vertices[i + 1]].x
# define Y1R env->vertices[env->sectors[wall.sector_dest].vertices[i]].y
# define Y2R env->vertices[env->sectors[wall.sector_dest].vertices[i + 1]].y
# define RNEIGHBOR env->sectors[wall.sector_dest].neighbors[i]
# include "env.h"

typedef struct  s_movement
{
    double      old_z;
    double      future_x;
    double      future_y;
    double      future_z;
    int         wall_v1;
    int         wall_v2;
    int         old_sector;
}               t_movement;

typedef struct  s_wall
{
    double      x1;
    double      x2;
    double      y1;
    double      y2;
    short       sector_or;
    short       sector_dest;  
}               t_wall;

typedef struct  s_data
{
    t_vertex    v0;
    t_sector    sector;
}               t_data;


int					check_collision(t_env *env, double x_move, double y_move);
int     			check_inside_sector(t_env *env, t_movement motion);
int					is_in_sector(t_env *env, short sector, double x, double y);
void                objects_collision(t_env *env);

#endif
