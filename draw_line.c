/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/10 21:10:26 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/11/29 11:53:10 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "minilibx_macos/mlx.h"

static	void	put_pixel(int x, int y, t_fdf *fdf, t_colour colour)
{
	int i;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		i = (x * fdf->bits_per_pixel / 8) + (y * fdf->size_line);
		fdf->data_addr[i] = colour.b;
		i++;
		fdf->data_addr[i] = colour.g;
		i++;
		fdf->data_addr[i] = colour.r;
	}
}

/*
** X++
*/

static	void	plot_line1(t_fdf *fdf, t_point a, t_point b)
{
	int		dxy[2];
	int		d;
	int		sy;
	float	dz;
	float	z;

	dxy[0] = b.x - a.x;
	dxy[1] = b.y - a.y;
	dz = ((float)b.ogz - a.ogz) / dxy[0];
	z = a.ogz;
	d = 2 * dxy[1] - dxy[0];
	sy = dxy[1] >= 0 ? 1 : -1;
	dxy[1] = ABS(dxy[1]);
	while (a.x <= b.x)
	{
		put_pixel(a.x, a.y, fdf, calculate_colour(fdf->gradient, z));
		if (d > 0)
		{
			a.y += sy;
			d -= 2 * dxy[0];
		}
		d += 2 * dxy[1];
		a.x++;
		z += dz;
	}
}

/*
** Y++
*/

static	void	plot_line2(t_fdf *fdf, t_point a, t_point b)
{
	int		dxy[2];
	int		d;
	int		sx;
	float	dz;
	float	z;

	dxy[0] = b.x - a.x;
	dxy[1] = b.y - a.y;
	dz = ((float)b.ogz - a.ogz) / dxy[1];
	z = a.ogz;
	d = 2 * dxy[0] - dxy[1];
	sx = dxy[0] >= 0 ? 1 : -1;
	dxy[0] = ABS(dxy[0]);
	while (a.y <= b.y)
	{
		put_pixel(a.x, a.y, fdf, calculate_colour(fdf->gradient, z));
		if (d > 0)
		{
			a.x += sx;
			d -= 2 * dxy[1];
		}
		d += 2 * dxy[0];
		a.y++;
		z += dz;
	}
}

/*
** Makes sure with the first 'if' statements which delta is bigger
** between X and Y and with the second 'if' statements it checks
** that the delta between a & b never a negative number is
*/

static	void	draw_line(t_fdf *fdf, t_point a, t_point b)
{
	int dx;
	int dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (ABS(dx) >= ABS(dy))
	{
		if (dx > 0)
			plot_line1(fdf, a, b);
		else
			plot_line1(fdf, b, a);
	}
	else
	{
		if (dy > 0)
			plot_line2(fdf, a, b);
		else
			plot_line2(fdf, b, a);
	}
}

void			calculate_line(t_fdf *fdf, t_point a, int i, int j)
{
	t_point	b;

	if (j < fdf->map->width - 1)
	{
		b = point(a.x + 1, a.y, fdf->map->map[i][j + 1]);
		draw_line(fdf, rot_matrix(a, fdf), rot_matrix(b, fdf));
	}
	if (i < fdf->map->height - 1)
	{
		b = point(a.x, a.y + 1, fdf->map->map[i + 1][j]);
		draw_line(fdf, rot_matrix(a, fdf), rot_matrix(b, fdf));
	}
}
