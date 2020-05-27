/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 11:53:54 by gaerhard          #+#    #+#             */
/*   Updated: 2020/05/20 16:22:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int		play_sound(t_env *env, FMOD_CHANNEL **chan, FMOD_SOUND *sound, float v)
{
	FMOD_BOOL	is_playing;
	int			res;

	if (v != 0 && (FMOD_Channel_IsPlaying(*chan, &is_playing) != FMOD_OK
		|| is_playing == 0))
	{
		if ((res = FMOD_System_PlaySound(env->sound.system, sound, 0, 0,
			chan)) != FMOD_OK)
			return (custom_error("FMOD_System_PlaySound error %d\n", res));
		if ((res = FMOD_Channel_SetVolume(*chan, v)) != FMOD_OK)
			return (custom_error("FMOD_Channel_SetVolume error %d\n", res));
	}
	return (0);
}

int		play_music(t_env *env, FMOD_CHANNEL **chan, FMOD_SOUND *music, float v)
{
	int			res;
	FMOD_BOOL	is_playing;

	if (!v)
		return (0);
	if (FMOD_Channel_IsPlaying(*chan, &is_playing) == FMOD_OK
		&& is_playing == 1)
	{
		if ((res = FMOD_Channel_SetPaused(*chan, 1)) != FMOD_OK)
			return (custom_error("FMOD_Channel_SetPaused 2 error %d\n", res));
	}
	if ((res = FMOD_System_PlaySound(env->sound.system, music, 0, 0, chan))
		!= FMOD_OK)
		return (custom_error("FMOD_System_PlaySound error %d\n", res));
	if ((res = FMOD_Channel_SetVolume(*chan, v)) != FMOD_OK)
		return (custom_error("FMOD_Channel_SetVolume error %d\n", res));
	if ((res = FMOD_Channel_SetPaused(*chan, 0)) != FMOD_OK)
		return (custom_error("FMOD_Channel_SetPaused 2 error %d\n", res));
	return (0);
}
