/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gaerhard <gaerhard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 11:56:46 by sipatry           #+#    #+#             */
/*   Updated: 2020/05/14 19:19:32 by gaerhard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "collision.h"
#include "parser.h"
#include <math.h>

int		init_game5(t_env *env)
{
	ft_printf("Starting music.. \n");
	if (play_music(env, &env->sound.music_chan,
		env->sound.musics[env->sound.ambient_music].music,
		env->sound.music_vol))
		return (crash("Could not launch main music\n", env));
	ft_printf("Launching game loop..\n");
	if (init_camera(&env->player.camera, env))
		return (crash("Could not init fixed camera\n", env));
	if (init_camera(&env->fixed_camera, env))
		return (crash("Could not init fixed camera\n", env));
	if (init_skybox(env))
		return (crash("Could not init skybox\n", env));
	if (find_dialog_box_max_char(env))
		return (crash("Could not find dialog box maximum chars\n", env));
	env->fixed_camera.pos = new_v3(3, 3, 7);
	env->fixed_camera.angle = 45 * CONVERT_RADIANS;
	env->fixed_camera.angle_cos = cos(env->fixed_camera.angle);
	env->fixed_camera.angle_sin = sin(env->fixed_camera.angle);
	env->fixed_camera.angle_z = 10 * CONVERT_RADIANS;
	env->fixed_camera.angle_z_cos = cos(env->fixed_camera.angle_z);
	env->fixed_camera.angle_z_sin = sin(env->fixed_camera.angle_z);
	update_camera_position(&env->fixed_camera);
	env->confirmation_box.font = env->sdl.fonts.lato20;
	return (init_game6(env));
}

int		init_game4(t_env *env, int i)
{
	while (i < env->nb_objects)
	{
		env->objects[i].exists = 1;
		i++;
	}
	i = -1;
	while (++i < env->nb_enemies)
	{
		env->enemies[i].exists = 1;
		env->enemies[i].health = env->enemies[i].map_hp * env->difficulty;
	}
	view(env);
	update_camera_position(&env->player.camera);
	if (SDL_SetRelativeMouseMode(SDL_TRUE))
		custom_error("Could not set relative mouse mode\n");
	init_animations(env);
	init_weapons(env);
	return (init_game5(env));
}

int		init_game3(t_env *env, char **av)
{
	if (!(env->save_file = ft_strdup(av[1])))
		return (crash("Could not malloc map name", env));
	if (valid_map(env))
		return (crash("Invalid map!\n", env));
	precompute_slopes(env);
	update_player_z(env);
	if (init_textures(env))
		return (crash("Could not load textures\n", env));
	if (generate_mipmaps(env))
		return (crash("Could not generate mipmaps\n", env));
	if (init_mipmap_arrays(env))
		return (crash("Could not init sectors map arrays\n", env));
	if (init_audio(env))
		return (crash("Could not load sound\n", env));
	if (init_ttf(env))
		return (crash("Could not load fonts\n", env));
	if (!(env->sector_list = (int *)ft_memalloc(sizeof(int) * env->nb_sectors)))
		return (crash("Could not allocate sector list\n", env));
	return (init_game4(env, 0));
}

int		init_game2(char **av, t_env *env)
{
	init_player(env);
	if (init_screen_size(env))
		return (crash("Could not initialize screen sizes\n", env));
	init_options(env);
	init_keys(env);
	init_inputs(env);
	init_selection_data(env);
	if (!(env->snprintf = ft_strnew(SNPRINTF_SIZE)))
		return (crash("Could not malloc snprintf string\n", env));
	if (init_sdl(env))
		return (crash("Coulnt not initialize SDL\n", env));
	if (check_resources(env))
		return (crash("Could not check resources\n", env));
	if (init_object_sprites(env))
		return (crash("Could not load object sprites\n", env));
	if (init_enemy_sprites(env))
		return (crash("Could not load enemy sprites\n", env));
	ft_printf("Parsing map \"%s\"..\n", av[1]);
	if (parse_map(av[1], env))
	{
		if (close(env->parser.fd))
			return (crash("Could not close the map file\n", env));
		return (crash("Error while parsing the map\n", env));
	}
	return (init_game3(env, av));
}

int		init_game(int ac, char **av)
{
	t_env	env;

	if (ac < 2)
		return (custom_error("No map file.\n"));
	ft_bzero(&env, sizeof(t_env));
	env.objects_sprites_start = MAX_ENEMIES;
	env.wall_sprites_start = MAX_ENEMIES + NB_OBJECTS_SPRITES;
	env.editor_start = env.wall_sprites_start + NB_WALL_SPRITES;
	env.hud_start = env.editor_start + NB_HUD_SPRITES;
	env.nprocs = ft_min(sysconf(_SC_NPROCESSORS_CONF), MAX_PROC);
	ft_printf("nprocs = %d\n", env.nprocs);
	env.menu = 1;
	env.difficulty = 1;
	if (ac == 3)
	{
		env.menu = 0;
		env.in_game = 1;
	}
	else if (ac == 2)
		env.in_game = 0;
	env.menu_select = 1;
	env.running = 1;
	env.editor.player_exist = 1;
	env.playing = 1;
	return (init_game2(av, &env));
}
