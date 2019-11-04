/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_box.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 09:59:10 by lnicosia          #+#    #+#             */
/*   Updated: 2019/11/04 17:08:49 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "env.h"
#include "input_box_utils.h"

int	init_input_box(t_input_box *box, t_env *env)
{
	box->state = 1;
	box->type = 2;
	box->del_delay = 100;
	box->input_delay = 100;
	box->move_cursor_delay = 100;
	box->cursor_delay = 500;
	box->cursor_state = 0;
	box->pos = new_point(env->h_w, env->h_h);
	box->font = env->sdl.fonts.playfair_display20;
	box->size = new_point(200, 30);
	return (0);
}

void	draw_input_box_content(t_input_box *box, t_env *env)
{
	t_printable_text	text;
	t_point			pos;

	if (!box->str || (box->str && box->str[0] == 0))
		return ;
	pos = new_point(box->pos.y, box->pos.x + 5);
	text = new_printable_text(box->str, box->font, 0x000000, box->size.x);
	print_text(pos, text, env);
}

void	draw_cursor(t_input_box *box, t_env *env)
{
	t_point	size;
	int	y;
	char	*sub;

	sub = ft_strsub(box->str, 0, box->cursor);
	TTF_SizeText(box->font, sub, &size.x, &size.y);
	y = box->pos.y + 3;
	while (y < box->pos.y + box->size.y - 3)
	{
		env->sdl.texture_pixels[box->pos.x + size.x + 5 + env->w * y] = 0xFF606060;
		y++;
	}
	ft_strdel(&sub);
}

void	draw_input_box(t_input_box *box, t_env *env)
{
	int	x;
	int	y;

	y = box->pos.y;
	while (y < box->pos.y + box->size.y)
	{
		x =  box->pos.x;
		while (x < box->pos.x + box->size.x)
		{
			if (x < box->pos.x + box->size.x - 3 && y < box->pos.y + box->size.y - 3
				&& x > box->pos.x + 3 && y > box->pos.y + 3)
				env->sdl.texture_pixels[x + env->w * y] = 0xFFFFFFFF;
			else
				env->sdl.texture_pixels[x + env->w * y] = 0xFF606060;
			x++;
		}
		y++;
	}
	draw_input_box_content(box, env);
	if (box->cursor_state
		|| env->inputs.right
		|| env->inputs.left)
		draw_cursor(box, env);
	if (SDL_GetTicks() - box->cursor_timer > box->cursor_delay)
	{
		box->cursor_timer = SDL_GetTicks();
		box->cursor_state = box->cursor_state ? 0 : 1;
	}
}

void	input_box_keys(t_input_box *box, t_env *env)
{
	if (env->inputs.enter
		|| env->sdl.event.key.keysym.sym == SDLK_KP_ENTER)
	{
		box->state = 0;
		env->inputs.enter = 0;
		if (box->str)
			ft_strdel(&box->str);
	}
	else if (env->inputs.backspace
		&& SDL_GetTicks() - box->del_timer > box->del_delay
		&& box->cursor > 0)
	{
		del_char(box, 0);
	}
	else if (env->inputs.del
		&& SDL_GetTicks() - box->del_timer > box->del_delay
		&& box->cursor < ft_strlen(box->str))
	{
		del_char(box, 1);
	}
	else if (env->sdl.event.key.keysym.sym == SDLK_LEFT
		&& box->cursor > 0 && SDL_GetTicks()
		- box->move_cursor_timer > box->move_cursor_delay)
	{
		box->cursor--;
		box->move_cursor_timer = SDL_GetTicks();
	}
	else if (env->sdl.event.key.keysym.sym == SDLK_RIGHT
		&& box->cursor < ft_strlen(box->str) && SDL_GetTicks()
		- box->move_cursor_timer > box->move_cursor_delay)
	{
		box->cursor++;
		box->move_cursor_timer = SDL_GetTicks();
	}
	else if (SDL_GetTicks() - box->input_timer > box->input_delay)
	{
		if (box->type == 0)
			parse_integer_input(box, env);
		else if (box->type == 1)
			parse_double_input(box, env);
		else if (box->type == 2)
			parse_str_input(box, env);
		box->input_timer = SDL_GetTicks();
	}
}
