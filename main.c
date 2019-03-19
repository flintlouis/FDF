/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/10 21:11:37 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/03/19 14:46:04 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

//ERRORS FIXEN

int		project(t_fdf *fdf)
{
	draw_grid(fdf);
	return (0);
}

void	init_fdf(char *file)
{
	t_fdf *fdf;

	fdf = NEW(t_fdf);
	fdf->mlx = mlx_init();
	fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FDF");
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel), &(fdf->size_line), &(fdf->endian));
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
	
	mlx_loop_hook(fdf->mlx, project, fdf);
	mlx_loop(fdf->mlx);
}

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putendl("usage: ./fdf file_name");
		return (0);
	}
	else
		init_fdf(argv[1]);
	return (0);
}