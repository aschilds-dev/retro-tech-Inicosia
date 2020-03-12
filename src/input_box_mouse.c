#include "env.h"

/*
**	Moves the cursor according to the click
*/

int	input_box_mouse(t_input_box *box, t_point pos, char *str, t_env *env)
{
	int	i;
	char	*sub;
	t_point	size;
	t_point	size2;

	(void)env;
	i = 0;
	size = new_point(0, 0);
	while (str[i])
	{
		if (!(sub = ft_strsub(str, 0, i + 1)))
			return (-1);
		TTF_SizeText(box->font, sub, &size2.x, &size2.y);
		if (sub)
			ft_strdel(&sub);
		if (env->sdl.mx < pos.y + size2.x)
		{
			if ((pos.y + size2.x) - env->sdl.mx
				> env->sdl.mx - (pos.y + size.x))
				box->cursor = i + box->count;
			else
				box->cursor = i + 1 + box->count;
			if (!box->selecting)
			{
				box->select_start = box->cursor;
				box->selecting = 1;
			}
			box->select_end = box->cursor;
			return (0);
		}
		size = size2;
		i++;
	}
	box->cursor = ft_strlen(str) + box->count;
	if (!box->selecting)
	{
		box->select_end = box->cursor;
		box->select_start = box->cursor;
	}
	return (0);
}
