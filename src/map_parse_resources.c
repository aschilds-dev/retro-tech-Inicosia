/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse_resources.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sipatry <sipatry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 11:37:30 by sipatry           #+#    #+#             */
/*   Updated: 2020/03/11 13:16:52 by sipatry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "map_parser.h"
#include "parser.h"

int		parse_resources(t_env *env, t_map_parser *parser)
{
	if (map_parse_textures(env, parser))
		return (custom_error("Error while parsing map textures\n"));
	if (map_parse_sprites(env, parser))
		return (custom_error("Error while parsing map sprites\n"));
	if (map_parse_skyboxes(env, parser))
		return (custom_error("Error while parsing map skyboxes\n"));
	if (map_parse_hud(env, parser))
		return (custom_error("Error while parsing map hud\n"));
	if (check_textures(env))
		return (custom_error("Error while initializing textures from map\n"));
	if (map_parse_sounds(env, parser))
		return (custom_error("Error while parsing map sounds\n"));
	if (map_parse_fonts(env, parser))
		return (custom_error("Error while parsing map fonts\n"));
	if (check_fonts(env))
		return (custom_error("Error while initializing fonts from the map\n"));
	return (0);
}