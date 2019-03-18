/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   angles.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/12 18:36:24 by fhignett       #+#    #+#                */
/*   Updated: 2019/03/15 12:25:27 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void		x_rot(t_point *point, double angle)
{
	int y;

	y = point->y;
	point->y = y * cos(angle) + point->z * sin(angle);
	point->z = -y * sin(angle) + point->z * cos(angle);
}

void		y_rot(t_point *point, double angle)
{
	int x;

	x = point->x;
	point->x = x * cos(angle) + point->z * sin(angle);
	point->z = -x * sin(angle) + point->z * cos(angle);
}

void		z_rot(t_point *point, double angle)
{
	int x;
	
	x = point->x;
	point->x = x * cos(angle) - point->y * sin(angle);
	point->y = x * sin(angle) + point->y * cos(angle);
}

t_point		rot_matrix(t_point pixel, t_fdf *fdf)
{
	//makes sure that the amount of pixels inbetween is correct
	pixel.x *= fdf->cam->zoom;
	pixel.y *= fdf->cam->zoom;
	pixel.z *= fdf->cam->zoom + (fdf->map->z * fdf->cam->zoom);
	
	//takes teh centre of the image
	pixel.x -= (fdf->map->width / 2) * fdf->cam->zoom;
	pixel.y -= (fdf->map->height / 2) * fdf->cam->zoom;
	
	//calc the rotations
	x_rot(&pixel, fdf->cam->xrot);
	y_rot(&pixel, fdf->cam->yrot);
	z_rot(&pixel, fdf->cam->zrot);
	
	//puts the image in teh centre of the window
	pixel.x += (WIDTH / 2);
	pixel.y += (HEIGHT / 2);
	return (pixel);
}