/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcody <gcody@student.21school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 20:29:30 by gcody             #+#    #+#             */
/*   Updated: 2020/02/22 20:31:40 by gcody            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fillit.h"

int		print_error(char *str)
{
	ft_putendl(str);
	return (1);
}

int		print_map(t_tet *set, int side)
{
	char		map[16][18];
	int			i;

	i = -1;
	ft_memset(map, '.', sizeof(char) * 18 * 16);
	while (++i < side)
	{
		map[i][side] = '\n';
		map[i][side + 1] = '\0';
	}
	while (set->id)
	{
		i = -1;
		while (++i < set->lx * set->ly)
			if (set->shape & (1 << (7 - i)))
				map[set->y + i / set->lx][set->x + i % set->lx] = set->id;
		set++;
	}
	i = -1;
	while (++i < side)
		ft_putstr(map[i]);
	return (0);
}

int		main(int argc, char **argv)
{
	t_tet		set[27];
	uint16_t	map[16];
	int			fd;
	int			set_count;
	int			side;

	if (!(argc == 2))
		return (print_error("usage: ./fillit, file_name"));
	ft_bzero(set, sizeof(t_tet) * 27);
	if ((fd = open(argv[1], O_RDONLY)) <= 0)
		return (print_error("error"));
	if ((set_count = read_tetriminos(fd, set)) <= 0)
		return (print_error("error"));
	ft_bzero(map, sizeof(uint16_t) * 16);
	if (!(side = place_set(set, map, set_count)))
		return (print_error("error"));
	print_map(set, side);
	return (0);
}
