/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzmuda <bzmuda@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 11:50:30 by bzmuda            #+#    #+#             */
/*   Updated: 2018/01/02 12:51:14 by bzmuda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

/*
**	Store line by line chars in the map.
*/

void	store_line_to_tab(t_e *e, char *line)
{
	if (!(e->tab[e->i] = (char *)malloc(sizeof(char) * e->east + 1)))
		exiterror();
	ft_strcpy(e->tab[e->i], line);
	free(line);
}

/*
**	Store all infos of the file, into a char map.
*/

void	store_tab(int fd, t_e *e)
{
	char *line;

	line = NULL;
	if (!(e->tab = (char **)malloc(sizeof(char *) * e->south + 1)))
		exiterror();
	while ((get_next_line(fd, &line)) == 1)
	{
		store_line_to_tab(e, line);
		e->i++;
	}
	free(line);
	if (border_check(e) == -1)
		exiterror();
}

/*
**	Checks if the the quadragle is delimited by 1's.
**	Returns an error if not.
*/

int		border_check(t_e *e)
{
	e->bou = 0;
	while (e->bou <= e->east)
	{
		if (e->tab[0][e->bou] != '1')
			return (-1);
		e->bou++;
	}
	e->bou = 1;
	while (e->bou <= (e->south - 1))
	{
		if (e->tab[e->bou][0] != '1')
			return (-1);
		if (e->tab[e->bou][e->east] != '1')
			return (-1);
		e->bou++;
	}
	e->bou = 0;
	while (e->bou <= e->east)
	{
		if (e->tab[e->south][e->bou] != '1')
			return (-1);
		e->bou++;
	}
	return (1);
}
