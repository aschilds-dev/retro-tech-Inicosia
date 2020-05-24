/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicosia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:50:28 by lnicosia          #+#    #+#             */
/*   Updated: 2020/04/29 15:14:15 by lnicosia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

unsigned int	blend_alpha(unsigned int src, unsigned int dest, uint8_t alpha)
{
	int	aalpha;

	aalpha = 256 - alpha;
	return (
		((aalpha * (src >> 16 & 0xFF) + alpha * (dest >> 16 & 0xFF)) / 256)
		<< 16
		| ((aalpha * (src >> 8 & 0xFF) + alpha * (dest >> 8 & 0xFF)) / 256)
		<< 8
		| ((aalpha * (src & 0xFF) + alpha * (dest & 0xFF)) / 256));
}

Uint32			apply_light_color(Uint32 src, Uint32 color, int intensity)
{
	int	aalpha;

	aalpha = 256 - intensity;
	src = ft_clamp((aalpha * (src >> 16 & 0xFF)
		+ intensity * (color >> 16 & 0xFF)) / 256, 0, 255) << 16
		| ft_clamp((aalpha * (src >> 8 & 0xFF)
		+ intensity * (color >> 8 & 0xFF)) / 256, 0, 255) << 8
		| ft_clamp((aalpha * (src & 0xFF)
		+ intensity * (color & 0xFF)) / 256, 0, 255);
	return (src);
}

Uint32			apply_light_brightness(Uint32 src, int brightness)
{
	src = ft_clamp(((brightness + 256) * (src >> 16 & 0xFF)) / 256, 0, 255)
	<< 16 | ft_clamp(((brightness + 256) * (src >> 8 & 0xFF)) / 256, 0, 255)
	<< 8 | ft_clamp(((brightness + 256) * (src & 0xFF)) / 256, 0, 255);
	return (src);
}

Uint32			apply_light_both(Uint32 src, Uint32 color, int intensity,
		int brightness)
{
	src = apply_light_color(src, color, intensity);
	return (apply_light_brightness(src, brightness));
}
