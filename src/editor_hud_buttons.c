/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_hud_buttons.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 13:52:01 by sipatry           #+#    #+#             */
/*   Updated: 2020/01/28 12:09:42 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		launch_game(void *target)
{
	t_env *env;
	char  *str;
	char  *tmp;

	env = (void*)target;
	tmp = NULL;
	tmp = env->save_file;
	env->editor.game = 0;
	str = ft_strdup("./doom ");
	env->save_file = ft_strdup("maps/tmp.map");
	save_map(env);
	str = (char*)ft_realloc(str, sizeof(char) * 7, sizeof(char) * ft_strlen(env->save_file));
	str = ft_strcat(str, env->save_file);
	ft_printf("starting game from editor:\n%s\n", str);  
	system (str);
	ft_strdel(&env->save_file);
	env->save_file = tmp;
	free(str);
	return (0);
}

int		change_mode(void *target)
{
    t_env *env;

    env = (t_env*)target;
	if (env->editor.in_game)
		going_in_2D_mode(env);
	else
		going_in_3D_mode(env);
	return (0);
}

int		save_button(void *target)
{
	t_env *env;

	env = (t_env*)target;
	if (!valid_map(env))
    {
    	SDL_SetRelativeMouseMode(0);
    	SDL_GetRelativeMouseState(&env->sdl.mouse_x, &env->sdl.mouse_y);
        new_input_box(&env->input_box, new_point(env->h_w, env->h_h),
        STRING, &env->save_file);
        env->inputs.s = 0;
        env->inputs.ctrl = 0;
    }
	return (0);
}

int		editor_mode_button(t_env *env)
{
	env->editor.change_mode = new_image_button(ON_RELEASE, &change_mode, env, env);
    env->editor.change_mode.img_up = env->sprite_textures[env->object_sprites[BUTTON_OFF].texture].surface;
	env->editor.change_mode.img_pressed = env->sprite_textures[env->object_sprites[BUTTON_OFF].texture].surface;
	env->editor.change_mode.img_down = env->sprite_textures[env->object_sprites[BUTTON_OFF].texture].surface;
    env->editor.change_mode.img_hover = env->sprite_textures[env->object_sprites[BUTTON_OFF].texture].surface;
    env->editor.change_mode.size_up = new_point(64, 64);
    env->editor.change_mode.size_down = new_point(env->editor.change_mode.img_down->w,
	env->editor.change_mode.img_down->h);
    env->editor.change_mode.size_hover = new_point(env->editor.change_mode.img_hover->w,
    env->editor.change_mode.img_hover->h);
    env->editor.change_mode.size_pressed = new_point(env->editor.change_mode.img_pressed->w,
    env->editor.change_mode.img_pressed->h);
	env->editor.change_mode.pos = new_point(0, 0);
	return (0);
}

int		editor_save_button(t_env *env)
{
	env->editor.save = new_image_button(ON_RELEASE, &save_button, env, env);
    env->editor.save.img_up = env->sprite_textures[env->object_sprites[BUTTON_OFF].texture].surface;
    env->editor.save.img_pressed = env->sprite_textures[env->object_sprites[BUTTON_OFF].texture].surface;
    env->editor.save.img_down = env->sprite_textures[env->object_sprites[BUTTON_OFF].texture].surface;
    env->editor.save.img_hover = env->sprite_textures[env->object_sprites[BUTTON_OFF].texture].surface;
    env->editor.save.size_up = new_point(64, 64);
    env->editor.save.size_down = new_point(env->editor.save.img_down->w,
    env->editor.save.img_down->h);
    env->editor.save.size_hover = new_point(env->editor.save.img_hover->w,
    env->editor.save.img_hover->h);
    env->editor.save.size_pressed = new_point(env->editor.save.img_pressed->w,
    env->editor.save.img_pressed->h);
    env->editor.save.pos = new_point(66, 0);
	return (0);
}

int		editor_launch_game(t_env *env)
{
	env->editor.launch_game = new_image_button(ON_RELEASE, &launch_game, env, env);
    env->editor.launch_game.img_up = env->sprite_textures[env->object_sprites[BUTTON_OFF].texture].surface;
    env->editor.launch_game.img_pressed = env->sprite_textures[env->object_sprites[BUTTON_OFF].texture].surface;
    env->editor.launch_game.img_down = env->sprite_textures[env->object_sprites[BUTTON_OFF].texture].surface;
    env->editor.launch_game.img_hover = env->sprite_textures[env->object_sprites[BUTTON_OFF].texture].surface;
    env->editor.launch_game.size_up = new_point(64, 64);
    env->editor.launch_game.size_down = new_point(env->editor.launch_game.img_down->w,
    env->editor.launch_game.img_down->h);
    env->editor.launch_game.size_hover = new_point(env->editor.launch_game.img_hover->w,
    env->editor.launch_game.img_hover->h);
    env->editor.launch_game.size_pressed = new_point(env->editor.launch_game.img_pressed->w,
    env->editor.launch_game.img_pressed->h);
    env->editor.launch_game.pos = new_point(132, 0);
	return (0);
}
