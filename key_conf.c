/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_conf.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/12 14:53:24 by fhignett       #+#    #+#                */
/*   Updated: 2019/03/19 15:30:57 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

int mouse_move(int x, int y, t_fdf *fdf)
{
	if (fdf->conf->rm_down == 1)
	{
		if (x >= fdf->conf->last_x)
			fdf->cam->yrot += 0.015;
		if (x < fdf->conf->last_x)
			fdf->cam->yrot -= 0.015;
		if (y >= fdf->conf->last_y)
			fdf->cam->xrot += 0.015;
		if (y < fdf->conf->last_y)
			fdf->cam->xrot -= 0.015;
	}
	fdf->conf->last_x = x;
	fdf->conf->last_y = y;
	return (0);
}

int		mouse_press(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 1)
		fdf->conf->rm_down = 1;
	if (button == 5)
		fdf->cam->zoom += 0.05 * fdf->cam->zoom;
	if (button == 4)
		fdf->cam->zoom -= 0.05 * fdf->cam->zoom;
	return (0);
}
int		mouse_release(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 1)
		fdf->conf->rm_down = 0;
	return (0);
}

int		close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	reset(t_fdf *fdf)
{
	fdf->conf->x = 0;
	fdf->conf->y = 0;
	fdf->conf->z = 0;
	fdf->cam->zoom = set_zoom(fdf->map);
	fdf->cam->xrot= 0;
	fdf->cam->yrot= 0;
	fdf->cam->zrot = 0;
}

int		key_press_conf(int key, t_fdf *fdf)
{
	if (key == 14)
		fdf->cam->zrot += 0.02;
	if (key == 12)
		fdf->cam->zrot -= 0.02;
	if (key == 24)
		fdf->conf->z += 0.02;
	if (key == 27)
		fdf->conf->z -= 0.02;
	if (key == 2)
		fdf->conf->x += 0.5;
	if (key == 0)
		fdf->conf->x -= 0.5;
	if (key == 1)
		fdf->conf->y += 0.5;
	if (key == 13)
		fdf->conf->y -= 0.5;
	if (key == 49)
		reset(fdf);
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

