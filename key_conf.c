/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_conf.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/12 14:53:24 by fhignett       #+#    #+#                */
/*   Updated: 2019/03/18 10:14:38 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

int		close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int		key_press_conf(int key, t_fdf *fdf)
{
	if (key == 13)
		fdf->cam->zoom += 0.05 * fdf->cam->zoom;
	if (key == 1)
		fdf->cam->zoom -= 0.05 * fdf->cam->zoom;
	if (key == 124)
		fdf->cam->yrot += 0.02;
	if (key == 123)
		fdf->cam->yrot -= 0.02;
	if (key == 125)
		fdf->cam->xrot += 0.02;
	if (key == 126)
		fdf->cam->xrot -= 0.02;
	if (key == 2)
		fdf->cam->zrot += 0.02;
	if (key == 0)
		fdf->cam->zrot -= 0.02;
	if (key == 24)
		fdf->map->z += 0.02;
	if (key == 27)
		fdf->map->z -= 0.02;
	// printf("key: * %d *\n", key);
	return (0);
}

int		key_release_conf(int key, t_fdf *fdf)
{
	(void)fdf;
	if (key == 53)
		close_window(fdf);
	return (0);
}

