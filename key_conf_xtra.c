/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_conf_xtra.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/21 14:37:18 by fhignett       #+#    #+#                */
/*   Updated: 2019/03/21 18:29:52 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

int				close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

static	void	iso(t_fdf *fdf)
{
	fdf->conf->x = 0;
	fdf->conf->y = 0;
	fdf->conf->z = 0;
	fdf->cam->xrot = -30 * (M_PI / 180);
	fdf->cam->yrot = 30 * (M_PI / 180);
	fdf->cam->zrot = -38 * (M_PI / 180);
	fdf->cam->zoom = set_zoom(fdf->map);
}

static	void	reset(t_fdf *fdf)
{
	fdf->conf->x = 0;
	fdf->conf->y = 0;
	fdf->conf->z = 0;
	fdf->cam->xrot = 0;
	fdf->cam->yrot = 0;
	fdf->cam->zrot = 0;
	fdf->cam->zoom = set_zoom(fdf->map);
}

int				key_release_conf(int key, t_fdf *fdf)
{
	(void)fdf;
	if (key == 53)
		close_window(fdf);
	if (key == 49 && fdf->conf->shift == 1)
	{
		if (key == 49)
			iso(fdf);
	}
	else if (key == 49 && fdf->conf->shift == 0)
		reset(fdf);
	if (key == 257)
		fdf->conf->shift = 0;
	return (0);
}
