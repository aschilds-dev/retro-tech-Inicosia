/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_mouseup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 14:44:06 by lnicosia          #+#    #+#             */
/*   Updated: 2019/11/06 18:18:53 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int	editor_mouseup(t_env *env)
{
	if (env->editor.in_game && env->sdl.event.button.button == SDL_BUTTON_LEFT)
		env->editor.select = 1;
	if (env->confirmation_box.state)
		confirmation_box_keyup(&env->confirmation_box, env);
	//if (env->sdl.mx > 
	button_mouseup(&env->test_button, env);
	return (0);
}
