/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gradient.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/18 21:58:18 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/03/21 16:54:35 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static	t_colour	colour(t_byte r, t_byte g, t_byte b)
{
	t_colour c;

	c.r = r;
	c.g = g;
	c.b = b;
	return (c);
}

t_gradient			*init_gradient(t_map *map)
{
	int			i;
	t_gradient	*gradient;
	t_range		range;

	i = 0;
	gradient = NEW(t_gradient);
	range = get_range_of_map(map);
	gradient->max_z = range.max;
	gradient->middle_z = (int)round((range.max + range.min) / 2);
	gradient->min_z = range.min;
	gradient->max_colour = colour(255, 0, 0);
	gradient->middle_colour = colour(0, 255, 0);
	gradient->min_colour = colour(0, 0, 255);
	return (gradient);
}

static	float		clamp(int min, int max, float z)
{
	if (z < min)
		return (min);
	else if (z > max)
		return (max);
	return (z);
}

/*
** first: scale z to the range [0, 1]
** second: clamp to make sure it doesn't go beyond 0 or 1 (floats aren't safe)
** return: calculate how much r,g,b, for the z it's currently on
*/

t_colour			calculate_colour(t_gradient *gradient, float z)
{
	if (z < gradient->middle_z)
	{
		z = (z - gradient->min_z) / (gradient->middle_z - gradient->min_z);
		z = clamp(0, 1, z);
		return (colour((char)(gradient->min_colour.r * (1 - z)
		+ gradient->middle_colour.r * z),
		(char)(gradient->min_colour.g * (1 - z)
		+ gradient->middle_colour.g * z),
		(char)(gradient->min_colour.b * (1 - z)
		+ gradient->middle_colour.b * z)));
	}
	else
	{
		z = (z - gradient->middle_z) / (gradient->max_z - gradient->middle_z);
		z = clamp(0, 1, z);
		return (colour((char)(gradient->middle_colour.r * (1 - z)
		+ gradient->max_colour.r * z),
		(char)(gradient->middle_colour.g * (1 - z)
		+ gradient->max_colour.g * z),
		(char)(gradient->middle_colour.b * (1 - z)
		+ gradient->max_colour.b * z)));
	}
}
