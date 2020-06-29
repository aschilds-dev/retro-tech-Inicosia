# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/06 15:56:21 by lnicosia          #+#    #+#              #
#    Updated: 2020/03/06 14:17:34 by gaerhard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = doom-nukem-project

GAME_NAME = doom-nukem

EDITOR_NAME = doom-editor

MAKEFILE = Makefile

LIB_DIR = lib
SRC_DIR = src
OBJ_GAME_DIR = obj_game
OBJ_EDITOR_DIR = obj_editor
OBJ_ALL_DIR = obj_all
FONTS_DIR = fonts
MAPS_DIR = maps
AUDIO_DIR = audio
INCLUDES_DIR = includes
IMAGES_DIR = images
TEXTURES_DIR = textures
SPRITES_DIR = sprites
SKYBOXES_DIR = skyboxes
HUD_DIR = HUD
UI_DIR = ui
GUN_DIR = gun
RAYGUN_DIR = raygun
SHOTGUN_DIR = shotgun
GAME_DIR = .
EDITOR_DIR = .
LIBFT_DIR = libft
SDL2_DIR = $(LIB_DIR)/SDL2-2.0.8
SDL2_TTF_DIR = $(LIB_DIR)/SDL2_ttf-2.0.15
FREETYPE_DIR = $(LIB_DIR)/freetype-2.9
MESA_DIR = $(LIB_DIR)/mesa_libs
SDL2_CONFIGURED = $(SDL2_DIR)/configured
SDL2_TTF_CONFIGURED = $(SDL2_TTF_DIR)/configured
FREETYPE_CONFIGURED = $(FREETYPE_DIR)/configured
FMOD_LIB_DIR = sound_lib
FMOD_INC_DIR = sound_inc
SOURCES_PATH =  /sgoinfre/goinfre/Perso/sipatry
INSTALL_DIR = install
INSTALL_TYPE = compile_all
LIB_INSTALL = $(LIB_DIR)/installed
SED = sed
ROOT = sudo

LIBFT = $(LIBFT_DIR)/libft.a

LIB_RAW = libelf-0.8.13 libXrender-0.9.10 libXrandr-1.5.2 libxshmfence-1.3 \
		   libXxf86vm-1.1.4 xcb-proto-1.14 libxcb-1.14 libXfixes-5.0 \
		   libXdamage-1.1 libX11-1.6.9 libpciaccess-0.13.4 libdrm-2.4.100 \
		   zlib-1.2.11 mesa-19.0.8 freetype-2.9 pkg-config-0.28 libXau-1.0.9 \
		   libpthread-stubs-0.1 \

SRC_GAME_RAW = main_game.c init_game.c draw_game.c doom.c enemy_utils.c \
				print_results.c projectile.c projectiles_maths.c \
				draw_projectiles.c projectile_on_wall_sprite.c \
				keys.c weapons.c draw_hud.c game_minimap.c explosion2.c \
				projectiles_collisions.c projectiles_utils.c weapons2.c \
		   		draw_projectile_no_light.c draw_projectile_color.c \
		   		draw_projectile_both.c draw_projectile_brightness.c \
				explosion.c draw_explosions.c draw_explosion.c doom_utils.c \
				explosion_maths.c enemy_maths.c enemy_combat.c weapons3.c \
				enemy_collision.c enemy_sight.c enemy_ai.c weapons4.c \
		   		add_projectile_bullet_hole.c add_hitscan_bullet_hole.c \
		   		shift_wall_bullet_hole.c get_bullet_hole_pos.c draw_weapon.c \
		   		delete_bullet_hole.c shift_bullet_hole_events.c \
		        add_floor_hitscan_bullet_hole.c doom_poll_event.c \
				add_ceiling_hitscan_bullet_hole.c projectile2.c projectile3.c \
		        add_floor_projectile_bullet_hole.c projectiles_collisions2.c \
				add_ceiling_projectile_bullet_hole.c projectiles_collisions3.c \
				shift_floor_bullet_hole.c shift_ceiling_bullet_hole.c \
				draw_game2.c entity_hit.c init_game2.c enemy_ai_utils.c \
				draw_inventory.c \

SRC_EDITOR_RAW = main_editor.c editor.c init_editor.c save_condition.c \
		draw_grid.c editor_keys.c grid_tools.c editor_render.c next_event.c \
		draw_grid_walls.c draw_grid_vertices.c event_panel_tab_functions.c \
		add_vertex.c print_target_functions2.c draw_action_panel_bottom.c \
		add_player.c editor_hud.c add_sector.c condition_panel2.c \
		save_map.c write_vertices.c write_sectors.c write_objects.c \
		write_player.c write_enemies.c add_object.c editor_keyup.c \
		player_selection.c objects_selection.c object_selection.c \
		draw_grid_player.c draw_grid_objects.c new_arrow_buttons.c \
		add_enemy.c enemy_selection.c delete_event.c draw_grid_start_player.c \
		delete_object.c delete_action.c delete_enemy.c draw_grid_enemies.c \
		editor_3d_keys.c wall_sprites_keys.c previous_event.c write_events2.c \
		apply_texture.c init_event_panel_buttons.c enemy_drag.c \
		editor_3d_keyup.c split_sector.c set_condition_panel_buttons_state.c \
		write_events.c init_print_target_data.c print_event_condition.c \
		write_events_utils.c write_events_utils2.c init_events_writers.c \
		write_event_conditions.c write_event_conditions_utils.c \
		write_event_conditions_utils2.c init_event_conditions_writers.c \
		write_events_links.c print_target_functions.c init_weapon_picker.c \
		split_sector_utils.c texture_selection.c init_hud_button.c \
		editor_hud_buttons.c init_hud_button_function.c editor_floor_tabs.c \
		editor_ceiling_tabs.c editor_player_tabs.c editor_wall_tabs.c \
		init_editor_tab_buttons.c editor_ceiling_tab_button.c \
		editor_floor_tab_button.c editor_wall_tab_button.c wall_edit_keyup.c \
		editor_env_wall_buttons.c editor_env_floor_buttons.c \
		editor_env_ceilling_buttons.c  change_editor_mode.c close_event_panel.c\
		editor_3d_button_keys.c editor_3d_button_keyup.c split_sector2.c \
		init_add_buttons.c editor_env_sector_buttons.c editor_2d.c \
		editor_sector_tab_button.c editor_sector_tabs.c editor_button_keys.c \
		editor_button_keyup.c editor_env_player_buttons.c split_sector3.c \
		editor_player_tab_button.c editor_enemy_tabs.c print_events_tabs2.c \
		editor_env_enemy_buttons.c editor_enemy_tab_button.c \
		editor_object_tabs.c editor_env_object_buttons.c write_events_link.c \
		sprite_selection.c init_sprite_selection_buttons.c \
		editor_object_tab_button.c print_events_tabs.c condition_panel_keys.c \
		init_events_selection_buttons.c print_event.c init_event_types.c \
		are_launch_condition_selection_buttons_visible.c split_sector_utils2.c \
		are_exec_condition_selection_buttons_visible.c next_launch_condition.c \
		are_exec_condition_selection_buttons_visible2.c save_condition_utils.c \
		init_event_links_types.c is_event_tabs_visible.c editor_keyup5.c\
		print_link_target_functions.c print_condition_target_functions.c \
		print_condition_target_functions2.c init_print_condition_target_data.c\
		change_sprite_buttons.c input_box_checkers.c input_box_updaters.c \
		update_textures_buttons.c init_skybox_selection_buttons.c \
		draw_editor_tabs.c editor_buttons_functions.c weapon_picker_keys.c \
		event_panel.c target_panel.c init_target_panel_buttons.c \
		init_action_panel_buttons.c init_conditions_tabs_buttons.c \
		target_panel_keys.c modify_condition.c init_new_sector_arrays.c \
		three_d_edit_change_floor_slope_start.c delete_selected_event.c \
		three_d_edit_change_ceiling_slope_start.c editor_3d_button_keys2.c \
		action_panel_keys.c conditions_panel_keys.c previous_launch_condition.c\
		event_panel_keys.c modify_event.c delete_action_utils.c \
		new_event_panel_buttons.c new_event_panel_buttons2.c choose_target.c \
		editor_tab_gestion.c editor_wall_sprites_keys.c next_exec_condition.c \
		three_d_edit_function.c action_panel.c conditions_tabs.c \
		event_panel_input_box.c three_d_edit_change_ceiling_floor_height.c \
		init_events_creation_buttons.c reduce_texture_scales_functions.c \
		increase_texture_scales_functions.c delete_condition.c \
		init_condition_panel_buttons.c condition_type_buttons_functions.c \
		condition_type_buttons_functions2.c init_condition_target_buttons.c \
		condition_target_panel.c condition_panel.c other_panel.c  \
		floor_panel.c ceiling_panel.c wall_panel.c wall_sprite_panel.c \
		weapon_panel.c enemy_panel.c object_panel.c player_panel.c \
		vertex_panel.c sector_other_panel.c check_event_creation.c \
		set_new_condition_target.c set_new_condition_target2.c \
		set_new_condition_target3.c set_new_condition_target4.c \
		set_new_condition_target5.c set_new_condition_target6.c \
		set_new_event_target.c set_new_event_target2.c target_panel_keyup.c \
		set_new_event_target3.c set_new_event_target4.c \
		set_new_event_target5.c set_new_event_target6.c \
		set_new_event_target7.c delete_wall_sprite.c draw_grid_walls_utils.c \
		condition_event_panel.c init_condition_event_buttons.c \
		three_d_edit_walls_texture_number.c three_d_edit_walls_keys.c \
		three_d_edit_slopes.c three_d_edit_change_slope_start.c \
		editor_3d_button_keyup2.c check_floor_height_input_box.c \
		editor_3d_tab_keys.c selection_tabs_button_keys.c \
		three_d_edit_right_walls_texture_align.c delete_floor_sprite.c \
		three_d_edit_left_walls_texture_align.c new_target.c \
		three_d_edit_keyup_functions.c three_d_edit_walls_keyup.c \
		editor_wall_sprites_keyup.c wall_sprites_keyup.c \
		add_floor_sprite.c add_ceiling_sprite.c add_wall_sprite.c \
		update_entities.c editor_vertices_tab.c selection_tabs_keyup.c \
		editor_vertices_tab_button.c editor_env_vertices_buttons.c \
		delete_sector.c delete_vertex.c weapon_picker.c write_ui.c \
		write_musics_choices.c write_resources.c write_textures.c \
		write_sounds.c write_sprites.c write_skyboxes.c write_fonts.c\
		editor_minimap.c init_editor_options_buttons.c delete_ceiling_sprite.c \
		editor_option_keys.c write_hud.c write_hud2.c previous_exec_condition.c\
		update_sector_with_deleted_vertex.c check_move_player_conditions.c \
		editor_buttons_functions2.c editor_buttons_functions3.c \
		editor_buttons_functions4.c editor_buttons_functions5.c \
		editor_ceiling_tabs2.c editor_floor_tabs2.c editor_hud2.c \
		editor_hud3.c launch_game.c editor_hud_buttons2.c editor_hud_buttons3.c\
		editor_keys2.c editor_keyup2.c editor_keyup3.c editor_keyup4.c \
		new_vertex.c editor_tab_gestion2.c editor_wall_tabs2.c \
		editor_wall_tabs3.c event_panel2.c new_event_panel_value_box.c \
		new_event_panel_box.c event_panel_keyup.c update_existing_events.c \
		are_events_selection_buttons_visible.c init_editor_options_buttons2.c \
		new_event_panel_dialog_box.c init_change_slope_direction_buttons.c \
		init_editor_options_buttons3.c set_trigger.c input_box_updaters2.c \
		init_editor_tab_buttons2.c init_enemy_selection_button.c \
		init_object_selection_button.c init_array_texture_buttons.c \
		change_slope_direction.c next_selected_wall.c save_selection.c \
		save_texture.c init_hud_button_function2.c print_event_action.c \
		init_print_condition_target_data2.c init_target_panel_buttons2.c \
		set_floor_condition_target.c set_ceiling_condition_target.c \
		select_floor_target.c select_ceiling_target.c check_condition_targets.c\
		update_existing_events2.c update_existing_events3.c \
		update_existing_events4.c write_resources2.c write_sectors2.c \
		write_sectors3.c check_ceiling_height_input_box.c editor_floor_tabs3.c\
		check_floor_slope_input_box.c check_ceiling_slope_input_box.c \
		input_box_checkers2.c input_box_checkers3.c draw_editor_tab_utils.c\
		update_sector_input_box.c editor_options.c draw_conditions_tab2.c\
		editor_3d_tab_keys2.c draw_editor_general_tab.c target_panel2.c\
		draw_editor_sector_tab.c editor_ceiling_tabs3.c editor_hud4.c\
		editor_object_sector_tabs.c editor_options2.c editor_enemy_tabs2.c \
		editor_wall_tabs4.c print_events_tabs3.c print_events_tabs4.c \
		vertices_selection.c is_new_vertex_valid.c 

SRC_ALL_RAW = init_sdl.c clear_image.c init_keys.c update_sprites.c \
		   draw_line.c menu_tools.c screen_utils.c init_ttf.c init_textures.c \
		   print_text.c bmp_parser.c bmp_parser_wall.c update_sprites_light.c \
		   bmp_parser_skybox.c bmp_parser_utils.c get_double_len.c \
		   bmp_parse_header.c bmp_parse_pixel_data.c bmp_parse_color_table.c \
		   check_bmp_parsing.c keyup.c render_utils.c movement.c create_event.c\
		   get_slope.c update_player_z.c movement_collision.c win.c \
		   get_screen_sectors.c view.c init_options.c confirmation_box_keys.c \
		   fps.c inputs.c init_editor_data.c set_button_images.c draw_button.c \
		   valid_map.c game_menu.c get_sector.c draw_line_minimap.c \
		   color_utils.c camera.c  new_tabs_position.c init_weapons2.c \
		   print_debug.c init_animations.c vertices_utils.c death.c \
		   map_parse_vertices.c is_in_sector.c add_vertex_in_sector.c \
		   get_existing_vertex.c ./map_parser_protection_utils.c \
		   map_parse_sectors.c map_parser_utils.c map_parse_sectors_utils.c \
		   physics.c map_parse_player.c create_portals.c init_weapons.c \
		   sound_utils.c draw_rectangle.c confirmation_box.c apply_image.c \
		   draw_objects.c sprites_maths.c draw_player.c save_init_data.c \
		   map_parse_objects.c map_init_objects.c init_events_data.c \
		   free_all.c map_parser.c animations.c map_init_enemies.c \
		   sprite_maths_enemies.c draw_enemies.c button.c dialog_box.c \
		   map_parse_enemies.c  draw_line_free.c render.c animations2.c \
		   project_wall.c render_sector.c draw_ceiling.c draw_wall.c \
		   precompute_skybox.c draw_skybox.c draw_floor.c apply_image2.c \
		   precompute_neighbors.c wall_hack.c check_conditions.c \
		   movement_utils.c update_sprites_state.c set_event_function.c \
		   select_line.c draw_wall_sprites.c input_box.c get_pixel.c \
		   init_objects_data.c reset_selection.c events_tab_conditions.c \
		   draw_circle_free.c draw_circle.c ft_getchar.c new_button.c \
		   objects_utils.c misc_utils.c map_parse_events.c new_button2.c \
		   gravity.c input_box_utils.c init_ui_textures.c draw_objects2.c \
		   input_box_mouse.c delete_box_selection.c event_target_exists.c \
		   validate_input.c button_event.c check_height_at_pos.c \
		   pop_events.c start_event.c event_updaters.c free_map.c \
		   generate_mipmaps.c get_current_wall_map.c get_current_floor_map.c \
		   get_current_ceiling_map.c init_skybox.c init_sprites.c \
		   draw_floor_sprites.c draw_floor_sprites_no_light.c set_enemies_hp.c \
		   draw_floor_sprites_color.c draw_floor_sprites_brightness.c \
		   draw_floor_sprites_both.c bmp_parser_ui.c bmp_parser_ui_skyboxes.c \
		   draw_ceiling_sprites.c draw_ceiling_sprites_no_light.c \
		   draw_ceiling_sprites_color.c draw_ceiling_sprites_brightness.c \
		   draw_ceiling_sprites_both.c get_clockwise_order.c draw_objects3.c \
		   map_parse_floor_sprites.c map_parse_ceiling_sprites.c \
		   draw_vline_ceiling.c draw_vline_ceiling_brightness.c \
		   draw_vline_ceiling_both.c draw_vline_ceiling_color.c mouse_inputs.c \
		   draw_vline_wall.c draw_vline_wall_brightness.c bmp_parser_utils2.c \
		   draw_vline_wall_both.c draw_vline_wall_color.c dialog_box_utils.c \
		   draw_vline_floor.c draw_vline_floor_brightness.c fill_new_sector2.c \
		   draw_vline_floor_both.c draw_vline_floor_color.c tabs_gestion.c \
		   free_sector.c init_screen_size.c dialog_parser.c update_event.c \
		   print_press_text.c realloc_sector_arrays.c keys_checkers.c \
		   draw_wall_bullet_holes.c intersect_maths.c camera2.c \
		   equals_condition.c less_condition.c greater_condition.c \
		   less_or_equals_condition.c greater_or_equals_condition.c \
		   event_ended_condition.c event_ended_start_condition.c \
		   different_condition.c init_events.c init_events_parser.c \
		   new_global_event.c new_press_event.c new_shoot_event.c \
		   new_stand_event.c new_walk_in_event.c new_walk_out_event.c \
		   new_enemy_event.c parse_event_target.c portal_loop.c \
		   init_events_parser_target_types.c parse_event_launch_conditions.c \
		   sector_parser.c enemy_parser.c wall_sprite_parser.c wall_parser.c \
		   vertex_parser.c set_event_target.c floor_sprite_parser.c \
		   ceiling_sprite_parser.c set_event_target2.c weapon_parser.c \
		   object_parser.c parse_event_type.c parse_event_various_data.c \
		   set_condition_target.c set_condition_target2.c update_sprites2.c \
		   init_events_parser_target_parsers.c parse_event_exec_conditions.c \
		   init_events_parser_checkers.c init_events_parser_updaters.c \
		   event_checkers.c check_vertex_event.c intersects_with_player.c \
		   parse_events_links.c events_links_protection.c set_event_link.c \
		   get_event_array.c get_event_nb.c init_objects_main_sprites.c \
		   precompute_floor_ceiling_sprites_scales.c check_event_validity.c \
		   menu_keys.c option_menu.c option_menu_keys.c collision_utils_2.c \
		   collision_maths.c collision_utils.c new_object_event.c \
		   collision_utils_3.c map_parse_music.c \
		   init_audio.c fill_new_sector.c \
		   map_parse_resources.c map_parser_bmp.c map_parse_sound.c \
		   map_parse_fonts.c angles_utils.c add_vertex_in_sector_utils.c \
		   add_vertex_in_sector_utils2.c add_vertex_in_sector_utils3.c \
		   check_vertex_event_utils.c draw_ceiling_utils.c option_menu2.c \
		   draw_enemies2.c draw_enemies3.c draw_vline_projectile.c \
		   draw_skybox2.c draw_floor_utils.c draw_wall_utils.c valid_map2.c \
		   draw_wall_sprites2.c draw_minimap_player.c minimap2.c minimap3.c \
		   check_floor_event.c check_ceiling_event.c check_floor_slope_event.c \
		   check_ceiling_slope_event.c check_x_collision_event.c valid_map3.c \
		   check_y_collision_event.c check_z_collision_event.c valid_map4.c \
		   event_checkers2.c event_checkers3.c event_updaters2.c \
		   event_updaters3.c event_updaters4.c events_links_protection2.c \
		   fill_triangle_minimap.c fill_triangle.c free_sector2.c \
		   free_fonts.c free_camera.c free_all2.c free_all3.c set_channels.c \
		   game_menu2.c game_menu3.c generate_mipmaps_utils.c \
		   get_event_array2.c get_event_array3.c get_event_nb2.c \
		   update_sector_slope.c init_selection_tabs.c no_parser.c \
		   init_enemies_data.c init_objects_data2.c init_objects_data3.c \
		   init_lost_soul_sprite.c init_lost_soul_rest.c option_menu3.c \
		   init_lost_soul_pursuit.c init_minigun.c init_rocket.c \
		   init_lost_soul_pursuit_two.c init_health_pack.c init_ammo.c \
		   init_lost_soul_death.c init_cyber_demon_pursuit.c \
		   init_cyber_demon_pursuit_two.c init_cyber_demon_pursuit_three.c \
		   init_cyber_demon_pursuit_four.c init_cyber_demon_firing_anim.c \
		   init_cyber_demon_firing_anim_two.c init_cyber_demon_death.c \
		   init_cyber_demon_firing_anim_three.c init_lamp.c init_barrel.c \
		   init_monitor.c init_candle.c init_camera_sprite.c free_buttons.c \
		   init_armor_green.c init_explosion.c init_grid_sprite.c \
		   init_bullet_hole.c init_object_lost_soul.c init_object_cyber_demon.c\
		   init_shotgun_sprite.c init_raygun_sprite.c init_doom_guy.c \
		   init_hd_sprite.c init_button_sprite.c new_input_box.c \
		   init_doom_guy_face.c init_skyboxes_textures.c new_input_var.c \
		   split_box_text.c input_box_utils2.c input_box_keys.c \
		   input_box_keys2.c init_inputs.c pos_changed.c valid_map5.c\
		   is_in_sector_utils.c init_vertices.c init_sectors.c \
		   parse_enemy_data.c parse_enemy_sprite.c parse_enemy_pos.c \
		   parse_object_sprite.c parse_object_pos.c map_parse_sectors_utils2.c \
		   map_parse_sectors_utils3.c valid_texture.c valid_sprite.c \
		   map_parser_utils2.c modify_event_utils.c movement_utils2.c \
		   movement_utils3.c parse_floor.c parse_floor2.c parse_ceiling.c \
		   parse_ceiling2.c init_sector_data.c parse_sector_neighbors.c \
		   parse_sector_vertices.c parse_sector_portals.c init_gun.c \
		   parse_sector_textures.c parse_sector_wall_sprites.c \
		   parse_current_sprite.c parse_sector_general.c count_conditions.c \
		   parse_link_target.c physics2.c int_event.c double_event.c \
		   uint32_event.c precompute_skybox2.c precompute_sector.c \
		   get_rendered_sectors_list.c precompute_values.c \
		   precompute_values2.c compute_wall.c get_intersections.c \
		   render_sector2.c render_sector3.c update_screen_zbuffer.c \
		   draw_skybox_wall.c draw_skybox_ceiling.c draw_skybox_floor.c \
		   damage_anim.c del_char.c add_char.c parse_double_input.c \
		   is_new_vertex_valid2.c is_new_vertex_valid3.c is_new_vertex_valid4.c\
		   option_menu4.c option_menu5.c option_menu6.c option_menu_hud.c \
		   set_new_string_input_box.c init_ui_textures2.c put_player_pixel.c \
		   parse_current_floor_sprite.c parse_current_ceiling_sprite.c \
		   is_new_sector_convex.c check_skyboxes2.c check_directories.c \
		   init_enemies_textures.c init_sprites_textures.c death_utils.c\
		   init_hud_textures.c init_wall_textures.c check_entities_height.c \
		   init_mini_skyboxes.c check_existing_files.c create_sound_file.c\
		   check_walls_textures.c free_resources_init.c input_box_utils3.c\
		   check_sprites_textures.c check_hud_textures.c init_objects_data4.c \
		   check_skyboxes.c parse_resources_utils.c map_parse_hud.c \
		   init_ttf2.c check_fonts.c free_all4.c split_box_text2.c\
		   check_ui.c map_parse_ui.c check_existing_files2.c\
		   check_existing_sounds.c map_parse_textures.c free_all5.c\
		   parse_sound.c map_parse_sprites.c map_parse_skyboxes.c \
		   parse_font.c check_resources.c check_shotgun.c \
		   check_gun.c check_raygun.c check_gatling.c init_mipmap_data.c \
		   check_sounds.c check_sounds2.c check_rocket_launcher.c \
		   sound_misc_functions.c check_wall_sprites_textures.c func_event.c \
		   event_updaters5.c init_rocket_launcher_sprite.c save_limits.c \
		   draw_ceiling_bullet_holes_both.c draw_ceiling_bullet_holes_color.c \
		   draw_ceiling_bullet_holes_no_light.c init_wall_textures2.c \
		   draw_ceiling_bullet_holes_brightness.c init_wall_textures3.c \
		   draw_floor_bullet_holes_both.c draw_floor_bullet_holes_color.c \
		   draw_floor_bullet_holes_no_light.c check_walls_textures2.c \
		   draw_floor_bullet_holes_brightness.c parse_player_data.c \
		   draw_entities_utils.c \

HEADERS = utils.h render.h collision.h bmp_parser.h map_parser.h object_types.h\
		  editor.h env.h save.h create_portals.h input_box_utils.h add_vertex.h\
		  wall_sprite_remover.h events_conditions.h \
		  events_parser.h draw_grid_walls.h valid_map.h events.h free.h\
		  draw_skybox.h pop_events.h events_protection.h init.h \
		  parser.h enemies.h draw.h defines_images.h \

TEXTURES =	black_tiles.bmp tiles.bmp floor0.bmp floor1.bmp grass1.bmp \
			grass2.bmp grass3.bmp grey.bmp magma_rock.bmp rock.bmp \
			menu_texture.bmp sand.bmp wall0.bmp wall1.bmp wall2.bmp wall3.bmp \
			wall4.bmp bigdoor1.bmp bigdoor2.bmp bigdoor3.bmp bigdoor4.bmp \
			bigdoor5.bmp bigdoor6.bmp bigdoor7.bmp blood1.bmp blood2.bmp \
			blood3.bmp bronze1.bmp bronze2.bmp bronze3.bmp bronze4.bmp \
			brovine2.bmp ceil1_1.bmp ceil1_2.bmp ceil1_3.bmp ceil3_4.bmp \
			cement1.bmp cement2.bmp cement3.bmp cement4.bmp cement5.bmp \
			cement6.bmp cement7.bmp cement8.bmp cement9.bmp comptall.bmp \
			compwerd.bmp cratop1.bmp cratop2.bmp door1.bmp door3.bmp \
			doorblu.bmp doorblu2.bmp doorred.bmp doorred2.bmp doorstop.bmp \
			doortrak.bmp dooryel.bmp dooryel2.bmp exitsign.bmp exitston.bmp \
			flat20.bmp flat23.bmp flat3.bmp flat4.bmp flat5_1.bmp floor3_3.bmp \
			floor4_8.bmp floor5_1.bmp floor5_2.bmp lite3.bmp lite5.bmp \
			liteblu1.bmp liteblu4.bmp pancase1.bmp pancase2.bmp panel1.bmp \
			panel2.bmp panel3.bmp panel4.bmp panel5.bmp panel6.bmp panel9.bmp \
			panred.bmp rock5.bmp rrock09.bmp slime01.bmp slime02.bmp \
			slime03.bmp slime04.bmp slime14.bmp slime15.bmp slime16.bmp \
			spcdoor1.bmp spcdoor2.bmp step4.bmp step6.bmp steplad1.bmp \
			steptop.bmp stone.bmp sw1cmt.bmp sw2cmt.bmp tlite6_1.bmp \
			tlite6_4.bmp tlite6_5.bmp tlite6_6.bmp wood1.bmp wood10.bmp \
			wood12.bmp wood3.bmp wood4.bmp wood5.bmp wood6.bmp wood7.bmp \
			wood8.bmp wood9.bmp woodgarg.bmp woodmet1.bmp woodmet2.bmp \
			woodmet3.bmp woodmet4.bmp woodvert.bmp zdoorb1.bmp zdoorf1.bmp \
			zzwolf11.bmp zzwolf12.bmp zzwolf13.bmp

SPRITES =	bullet_hole.bmp button_off.bmp button_on.bmp camera.bmp \
			cyber_demon.bmp doom_guy_face.bmp doom_guy.bmp lost_soul.bmp \
			MIDSPACE.bmp objects_sprites.bmp projectiles_sprites.bmp \
			raygun.bmp sprite_sheet.bmp gun_sprite_sheet.bmp \
			rocket_launcher_sprites.bmp \

SKYBOXES =	back.bmp bottom.bmp top.bmp left.bmp right.bmp front.bmp \
			nebula_back.bmp nebula_bottom.bmp nebula_top.bmp nebula_right.bmp\
			nebula_left.bmp nebula_front.bmp night_back.bmp night_bottom.bmp \
			night_left.bmp night_right.bmp night_top.bmp night_front.bmp \

HUD =	hud.bmp Ammo_hud.bmp Life_armor_hud.bmp raygun1.bmp raygun2.bmp \
		raygun3.bmp raygun4.bmp raygun5.bmp raygun6.bmp raygun7.bmp \
		shot1.bmp shot2.bmp shot3.bmp shot4.bmp shot5.bmp shot6.bmp shot7.bmp \
		shot8.bmp shot9.bmp shot10.bmp shot11.bmp shot12.bmp shot13.bmp \
		shot14.bmp shot15.bmp Gatling_1.bmp Gatling_2.bmp Gatling_3.bmp \
		Gatling_4.bmp Gatling_5.bmp Gatling_6.bmp rocket_launcher1.bmp \
		rocket_launcher2.bmp rocket_launcher3.bmp rocket_launcher4.bmp \
		rocket_launcher5.bmp rocket_launcher6.bmp rocket_launcher7.bmp \
		rocket_launcher8.bmp rocket_launcher9.bmp

UI =	button-default-up.bmp button-default-pressed.bmp \
		button-default-hover.bmp background-up-64.bmp \
		background-pressed-64.bmp background-hover-64.bmp \
		onglet-up.bmp onglet-pressed.bmp onglet-hover.bmp tab-button-up.bmp\
		tab-button-pressed.bmp tab-button-hover.bmp plus-button-up.bmp \
		plus-button-pressed.bmp plus-button-hover.bmp next-up2.bmp \
		next-pressed2.bmp next-hover2.bmp previous-up2.bmp \
		previous-pressed2.bmp  previous-hover2.bmp \
		minus-button-up.bmp minus-button-pressed.bmp minus-button-hover.bmp \
		file.bmp file_straight.bmp plus-button-up2.bmp \
		plus-button-pressed2.bmp plus-button-hover2.bmp minus-button-up2.bmp \
		minus-button-pressed2.bmp minus-button-hover2.bmp background-up2.bmp \
		background-pressed2.bmp background-hover2.bmp add_button.bmp \
		onglet-up2.bmp onglet-pressed2.bmp onglet-hover2.bmp \
		hud-button-up.bmp hud-button-pressed.bmp hud-button-hover.bmp \
		play_icon.bmp target_icon.bmp event_icon.bmp condition_icon.bmp \
		play_icon_down.bmp target_icon_down_blue.bmp event_icon_down_blue.bmp\
		condition_icon_down_blue.bmp play_icon_hover.bmp \
		target_icon_hover.bmp event_icon_hover.bmp condition_icon_hover.bmp \
		previous_arrow.bmp next_arrow.bmp previous_arrow_down.bmp \
		next_arrow_down.bmp previous_arrow_hover.bmp next_arrow_hover.bmp \
		moonlight.bmp moonlight_128.bmp nebula.bmp nebula_128.bmp \
		beautifull_scenery.bmp beautifull_scenery_128.bmp \
		previous-hover2_pink.bmp previous-pressed2_pink.bmp \
		previous-up2_pink.bmp

AUDIO = Mt_Erebus.wav bim_bam_boum.wav at_dooms_gate.wav footstep.wav \
		shotgun_shot.wav raygun_shot.wav handgun_shot.wav \
		rocket_launcher_shot.wav gatling_shot.wav player_hit.wav \
		player_death.wav cyberdemon_death.wav lost_soul_death.wav \
		lost_soul_attack.wav monster_hit.wav monster_nearby.wav \
		explosion.wav \

FONTS = alice/Alice-Regular.ttf bebas_neue/BebasNeue-Regular.ttf \
		amazdoom/AmazDooMLeft.ttf montserrat/Montserrat-Regular.ttf \
		playfair-display/PlayfairDisplay-Regular.ttf \
		lato/Lato-Regular.ttf lato/Lato-Bold.ttf lato/Lato-Black.ttf

#
# Creation of files path
#

SRC_GAME = $(addprefix $(SRC_DIR)/, $(SRC_GAME_RAW))
OBJ_GAME = $(addprefix $(OBJ_GAME_DIR)/, $(SRC_GAME_RAW:.c=.o))

SRC_EDITOR = $(addprefix $(SRC_DIR)/, $(SRC_EDITOR_RAW))
OBJ_EDITOR = $(addprefix $(OBJ_EDITOR_DIR)/, $(SRC_EDITOR_RAW:.c=.o))

SRC_ALL = $(addprefix $(SRC_DIR)/, $(SRC_ALL_RAW))
OBJ_ALL = $(addprefix $(OBJ_ALL_DIR)/, $(SRC_ALL_RAW:.c=.o))

INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(HEADERS))

MESA_LIB = $(addprefix $(MESA_DIR)/, $(LIB_RAW))

MESA_ARCHIVES = $(addsuffix .tar.gz, $(MESA_LIB))

TEXTURES_FILES = $(addprefix $(IMAGES_DIR)/, \
				 $(addprefix $(TEXTURES_DIR)/, $(TEXTURES)))
SPRITES_FILES = $(addprefix $(IMAGES_DIR)/, \
				$(addprefix $(SPRITES_DIR)/, $(SPRITES)))
SKYBOXES_FILES = $(addprefix $(IMAGES_DIR)/, \
				 $(addprefix $(SKYBOXES_DIR)/, $(SKYBOXES)))
HUD_FILES = $(addprefix $(IMAGES_DIR)/, $(addprefix $(HUD_DIR)/, $(HUD)))
UI_FILES = $(addprefix $(IMAGES_DIR)/, $(addprefix $(UI_DIR)/, $(UI)))
AUDIO_FILES = $(addprefix $(AUDIO_DIR)/, $(AUDIO))
FONTS_FILES = $(addprefix $(FONTS_DIR)/, $(FONTS))

TEXTURES_PATH = $(addprefix $(IMAGES_DIR)/, $(TEXTURES_DIR))
SPRITES_PATH =  $(addprefix $(IMAGES_DIR)/, $(SPRITES_DIR))
SKYBOXES_PATH =  $(addprefix $(IMAGES_DIR)/, $(SKYBOXES_DIR))
HUD_PATH =  $(addprefix $(IMAGES_DIR)/, $(HUD_DIR))
UI_PATH =  $(addprefix $(IMAGES_DIR)/, $(UI_DIR))
AUDIO_PATH = $(AUDIO_DIR)
FONTS_PATH = $(FONTS_DIR)

RESOURCES = $(TEXTURES_FILES) $(SPRITES_FILES) $(SKYBOXES_FILES) $(HUD_FILES) \
			$(UI_FILES) $(AUDIO_FILES) $(FONTS_FILES)

OPTI_FLAGS = -O3

CFLAGS =  -Wall -Wextra -Werror -I $(INCLUDES_DIR) \
		  -I $(LIBFT_DIR) -I $(SDL2_DIR)/include -I $(SDL2_TTF_DIR) \
		  -I $(FMOD_INC_DIR) \
          -Wno-unused-result \
		  $(OPTI_FLAGS) \
		  #-fsanitize=address -g3 \
	
#
# Flags for FMOD, SDL2 and SDL2_ttf linking
#

FMOD_FLAGS = -lfmod -lfmodL

SDL2_FLAGS = -lSDL2

SDL2_TTF_FLAGS = -lSDL2_ttf

#
# Needed lib files to link
#

#### FMOD ####

FMOD_WINDOWS = /usr/lib/fmod.dll /usr/lib/fmodL.dll

FMOD_OSX = /usr/local/lib/libfmod.dylib /usr/local/lib/libfmodL.dylib

FMOD_LINUX = /usr/lib/libfmod.so /usr/lib/libfmodL.so \
			 /usr/lib/libfmod.so.12 /usr/lib/libfmodL.so.12 \
			 /usr/lib/libfmod.so.12.0 /usr/lib/libfmodL.so.12.0

#### SDL2 ####

SDL2_WINDOWS = /usr/local/bin/SDL2.dll

SDL2_OSX = 

SDL2_LINUX = /usr/local/lib/libSDL2.so

#### SDL2_ttf ####

SDL2_TTF_WINDOWS = /usr/local/bin/SDL2_ttf.dll

SDL2_TTF_OSX = 

SDL2_TTF_LINUX = /usr/local/lib/libSDL2_ttf.so 

#### Freetype ###

FREETYPE_WINDOWS =

FREETYPE_OSX =

FREETYPE_LINUX = /usr/local/lib/libfreetype.so

#
# Includes lib files needed for compilation (needs an archive to be extracted)
#

SDL2_INCLUDES = $(SDL2_DIR)/include/SDL.h

SDL2_TTF_INCLUDES = $(SDL2_TTF_DIR)/SDL_ttf.h

#
# Setting right flags and files dependencies to link external libs
# according to user's os
#

ifeq ($(OS), Windows_NT)
	SDL2_FLAGS += -Wl,-rpath,/usr/local/bin
	SDL2 = $(SDL2_WINDOWS)
	SDL2_TTF = $(SDL2_TTF_WINDOWS)
	FREETYPE = $(FREETYPE_WINDOWS)
	FMOD = $(FMOD_WINDOWS)
	CFLAGS += -Wno-misleading-indentation
	COMPILE_ALL = $(INSTALL_DIR)/compile_all_windows.sh
	INSTALL_SDL_DEPENDENCIES = $(INSTALL_DIR)/install_windows.sh
	INSTALL_ALL = $(INSTALL_DIR)/install_all_windows.sh
	ROOT = 
else
	UNAME_S = $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
		SDL2 = $(SDL2_OSX)
		SDL2_TTF = $(SDL2_TTF_OS)
		FREETYPE = $(FREETYPE_OSX)
		FMOD = $(FMOD_OSX)
		COMPILE_ALL = $(INSTALL_DIR)/compile_all_osx.sh
		INSTALL_SDL_DEPENDENCIES = $(INSTALL_DIR)/install_osx.sh
		INSTALL_ALL = $(INSTALL_DIR)/install_all_osx.sh
		OPTI_FLAGS += -flto
		SED = gsed
    else
		SDL2_FLAGS += -Wl,-rpath,/usr/local/lib -lm -lpthread
		SDL2 = $(SDL2_LINUX)
		SDL2_TTF = $(SDL2_TTF_LINUX)
		FREETYPE = $(FREETYPE_LINUX)
		FMOD = $(FMOD_LINUX)
		COMPILE_ALL = $(INSTALL_DIR)/compile_all_linux.sh
		INSTALL_SDL_DEPENDENCIES = $(INSTALL_DIR)/install_linux.sh
		INSTALL_ALL = $(INSTALL_DIR)/install_all_linux.sh
		CFLAGS += -Wno-misleading-indentation
		OPTI_FLAGS += -flto
    endif
endif

#
# Color declarations
#

RED := "\e[0;31m"
GREEN := "\e[0;32m"
YELLOW := "\e[0;33m"
BLUE := "\e[0;34m"
MAGENTA := "\e[0;35m"
CYAN := "\e[0;36m"
RESET :="\e[0m"

#
# Rules
#

all: $(RESOURCES)
	@printf $(CYAN)"[INFO] Buidling libft..\n"$(RESET) 
	@make --no-print-directory -C $(LIBFT_DIR)
	@printf $(RESET)
	@printf $(CYAN)"[INFO] Buidling game..\n"$(RESET) 
	@make --no-print-directory $(GAME_DIR)/$(GAME_NAME)
	@printf $(CYAN)"[INFO] Buidling editor..\n"$(RESET) 
	@make --no-print-directory $(EDITOR_DIR)/$(EDITOR_NAME)

$(NAME): all

game: $(RESOURCES)
	@printf $(CYAN)"[INFO] Compiling libft..\n"$(RESET) 
	@make --no-print-directory -C $(LIBFT_DIR)
	@printf $(CYAN)"[INFO] Compiling libft..\n"$(RESET) 
	@make --no-print-directory $(GAME_DIR)/$(GAME_NAME)

editor: $(RESOURCES)
	@printf $(CYAN)"[INFO] Building libft..\n"$(RESET) 
	@make --no-print-directory -C $(LIBFT_DIR)
	@printf $(CYAN)"[INFO] Building editor..\n"$(RESET) 
	@make --no-print-directory $(EDITOR_DIR)/$(EDITOR_NAME)

$(LIB_DIR): $(LIB_DIR)%.tar.gz
	@printf $(YELLOW)"Extracting $< archive..\n"$(RESET)
	@tar -xf $< 

$(EXTRACT_ALL): $(LIB_ARCHIVE)

$(EXTRACT_SDL): $(SDL2_DIR) $(SDL2_TTF_DIR)

$(LIB_INSTALL):
	@printf $(CYAN)"[INFO] Checking SDL dependencies..\n"$(RESET)
ifeq ($(INSTALL_TYPE),compile_all)
	@printf $(CYAN)"[INFO] Manually compiling all the libraries..\n"$(RESET)
	@$(ROOT) sh $(COMPILE_ALL)
	@touch $(LIB_DIR)/installed
else
    ifeq ($(INSTALL_TYPE),compile_sdl)
		@printf $(CYAN)"[INFO] Compiling SDL2 and SDL2_ttf..\n"$(RESET)
		@$(ROOT) sh $(INSTALL_SDL_DEPENDENCIES)
		@touch $(LIB_DIR)/installed
    else
        ifeq ($(INSTALL_TYPE),install)
			@printf $(CYAN)"[INFO] Installing all the libraries..\n"
			@printf $(RESET)
			@$(ROOT) sh $(INSTALL_ALL)
			@touch $(LIB_DIR)/installed
        else
			@printf $(RED)"[ERROR] Unsupported install type.\n"$(RESET)
        endif
     endif
endif

$(SDL2_DIR)/exists:
	@printf $(YELLOW)"Extracting SDL2 archive..\n"$(RESET) 
	@cd $(LIB_DIR) && tar -xf SDL2-2.0.8.tar.gz
	@touch $@

$(SDL2_TTF_DIR)/exists:
	@printf $(YELLOW)"Extracting SDL2_ttf archive..\n"$(RESET) 
	@cd $(LIB_DIR) && tar -xf SDL2_ttf-2.0.15.tar.gz
	@touch $@

$(FREETYPE_DIR)/exists:
	@printf $(YELLOW)"Extracting FreeType archive..\n"$(RESET) 
	@cd $(LIB_DIR) && tar -xf freetype-2.9.tar.gz
	@touch $@

$(SDL2_CONFIGURED): $(SDL2_DIR)/exists
	@printf $(YELLOW)"Configuring SDL2..\n"$(RESET) 
	@cd $(SDL2_DIR) && $(ROOT) ./configure && touch configured

$(FREETYPE_CONFIGURED): $(FREETYPE_DIR)/exists
	@printf $(YELLOW)"Configuring FreeType..\n"$(RESET) 
	@cd $(FREETYPE_DIR) && $(ROOT) ./configure && touch configured

$(SDL2_TTF_CONFIGURED): $(SDL2_TTF_DIR)/exists $(SDL2) $(FREETYPE)
	@printf $(YELLOW)"Configuring SDL2_ttf..\n"$(RESET) 
	@cd $(SDL2_TTF_DIR) && $(ROOT) ./configure && touch configured

$(SDL2): $(LIB_INSTALL) $(SDL2_CONFIGURED)
	@printf $(YELLOW)"Compiling SDL2..\n"$(RESET) 
	@$(ROOT) make -C $(SDL2_DIR)
	@$(ROOT) make install -C $(SDL2_DIR)

$(SDL2_TTF): $(SDL2_TTF_CONFIGURED)
	@printf $(YELLOW)"Compiling SDL2_ttf..\n"$(RESET) 
	@$(ROOT) make -C $(SDL2_TTF_DIR)
	@$(ROOT) make install -C $(SDL2_TTF_DIR)

$(FREETYPE): $(FREETYPE_CONFIGURED)
	@printf $(YELLOW)"Compiling FreeType..\n"$(RESET) 
	@$(ROOT) make -C $(FREETYPE_DIR)
	@$(ROOT) make install -C $(FREETYPE_DIR)

$(SDL2_INCLUDES):
	@printf $(CYAN)"[INFO] SDL2 includes are missing.\n"
	@printf $(YELLOW)"Extracting SDL2 archive..\n"$(RESET) 
	@cd $(LIB_DIR) && tar -xf SDL2-2.0.8.tar.gz

$(SDL2_TTF_INCLUDES):
	@printf $(CYAN)"[INFO] SDL2 includes are missing.\n"
	@printf $(YELLOW)"Extracting SDL2_ttf archive..\n"$(RESET) 
	@cd $(LIB_DIR) && tar -xf SDL2_ttf-2.0.15.tar.gz

$(FMOD_WINDOWS):
	@$(ROOT) cp sound_lib/fmod.dll /usr/lib/
	@$(ROOT) cp sound_lib/fmodL.dll /usr/lib/

$(FMOD_OSX):
	@$(ROOT) cp sound_lib/libfmod.dylib /usr/local/lib
	@$(ROOT) cp sound_lib/libfmodL.dylib /usr/local/lib

$(FMOD_LINUX):
	@$(ROOT) cp sound_lib/libfmod.so /usr/lib/
	@$(ROOT) cp sound_lib/libfmod.so.12 /usr/lib/
	@$(ROOT) cp sound_lib/libfmod.so.12.0 /usr/lib/
	@$(ROOT) cp sound_lib/libfmodL.so /usr/lib/
	@$(ROOT) cp sound_lib/libfmodL.so.12 /usr/lib/
	@$(ROOT) cp sound_lib/libfmodL.so.12.0 /usr/lib/

$(LIBFT):
	@make -C $(LIBFT_DIR) -j8

$(OBJ_GAME_DIR):
	@mkdir -p $(OBJ_GAME_DIR)

$(OBJ_EDITOR_DIR):
	@mkdir -p $(OBJ_EDITOR_DIR)

$(OBJ_ALL_DIR):
	@mkdir -p $(OBJ_ALL_DIR)

$(RESOURCES):
	@rm -rf images
	@rm -rf fonts
	@rm -rf audio
	@rm -rf maps
	@printf $(CYAN)"[INFO] Importing resources\n"$(YELLOW)
	@wget -q --show-progress --load-cookies /tmp/cookies.txt \
	"https://docs.google.com/uc?export=download&confirm=$$(wget --quiet $\
	--save-cookies /tmp/cookies.txt --keep-session-cookies $\
	--no-check-certificate 'https://docs.google.com/uc?export=download&id=$\
	1KM0xklJbHRlNhkzCB0wyGNhKaU2YWulr' -O- | $(SED) -rn $\
	's/.*confirm=([0-9A-Za-z_]+).*/\1\n/p')\
	&id=1KM0xklJbHRlNhkzCB0wyGNhKaU2YWulr" -O resources.tar.gz \
	&& rm -rf /tmp/cookies.txt
	@printf $(CYAN)"[INFO] Unarchiving resources\n"$(YELLOW)
	@tar -xf resources.tar.gz
	@printf $(RESET)
	@rm -rf resources.tar.gz

$(OBJ_ALL_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES) $(SDL2_INCLUDES) \
					$(SDL2_TTF_INCLUDES)
	@printf $(YELLOW)"Compiling $<\n"$(RESET)
	@gcc -c $< -o $@ $(CFLAGS) 

$(OBJ_GAME_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES) $(SDL2_INCLUDES) \
					$(SDL2_TTF_INCLUDES)
	@printf $(YELLOW)"Compiling $<\n"$(RESET)
	@gcc -c $< -o $@ $(CFLAGS) 

$(OBJ_EDITOR_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDES) $(SDL2_INCLUDES) \
					$(SDL2_TTF_INCLUDES)
	@printf $(YELLOW)"Compiling $<\n"$(RESET)
	@gcc -c $< -o $@ $(CFLAGS) 

$(EDITOR_NAME): $(LIBFT) $(SDL2) $(SDL2_TTF) $(FMOD) $(OBJ_EDITOR_DIR) \
				$(OBJ_ALL_DIR) $(OBJ_EDITOR) $(OBJ_ALL)
	@printf $(CYAN)"[INFO] Linking ${EDITOR_DIR}/${EDITOR_NAME}...\n"$(RESET)
	@gcc $(CFLAGS) $(OBJ_EDITOR) $(OBJ_ALL) $(LIBFT) -o $(EDITOR_NAME) \
		$(SDL2_FLAGS) $(SDL2_TTF_FLAGS) $(FMOD_FLAGS)
	@printf ${GREEN}"[INFO] Compiled $(EDITOR_DIR)/$(EDITOR_NAME)"
	@printf " with success!\n"${RESET}

$(GAME_NAME): $(LIBFT) $(SDL2) $(SDL2_TTF) $(FMOD) $(OBJ_GAME_DIR) \
			  $(OBJ_ALL_DIR) $(OBJ_GAME) $(OBJ_ALL)
	@printf $(CYAN)"[INFO] Linking ${GAME_DIR}/${GAME_NAME}\n"$(RESET)
	@gcc $(CFLAGS) $(OBJ_GAME) $(OBJ_ALL) $(LIBFT) -o $(GAME_NAME) \
		$(SDL2_FLAGS) $(SDL2_TTF_FLAGS) $(FMOD_FLAGS)
	@printf ${GREEN}"[INFO] Compiled $(GAME_DIR)/$(GAME_NAME) with success!\n"
	@printf ${RESET}

$(CLEAN_LIB): $(LIB)
	printf $(YELLOW)"Make clean $<\n"$(RESET)
	make clean -C $<

$(FCLEAN_LIB): $(LIB)
	@printf $(YELLOW)"Make clean $<\n"$(RESET)
	@$(ROOT) make clean -C $<
	@printf $(YELLOW)"Removing $<\n"$(RESET)
	@rm -rf $<

clean_libs:
	@printf ${CYAN}"[INFO] Removing libs\n"${RESET}
	$(ROOT) rm -rf $(MESA_LIB)
	$(ROOT) rm -rf $(SDL2_DIR)
	$(ROOT) rm -rf $(SDL2_TTF_DIR)
	$(ROOT) rm -rf $(FREETYPE_DIR)
	$(ROOT) rm -rf $(LIB_DIR)/installed

clean: $(CLEAN_LIB)
	@printf ${CYAN}"[INFO] Removing objs\n"${RESET}
	@make clean -C libft
	rm -rf $(OBJ_ALL_DIR)
	rm -rf $(OBJ_EDITOR_DIR)
	rm -rf $(OBJ_GAME_DIR)

fclean:
	@make fclean -C libft
	@printf ${CYAN}"[INFO] Removing objs\n"${RESET}
	rm -rf $(OBJ_ALL_DIR)
	rm -rf $(OBJ_EDITOR_DIR)
	rm -rf $(OBJ_GAME_DIR)
	@printf ${CYAN}"[INFO] Removing $(GAME_DIR)/$(GAME_NAME)"
	@printf " and $(EDITOR_DIR)/$(EDITOR_NAME)\n"${RESET}
	rm -rf $(GAME_DIR)/$(GAME_NAME)
	rm -rf $(EDITOR_DIR)/$(EDITOR_NAME)

re: fclean all

death_race:
	@printf $(RED)"Une seule règle. Pas de règles.\n"

.PHONY: fclean all clean libft maps $(SDL_DEPENDENCIES)
