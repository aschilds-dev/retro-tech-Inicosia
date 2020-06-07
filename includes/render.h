/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 14:41:44 by lnicosia          #+#    #+#             */
/*   Updated: 2020/05/01 14:04:38 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "env.h"

typedef struct		s_vline
{
	int				start;
	int				end;
	int				x;
	int				draw_wall;
	unsigned int	color;
}					t_vline;

typedef struct		s_render
{
	t_camera		*camera;
	t_sector		*sector;
	t_render_vertex	*v1;
	t_v2			texel;
	t_v2			texture_scale;
	double			alpha;
	double			clipped_alpha;
	double			z;
	double			max_floor;
	double			current_floor;
	double			no_slope_current_floor;
	double			floor_start;
	double			floor_horizon;
	double			max_ceiling;
	double			current_ceiling;
	double			no_slope_current_ceiling;
	double			ceiling_start;
	double			ceiling_horizon;
	double			line_height;
	double			ceiling_height;
	double			floor_height;
	double			neighbor_max_ceiling;
	double			neighbor_current_ceiling;
	double			neighbor_max_floor;
	double			neighbor_current_floor;
	double			divider;
	double			z_near_z;
	double			texel_x_near_z;
	double			texel_y_near_z;
	double			camera_x_z;
	double			camera_y_z;
	double			texel_x_camera_range;
	double			texel_y_camera_range;
	double			zrange;
	double			falpha;
	double			calpha;
	double			neighbor_falpha;
	double			neighbor_calpha;
	double			wall_xstart;
	double			wall_xend;
	double			floor_xstart;
	double			floor_xend;
	double			ceiling_xstart;
	double			ceiling_xend;
	double			nfloor_xstart;
	double			nfloor_xend;
	double			nceiling_xstart;
	double			nceiling_xend;
	double			neighbor_ceiling_ystart;
	double			neighbor_ceiling_yend;
	double			neighbor_floor_ystart;
	double			neighbor_floor_yend;
	double			sprite_x;
	int				neighbor;
	int				nv1;
	int				nv2;
	int				selected;
	int				xmin;
	int				xmax;
	int				xstart;
	int				xend;
	int				ystart;
	int				yend;
	int				x;
	int				y;
	int				texture;
	int				map_lvl;
	int				i;
	int				thread;
	int				texture_w;
	int				texture_h;
	int				threadmin;
	int				threadmax;
	int				*ymin;
	int				*ymax;
}					t_render;

typedef struct		s_drawer
{
	t_vline			vline;
	double			x;
	double			y;
	double			sprite_x;
	double			sprite_y;
	double			text_x;
	double			text_y;
	double			alpha;
	double			yalpha;
	double			salpha;
	double			z;
	double			divider;
	double			pos;
	t_sprite		*sprite;
	t_sector		*sector;
	Uint32			*texture_pixels;
	int				i;
	int				start;
	int				end;
	int				coord;
	int				map_lvl;
	int				sprite_w;
	int				texture_w;
	int				texture_h;
}					t_drawer;

typedef struct		s_sprite_drawer
{
	double			xalpha;
	double			yalpha;
	void			*param;
	t_explosion		*explosion;
	t_projectile	*projectile;
	t_enemy			*enemy;
	t_object		*object;
	t_texture		*texture;
	t_sprite		*sprite;
	t_sector		*sector;
	int				x;
	int				y;
	int				xend;
	int				yend;
	int				textx;
	int				texty;
}					t_sprite_drawer;

typedef struct		s_render_projectile
{
	t_camera		*camera;
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	int				xstart;
	int				ystart;
	int				xend;
	int				yend;
	int				index;
	int				brightness;
	Uint32			light_color;
	int				intensity;
	double			xrange;
	double			yrange;
	t_point			screen_pos;
}					t_render_projectile;

typedef struct		s_render_explosion
{
	t_camera		*camera;
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	int				xstart;
	int				ystart;
	int				xend;
	int				yend;
	int				index;
	double			xrange;
	double			yrange;
	t_point			screen_pos;
}					t_render_explosion;

typedef struct		s_render_object
{
	t_camera		*camera;
	int				x1;
	int				x2;
	int				y1;
	int				y2;
	int				xstart;
	int				ystart;
	int				xend;
	int				yend;
	int				index;
	int				brightness;
	Uint32			light_color;
	int				intensity;
	double			xrange;
	double			yrange;
	t_point			screen_pos;
}					t_render_object;

typedef struct		s_skybox_data
{
	double		z;
	double		ceiling_start;
	double		ceiling_horizon;
	double		max_ceiling;
	double		max_floor;
	int			i;
	int			mode;
}					t_skybox_data;

typedef struct		s_render_thread
{
	t_render		render;
	t_sector		*sector;
	t_camera		*camera;
	t_env			*env;
	int				xstart;
	int				xend;
	int				ystart;
	int				yend;
	int				screen_sectors;
	int				id;
}					t_render_thread;

typedef struct		s_precompute_thread
{
	int			start;
	int			end;
	t_env		*env;
	t_camera	*camera;
}					t_precompute_thread;

typedef struct		s_object_thread
{
	t_env			*env;
	t_camera		*camera;
	t_object		*object;
	t_render_object	*orender;
	int				xstart;
	int				xend;
}					t_object_thread;

typedef struct		s_explosion_thread
{
	t_env				*env;
	t_camera			*camera;
	t_explosion			*explosion;
	t_render_explosion	*erender;
	int					xstart;
	int					xend;
}					t_explosion_thread;

typedef struct		s_projectile_thread
{
	t_env				*env;
	t_camera			*camera;
	t_projectile		*projectile;
	t_render_projectile	*prender;
	int					xstart;
	int					xend;
}					t_projectile_thread;

typedef struct		s_enemy_thread
{
	t_env			*env;
	t_camera		*camera;
	t_enemy			*enemy;
	t_render_object	*orender;
	int				xstart;
	int				xend;
}					t_enemy_thread;

void				precompute_sector(t_camera *camera, t_sector *sector,
t_env *env);
void				get_rendered_sectors_list(int screen_sectors,
t_camera *camera, t_env *env);
void				set_render(t_camera *camera, t_env *env, int i,
t_render *render);
void				get_intersections(int i, t_camera *camera,
t_sector *sector, t_env *env);
void				precompute_values(int i, t_camera *camera,
t_sector *sector, t_env *env);
void				precompute_visible_vertex(int i, t_camera *camera,
t_sector *sector, t_env *env);
void				precompute_visible_bullet_holes(int i, t_camera *camera,
t_sector *sector, t_env *env);
void				precompute_clipped_vertex(int i, t_camera *camera,
t_sector *sector, t_env *env);
void				precompute_clipped_bullet_holes(int i, t_camera *camera,
t_sector *sector, t_env *env);
void				compute_wall(int i, t_camera *camera,
t_sector *sector, t_env *env);
void				clip_wall(int i, t_camera *camera,
t_sector *sector, t_env *env);
void				select_line(t_vline vline, t_env *env);
int					select_portal(t_sector *sector, t_render *render,
t_env *env);
int					colorize_selected_portal(t_sector *sector,
t_render *render, t_env *env);
int					threaded_wall_loop(t_sector *sector, t_render *render,
t_env *env);
void				render_current_wall_vline(t_sector *sector,
t_render *render, t_env *env);
void				compute_vline_data(t_sector *sector,
t_render *render, t_env *env);
void				draw_bottom_and_upper_walls(t_sector *sector,
t_render *render, t_env *env);
void				precompute_texels(t_render *render);
void				draw_floor_and_ceiling(t_sector *sector,
t_render *render, t_env *env);
int					wall_loop(void *param);
int					render_sector(t_render render, t_env *env);
void				draw_ceiling(t_sector *sector, t_render *render,
t_env *env);
void				draw_vline_ceiling(t_sector *sector, t_vline vline,
t_render *render, t_env *env);
void				draw_vline_ceiling_color(t_sector *sector, t_vline vline,
t_render *render, t_env *env);
void				draw_vline_ceiling_brightness(t_sector *sector,
t_vline vline, t_render *render, t_env *env);
void				draw_vline_ceiling_both(t_sector *sector, t_vline vline,
t_render *render, t_env *env);
void				get_ceiling_z(t_render *render, t_drawer *drawer,
t_env *env);
void				get_ceiling_texels(t_drawer *drawer, t_render *render,
t_env *env);
void				click_on_ceiling(t_drawer *drawer, t_render *render,
t_env *env);
void				get_floor_texels(t_drawer *drawer, t_render *render,
t_env *env);
void				click_on_floor(t_drawer *drawer, t_render *render,
t_env *env);
void				get_floor_z(t_render *render, t_drawer *drawer,
t_env *env);
void				get_texels(t_render *render, t_drawer *drawer);
void				draw_vline_wall(t_sector *sector, t_vline vline,
t_render *render, t_env *env);
void				draw_vline_wall_color(t_sector *sector, t_vline vline,
t_render *render, t_env *env);
void				draw_vline_wall_brightness(t_sector *sector, t_vline vline,
t_render *render, t_env *env);
void				draw_vline_wall_both(t_sector *sector, t_vline vline,
t_render *render, t_env *env);
void				draw_vline_floor(t_sector *sector, t_vline vline,
t_render *render, t_env *env);
void				draw_vline_floor_color(t_sector *sector, t_vline vline,
t_render *render, t_env *env);
void				draw_vline_floor_brightness(t_sector *sector, t_vline vline,
t_render *render, t_env *env);
void				draw_vline_floor_both(t_sector *sector, t_vline vline,
t_render *render, t_env *env);
void				draw_floor(t_sector *sector, t_render *render, t_env *env);
void				draw_wall(t_sector *sector, t_render *render, t_env *env);
void				draw_wall_no_light(t_sector *sector, t_render *render,
t_env *env);
int					draw_wall_sprites(t_sector *sector, t_render *render,
t_env *env);
void				draw_wall_bullet_holes(t_sector *sector, t_render *render,
t_env *env);
void				draw_floor_sprites(t_sector *sector, t_render *render,
t_env *env);
void				draw_floor_sprites_no_light(t_sector *sector,
t_render *render, t_env *env);
void				draw_floor_sprites_color(t_sector *sector,
t_render *render, t_env *env);
void				draw_floor_sprites_brightness(t_sector *sector,
t_render *render, t_env *env);
void				draw_floor_sprites_both(t_sector *sector,
t_render *render, t_env *env);
void				draw_ceiling_sprites(t_sector *sector, t_render *render,
t_env *env);
void				draw_ceiling_sprites_no_light(t_sector *sector,
t_render *render, t_env *env);
void				draw_ceiling_sprites_color(t_sector *sector,
t_render *render, t_env *env);
void				draw_ceiling_sprites_brightness(t_sector *sector,
t_render *render, t_env *env);
void				draw_ceiling_sprites_both(t_sector *sector,
t_render *render, t_env *env);
void				draw_floor_bullet_holes_both(t_sector *sector,
t_drawer *drawer, t_env *env);
void				draw_floor_bullet_holes_brightness(t_sector *sector,
t_drawer *drawer, t_env *env);
void				draw_floor_bullet_holes_color(t_sector *sector,
t_drawer *drawer, t_env *env);
void				draw_floor_bullet_holes_no_light(t_sector *sector,
t_drawer *drawer, t_env *env);
void				draw_ceiling_bullet_holes_both(t_sector *sector,
t_drawer *drawer, t_env *env);
void				draw_ceiling_bullet_holes_brightness(t_sector *sector,
t_drawer *drawer, t_env *env);
void				draw_ceiling_bullet_holes_color(t_sector *sector,
t_drawer *drawer, t_env *env);
void				draw_ceiling_bullet_holes_no_light(t_sector *sector,
t_drawer *drawer, t_env *env);
void				draw_upper_wall(t_sector *sector, t_render *render,
t_env *env);
void				draw_bottom_wall(t_sector *sector, t_render *render,
t_env *env);
void				click_on_wall(t_drawer *drawer, t_render *render,
t_env *env);
void				new_wall_bullet_hole(t_drawer *drawer, t_render *render,
t_env *env);
int					get_wall_x(t_drawer *drawer, t_render *render,
t_env *env);
int					get_wall_y(t_drawer *drawer, t_render *render);
int					click_on_wall_sprite(t_drawer *drawer, int sprite,
t_render *render, t_env *env);
void				apply_wall_sprite_filters(t_drawer *drawer, int sprite,
t_render *render, t_env *env);
void				init_drawer(t_drawer *drawer, int sprite,
t_render *render, t_env *env);
void				draw_skybox(t_render *render, int mode, t_env *env);
void				precompute_skybox(t_env *env);
void				precompute_skybox_values(int i, t_env *env);
int					project_skybox(int i, t_env *env);
t_v2				set_v2(int i);
int					get_vertex_nb_in_sector(int vertex, t_sector *sector);
void				precompute_neighbors(int i, t_camera *camera,
t_sector *sector, t_env *env);
void				draw_skybox_ceiling(t_vline vline, t_skybox_data wall_data,
		t_render *render, t_env *env);
void				draw_skybox_wall(t_vline vline, t_skybox_data wall_data,
		t_render *render, t_env *env);
void				draw_skybox_floor(t_vline vline, t_skybox_data wall_data,
		t_render *render, t_env *env);
void				draw_vline_color(t_vline vline, t_env *env);
int					get_screen_sectors(t_camera *camera, t_env *env);
void				restrict_floor(t_render_vertex v1, t_render *render,
		t_sector *sector, t_env *env);
void				restrict_ceiling(t_render_vertex v1, t_render *render,
		t_sector *sector, t_env *env);
void				reset_x_restrictions(t_sector *sector, t_env *env);
void				reset_screen_limits(t_render *render, t_env *env);
void				save_limits(int *ymin, int *ymax, t_render *render,
t_env *env);
void				get_vline_data(t_render_vertex v1, t_sector *sector,
		t_render *render, t_env *env);
int					get_current_wall_map(int texture, double z,
t_render *render, t_env *env);
int					get_current_floor_map(int texture, double z,
t_render *render, t_env *env);
int					get_current_ceiling_map(int texture, double z,
t_render *render, t_env *env);
int					portal_loop(void *param);
int					select_portal_loop(void *param);
void				get_sprite_x(t_render_object *orender,
t_sprite_drawer *drawer);
void				draw_vline_enemy(t_render_object *orender,
t_sprite_drawer *drawer, t_env *env);
int					get_enemy_direction(t_enemy *enemy);
void				put_enemy_pixel(t_render_object *orender,
t_sprite_drawer *drawer, t_env *env);
int					draw_explosion(t_camera *camera, t_explosion *explosion,
t_env *env, int sprite_index);
void				get_sprite_y(t_render_object *orender,
t_sprite_drawer *drawer);
void				draw_vline_object(t_render_object *orender,
t_sprite_drawer *drawer, t_env *env);
int					get_object_direction(t_object *object);
void				put_object_pixel(t_render_object *orender,
t_sprite_drawer *drawer, t_env *env);
void				put_player_pixel(t_render_object *orender,
t_sprite_drawer *drawer, t_env *env);
int					draw_explosion(t_camera *camera, t_explosion *explosion,
t_env *env, int sprite_index);
int					threaded_object_loop(t_object *object,
t_render_object *orender, t_env *env);
void				apply_object_filter(t_sprite_drawer *drawer, t_env *env);
void				init_object_render(t_render_object *orender,
t_object *object, t_v2 size, t_env *env);
void				init_projectile_render(t_render_projectile *prender,
t_projectile *projectile, t_v2 size, t_env *env);
void				draw_vline_projectile_both(t_render_projectile *prender,
t_sprite_drawer *drawer, t_env *env);
void				draw_vline_projectile_brightness(
t_render_projectile *prender, t_sprite_drawer *drawer, t_env *env);
void				draw_vline_projectile_color(t_render_projectile *prender,
t_sprite_drawer *drawer, t_env *env);
void				draw_vline_projectile_no_light(t_render_projectile *prender,
t_sprite_drawer *drawer, t_env *env);
void				get_projectile_x(t_render_projectile *prender,
t_sprite_drawer *drawer);

/*
**	Sprite part
*/

int					get_enemy_relative_pos(void *param);
void				get_translated_enemy_pos(t_camera *camera, t_enemy *enemy);
void				get_rotated_enemy_pos(t_camera *camera, t_enemy *enemy);
void				project_enemy(t_render_object *erender, t_enemy *enemy,
t_env *env);

int					get_projectile_relative_pos(t_camera *camera, t_env *env);
void				get_translated_projectile_pos(t_camera *camera,
t_projectile *projectile);
void				get_rotated_projectile_pos(t_camera *camera,
t_projectile *projectile);
void				project_projectile(t_render_projectile *prender,
t_projectile *projectile, t_env *env);

int					get_explosion_relative_pos(t_camera *camera,
t_env *env);
void				get_translated_explosion_pos(t_camera *camera,
t_explosion *explosion);
void				get_rotated_explosion_pos(t_camera *camera,
t_explosion *explosion);
void				project_explosion(t_render_explosion *erender,
t_explosion *explosion, t_env *env);

void				get_translated_object_pos(t_camera *camera,
t_object *object);
void				get_rotated_object_pos(t_camera *camera, t_object *object);
int					get_object_relative_pos(void *param);
void				project_object(t_render_object *orender, t_object *object,
t_env *env);
void				get_neighbor_ceil_floor(t_render *render, t_env *env,
int x);
int					raycasting(void *param);
int					skybox_thread(void *param);
void				threaded_skybox(t_env *env, t_render render);
int					draw_object(t_camera *camera, t_object *object, t_env *env,
int death_sprite);
void				get_rendered_objects(t_env *env);
void				get_rendered_enemies(t_env *env);

#endif
