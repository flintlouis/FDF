/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FDF.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/11 14:34:24 by fhignett       #+#    #+#                */
/*   Updated: 2019/03/18 11:16:15 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "minilibx_macos/mlx.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
////////////////////////////////////////////////////////////////////
#include <stdio.h> ///////////** delete me later **////////////////
//////////////////////////////////////////////////////////////////
# define WIDTH 1000
# define HEIGHT 1000
# define COLOUR 11207941

typedef struct	s_cam
{
	double zoom;
	double xrot;
	double yrot;
	double zrot;
}				t_cam;

typedef struct	s_point
{
	int x;
	int y;
	int z;
	int ogz; // colour
}				t_point;

typedef struct	s_map
{
	int width;
	int height;
	double z;
	int **map;
}				t_map;

typedef struct	s_fdf
{
	void *mlx;
	void *win;
	void *img; //*| USE FOR PUT IMAGE |*
	char *data_addr; //*| USE FOR PUT IMAGE |*
	int bits_per_pixel; //*| USE FOR PUT IMAGE |*
	int	size_line; //*| USE FOR PUT IMAGE |*
	int endian; //*| USE FOR PUT IMAGE |*
	t_cam *cam;
	t_map *map;
}				t_fdf;

void		draw_grid(t_fdf *fdf);
void		draw_line(t_fdf *fdf, t_point a, t_point b);

t_map		*get_map(char *file);
t_cam		*init_cam(t_fdf *fdf);
t_point		rot_matrix(t_point point, t_fdf *fdf);
t_point		point(int x, int y, int z);

int			close_window(void *param);
int			key_release_conf(int key, t_fdf *fdf);
int			key_press_conf(int key, t_fdf *fdf);

#endif