/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcody <gcody@student.21school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 21:39:18 by gcody             #+#    #+#             */
/*   Updated: 2020/02/22 21:39:21 by gcody            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

int			verify_block(char *buf)
{
	int			joint;
	int			block;
	int			i;

	joint = 0;
	block = 4;
	i = -1;
	while (++i < 16)
	{
		if (buf[i] == '#')
		{
			block--;
			if (i + 1 < 16 && i % 4 != 3 && buf[i + 1] == '#')
				joint++;
			if (i - 1 >= 0 && i % 4 != 0 && buf[i - 1] == '#')
				joint++;
			if (i + 4 < 16 && buf[i + 4] == '#')
				joint++;
			if (i - 4 >= 0 && buf[i - 4] == '#')
				joint++;
		}
	}
	return (!block && (joint == 6 || joint == 8) ? 0 : -5);
}

int			verify_line(int l, char *line, char *buf)
{
	int			i;

	if (l % 5 > 0)
	{
		if (l % 5 == 1)
			ft_bzero(buf, sizeof(char) * 17);
		i = 0;
		while (line[i] != '\0')
			if (!(line[i] == '#' || line[i] == '.') || i++ == 4)
				return (-2);
		if (i != 4)
			return (-3);
	}
	else if (ft_strlen(line))
		return (-4);
	ft_strcat(buf, line);
	if (l % 5 == 4)
		return (verify_block(buf));
	return (0);
}

uint16_t	fill_block(char *buf, t_tet *block, int i)
{
	uint16_t	temp;

	temp = 0;
	block->lx = 4;
	block->ly = 4;
	while (i < 16)
	{
		temp = temp << 1;
		if (buf[i++] == '#')
			temp++;
	}
	i = -1;
	while (++i < 3)
	{
		if (!(temp & 61440))
			temp = temp << 4;
		if (!(temp & 34952))
			temp = temp << 1;
		if (!(temp & (4369 << i)))
			block->lx--;
		if (!(temp & (15 << (4 * i))))
			block->ly--;
	}
	return (temp);
}

t_tet		append_set(char *buf, char id)
{
	t_tet		block;
	uint16_t	temp;
	uint16_t	mask;
	int			y;

	temp = fill_block(buf, &block, 0);
	y = -1;
	mask = 0;
	block.shape = 0;
	while (++y < block.ly)
	{
		mask = (uint16_t)(temp << (y * 4));
		mask = mask >> (16 - block.lx);
		mask = mask << (8 - block.lx * (y + 1));
		block.shape |= mask;
	}
	block.id = id;
	return (block);
}

int			read_tetriminos(const int fd, t_tet *set)
{
	char		*line;
	char		buf[17];
	int			l;
	int			flag;
	int			j;

	l = 1;
	flag = 0;
	while (get_next_line(fd, &line) > 0)
	{
		flag = verify_line(l, line, buf);
		free(line);
		if (l % 5 == 4 && !flag)
		{
			j = l / 5;
			set[j] = append_set(buf, (char)(j + 65));
		}
		if (l++ > 130 || flag)
			return (flag);
	}
	close(fd);
	return (l % 5 == 1 ? flag : set[(l - 1) / 5].id - 64);
}
