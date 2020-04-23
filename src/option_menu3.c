#include "env.h"

int		return_button(t_env *env)
{
	env->return_button = new_image_button(ON_RELEASE, &return_button_func,
		env, env);
	env->return_button.pos =
		new_point(env->h_w - env->start_game_button.size_down.x / 2,
		(env->h_h - env->start_game_button.size_down.y / 2) / 2);
	return (0);
}

int		music_vol_up_button(t_env *env)
{
	env->music_vol_up = new_add_button(ON_RELEASE,
		&music_volume_up, env, env);
	env->music_vol_up.pos = new_point(env->h_w + env->h_w / 4,
		env->h_h + env->music_vol_up.size_down.y);
	return (0);	
}

int		music_vol_down_button(t_env *env)
{
	env->music_vol_down = new_minus_button(ON_RELEASE,
		&music_volume_down, env, env);
	env->music_vol_down.pos = new_point(env->h_w - env->h_w / 4,
		env->h_h + env->music_vol_down.size_down.y);
	return (0);	
}

int		sounds_vol_up_button(t_env *env)
{
	env->sounds_vol_up = new_add_button(ON_RELEASE,
		&sounds_volume_up, env, env);
	env->sounds_vol_up.pos = new_point(env->h_w + env->h_w / 4,
		env->h_h + env->h_h / 4 + env->sounds_vol_up.size_down.y);
	return (0);	
}

int		sounds_vol_down_button(t_env *env)
{
	env->sounds_vol_down = new_minus_button(ON_RELEASE,
		&sounds_volume_down, env, env);
	env->sounds_vol_down.pos = new_point(env->h_w - env->h_w / 4,
		env->h_h + env->h_h / 4 + env->sounds_vol_down.size_down.y);
	return (0);	
}
