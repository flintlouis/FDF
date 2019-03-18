/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_cam.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/11 16:15:50 by fhignett       #+#    #+#                */
/*   Updated: 2019/03/15 12:28:14 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

double		set_zoom(t_map *map)
{
	int window;
	int map_size;
	int zoom;

	window = 0.5 * (HEIGHT * WIDTH);
	map_size = map->height * map->width;
	zoom = sqrt(((HEIGHT * WIDTH) - window) / map_size);
	return ((double)zoom);
}

t_cam		*init_cam(t_fdf *fdf)
{
	t_cam *cam;

	cam = (t_cam*)ft_memalloc(sizeof(t_cam));
	cam->zoom = set_zoom(fdf->map);
	return (cam);
}