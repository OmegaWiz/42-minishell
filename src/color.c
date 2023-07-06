/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkaiyawo <kkaiyawo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 09:25:39 by kkaiyawo          #+#    #+#             */
/*   Updated: 2023/07/06 17:00:58 by kkaiyawo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	color2int(int r, int g, int b)
{
	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;
	return (r << 16 | g << 8 | b);
}

int	get_color(t_obj *obj)
{
	if (obj->type == SPHERE)
	{
		t_sphere *sphere = (t_sphere *) obj->obj;
		return (sphere->color);
	}
	else if (obj->type == PLANE)
	{
		t_plane *plane = (t_plane *) obj->obj;
		return (plane->color);
	}
	return (0);
}

int	color_scale(int color, double scale)
{
	int r;
	int g;
	int b;

	r = (color >> 16) & 0xFF;
	g = (color >> 8) & 0xFF;
	b = color & 0xFF;
	r = floor(r * scale);
	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;
	g = floor(g * scale);
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;
	b = floor(b * scale);
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;
	return (color2int(r, g, b));
}

int	color_add(int color1, int color2)
{
	int r;
	int g;
	int b;

	r = ((color1 >> 16) & 0xFF) + ((color2 >> 16) & 0xFF);
	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;
	g = ((color1 >> 8) & 0xFF) + ((color2 >> 8) & 0xFF);
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;
	b = (color1 & 0xFF) + (color2 & 0xFF);
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;
	return (color2int(r, g, b));
}

int	color_mult(int color1, int color2)
{
	int r;
	int g;
	int b;

	r = ((color1 >> 16) & 0xFF) * ((color2 >> 16) & 0xFF) / 255.0f;
	if (r > 255)
		r = 255;
	else if (r < 0)
		r = 0;
	g = ((color1 >> 8) & 0xFF) * ((color2 >> 8) & 0xFF) / 255.0f;
	if (g > 255)
		g = 255;
	else if (g < 0)
		g = 0;
	b = (color1 & 0xFF) * (color2 & 0xFF) / 255.0f;
	if (b > 255)
		b = 255;
	else if (b < 0)
		b = 0;
	return (color2int(r, g, b));
}
