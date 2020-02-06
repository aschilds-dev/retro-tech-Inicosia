/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_panel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 12:05:33 by lnicosia          #+#    #+#             */
/*   Updated: 2020/02/06 21:03:52 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	draw_target_tab(t_env *env)
{
	SDL_Surface	*img;

	if (env->editor.event_panel.target_tab.anim_state == HOVER)
		img = env->ui_textures[TARGET_ICON_HOVER].surface;
	else if (env->editor.event_panel.target_tab.state == DOWN
		|| env->editor.event_panel.target_tab.anim_state == PRESSED)
		img = env->ui_textures[TARGET_ICON_DOWN].surface;
	else
		img = env->ui_textures[TARGET_ICON].surface;
	draw_button(env, env->editor.event_panel.target_tab, NULL);
	apply_surface(img,
	new_point(env->editor.event_panel.pos.y + 100 + (50 - img->h / 2),
	env->editor.event_panel.pos.x + (50 - img->h / 2)),
	new_point(img->w, img->h), env);
}

void	draw_action_tab(t_env *env)
{
	SDL_Surface	*img;

	if (env->editor.event_panel.action_tab.anim_state == HOVER)
		img = env->ui_textures[ACTION_ICON_HOVER].surface;
	else if (env->editor.event_panel.action_tab.state == DOWN
		|| env->editor.event_panel.action_tab.anim_state == PRESSED)
		img = env->ui_textures[ACTION_ICON_DOWN].surface;
	else
		img = env->ui_textures[ACTION_ICON].surface;
	draw_button(env, env->editor.event_panel.action_tab, NULL);
	apply_surface(img,
	new_point(env->editor.event_panel.pos.y + 200 + (50 - img->h / 2),
	env->editor.event_panel.pos.x + (50 - img->h / 2)),
	new_point(img->w, img->h), env);
}

void	draw_launch_conditions_tab(t_env *env)
{
	SDL_Surface	*img;

	if (env->editor.event_panel.launch_conditions_tab.anim_state == HOVER)
		img = env->ui_textures[CONDITION_ICON_HOVER].surface;
	else if (env->editor.event_panel.launch_conditions_tab.state == DOWN
		|| env->editor.event_panel.launch_conditions_tab.anim_state == PRESSED)
		img = env->ui_textures[CONDITION_ICON_DOWN].surface;
	else
		img = env->ui_textures[CONDITION_ICON].surface;
	draw_button(env, env->editor.event_panel.launch_conditions_tab, NULL);
	apply_surface(img,
	new_point(env->editor.event_panel.pos.y + 300 + (50 - img->h / 2),
	env->editor.event_panel.pos.x + (50 - img->h / 2)),
	new_point(img->w, img->h), env);
}

void	draw_exec_conditions_tab(t_env *env)
{
	SDL_Surface	*img;

	if (env->editor.event_panel.exec_conditions_tab.anim_state == HOVER)
		img = env->ui_textures[CONDITION_ICON_HOVER].surface;
	else if (env->editor.event_panel.exec_conditions_tab.state == DOWN
		|| env->editor.event_panel.exec_conditions_tab.anim_state == PRESSED)
		img = env->ui_textures[CONDITION_ICON_DOWN].surface;
	else
		img = env->ui_textures[CONDITION_ICON].surface;
	draw_button(env, env->editor.event_panel.exec_conditions_tab, NULL);
	apply_surface(img,
	new_point(env->editor.event_panel.pos.y + 400 + (50 - img->h / 2),
	env->editor.event_panel.pos.x + (50 - img->h / 2)),
	new_point(img->w, img->h), env);
}

int		draw_event_panel(t_env *env)
{
	t_point		text_size;

	// Ecran de debbug/placement
	draw_rectangle_alpha(env, new_rectangle(0xdcdde1, 0xdcdde1, 1, 0),
	env->editor.event_panel.pos, env->editor.event_panel.size);

	// Bande du haut
	draw_rectangle_alpha(env, new_rectangle(0xFFf1f2f3, 0xFFf1f2f3, 1, 0),
	env->editor.event_panel.pos, new_point(env->editor.event_panel.size.x,
	env->editor.event_panel.size.y / 5 - 2));

	// Background
	draw_rectangle_alpha(env, new_rectangle(0xe3e4e8, 0xe3e4e8 + 100, 1, 0),
	new_point(env->editor.event_panel.pos.x + 100,
	env->editor.event_panel.pos.y + 100),
	new_point(env->editor.event_panel.size.x -
	env->editor.event_panel.size.y / 5,
	env->editor.event_panel.size.y - env->editor.event_panel.size.y / 5));

	// Text
	//ft_snprintf(env->snprintf, SNPRINTF_SIZE, "Events");
	TTF_SizeText(env->sdl.fonts.lato_black50, "Events", &text_size.x, &text_size.y);
	print_text(new_point(env->editor.event_panel.pos.y + 17,
	env->editor.event_panel.pos.x + 110),
	new_printable_text("Events", env->sdl.fonts.lato_black50, 0x333333FF, 0), env);

	apply_surface(env->ui_textures[EVENT_ICON].surface,
	new_point(env->editor.event_panel.pos.y +
	(50 - env->ui_textures[EVENT_ICON].surface->h / 2),
	env->editor.event_panel.pos.x +
	(50 - env->ui_textures[EVENT_ICON].surface->h / 2)),
	new_point(env->ui_textures[EVENT_ICON].surface->w,
	env->ui_textures[EVENT_ICON].surface->h), env);

	draw_target_tab(env);
	draw_action_tab(env);
	draw_launch_conditions_tab(env);
	draw_exec_conditions_tab(env);

	
	return (0);
}
