/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_map.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/10 21:12:50 by FlintLouis     #+#    #+#                */
/*   Updated: 2019/03/19 13:49:59 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "FDF.h"

void		free_tab(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
    free(tab[i]);
	free(tab);
}

int			map_width(char *line)
{
	char **tab;
	int width;

	width = 0;
	tab = ft_strsplit(line, ' ');
	while (*tab)
	{
		width++;
		tab++;
	}
	return(width);
}

void		set_map_size(t_map **map, char *file)
{
	int fd;
	int width;
	char *line;
	
	fd = open(file, O_RDONLY);
	width = 0;
	while (ft_get_next_line(fd, &line))
	{
		width = map_width(line);
		if ((*map)->width == 0)
			(*map)->width = width;
		else if ((*map)->width != width)
			exit(1);
		(*map)->height++;
		free(line);
	}
	close(fd);
}

t_map		*get_map(char *file)
{
	int fd;
	int x;
	int y;
	char **tab;
	char *line;
	t_map *map;

	y = 0;
	map = NEW(t_map);
	set_map_size(&map, file);
	fd = open(file, O_RDONLY);
	map->map = (int**)ft_memalloc(sizeof(int*) * map->height);
	while (ft_get_next_line(fd, &line))
	{
		tab = ft_strsplit(line, ' ');
		map->map[y] = (int*)ft_memalloc(sizeof(int) * map->width);
		x = 0;
		while (tab[x])
		{
			map->map[y][x] = ft_atoi(tab[x]);
			x++;
		}
		y++;
		free(line);
	}
	close(fd);
	free_tab(tab);
	return (map);
}

t_range get_range_of_map(t_map *map)
{
	t_range range;

	range.min = 2147483647;
	range.max = -2147483648;

	int x = 0;
	int y = 0;
	int z;

	while (x < map->height)
	{
		while (y < map->width)
		{
			z = map->map[x][y];

			if (z < range.min)
				range.min = z;
			if (z > range.max)
				range.max = z;
			y++;
		}
		y = 0;
		x++;
	}
	
	return range;
}