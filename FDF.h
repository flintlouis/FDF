/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   FDF.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/11 14:34:24 by fhignett       #+#    #+#                */
/*   Updated: 2019/03/19 15:47:28 by fhignett      ########   odam.nl         */
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

# define NEW(x) (x*)ft_memalloc(sizeof(x))

typedef unsigned char BYTE;

typedef struct s_range {
	int min;
	int middle;
	int max;
} t_range;

typedef struct s_colour 
{
    BYTE r;
    BYTE g;
    BYTE b;
} t_colour;

typedef struct s_gradient {

    int min_z;
    t_colour min_colour;
	int middle_z;
	t_colour middle_colour;
    int max_z;
    t_colour max_colour;
} t_gradient;

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
	int ogz;
}				t_point;

typedef struct	s_conf
{
	double z;
	double x;
	double y;
	int		last_x;
	int		last_y;
	int		rm_down;
}				t_conf;

typedef struct	s_map
{
	int width;
	int height;
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
	t_gradient *gradient;
	t_conf *conf;
}		t_fdf;

void		draw_grid(t_fdf *fdf);
void		draw_line(t_fdf *fdf, t_point a, t_point b);

t_map		*get_map(char *file);
t_cam		*init_cam(t_fdf *fdf);
t_point		rot_matrix(t_point point, t_fdf *fdf);
t_point		point(int x, int y, int z);

double		set_zoom(t_map *map);

int			close_window(void *param);
int			key_release_conf(int key, t_fdf *fdf);
int			key_press_conf(int key, t_fdf *fdf);
int			mouse_move(int x, int y, t_fdf *fdf);
int			mouse_release(int button, int x, int y, t_fdf *fdf);
int			mouse_press(int button, int x, int y, t_fdf *fdf);

t_range get_range_of_map(t_map *map);
t_gradient *init_gradient(t_map *map);
t_colour calculate_colour(t_gradient *gradient, float z);

#endif
