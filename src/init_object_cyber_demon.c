#include "env.h"

void	init_object_cyber_demon(t_env *env)
{
	env->object_sprites[28].texture = 24;
	env->object_sprites[28].death_counterpart = 12;
	env->object_sprites[28].pursuit_sprite = 6;
	env->object_sprites[28].firing_sprite = 9;
	env->object_sprites[28].rest_sprite = 28;
	env->object_sprites[28].curr_sprite = 5;
	env->object_sprites[28].oriented = 0;
	env->object_sprites[28].nb_death_sprites = 8;
	env->object_sprites[28].start[0].x = 44;
	env->object_sprites[28].start[0].y = 33;
	env->object_sprites[28].end[0].x = 125;
	env->object_sprites[28].end[0].y = 140;
	env->object_sprites[28].size[0].x = 82;
	env->object_sprites[28].size[0].y = 108;
	env->object_sprites[28].reversed[0] = 0;
}
