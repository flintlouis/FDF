/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   angles.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/12 18:36:24 by fhignett       #+#    #+#                */
/*   Updated: 2019/03/21 13:42:00 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static	void		x_rot(t_point *point, double angle)
{
	int y;

	y = point->y;
	point->y = y * cos(angle) + point->z * sin(angle);
	point->z = -y * sin(angle) + point->z * cos(angle);
}

static	void		y_rot(t_point *point, double angle)
{
	int x;

	x = point->x;
	point->x = x * cos(angle) + point->z * sin(angle);
	point->z = -x * sin(angle) + point->z * cos(angle);
}

static	void		z_rot(t_point *point, double angle)
{
	int x;

	x = point->x;
	point->x = x * cos(angle) - point->y * sin(angle);
	point->y = x * sin(angle) + point->y * cos(angle);
}

/*
** first: make sure that the amount of pixels inbetween is correct
** second: takes the centre of the image
** third: calculates the rotation
** fourth: puts the image in the centre of the window
*/

t_point				rot_matrix(t_point pixel, t_fdf *fdf)
{
	pixel.x *= fdf->cam->zoom;
	pixel.y *= fdf->cam->zoom;
	pixel.z *= fdf->cam->zoom + (fdf->conf->z * fdf->cam->zoom);
	pixel.x -= (fdf->map->width / 2) * fdf->cam->zoom;
	pixel.y -= (fdf->map->height / 2) * fdf->cam->zoom;
	x_rot(&pixel, fdf->cam->xrot);
	y_rot(&pixel, fdf->cam->yrot);
	z_rot(&pixel, fdf->cam->zrot);
	pixel.x += (WIDTH / 2) + fdf->conf->x * fdf->cam->zoom;
	pixel.y += (HEIGHT / 2) + fdf->conf->y * fdf->cam->zoom;
	return (pixel);
}
