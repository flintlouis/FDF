/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   xtra_key_conf.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/21 14:37:18 by fhignett       #+#    #+#                */
/*   Updated: 2019/03/21 14:46:58 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

int				close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

int				key_release_conf(int key, t_fdf *fdf)
{
	(void)fdf;
	if (key == 53)
		close_window(fdf);
	return (0);
}

void			reset(t_fdf *fdf)
{
	fdf->conf->x = 0;
	fdf->conf->y = 0;
	fdf->conf->z = 0;
	fdf->cam->xrot = 0;
	fdf->cam->yrot = 0;
	fdf->cam->zrot = 0;
	fdf->cam->zoom = set_zoom(fdf->map);
}
