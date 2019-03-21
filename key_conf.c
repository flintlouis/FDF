/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   key_conf.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/12 14:53:24 by fhignett       #+#    #+#                */
/*   Updated: 2019/03/21 18:16:23 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				mouse_move(int x, int y, t_fdf *fdf)
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

int				mouse_press(int button, int x, int y, t_fdf *fdf)
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

int				mouse_release(int button, int x, int y, t_fdf *fdf)
{
	(void)x;
	(void)y;
	if (button == 1)
		fdf->conf->rm_down = 0;
	return (0);
}

static	void	key_press_conf_xtra(int key, t_fdf *fdf)
{
	if (key == 124)
		fdf->cam->yrot += 0.02;
	if (key == 123)
		fdf->cam->yrot -= 0.02;
	if (key == 125)
		fdf->cam->xrot += 0.02;
	if (key == 126)
		fdf->cam->xrot -= 0.02;
}

int				key_press_conf(int key, t_fdf *fdf)
{
	if (key == 14)
		fdf->cam->zrot += 0.02;
	if (key == 12)
		fdf->cam->zrot -= 0.02;
	if (key == 24)
		fdf->conf->z += 0.02;
	if (key == 27)
		fdf->conf->z -= 0.02;
	if (key == 0)
		fdf->conf->x += 0.5;
	if (key == 2)
		fdf->conf->x -= 0.5;
	if (key == 13)
		fdf->conf->y += 0.5;
	if (key == 1)
		fdf->conf->y -= 0.5;
	if (key == 257)
		fdf->conf->shift = 1;
	key_press_conf_xtra(key, fdf);
	return (0);
}
