/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_line.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/10 21:10:26 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/03/18 10:05:14 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

t_point point(int x, int y, int z)
{
	t_point p;

	p.x = x;
	p.y = y;
	p.z = z;
	return (p);
}

void		put_pixel(int x, int y, int colour, t_fdf *fdf) //*| USE FOR PUT IMAGE |*
{
	int i;

	// index for the data address
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT)
	{
		i = (x * fdf->bits_per_pixel / 8) + (y * fdf->size_line);
		fdf->data_addr[i] = colour;
		fdf->data_addr[++i] = colour >> 8;
		fdf->data_addr[++i] = colour >> 16;
	}
}


// X plus 1
void       plot_line1(t_fdf *fdf, t_point a, t_point b)
{
    int dx;
    int dy;
    int d;
    int sy;

    dx = b.x - a.x;
    dy = b.y - a.y;
    d = 2 * dy - dx;
    sy = dy >= 0 ? 1 : -1;
    dy = ABS(dy);
    while (a.x <= b.x)
    {
		put_pixel(a.x, a.y, COLOUR, fdf); //*| USE FOR PUT IMAGE |*
		//mlx_pixel_put(fdf->mlx, fdf->win, a.x, a.y, COLOUR); //*| USE FOR PUT WINDOW |*
        if (d > 0)
        {
        	a.y += sy;
        	d -= 2 * dx;
        }
        d += 2 * dy;
        a.x++;
    }
}
 
// Y plus 1
void       plot_line2(t_fdf *fdf, t_point a, t_point b)
{
    int dx;
    int dy;
    int d;
    int sx;

	dx = b.x - a.x;
    dy = b.y - a.y;
    d = 2 * dx - dy;
    sx = dx >= 0 ? 1 : -1;
    dx = ABS(dx);
    while (a.y <= b.y)
    {
		put_pixel(a.x, a.y, COLOUR, fdf); //*| USE FOR PUT IMAGE |*
		//mlx_pixel_put(fdf->mlx, fdf->win, a.x, a.y, COLOUR); //*| USE FOR PUT WINDOW |*
        if (d > 0)
        {
            a.x += sx;
            d -= 2 * dy;
        }
        d += 2 * dx;
        a.y++;
    }
}
 
void       draw_line(t_fdf *fdf, t_point a, t_point b)
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

void	draw_grid(t_fdf *fdf)
{
	int i;
	int j;
	t_point a;
	t_point b;

	// Cleans screen
	ft_bzero(fdf->data_addr, HEIGHT * WIDTH * (fdf->bits_per_pixel / 8)); //*| USE FOR PUT IMAGE |*
	////////////////

	// mlx_clear_window(fdf->mlx, fdf->win); //*| USE FOR PUT WINDOW |*

	i = 0;
	while (i < fdf->map->height)
	{
		j = 0;
		a = point(j, i, fdf->map->map[i][j]);
		while (j < fdf->map->width)
		{
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
			j++;
			a = point(j, i, fdf->map->map[i][j]);
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0); //*| USE FOR PUT IMAGE |*
}
