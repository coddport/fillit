/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcody <gcody@student.21school.ru>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 21:39:32 by gcody             #+#    #+#             */
/*   Updated: 2020/02/22 21:39:36 by gcody            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <stdint.h>
# include "libft.h"

typedef struct		s_tetris
{
	uint8_t			shape;
	unsigned char	id;
	unsigned char	lx;
	unsigned char	ly;
	unsigned char	x;
	unsigned char	y;
}					t_tet;

int					read_tetriminos(const int fd, t_tet *set);
int					place_set(t_tet *set, uint16_t *map, int block_count);

#endif
