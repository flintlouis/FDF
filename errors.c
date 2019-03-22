/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   errors.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: fhignett <fhignett@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/03/22 16:27:21 by fhignett       #+#    #+#                */
/*   Updated: 2019/03/22 16:46:41 by fhignett      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int		errors(int error, char *str)
{
	if (error == 1)
	{
		error = open(str, O_RDONLY);
		close(error);
		if (error < 0)
			return (0);
	}
	else if (error == 2)
	{
		(void)str;
		ft_putendl("Found wrong line length. Exiting.");
		exit(0);
	}
	return (1);
}
