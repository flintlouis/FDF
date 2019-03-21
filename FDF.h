/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/11 14:34:24 by fhignett       #+#    #+#                */
/*   Updated: 2019/03/21 18:17:07 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"

# define WIDTH 1000
# define HEIGHT 1000
# define NEW(x) (x*)ft_memalloc(sizeof(x))

typedef unsigned char	t_byte;

typedef struct			s_range
{
	int					min;
	int					middle;
	int					max;
}						t_range;

typedef struct			s_colour
{
	t_byte				r;
	t_byte				g;
	t_byte				b;
}						t_colour;

typedef	struct			s_gradient
{
	int					min_z;
	int					middle_z;
	int					max_z;
	t_colour			min_colour;
	t_colour			middle_colour;
	t_colour			max_colour;
}						t_gradient;

typedef struct			s_cam
{
	double				zoom;
	double				xrot;
	double				yrot;
	double				zrot;
}						t_cam;

typedef	struct			s_point
{
	int					x;
	int					y;
	int					z;
	int					ogz;
}						t_point;

typedef struct			s_conf
{
	double				z;
	double				x;
	double				y;
	int					shift;
	int					last_x;
	int					last_y;
	int					rm_down;
}						t_conf;

typedef struct			s_map
{
	int					width;
	int					height;
	int					**map;
}						t_map;

typedef struct			s_fdf
{
	void				*mlx;
	void				*win;
	void				*img;
	char				*data_addr;
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	t_cam				*cam;
	t_map				*map;
	t_gradient			*gradient;
	t_conf				*conf;
}						t_fdf;

void					calculate_line(t_fdf *fdf, t_point a, int i, int j);

double					set_zoom(t_map *map);

int						close_window(void *param);
int						key_release_conf(int key, t_fdf *fdf);
int						key_press_conf(int key, t_fdf *fdf);
int						mouse_move(int x, int y, t_fdf *fdf);
int						mouse_release(int button, int x, int y, t_fdf *fdf);
int						mouse_press(int button, int x, int y, t_fdf *fdf);

t_map					*get_map(char *file);
t_cam					*init_cam(t_fdf *fdf);
t_point					rot_matrix(t_point point, t_fdf *fdf);
t_point					point(int x, int y, int z);
t_range					get_range_of_map(t_map *map);
t_gradient				*init_gradient(t_map *map);
t_colour				calculate_colour(t_gradient *gradient, float z);

#endif
