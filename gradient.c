/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gradient.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/18 21:58:18 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/03/19 15:04:17 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h" 

t_colour colour(BYTE r, BYTE g, BYTE b)
{
    t_colour c;
 
    c.r = r;
    c.g = g;
    c.b = b;
    return (c);
}

t_gradient *init_gradient(t_map *map)
{
	int i;
	t_gradient *gradient;
	t_range range;

	i = 0;
	gradient = NEW(t_gradient);
	range = get_range_of_map(map);
	gradient->max_z = range.max;
	gradient->min_z = range.min;
	gradient->max_color = colour(255,255,255);
	gradient->min_color = colour(255,0,0);
	return(gradient); 
}

float clamp(int min, int max, float z)
{
    if (z < min)
        return min;
    else if (z > max)
        return max;
    return (z);
}

t_colour calculate_colour(t_gradient *gradient, float z)

{
    // scale z to the range [0, 1]
    z = (z - gradient->min_z)/(gradient->max_z - gradient->min_z);
	// just to be safe
    z = clamp(0, 1, z);
    return (colour((char)(gradient->min_color.r * (1-z) + gradient->max_color.r * z),
	(char)(gradient->min_color.g * (1-z) + gradient->max_color.g * z),
	(char)(gradient->min_color.b * (1-z) + gradient->max_color.b * z)));
}