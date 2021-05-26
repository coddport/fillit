/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcody <gcody@student.21school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 21:26:00 by gcody             #+#    #+#             */
/*   Updated: 2020/02/22 21:32:41 by gcody            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fillit.h"

int		check_space(t_tet *set, uint16_t *map, int side, uint16_t *tmap)
{
	uint8_t		mask;
	uint8_t		temp;
	int			i;

	mask = 0;
	temp = 0;
	if (set->x + set->lx > side || set->y + set->ly > side)
		return (0);
	i = -1;
	while (++i < set->ly)
	{
		temp = map[set->y + i] >> (16 - (set->lx + set->x));
		temp = (uint8_t)(temp << (8 - set->lx));
		mask |= temp >> (set->lx * i);
	}
	if (mask & set->shape)
		return (0);
	ft_memcpy(tmap, map, sizeof(uint16_t) * 16);
	i = -1;
	while (++i < set->ly)
	{
		temp = ((uint8_t)(set->shape << (set->lx * i))) >> (8 - set->lx);
		tmap[set->y + i] |= temp << (16 - (set->x + set->lx));
	}
	return (1);
}

int		check_piece(t_tet *set, uint16_t *map, int side)
{
	uint16_t	tmap[16];

	if (set->id == 0)
		return (1);
	set->y = -1;
	while (++set->y <= side - set->ly)
	{
		set->x = -1;
		while (++set->x <= side - set->lx)
			if (check_space(set, map, side, tmap))
				if (check_piece(set + 1, tmap, side))
					return (1);
	}
	return (0);
}

int		place_set(t_tet *set, uint16_t *map, int set_count)
{
	int	side;

	side = 0;
	while (side * side < set_count * 4)
		side++;
	while (side <= 16 && !(check_piece(set, map, side)))
	{
		ft_bzero(map, sizeof(uint16_t) * 16);
		side++;
	}
	return (side == 17 ? 0 : side);
}
