/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/10 21:11:37 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/03/22 18:30:28 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
** ERRORS FIXEN
*/

#include "fdf.h"
#include <stdlib.h>
#include "minilibx_macos/mlx.h"

t_point			point(int x, int y, int z)
{
	t_point p;

	p.x = x;
	p.y = y;
	p.z = z;
	p.ogz = z;
	return (p);
}

/*
** bzero cleans the screen
*/

static	int		draw_grid(t_fdf *fdf)
{
	int		i;
	int		j;
	t_point	a;

	ft_bzero(fdf->data_addr, HEIGHT * WIDTH * (fdf->bits_per_pixel / 8));
	i = 0;
	while (i < fdf->map->height)
	{
		j = 0;
		a = point(j, i, fdf->map->map[i][j]);
		while (j < fdf->map->width)
		{
			calculate_line(fdf, a, i, j);
			j++;
			a = point(j, i, fdf->map->map[i][j]);
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	return (0);
}

static	void	init_fdf(char *file)
{
	t_fdf *fdf;

	fdf = NEW(t_fdf);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel),
	&(fdf->size_line), &(fdf->endian));
	fdf->map = get_map(file);
	fdf->cam = init_cam(fdf);
	fdf->gradient = init_gradient(fdf->map);
	fdf->conf = NEW(t_conf);
	mlx_hook(fdf->win, 4, 1L << 2, mouse_press, fdf);
	mlx_hook(fdf->win, 5, 1L << 3, mouse_release, fdf);
	mlx_hook(fdf->win, 6, 1L << 6, mouse_move, fdf);
	mlx_hook(fdf->win, 2, 1L << 0, key_press_conf, fdf);
	mlx_hook(fdf->win, 3, 1L << 1, key_release_conf, fdf);
	mlx_hook(fdf->win, 17, 1L << 17, close_window, NULL);
	mlx_loop_hook(fdf->mlx, draw_grid, fdf);
	mlx_loop(fdf->mlx);
}

int				main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl("Usage: ./fdf <filename> [ case_size z_size ]");
		return (0);
	}
	if (errors(1, argv[1]) == 1)
		init_fdf(argv[1]);
	else
	{
		ft_putstr("No file ");
		ft_putendl(argv[1]);
	}
	return (0);
}
