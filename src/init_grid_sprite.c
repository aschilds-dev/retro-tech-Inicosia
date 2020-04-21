#include "env.h"

void	init_grid_sprite(t_env *env)
{
	env->object_sprites[23].texture = 31;
	env->object_sprites[23].death_counterpart = 0;
	env->object_sprites[23].pursuit_sprite = 0;
	env->object_sprites[23].rest_sprite = 23;
	env->object_sprites[23].curr_sprite = 0;
	env->object_sprites[23].oriented = 0;
	env->object_sprites[23].nb_death_sprites = 0;
	env->object_sprites[23].start[0].x = 0;
	env->object_sprites[23].start[0].y = 0;
	env->object_sprites[23].end[0].x = 128;
	env->object_sprites[23].end[0].y = 256;
	env->object_sprites[23].size[0].x = 128;
	env->object_sprites[23].size[0].y = 256;
	env->object_sprites[23].reversed[0] = 0;
}
